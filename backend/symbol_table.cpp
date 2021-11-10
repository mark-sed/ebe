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

SymbolTable::SymbolTable() : Compiler("Symbol table") {
    this->table = new Variable *[SIZE]();
}

SymbolTable::~SymbolTable() { 
    delete[] table;
}

bool SymbolTable::assert_set(int index){
    if(index >= SIZE){
        throw Exception::EbeSymTableOutOfRangeException("Variable $"+std::to_string(index)+"is out of range. Maximum allowed variable is $"+std::to_string(SIZE));
        return false;
    }
    // Remove previous possible value
    if(table[index] != nullptr){
        delete table[index];
    }
    return true;
}

bool SymbolTable::assert_get(int index){
    if(index >= SIZE){
        throw Exception::EbeSymTableOutOfRangeException("Variable $"+std::to_string(index)+"is out of range. Maximum allowed variable is $"+std::to_string(SIZE));
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
    return 0;
}

