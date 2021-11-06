/**
 * @file scanner_text.hpp
 * @author Marek Sedlacek
 * @date October 2021
 * @copyright Copyright 2021 Marek Sedlacek. All rights reserved.
 * 
 * @brief Syntactical analysis for text files
 * 
 * Scanner can parse text, numbers, floats (with exponent as well), symbols and delimiters.
 * All types are saved as text into IR.
 */

#ifndef _SCANNER_TEXT_HPP_
#define _SCANNER_TEXT_HPP_

// Flex include has to be guarded
#if ! defined(yyFlexLexerOnce)
#include "FlexLexer.h"
#endif
#include <istream>
#include <list>
#include "ir.hpp"
#include "scanner.hpp"
#include "parser_text.hpp"

/**
 * Namespace for lexers and parsers used by flex and bison/yacc.
 */ 
namespace TextFile {

/**
 * Scanner for text files 
 */ 
class ScannerText : public Scanner, public yyFlexLexer {
private:
    TextFile::ParserText::semantic_type *yylval = nullptr;
    TextFile::ParserText::location_type *loc = nullptr;

    IR::Node *current_parse;              ///< Holds node that is currently being parsed during process method
    std::list<IR::Word *> *current_line;  ///< Holds line currently being parsed during process method

    /** If current line is nullptr allocates a new one */
    void touch_line();
public:
    ScannerText();

    virtual int yylex(TextFile::ParserText::semantic_type *const lval,
                      TextFile::ParserText::location_type *location);

    /**
     * @defgroup wordparse Word parsers
     * Receive Word of certain type and add it to the current_parse.
     * @param v Text of the word
     * @{
     */  
    void add_text(const std::string &v);
    void add_number(const std::string &v);
    void add_delimiter(const std::string &v);
    void add_symbol(const std::string &v);
    void add_float(const std::string &v);
    void add_newline();
    /** @} */

    IR::Node *process(std::istream *text, const char *file_name) override;
};

}


#endif//_SCANNER_TEXT_HPP_
