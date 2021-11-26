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
#include "logging.hpp"
#include "arg_parser.hpp"
#include "symbol_table.hpp"
#include "instruction.hpp"

#include <iostream>

using namespace TextFile;

ScannerText::ScannerText() : Scanner("Text scanner"), yyFlexLexer() {
    
}

IR::Node *ScannerText::process(std::istream *text, const char *file_name) {
    // Set lexer to new stream
    this->switch_streams(text);
    this->current_file_name = file_name;
    loc = new TextFile::ParserText::location_type();

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

void ScannerText::sub_error(Error::ErrorCode code, const std::string &err_message) {
    this->error(code, this->current_file_name, loc->begin.line, loc->begin.column, 
                    Utils::capitalize(err_message).c_str());
}

void ScannerText::touch_line() {
    if(current_line == nullptr){ 
        // Create new line if not created yet
        this->current_line = new std::list<IR::Word *>();
    }
}

void ScannerText::expr_start() {
    this->inside_expression = Args::arg_opts.expr;
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

int ScannerText::walk_expr(Expr::Expression *expr, IR::PassExpression *pass, int var_num) {
    // TODO: If more than 1 argument instructions are added for loop will be needed
    Vars::Variable *arg1 = nullptr;
    int iarg1 = -1;
    if(expr->children.size() > 0 && expr->children[0].children.empty()){
        // Leaf - Arg1
        if(expr->children[0].value.type == Expr::Type::NUMBER) {
            arg1 = new Vars::NumberVar(atoi(expr->children[0].value.text.c_str()));
        }
        else {
            this->error(Error::ErrorCode::INTERNAL, this->current_file_name, loc->begin.line, loc->begin.column, 
                    (std::string("There is no variable binding for type with id "
                    +expr->children[0].value.type)).c_str());
        }
    }
    else {
        iarg1 = walk_expr(&expr->children[0], pass, var_num+1);
    }

    Vars::Variable *arg2 = nullptr;
    int iarg2 = -1;
    if(expr->children.size() > 1 && expr->children[1].children.empty()){
        // Leaf - Arg1
        if(expr->children[1].value.type == Expr::Type::NUMBER) {
            arg1 = new Vars::NumberVar(atoi(expr->children[1].value.text.c_str()));
        }
        else {
            this->error(Error::ErrorCode::INTERNAL, this->current_file_name, loc->begin.line, loc->begin.column, 
                    (std::string("There is no variable binding for type with id "
                    +expr->children[1].value.type)).c_str());
        }
    }
    else {
        iarg1 = walk_expr(&expr->children[1], pass, var_num+1);
    }
    
    
    switch(expr->value.type) {
        case VAR:
            // Just `$` expression
            // No need to generate any code
            return 0;
        break;
        case NUMBER:
            // Just 42 expression (constant assignment)
            pass->push_back(new Inst::MOVE(0, new Vars::NumberVar(atoi(expr->value.text.c_str()))));
            return 0;
        break;
        case ADD:
            pass->push_back(new Inst::ADD(var_num, iarg1, iarg2, arg1, arg2));
        break;
        case IMUL:

        break;
        case SUB:

        break;
        case IDIV:

        break;
        case MOD:

        break;
        case POW:

        break;
        case EQ:
            walk_expr(&expr->children[0], pass, var_num);
        break;
        default:
            this->error(Error::ErrorCode::INTERNAL, this->current_file_name, loc->begin.line, loc->begin.column, 
                    (std::string("There is no instruction binding for expression type with id "
                    +expr->value.type)).c_str());
    }

    return var_num;
}

IR::PassExpression *ScannerText::expr2pass(Expr::Expression *expr, IR::Type type) {
    auto pass = new IR::PassExpression(type);
    walk_expr(expr, pass, 0);
    return pass;
}

void ScannerText::add_expr(Expr::Expression *e, IR::Type type) {
    this->touch_line();
    std::stringstream ss;
    ss << '(' << IR::get_type_name(type) << ')';
    expr2strs(ss, e);
    auto expr_pass = expr2pass(e, type);
    std::cout << *expr_pass << std::endl;
    current_line->push_back(new IR::Word(ss.str(), IR::Type::EXPRESSION, e));
    // Expression was parsed, so notify that expression is no longer being parsed
    this->expr_end();
}