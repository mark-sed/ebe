/**
 * @file scanner.hpp
 * @author Marek Sedlacek
 * @date July 2021
 * @copyright Copyright 2021 Marek Sedlacek. All rights reserved.
 * 
 * @brief Syntactical analysis
 * 
 * Handles scanning of input example files and ebel code as well
 */

#ifndef _SCANNER_HPP_
#define _SCANNER_HPP_

#include <vector>
#include <string>
#include <set>
#include "ir.hpp"
#include "compiler.hpp"

/**
 * Lexical analysis for example files
 */
class Scanner : public Compiler {
private:
    std::set<char> delimiters;  ///< Set of characters considered word delimiters

    /**
     * FSM states of the scanner
     */
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
    };

    /** @return True if character is alphabetical */
    bool is_alpha(char c);

    /** @return True if character is a delimiter */
    bool is_delimiter(char c);

    /** @return True if character is a symbol */
    bool is_symbol(char c);

    /** @return True if character is a number */
    bool is_number(char c);

    /** @return True if character is floating point delimiter */
    bool is_float_delim(char c);

    /** @return True if character is floating point exponent (e/E) */
    bool is_float_exp(char c);
public:
    /** Constructor */
    Scanner();

    /**
     * Does syntactical parsing of passed in text
     * @param in_text Example file's text parsed into vector of lines by preprocessor
     * @param file_name Example file's name for error information
     * @return Text parsed into IR node
     */
    IR::Node *process(std::vector<std::string> *text, const char *file_name);
};

/**
 * Scanner for ebel code
 */
class EbelScanner : public Compiler {
private:
    /** FSM states of the scanner */
    enum class State {
        START,
        COMMENT,
        INST,
        SPACE,
        ARG
    };

    
};

#endif//_SCANNER_HPP_