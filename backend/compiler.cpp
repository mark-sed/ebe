/**
 * @file compiler.cpp
 * @author Marek Sedlacek
 * @date July 2021
 * @copyright Copyright 2021 Marek Sedlacek. All rights reserved.
 * 
 * @brief Abstract data for all processing units
 * 
 * Every input processing unit should extend processor class
 * so that all needed information and methods are present in it.
 */

#include <cstdlib>
#include <iostream>
#include "compiler.hpp"
#include "exceptions.hpp"
#include "logging.hpp"
#include "arg_parser.hpp"

namespace Error {
    namespace Colors {
        const char * NO_COLOR="\033[0m";
        const char * BLACK="\033[0;30m";
        const char * GRAY="\033[1;30m";
        const char * RED="\033[0;31m";
        const char * LIGHT_RED="\033[1;31m";
        const char * GREEN="\033[0;32m";
        const char * LIGHT_GREEN="\033[1;32m";
        const char * BROWN="\033[0;33m";
        const char * YELLOW="\033[1;33m";
        const char * BLUE="\033[0;34m";
        const char * LIGHT_BLUE="\033[1;34m";
        const char * PURPLE="\033[0;35m";
        const char * LIGHT_PURPLE="\033[1;35m";
        const char * CYAN="\033[0;36m";
        const char * LIGHT_CYAN="\033[1;36m";
        const char * LIGHT_GRAY="\033[0;37m";
        const char * WHITE="\033[1;37m";
        const char * RESET = "\033[39m";
    }
}

const char *Error::get_code_name(Error::ErrorCode code){
    const char *NAMES[] = {
        "None",
        "Unknown",
        "Internal",
        "File access",
        "Arguments",
        "Syntactic",
        "Semantic",
        "Unimplemented",
        "Runtime",
        "Version"
    };
    constexpr int names_size = sizeof(NAMES)/sizeof(char *);
    if(static_cast<int>(code) < names_size){
        return NAMES[static_cast<int>(code)];
    }
    return "Unknown";
}

void Error::error(Error::ErrorCode code, const char *msg, Exception::EbeException *exc, bool exit){
    if(!Args::arg_opts.no_error_print) {
        std::cerr << Error::Colors::colorize(Error::Colors::RED) << "ERROR" << Error::Colors::reset() 
                << " (" << Error::get_code_name(code); 
        if(exc == nullptr) {
            std::cerr << "): " << msg << "." << std::endl;
        }
        else {
            std::cerr << ", " << exc->get_type() << "): " << msg << ". " << exc->what() << "." << std::endl;
        }
    }
    if(exit){
        Error::exit(code);
    }
}

void Error::warning(const char *msg) {
    if(!Args::arg_opts.no_warn_print) {
        std::cerr << Colors::colorize(Colors::PURPLE) << "WARNING: " << Colors::reset() << msg << "." << std::endl;
    }
}


void Compiler::error(Error::ErrorCode code, const char *file, 
                                  long line, long column, const char *msg,
                                  Exception::EbeException *exc, bool exit){
    if(!Args::arg_opts.no_error_print) {
        if(file) {
            // Dont print name if it is nullptr
            std::cerr << file;
            if(line < 0) {
                std::cerr << ":";
            }
        }
        if(line >= 0){
            std::cerr << ":" << line;
            if(column >= 0) {
                std::cerr << ":" << column;
            }
            std::cerr << ":";
        }
#ifdef DEVELOPER
        std::cerr << "[" << unit_name << "]: ";
#endif
        std::cerr << Error::Colors::colorize(Error::Colors::RED) << "ERROR " 
                  << Error::Colors::reset() << "(" << Error::get_code_name(code);
        if(exc == nullptr) {
            std::cerr << "): " << msg << "." << std::endl;
        }
        else {
            std::cerr << ", " << exc->get_type() << "): " << msg << ". " << exc->what() << "." << std::endl;
        }
    }
    if(exit){
        Error::exit(code);
    }
}

[[noreturn]] void Error::exit(Error::ErrorCode code) {
    LOG1("Exiting program with code " << code);
    std::exit(code);
}

Compiler::Compiler(const char *unit_name) : unit_name{unit_name} {

}
