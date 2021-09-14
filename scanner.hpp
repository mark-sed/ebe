/**
 * @file scanner.hpp
 * @author Marek Sedlacek
 * @date July 2021
 * @copyright Copyright 2021 Marek Sedlacek. All rights reserved.
 * 
 * @brief Syntactical analysis
 * 
 * Handles scanning of input example files and ebel code as well
 * Each file type can have its own scanner which extends base Scanner class
 */

#ifndef _SCANNER_HPP_
#define _SCANNER_HPP_

#include <vector>
#include <string>
#include <set>
#include <cstddef>
#include "ir.hpp"
#include "compiler.hpp"

class Scanner : public Compiler {
public:
    /** Constructor */
    Scanner(const char *scanner_name);
    virtual ~Scanner() {}

    /**
     * Does syntactical parsing of passed in text
     * @param text Example file's text parsed into vector of lines by preprocessor
     * @param file_name Example file's name for error information
     * @return Text parsed into IR node
     */
    virtual IR::Node *process(std::vector<std::string> *text, const char *file_name) = 0;
};

/**
 * Lexical analysis for example files
 */
class TextScanner : public Scanner {
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
public:
    /** Constructor */
    TextScanner();
    ~TextScanner();

    IR::Node *process(std::vector<std::string> *text, const char *file_name) override;

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

    /** @return True if the character is a whitespace character */
    bool is_whitespace(char c);

    /** @return True if the character is a start of an instruction */
    bool is_inst_start(char c);

    /** @return True if the character is eol character */
    bool is_eol(char c);

    /** @return True if the character is comment start character */
    bool is_comment(char c);
public:
    /** Constructor */
    EbelScanner();

    /**
     * Does syntactical parsing of passed in ebel code
     * @param text Ebel code text parsed into vector of lines by preprocessor
     * @param file_name Ebel file's name for error information
     * @return Code parsed into IR ebel node
     */
    IR::EbelNode *process(std::vector<std::string> *text, const char *file_name);
};

class ConstraintChecker : public Compiler {
private:
    std::vector<std::string> * const args;
    std::string * const inst_name;
    unsigned long line_number;
    unsigned long column;
    const char * const file_name;

    [[noreturn]] void fail(std::string msg); 
public:
    /**
     * Constructor
     * @param args Arguments
     * @param inst_name Instruction name
     * @param line_number Current line number in code
     * @param column Current column in code
     * @param file_name Name of parsed file
     */
    ConstraintChecker(std::vector<std::string> * const args, 
                      std::string * const inst_name, 
                      unsigned long line_number,
                      unsigned long column,
                      const char * const file_name);
    
    /**
     * Checks amount of arguments
     * @param expected Expected amount
     */
    void arg_size(size_t expected);

    /**
     * Checks argument value
     * @param expected Set of allowed values
     * @param case_sensitive If the letter case is important (false by default)
     */
    void arg_value(size_t index, std::vector<std::string> expected, bool case_sensitive=false);
};

#endif//_SCANNER_HPP_