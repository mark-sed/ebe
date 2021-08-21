/**
 * @file scanner.cpp
 * @author Marek Sedlacek
 * @date July 2021
 * @copyright Copyright 2021 Marek Sedlacek. All rights reserved.
 * 
 * @brief Syntactical analysis
 * 
 * Scanner can parse text, numbers, floats (with exponent as well), symbols and delimiters.
 * All types are saved as text anyway into IR.
 */

#include <vector>
#include <algorithm>
#include <list>
#include <string>
#include <cstddef>
#include "scanner.hpp"
#include "ir.hpp"
#include "arg_parser.hpp"
#include "instruction.hpp"
#include "utils.hpp"

#include <iostream>

Scanner::Scanner() : Compiler("Example scanner") {
    this->delimiters = std::set<char>{
        ' ', '\f', '\r', '\t', '\v', '\n', // whitespace chars (new line is added for when line_delim is different)
        ',', '.', ':', ';'                 // other characters that are usualy delimiters
    };
}

inline bool Scanner::is_alpha(char c){
    return std::isalpha(c) || 
           (Args::arg_opts.alpha_num && is_number(c)) ||
           (Args::arg_opts.alpha_sym && is_symbol(c));
}

inline bool Scanner::is_delimiter(char c){
    return this->delimiters.find(c) != this->delimiters.end();
}

inline bool Scanner::is_symbol(char c){
    return std::ispunct(c) && !is_delimiter(c);
}

inline bool Scanner::is_number(char c){
    return std::isdigit(c);
}

inline bool Scanner::is_float_delim(char c){
    return c == Args::arg_opts.float_delim;
}

inline bool Scanner::is_float_exp(char c){
    return c == 'e' || c == 'E';
}

IR::Node *Scanner::process(std::vector<std::string> *text, const char *file_name) {
    auto ir = new IR::Node();

    long line_number = 1;
    State state = State::START;
    for(auto line_text: *text){
        auto line = new std::list<IR::Word *>();
        // Parse words and delimiters
        state = State::START; // Reset FSM
        size_t start_i = 0;
        bool end_state = false;
        IR::Type type = IR::Type::TEXT;
        for(size_t i = 0; i < line_text.length(); i++){
            char c = line_text[i];
            switch(state){
                case State::START:
                    start_i = i; // Reset word start index
                    if(is_alpha(c)){
                        state = State::ALPHA;
                        break;
                    }
                    if(is_delimiter(c)){
                        state = State::DELIMITER;
                        break;
                    }
                    // Has to be after delimiter
                    if(c == '+' || c == '-'){
                        state = State::POS_NUM;
                        break;
                    }
                    if(is_symbol(c)){
                        state = State::SYMBOL;
                        break;
                    }
                    if(is_number(c)){
                        state = State::NUM;
                        break;
                    }
                    // Make sure to break after state change
                    // This should not be executed
                    state = State::UNKNOWN;
                break;
                case State::ALPHA:
                    if(is_alpha(c)){
                        break;
                    }
                    type = IR::Type::TEXT;
                    end_state = true;
                break;
                case State::DELIMITER:
                    if(Args::arg_opts.group_delim && is_delimiter(c)){
                        break;
                    }
                    type = IR::Type::DELIMITER;
                    end_state = true;
                break;
                case State::SYMBOL:
                    if(Args::arg_opts.group_sym && is_symbol(c)){
                        break;
                    }
                    type = IR::Type::SYMBOL;
                    end_state = true;
                break;
                case State::NUM:
                    if(is_number(c)){
                        break;
                    }
                    // Possible float
                    if(is_float_delim(c)){
                        state = State::POS_FLOAT;
                        break;
                    }
                    type = IR::Type::NUMBER;
                    end_state = true;
                break;
                case State::POS_NUM:
                    if(is_number(c)){
                        state = State::NUM;
                        break;
                    }
                    i--;
                    // No need to check is +/- are delimiters because if they were this stat would not execute
                    state = State::SYMBOL;
                break;
                case State::POS_FLOAT:
                    if(is_number(c)){
                        state = State::FLOAT;
                        break;
                    }
                    // Not a float, so return number and put back delimiter
                    i--;
                    type = IR::Type::NUMBER;
                    end_state = true;
                break;
                case State::FLOAT:
                    if(is_number(c)){
                        break;
                    }
                    if(is_float_exp(c)){
                        // Float defined with exponent
                        state = State::EXP;
                        break;
                    }
                    type = IR::Type::FLOAT;
                    end_state = true;
                break;
                case State::EXP:
                    if(c == '+' || c == '-'){
                        // Signed exponent
                        state = State::EXP_SIGN;
                        break;
                    }
                    if(is_number(c)){
                        state = State::EXP_VAL;
                        break;
                    }
                    // Incorrect format put back char and return float without exponent
                    // TODO: Should be a warning printed?
                    i--;
                    type = IR::Type::FLOAT;
                    end_state = true;
                break;
                case State::EXP_SIGN:
                    if(is_number(c)){
                        state = State::EXP_VAL;
                        break;
                    }
                    // Incorrect format put back char and return float without exponent
                    // TODO: Should be a warning printed?
                    i -= 2;
                    type = IR::Type::FLOAT;
                    end_state = true;
                break;
                case State::EXP_VAL:
                    if(is_number(c)){
                        break;
                    }
                    type = IR::Type::FLOAT;
                    end_state = true;
                break;
                default:
                    // UNKNOWN fsm state, this will never happen
                    error(Error::ErrorCode::INTERNAL, file_name, line_number, static_cast<unsigned long>(i+1), "Unknown state");
            }
            // Add word to IR
            if(end_state){
                line->push_back(new IR::Word(line_text.substr(start_i, i-start_i), type));
                end_state = false;
                i--; // Character was read to determine change of state so load it back
                state = State::START;
            }
        }
        // Parse empty line as EMPTY type
        if(line->empty()){
            line->push_back(new IR::Word("", IR::Type::EMPTY));
        }
        line_number++;
        ir->push_back(line);
    }
    return ir;
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
                    unsigned int arg1 = Cast::to<unsigned int>(args[0]);
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
                    unsigned int arg1 = Cast::to<unsigned int>(args[0]);
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

        