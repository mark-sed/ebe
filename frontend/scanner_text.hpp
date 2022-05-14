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
#include "expression.hpp"

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
    bool inside_expression = false;
    bool multiple_expr_types = false;
    bool inside_string = false;
    const char *current_file_name;

    IR::Node *current_parse;              ///< Holds node that is currently being parsed during process method
    std::list<IR::Word *> *current_line;  ///< Holds line currently being parsed during process method

    /** If current line is nullptr allocates a new one */
    void touch_line();

    /** 
     * Used by the lexer to denot that expression might start now
     */ 
    void expr_start();

    /**
     * Used by lexer to denote that an expression ends
     */ 
    void expr_end();

    /** 
     * Used by lexer to determine when string in expression is being parsed 
     */
    void quote_parsed();

    /**
     * Parses abstract syntax tree into an expression pass
     * @param expr Abstract syntax tree expression
     * @param type Expression input type
     * @return Passed in expression in as a pass of ebel instructions
     */
    IR::PassExpression *expr2pass(Expr::Expression *expr, IR::Type type); 

    /**
     * Walks expression creating expression pass, used by expr2pass.
     * @param expr Expression to walk
     * @param pass Output pass
     * @param var_num Destination variable
     * @param last True should be set only for the 2nd argument of root assignment expression
     * @note This method is recursive
     * @return Destination variable used
     */ 
    int walk_expr(Expr::Expression *expr, IR::PassExpression *pass, int *var_num, bool last=false);
public:
    TextFile::ParserText::location_type *loc = nullptr;
    ScannerText();
    IR::Type expr_type; ///< Deducted expression type

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
    void add_expr(Expr::Expression *e, IR::Type type);
    /** @} */

    /**
     * @brief Used by the parser to set deducted expression type
     * @param type Type found
     */
    void deducted_expr_type(IR::Type type);

    /**
     * Error handeling from parser and lexer
     * @param code Error code to report
     * @param err_message Error message
     */ 
    void sub_error(Error::ErrorCode code, const std::string &err_message);

    /**
     * Used by the lexer and parser to tell it if it is currently inside of an expression
     * @return true if currently it's inside of an expression
     */ 
    bool is_in_expr();

    /**
     * Used by the lexer and parser to tell it if it is currently inside of a string in an expression
     * @return true if currently it's inside of a string in an expression
     */ 
    bool is_in_str();

    IR::Node *process(std::istream *text, const char *file_name) override;
};

}


#endif//_SCANNER_TEXT_HPP_
