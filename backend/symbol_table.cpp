/**
 * @file symbol_table.cpp
 * @author Marek Sedlacek
 * @date November 2021
 * @copyright Copyright 2021 Marek Sedlacek. All rights reserved.
 * 
 * @brief Symbol table for expression passes
 * 
 * Symbol table holds variables used in pass expressions
 */

#include "symbol_table.hpp"
#include "exceptions.hpp"
#include "ir.hpp"
#include "arg_parser.hpp"

using namespace Vars;

int Variable::get_number() {
    throw Exception::EbeSymTableTypeException("Attempt to extract NUMBER from variable of different type");
    return 0;
}

float Variable::get_float() {
    throw Exception::EbeSymTableTypeException("Attempt to extract FLOAT from variable of different type");   
    return 0.0;
}

std::string Variable::get_text() {
    throw Exception::EbeSymTableTypeException("Attempt to extract TEXT from variable of different type");
    return std::string("");
}


SymbolTable::SymbolTable() : Compiler("Symbol table"), size{Args::arg_opts.sym_table_size} {
    this->table = new Variable *[size]();
}

SymbolTable::SymbolTable(IR::Word *var0) : Compiler("Symbol table"), size{Args::arg_opts.sym_table_size} {
    this->table = new Variable *[size]();
    if(var0->type == IR::Type::NUMBER) {
        table[0] = new NumberVar(var0->to_int<IR::Type::NUMBER>());
    }
    else if(var0->type == IR::Type::FLOAT) {
        table[0] = new FloatVar(var0->to_float<IR::Type::FLOAT>());
    }
    else if(var0->type == IR::Type::TEXT || var0->type == IR::Type::SYMBOL || var0->type == IR::Type::DELIMITER) {
        table[0] = new TextVar(var0->to_string<IR::Type::TEXT>());
    }

}

SymbolTable::~SymbolTable() { 
    delete[] table;
}

bool SymbolTable::assert_set(int index){
    if(index >= size){
        throw Exception::EbeSymTableOutOfRangeException("Variable $"+std::to_string(index)
                +"is out of range. Maximum allowed variable is $"+std::to_string(size));
        return false;
    }
    // Remove previous possible value
    if(table[index] != nullptr){
        delete table[index];
    }
    return true;
}

bool SymbolTable::assert_get(int index){
    if(index >= size){
        throw Exception::EbeSymTableOutOfRangeException("Variable $"+std::to_string(index)
                +"is out of range. Maximum allowed variable is $"+std::to_string(size));
        return false;
    }
    if(table[index] == nullptr){
        throw Exception::EbeSymTableUndefinedVarException("Attempt to access undefined variable $"+std::to_string(index));
        return false;
    }
    return true;
}

IR::Type SymbolTable::type_at(int index) {
    if(this->assert_get(index)){
        return table[index]->type;
    }
    return IR::Type::DERIVED;
}

template<typename T>
void SymbolTable::set(int index, T value) {
    throw Exception::EbeSymTableUnknwonTypeException("Attempt to set variable to not supported type");
}

template<>
void SymbolTable::set(int index, int value) {
    if(this->assert_set(index)){
        table[index] = new NumberVar(value);
    }
}

template<>
void SymbolTable::set(int index, float value) {
    if(this->assert_set(index)){
        table[index] = new FloatVar(value);
    }
}

template<>
void SymbolTable::set(int index, std::string value) {
    if(this->assert_set(index)){
        table[index] = new TextVar(value);
    }
}

template<>
void SymbolTable::set(int index, NumberVar *value) {
    table[index] = value;
}

template<>
void SymbolTable::set(int index, FloatVar *value) {
    table[index] = value;
}

template<>
void SymbolTable::set(int index, TextVar *value) {
    table[index] = value;
}

template<typename T>
T SymbolTable::get(int index) {
    throw Exception::EbeSymTableUnknwonTypeException("Attempt to set variable to not supported type");
    return T();
}

template<>
int SymbolTable::get(int index) {
    if(this->assert_get(index)){
        return table[index]->get_number();
    }
    return 0;
}

template<>
float SymbolTable::get(int index) {
    if(this->assert_get(index)){
        return table[index]->get_float();
    }
    return 0.0f;
}

template<>
std::string SymbolTable::get(int index) {
    if(this->assert_get(index)){
        return table[index]->get_text();
    }
    return "";
}

void SymbolTable::copy(int dst, int src) {
    assert_set(dst);
    assert_get(src);
    table[dst] = table[src]->clone();
}

std::string SymbolTable::to_string(int index) {
    if(index >= size) { 
        throw Exception::EbeSymTableOutOfRangeException("Variable $"+std::to_string(index)
            +"is out of range. Maximum allowed variable is $"+std::to_string(size));
    }
    auto var = table[index];
    if(var->type == IR::Type::NUMBER) {
        return std::to_string(var->get_number());
    }
    if(var->type == IR::Type::FLOAT) {
        return std::to_string(var->get_float());
    }
    if(var->type == IR::Type::TEXT) {
        return var->get_text();
    }
    throw Exception::EbeSymTableTypeException("Variable $"+std::to_string(index)+" type could not be casted to a string");
}

namespace Vars {
    std::ostream& operator<< (std::ostream &out, Vars::Variable& var) {
        var.format_value(out);
        return out;
    }
}