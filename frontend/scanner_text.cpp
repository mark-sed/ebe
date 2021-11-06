/**
 * @file scanner_text.cpp
 * @author Marek Sedlacek
 * @date October 2021
 * @copyright Copyright 2021 Marek Sedlacek. All rights reserved.
 * 
 * @brief Syntactical analysis for text files
 * 
 * Scanner can parse text, numbers, floats (with exponent as well), symbols and delimiters.
 * All types are saved as text into IR.
 */

#include <istream>
#include <sstream>
#include "scanner_text.hpp"
#include "parser_text.hpp"
#include "scanner.hpp"
#include "ir.hpp"
#include "expression.hpp"

#include <iostream>

using namespace TextFile;

ScannerText::ScannerText() : Scanner("Text scanner"), yyFlexLexer() {
    loc = new TextFile::ParserText::location_type();
}

IR::Node *ScannerText::process(std::istream *text, const char *file_name) {
    // Set lexer to new stream
    this->switch_streams(text);

    // Create new parse node (don't delete last one)
    this->current_parse = new IR::Node();
    this->current_line = nullptr;

    auto parser = new TextFile::ParserText(this);

    if(parser->parse() != 0){
        this->error(Error::ErrorCode::SYNTACTIC, file_name, 0, 0, 
                    (std::string("Parsing failed for file ")+std::string(file_name)).c_str());
    }

    if(this->current_line != nullptr) {
        // To avoid pushing empty line created automatically lines are created by new words
        // thus current_line might be nullptr if it wasn't created
        this->current_parse->push_back(this->current_line);
    }

    // Set private variables to nullptr to make sure nothing else touches them
    this->current_line = nullptr;
    auto *parsed = this->current_parse;
    this->current_parse = nullptr;
    return parsed;
}

void ScannerText::touch_line() {
    if(current_line == nullptr){ 
        // Create new line if not created yet
        this->current_line = new std::list<IR::Word *>();
    }
}

void ScannerText::expr_start() {
    // FIXME: Check if expressions are allowed
    this->inside_expression = true;
}

void ScannerText::expr_end() {
    this->inside_expression = false;
}

bool ScannerText::is_in_expr() {
    return this->inside_expression;
}

void ScannerText::add_text(const std::string &v) {
    this->touch_line();
    current_line->push_back(new IR::Word(v, IR::Type::TEXT));
}

void ScannerText::add_number(const std::string &v) {
    this->touch_line();
    current_line->push_back(new IR::Word(v, IR::Type::NUMBER));
}

void ScannerText::add_delimiter(const std::string &v) {
    this->touch_line();
    current_line->push_back(new IR::Word(v, IR::Type::DELIMITER));
}

void ScannerText::add_symbol(const std::string &v) {
    this->touch_line();
    current_line->push_back(new IR::Word(v, IR::Type::SYMBOL));
}

void ScannerText::add_float(const std::string &v) {
    this->touch_line();
    current_line->push_back(new IR::Word(v, IR::Type::FLOAT));
}

void ScannerText::add_newline() {
    if(this->current_line == nullptr){
        // In a case that the file contains just an empty line this has to be represented with EMPTY word
        this->current_line = new std::list<IR::Word *>{new IR::Word("", IR::Type::EMPTY)};
    }
    // Push current line
    this->current_parse->push_back(this->current_line);
    // Reset current line to force creating new one on input
    this->current_line = nullptr;
}

static void expr2strs(std::stringstream &ss, const Expr::Expression *e) {
    if(e->children.size() > 0) {
        expr2strs(ss, &e->children[0]);
    }
    ss << e->value.text;
    if(e->children.size() > 1) {
        expr2strs(ss, &e->children[1]);
    }
}

void ScannerText::add_expr(Expr::Expression *e) {
    this->touch_line();
    std::stringstream ss;
    expr2strs(ss, e);
    // TODO: Most likely the expression has to be reparsed and made into Pass Expression 
    //   filled with the instructions already so that reparsing isn't done multiple times
    //   in engine. Possibly the pass could be inside Expr::Expression or replace it even.
    current_line->push_back(new IR::Word(ss.str(), IR::Type::EXPRESSION, e));
}