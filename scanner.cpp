/**
 * @file scanner.cpp
 * @author Marek Sedlacek
 * @date July 2021
 * @copyright Copyright 2021 Marek Sedlacek. All rights reserved.
 * 
 * @brief Syntactical analysis
 * 
 */

#include <vector>
#include <list>
#include <string>
#include <cstddef>
#include "scanner.hpp"
#include "ir.hpp"
#include "arg_parser.hpp"

#include <iostream>

Scanner::Scanner(std::vector<std::string> *in_text, std::vector<std::string> *out_text) : 
                 Compiler("Scanner"), in_text{in_text}, out_text{out_text} {
    this->delimiters = std::set<char>{
        ' ', '\f', '\r', '\t', '\v', // whitespace chars 
        ',', '.', ':', ';'           // other characters that are usualy delimiters
    };
}

inline bool Scanner::is_alpha(char c){
    return std::isalpha(c) || 
           (arg_opts.alpha_num && is_number(c)) ||
           (arg_opts.alpha_sym && is_symbol(c));
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
    return c == arg_opts.float_delim;
}

inline bool Scanner::is_float_exp(char c){
    return c == 'e' || c == 'E';
}

IR::Node *Scanner::process(std::vector<std::string> *text, const char *file_name) {
    auto ir = new IR::Node();

    long line_number = 1;
    for(auto line_text: *text){
        auto line = new std::list<IR::Word>();
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
                    if(arg_opts.group_delim && is_delimiter(c)){
                        break;
                    }
                    type = IR::Type::DELIMITER;
                    end_state = true;
                break;
                case State::SYMBOL:
                    if(arg_opts.group_symbol && is_symbol(c)){
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
                line->push_back(IR::Word(line_text.substr(start_i, i-start_i), type));
                end_state = false;
                i--; // Character was read to determine change of state so load it back
                state = State::START;
            }
        }
        line_number++;
        ir->push_back(line);
    }
    return ir;
}