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
#include <FlexLexer.h>
#endif

#include "scanner.hpp"
#include "parser_text.hpp"
#include "location.hh"

/**
 * Namespace for lexers and parsers used by flex and bison/yacc.
 */ 
namespace Parsing {

/**
 * Scanner for text files
 */ 
class ScannerText : public Scanner, public yyFlexLexer {
public:
    ScannerText(std::istream *input);

    // Using has to be here to avoid compiler warnings
    using FlexLexer::yylex
    
    virtual int yylex(EE::TextParser::semantic_type *const lval,
                      EE::TextParser::location_type *location);

    void add_text(const std::string &v);
    void add_number(const std::string &v);
    void add_delimiter(const std::string &v);
    void add_symbol(const std::string &v);
    void add_float(const std::string &v);
    void add_newline();
private:
    Parsing::TextParser::semantic_type *yylval = nullptr;
    Parsing::TextParser::location_type *loc = nullptr;
};

}


#endif//_SCANNER_TEXT_HPP_
