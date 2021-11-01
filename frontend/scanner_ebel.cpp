/**
 * @file scanner_ebel.cpp
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

#include "scanner_ebel.hpp"
#include <istream>
#include <string>
#include "parser_ebel.hpp"
#include "instruction.hpp"
#include "scanner.hpp"
#include "ir.hpp"
#include "logging.hpp"

using namespace EbelFile;

ScannerEbel::ScannerEbel() : Compiler("Ebel scanner"), yyFlexLexer() {
    this->error_code = Error::ErrorCode::NO_ERROR;
    loc = new EbelFile::ParserEbel::location_type();
}

void ScannerEbel::error_found(Error::ErrorCode code) {
    if(this->error_code == Error::ErrorCode::NO_ERROR){
        this->error_code = code;
    }
}


IR::EbelNode *ScannerEbel::process(std::istream *text, const char *file_name) {
    // Set lexer to new stream
    this->switch_streams(text);
    this->current_file_name = file_name;

    // Create new parse node (don't delete last one)
    this->current_parse = new IR::EbelNode();
    this->current_pass = nullptr;

    auto parser = new EbelFile::ParserEbel(this);

    LOGMAX("Started parser for " << file_name);
    // Start parsing
    parser->parse();

    // Check if parser or lexer found an error
    if(this->error_code != Error::ErrorCode::NO_ERROR){
        LOG1("Error while parsing, exitting");
        Error::exit(this->error_code);
    }

    if(this->current_pass != nullptr) {
        // To avoid pushing empty pass created automatically passes are created by new instruction
        // thus current_pass might be nullptr if it wasn't created
        this->current_parse->push_back(this->current_pass);
    }

    // Set private variables to nullptr to make sure nothing else touches them
    this->current_pass = nullptr;
    auto *parsed = this->current_parse;
    this->current_parse = nullptr;
    this->current_file_name = nullptr;
    return parsed;
}

void ScannerEbel::touch_pass() {
    // This should happen only for the first instruction when PASS name is missing
    // TODO: Possibly rather detect what is the first instruction and if not pass then create new pass
    if(current_pass == nullptr){ 
        // Create new line if not created yet
        this->current_pass = new IR::PassWords();
    }
}

void ScannerEbel::add_concat(int offset) {
    this->touch_pass();
    // Check if pass is lines
    if(std::string(this->current_pass->get_name()) != std::string("Lines")){
        this->error(Error::SEMANTIC, this->current_file_name, loc->begin.line, loc->begin.column, 
                    "CONCAT can be used only in PASS lines", nullptr, false);
        this->error_found(Error::SEMANTIC);
    }
    this->current_pass->push_back(new Inst::CONCAT(offset));
}

void ScannerEbel::add_del() {
    this->touch_pass();
    this->current_pass->push_back(new Inst::DEL());
}

void ScannerEbel::add_loop() {
    this->touch_pass();
    this->current_pass->push_back(new Inst::LOOP());
}

void ScannerEbel::add_nop() {
    this->touch_pass();
    this->current_pass->push_back(new Inst::NOP());
}

void ScannerEbel::add_pass_words() {
    if(this->current_pass) {
        this->current_parse->push_back(this->current_pass);
    }
    this->current_pass = new IR::PassWords();
}

void ScannerEbel::add_pass_lines() {
    if(this->current_pass) {
        this->current_parse->push_back(this->current_pass);
    }
    this->current_pass = new IR::PassLines();
}

void ScannerEbel::add_pass_documents() {
    if(this->current_pass) {
        this->current_parse->push_back(this->current_pass);
    }
    this->current_pass = new IR::PassDocuments();
}

void ScannerEbel::add_swap(int offset) {
    this->touch_pass();
    this->current_pass->push_back(new Inst::SWAP(offset));
}
