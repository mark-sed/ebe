/**
 * @file scanner.cpp
 * @author Marek Sedlacek
 * @date July 2021
 * @copyright Copyright 2021 Marek Sedlacek. All rights reserved.
 * 
 * @brief Syntactical analysis base class
 * 
 * Base scanner class
 */

#include <vector>
#include <algorithm>
#include <list>
#include <string>
#include <cstddef>
#include "scanner.hpp"
#include "ir.hpp"
#include "instruction.hpp"
#include "arg_parser.hpp"
#include "utils.hpp"
#include "exceptions.hpp"

#include <iostream>

Scanner::Scanner(const char *scanner_name) : Compiler(scanner_name) {

}

EbelScanner::EbelScanner() : Compiler("Ebel scanner") {

}

inline bool EbelScanner::is_whitespace(char c){
    return std::isspace(c) && c != '\n';
}

inline bool EbelScanner::is_inst_start(char c){
    return std::isalnum(c);
}

inline bool EbelScanner::is_eol(char c){
    return c == '\n';
}

inline bool EbelScanner::is_comment(char c){
    return c == '#';
}

IR::EbelNode *EbelScanner::process(std::vector<std::string> *text, const char *file_name){
    auto ir = new IR::EbelNode();

    long line_number = 1;
    State state = State::START;
    
    IR::Pass *curr_pass = nullptr; // Implicit pass is created when pushed, to avoid allocation when not used
    for(auto line_text: *text){
        state = State::START; // Reset FSM
        size_t start_i = 0;
        std::string inst_name = "";
        std::vector<std::string> args;
        for(size_t i = 0; i < line_text.length(); i++){
            char c = line_text[i];
            switch(state){
                case State::START:
                    start_i = i; // Reset word start index
                    if(this->is_whitespace(c) || this->is_eol(c)){
                        break;
                    }
                    if(this->is_comment(c)){
                        state = State::COMMENT;
                        break;
                    }
                    if(this->is_inst_start(c)){
                        state = State::INST;
                        break;
                    }
                    // Not a letter
                    error(Error::ErrorCode::SYNTACTIC, file_name, line_number, static_cast<unsigned long>(i+1), 
                        "Incorrect symbol");
                break;
                case State::COMMENT:
                    // Cycle till the eol (checked at the end)
                break;
                case State::INST:
                    if(this->is_comment(c)){
                        state = State::COMMENT;
                    }
                    else if(this->is_whitespace(c)){
                        state = State::SPACE;
                    }
                    else if(!this->is_eol(c)){
                        // Cycle letters and symbols and numbers
                        break;
                    }
                    // Was not break, so this state ends, save it as an instruction
                    // Check if instruction was not yet set
                    if(!inst_name.empty()){
                        error(Error::ErrorCode::SYNTACTIC, file_name, line_number, static_cast<unsigned long>(i+1), 
                                "Multiple instructions on one line");
                    }
                    inst_name = line_text.substr(start_i, i-start_i);
                break;
                case State::SPACE:
                    if(this->is_comment(c)){
                        state = State::COMMENT;
                        break;
                    }
                    if(this->is_whitespace(c) || this->is_eol(c)){
                        break;
                    }
                    // Something else than spaces/comment was found, it might be an argument
                    start_i = i; // Reset start index to remove whitespace
                    state = State::ARG;
                break;
                case State::ARG:
                    if(this->is_comment(c)){
                        state = State::COMMENT;
                    }
                    else if(this->is_whitespace(c)){
                        state = State::SPACE;
                    }
                    else if(!this->is_eol(c)){
                        break;
                    }
                    // No break, so end of argument was reached
                    args.push_back(line_text.substr(start_i, i-start_i));
                break;
                default:
                    // UNKNOWN fsm state, this will never happen
                    error(Error::ErrorCode::INTERNAL, file_name, line_number, static_cast<unsigned long>(i+1), 
                            "Unknown state");
            }
            if(this->is_eol(c) && !inst_name.empty()){
                // End of line reached analyse content
                // Init constraint checker
                ConstraintChecker checker(&args, &inst_name, line_number, static_cast<unsigned long>(i+1), file_name); 

                std::string parsed_inst = Utils::to_upper(inst_name);

                // Checking if the first instruction is for setting the mode (otherwise initialize it to default)
                if(!curr_pass && parsed_inst != Inst::PASS::NAME){
                    curr_pass = new IR::PassWords();
                }

                /*
                 * Instruction parsing
                 */
                size_t cc_args_size = 0;
                // CONCAT
                if(parsed_inst == Inst::CONCAT::NAME){
                    cc_args_size = 1;
                    unsigned int arg1;
                    try {
                        arg1 = Cast::to<unsigned int>(args[0]);
                    } catch (Exception::EbeException e) {
                        error(Error::ErrorCode::INTERNAL, file_name, line_number, static_cast<unsigned long>(i+1), 
                              "Incorrect argument type", &e);
                    }
                    curr_pass->push_back(new Inst::CONCAT(arg1));
                }
                // DEL
                else if(parsed_inst == Inst::DEL::NAME){
                    curr_pass->push_back(new Inst::DEL());
                }
                // LOOP
                else if(parsed_inst == Inst::LOOP::NAME){
                    // FIXME: Check that LOOP is in correct place
                    // Check if there are instructions to loop, otherwise skip loop
                    if(!curr_pass->empty()){
                        curr_pass->push_back(new Inst::LOOP());
                    }
                }
                // NOP
                else if(parsed_inst == Inst::NOP::NAME){
                    curr_pass->push_back(new Inst::NOP());
                }
                // PASS
                else if(parsed_inst == Inst::PASS::NAME){
                    cc_args_size = 1;
                    std::vector<std::string> allowed_vals{"words", "lines", "documents"};
                    checker.arg_value(0, allowed_vals);
                    // Exec
                    if(curr_pass){
                        // Push previous pass
                        ir->push_back(curr_pass);
                    }
                    auto arg1_up = Utils::to_upper(args[0]);
                    if(arg1_up == "WORDS"){
                        curr_pass = new IR::PassWords();
                    }else if(arg1_up == "LINES"){
                        curr_pass = new IR::PassLines();
                    }else if(arg1_up == "DOCUMENTS"){
                        curr_pass = new IR::PassDocuments();
                    }else{
                        error(Error::ErrorCode::INTERNAL, file_name, line_number, static_cast<unsigned long>(i+1), 
                              "Incorrect pass name conversion");
                    }
                }
                // SWAP
                else if(parsed_inst == Inst::SWAP::NAME){
                    cc_args_size = 1;
                    // FIXME: Check if argument is >0
                    unsigned int arg1;
                    try {
                        arg1 = Cast::to<unsigned int>(args[0]);
                    } catch (Exception::EbeException e){
                        error(Error::ErrorCode::INTERNAL, file_name, line_number, static_cast<unsigned long>(i+1), 
                              "Incorrect argument type", &e);
                    }
                    curr_pass->push_back(new Inst::SWAP(arg1));
                }
                // Constraint check for all instructions
                checker.arg_size(cc_args_size);
            }
        }
        line_number++;
    }
    if(curr_pass){
        // Pass might be nullptr in case of empty file
        ir->push_back(curr_pass);
    }
    return ir;
}   

ConstraintChecker::ConstraintChecker(std::vector<std::string> * const args, 
                                     std::string * const inst_name, 
                                     unsigned long line_number,
                                     unsigned long column,
                                     const char * const file_name) 
    : Compiler("Ebel scanner checker"), 
      args{args}, inst_name{inst_name}, line_number{line_number}, column{column}, file_name{file_name}{

}

[[noreturn]] void ConstraintChecker::fail(std::string msg){
    error(Error::ErrorCode::SYNTACTIC, this->file_name, this->line_number, this->column, msg.c_str());
}

void ConstraintChecker::arg_size(size_t expected){
    if(this->args->size() != expected){
        fail("Incorrect amount of arguments");
    }
}

void ConstraintChecker::arg_value(size_t index, std::vector<std::string> expected, bool case_sensitive){
    std::string arg_copy = (*args)[index];
    std::vector<std::string> exp_copy(expected);
    if(!case_sensitive){
        arg_copy = Utils::to_upper((*args)[index]);
        Utils::to_upper(&exp_copy);
    }
    if(std::find(exp_copy.begin(), exp_copy.end(), arg_copy) == exp_copy.end()){
        fail("Incorrect argument value");
    }
}

        