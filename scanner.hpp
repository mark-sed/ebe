/**
 * @file scanner.hpp
 * @author Marek Sedlacek
 * @date July 2021
 * @copyright Copyright 2021 Marek Sedlacek. All rights reserved.
 * 
 * @brief Syntactical analysis
 * 
 */

#ifndef _SCANNER_HPP_
#define _SCANNER_HPP_

#include <vector>
#include <string>
#include <set>
#include "ir.hpp"
#include "compiler.hpp"

class Scanner : public Compiler {
private:
    std::vector<std::string> *in_text;
    std::vector<std::string> *out_text;
    std::set<char> delimiters;

    enum class State {
        START,
        ALPHA,
        DELIMITER,
        SYMBOL,
        NUM,
        POS_NUM,
        POS_FLOAT,
        FLOAT,
        EXP,
        EXP_SIGN,
        EXP_VAL,
        UNKNOWN,
    } state = State::START;

    bool is_alpha(char c);
    bool is_delimiter(char c);
    bool is_symbol(char c);
    bool is_number(char c);
    bool is_float_delim(char c);
    bool is_float_exp(char c);
public:
    Scanner(std::vector<std::string> *in_text, std::vector<std::string> *out_text);
    IR::Node *process(std::vector<std::string> *text, const char *file_name);
};

#endif//_SCANNER_HPP_