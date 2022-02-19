/**
 * @file pragmas.cpp
 * @author Marek Sedlacek
 * @date February 2021
 * @copyright Copyright 2022 Marek Sedlacek. All rights reserved.
 * 
 * @brief Ebel pragmas handeling and parsing
 * 
 * Parses and sets ebel pragmas
 */

#include <vector>
#include <string>
#include "pragmas.hpp"
#include "ir.hpp"
#include "symbol_table.hpp"
#include "arg_parser.hpp"
#include "compiler.hpp"
#include "utils.hpp"
#include "exceptions.hpp"
#include "ebe.hpp"
#include "logging.hpp"

using namespace Pragma;

Pragmas::Pragmas(IR::EbelNode *ebel) : ebel{ebel},
                                       sym_table_size{0} {
}

Pragmas::Pragmas(const Pragmas &other, IR::EbelNode *ebel) {
    this->ebel = ebel;
    this->sym_table_size = other.sym_table_size;
}

std::vector<std::string> Pragmas::split_pragma(std::string value) {
    std::vector<std::string> values;
    int start = -1;
    /** Enum for split_pragma scanner */
    enum class SPLIT_FSM {
        START,
        STRING,
        VALUE,
        COMMENT
    } state{SPLIT_FSM::START};
    for(int i = 0; i < value.size(); ++i) {
        char c = value[i];
        switch(state) {
            case SPLIT_FSM::START:
                if(c == '"') {
                    state = SPLIT_FSM::STRING;
                }
                else if(c == '#') {
                    state = SPLIT_FSM::COMMENT;
                }
                else if(!std::isspace(c)) {
                    --i;
                    state = SPLIT_FSM::VALUE;
                }
                start = i+1;
            break;
            case SPLIT_FSM::VALUE:
                if(std::isspace(c)) {
                    values.push_back(value.substr(start, i-start));
                    state = SPLIT_FSM::START;
                }
                else if(c == '#') {
                    values.push_back(value.substr(start, i-start));
                    state = SPLIT_FSM::START;
                }
            break;
            case SPLIT_FSM::STRING:
                if(c == '"') {
                    values.push_back(value.substr(start, i-start));
                    state = SPLIT_FSM::START;
                }
            break;
            case SPLIT_FSM::COMMENT:
                // Just let all letters load
            break;
            default:
                Error::error(Error::ErrorCode::INTERNAL, "Somwhow pragma parsing got unexpected state");
            break;
        }
        if(i == value.size()-1) {
            // Last iteration, save value or error on string
            if(state == SPLIT_FSM::STRING) {
                Error::error(Error::ErrorCode::SYNTACTIC, "Missing closing quote in pragma value");
            }
            else if(state == SPLIT_FSM::VALUE) {
                values.push_back(value.substr(start, i));
            }
        }
    }
    
    return values;
}

void Pragmas::parse(std::string value) {
    auto vs = this->split_pragma(value);
    if(vs.empty()) {
        Error::error(Error::ErrorCode::SYNTACTIC, "Missing pragma value/s");
    }

    if(vs[0] == "sym_table_size") {
        if(vs.size() != 2) {
            Error::error(Error::ErrorCode::SYNTACTIC, "Incorrect amount of argument for sym_table_size pragma");
        }
        unsigned int arg1;
        try{
            arg1 = Cast::to<unsigned int>(vs[1]);
        } catch (Exception::EbeException e) {
            Error::error(Error::ErrorCode::SEMANTIC, 
                         "Incorrect sym_table_size argument value",
                         &e);
        }
        if(arg1 < 1) {
            Error::error(Error::ErrorCode::SEMANTIC, "Symbol table size has to be bigger than 0");
        }
        this->sym_table_size = arg1;
    }
    else if(vs[0] == "requires") {
        if(vs.size() != 2) {
            Error::error(Error::ErrorCode::SYNTACTIC, "Incorrect amount of argument for requires pragma");
        }
        // Version can be handeled as a csv that uses .
        auto versions = Utils::split_csv(vs[1], '.');
        if(versions.empty()) {
            Error::error(Error::ErrorCode::SYNTACTIC, "Incorrect version number in requires pragma");
        }
        // Input can leave out 0s
        int major = 0;
        int minor = 0;
        int patch = 0;
        try{
            major = Cast::to<unsigned int>(versions[0]);
            if(versions.size() > 1) {
                minor = Cast::to<unsigned int>(versions[1]);
                if(versions.size() > 2) {
                    patch = Cast::to<unsigned int>(versions[2]);
                }
            }
        } catch(Exception::EbeException e) {
            Error::error(Error::ErrorCode::SEMANTIC, 
                         "Incorrect version number in requires pragma",
                         &e);
        }
        bool version_ok = true;
        if(major > EBE_VERSION_MAJOR) {
            version_ok = false;
        }
        else if(major == EBE_VERSION_MAJOR) {
            if(minor > EBE_VERSION_MINOR) {
                version_ok = false;
            }
            else if(minor == EBE_VERSION_MINOR) {
                if(patch > EBE_VERSION_PATCH) {
                    version_ok = false;
                }
            }
        }
        if(!version_ok) {
            Error::error(Error::ErrorCode::VERSION, 
                         (
                            std::string("Current Ebe version ")
                            +std::to_string(EBE_VERSION_MAJOR)+"." 
                            +std::to_string(EBE_VERSION_MINOR)+"."
                            +std::to_string(EBE_VERSION_PATCH)
                            +std::string(" does not fulfill requires pragma for version ")
                            +vs[1]
                         ).c_str());
        }
    }
    else {
        Error::error(Error::ErrorCode::SYNTACTIC, 
                     (std::string("Unknown pragma name \"")+vs[0]+"\"").c_str());
    }
}

void Pragmas::apply() {
    if(this->sym_table_size > 0) {
        Args::arg_opts.sym_table_size = this->sym_table_size;
        LOG1("Applied pragma: sym_table_size = " << this->sym_table_size);
    }
}
