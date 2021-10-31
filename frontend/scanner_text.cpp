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
#include "scanner_text.hpp"
#include "parser_text.hpp"
#include "scanner.hpp"
#include "ir.hpp"

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