/**
 * @file scanner_ebel.hpp
 * @author Marek Sedlacek
 * @date October 2021
 * @copyright Copyright 2021 Marek Sedlacek. All rights reserved.
 * 
 * @brief Syntactical analysis for ebel source code files
 * 
 * Scanner can parse ebel source code ignoring case, whitespace
 * and allows for line comments (# denoted).
 * Comments are not saved.
 */

#ifndef _SCANNER_EBEL_HPP_
#define _SCANNER_EBEL_HPP_

// Flex include has to be guarded
#if ! defined(yyFlexLexerOnce)
#include "FlexLexer.h"
#endif
#include <istream>
#include <list>
#include "ir.hpp"
#include "scanner.hpp"
#include "parser_ebel.hpp"

namespace EbelFile {

/**
 * Scanner for ebel source code files 
 */ 
class ScannerEbel : public Compiler, public yyFlexLexer {
private:
    EbelFile::ParserEbel::semantic_type *yylval = nullptr;

    IR::EbelNode *current_parse;          ///< Holds program that is currently being parsed during process method
    IR::Pass *current_pass;               ///< Holds line currently being parsed during process method
    const char *current_file_name;        ///< File currently being parsed
    /**
     * Indicates that an error was found by lexer or parser.
     * This is done this way to let all errors be discovered in one parse.
     * @note This variable is set to true by error method
     */ 
    Error::ErrorCode error_code;

    /** If current pass is nullptr allocates a new one */
    void touch_pass();
public:
    EbelFile::ParserEbel::location_type *loc = nullptr;     ///< Current parsing location

    ScannerEbel();

    virtual int eelex(EbelFile::ParserEbel::semantic_type *const lval,
                      EbelFile::ParserEbel::location_type *location);

    /**
     * @defgroup instparse Instruction parsers
     * Receive instruction and add it to the current_parse.
     * @param v Text of the word
     * @{
     */  
    void add_concat(int offset);
    void add_del();
    void add_loop();
    void add_nop();
    void add_pass_expression();
    void add_pass_words();
    void add_pass_lines();
    void add_pass_documents();
    void add_swap(int offset);
    /** @} */

    /**
     * Should be called only by parser and lexer whan an error is found.
     * If this method was called already with non zero code than the code won't be changed,
     * meaning the code saves only the first non zero error code.
     * @param code Error type that was found and printed
     * @note Passing in NO_ERROR won't change the error to NO_ERROR
     */ 
    void error_found(Error::ErrorCode code);

    IR::EbelNode *process(std::istream *text, const char *file_name);
};

}

#endif//_SCANNER_EBEL_HPP_
