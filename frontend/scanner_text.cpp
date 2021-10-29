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

#include "scanner_text.hpp"
#include "scanner.hpp"

using namespace Parsing;

ScannerText::ScannerText(std::istream *input) : Scanner("Text scanner"), yyFlexLexer(input) {
    loc = new Parsing::ParserText::location_type();
}

void ScannerText::add_text(const std::string &v) {

}

void ScannerText::add_number(const std::string &v) {

}

void ScannerText::add_delimiter(const std::string &v) {

}

void ScannerText::add_symbol(const std::string &v) {

}

void ScannerText::add_float(const std::string &v) {

}

void ScannerText::add_newline() {
    
}