/**
 * @file instruction.cpp
 * @author Marek Sedlacek
 * @date July 2021
 * @copyright Copyright 2021 Marek Sedlacek. All rights reserved.
 * 
 * @brief Ebel instructions
 * 
 * Holds ebel instructions and defines their behavior
 */

#include <string>
#include <ostream>
#include <initializer_list>
#include <algorithm>
#include "ir.hpp"
#include "instruction.hpp"
#include "compiler.hpp"
#include "utils.hpp"
#include "rng.hpp"
#include "logging.hpp"
#include "symbol_table.hpp"

#include <iostream>

using namespace Inst;

// TODO: Convert to macro extracting class name
const char * const CALL::NAME = "CALL";
const char * const CONCAT::NAME = "CONCAT";
const char * const DEL::NAME = "DEL";
const char * const LOOP::NAME = "LOOP";
const char * const NOP::NAME = "NOP";
const char * const PASS::NAME = "PASS";
const char * const SWAP::NAME = "SWAP";
// ExprInstructions
const char * const ADD::NAME = "ADD";
const char * const SUB::NAME = "SUB";


inline void Instruction::format_args(std::ostream &out){
    
}

inline void ArithmeticInstruction::format_args(std::ostream &out) {
    out << "$" << this->dst << ", ";
    if(isrc1 >= 0)
        out << "$" << isrc1;
    else
        out << *src1; 
    out << ", ";
    if(isrc2 >= 0)    
        out << "$" << isrc2;
    else
        out << *src2;
}

inline void CALL::format_args(std::ostream &out){
    out << this->arg1;
}

inline void CONCAT::format_args(std::ostream &out){
    out << this->arg1;
}

inline void SWAP::format_args(std::ostream &out){
    out << this->arg1;
}


Instruction *Inst::rand_instruction(){
    // TODO: Make arguments be generated better and with passed in values
    // FIXME: return instructions only for specified pass
    switch(RNG::rand_int(0, 3)){
        case 0: return new SWAP(RNG::rand_int(1, 5));
        case 1: return new DEL();
        case 2: return new LOOP();
        case 3: return new NOP();
        //case 4: return new CONCAT(RNG::rand_int(1, 5));
    }
    return new NOP();
}

// Instruction interpretation

void CALL::exec(std::list<IR::Word *>::iterator &word, std::list<IR::Word *> *line, IR::PassEnvironment &env){
    // Words pass
    env.reprocess_obj = true;
}

void CALL::exec(std::list<std::list<IR::Word *> *>::iterator &line, 
                  std::list<std::list<IR::Word *> *> *doc, IR::PassEnvironment &env) {
    // Lines pass
    env.reprocess_obj = true;
}


void CONCAT::exec(std::list<IR::Word *>::iterator &word, std::list<IR::Word *> *line, IR::PassEnvironment &env){
    // Words pass
}

void CONCAT::exec(std::list<std::list<IR::Word *> *>::iterator &line, 
                  std::list<std::list<IR::Word *> *> *doc, IR::PassEnvironment &env) {
    // Lines pass
    if(std::distance(line, doc->end()) <= this->arg1){
        LOG1("CONCAT argument in lines pass is out of range, skipping");
        return;
    }
    auto src = line;
    std::advance(src, this->arg1);
    (*line)->insert((*line)->end(), (*src)->begin(), (*src)->end());
    doc->erase(src);
}

void DEL::exec(std::list<IR::Word *>::iterator &word, std::list<IR::Word *> *line, IR::PassEnvironment &env){
    // Words pass
    if((*word)->type == IR::EMPTY){
        // Don't delete empty line
        return;
    }
    delete *word;
    word = line->erase(word);

    // If line is empty, then place in the empty word
    if(line->empty()){
        line->push_back(new IR::Word("", IR::Type::EMPTY));
    }
    else{
        // Word was deleted, make sure to not skip word
        env.reprocess_obj = true;
    }
}

void DEL::exec(std::list<std::list<IR::Word *> *>::iterator &line, 
               std::list<std::list<IR::Word *> *> *doc, IR::PassEnvironment &env) {
    // Lines pass
    for(auto word: **line){
        delete word;
    }
    delete *line;
    line = doc->erase(line);
    env.reprocess_obj = true;
}

void LOOP::exec(std::list<IR::Word *>::iterator &word, std::list<IR::Word *> *line, IR::PassEnvironment &env){
    // Words pass
    env.loop_inst = this;
    // This is not an instruction tied to a word so process word in next instruction
    env.reprocess_obj = true;
}

void LOOP::exec(std::list<std::list<IR::Word *> *>::iterator &line, 
                  std::list<std::list<IR::Word *> *> *doc, IR::PassEnvironment &env) {
    // Lines pass
    env.loop_inst = this;
    env.reprocess_obj = true;
}

void NOP::exec(std::list<IR::Word *>::iterator &word, std::list<IR::Word *> *line, IR::PassEnvironment &env){
    // Words pass
}

void NOP::exec(std::list<std::list<IR::Word *> *>::iterator &line, 
                  std::list<std::list<IR::Word *> *> *doc, IR::PassEnvironment &env) {
    // Lines pass
}

void SWAP::exec(std::list<IR::Word *>::iterator &word, std::list<IR::Word *> *line, IR::PassEnvironment &env){
    // Words pass
    // Check if advanced iterator is correct otherwise dont do anything
    if(std::distance(word, line->end()) <= this->arg1){
        LOG1("SWAP argument in words pass is out of range, skipping");
        return;
    }
    auto src = word;
    std::advance(word, this->arg1);
    std::iter_swap(src, word);
}

void SWAP::exec(std::list<std::list<IR::Word *> *>::iterator &line, 
                  std::list<std::list<IR::Word *> *> *doc, IR::PassEnvironment &env) {
    // Lines pass
    if(std::distance(line, doc->end()) <= this->arg1){
        LOG1("SWAP argument in lines pass is out of range, skipping");
        return;
    }
    auto src = line;
    std::advance(line, this->arg1);
    std::iter_swap(src, line);
}

// ExprInstructions

void ExprInstruction::assert_type(int arg_num, const char *inst_name, IR::Type type, std::initializer_list<IR::Type> allowed) {
    for(auto &a: allowed) {
        if(type == a)
            return;
    }
    throw Exception::EbeSymTableTypeException(std::string("Incorrect ")+ std::to_string(arg_num) 
                                                         +". argument type in instruction "+inst_name);
}

inline void ExprInstruction::assert_eq_type(const char *inst_name, IR::Type t1, IR::Type t2) {
    if(t1 != t2) {
        throw Exception::EbeSymTableTypeException(std::string("Mismatched argument types in ")+inst_name+" instruction");
    }
}

inline IR::Type ExprInstruction::extract_type_var(int var, Vars::Variable *value, Vars::SymbolTable *sym_table) {
    if(var >= 0) {
        return sym_table->type_at(var);
    }
    return value->type;
}

int ExprInstruction::extract_int_var(int var, Vars::Variable *value, Vars::SymbolTable *sym_table) {
    if(var >= 0) {
        return sym_table->get<int>(var);
    }
    return value->get_number();
}

float ExprInstruction::extract_float_var(int var, Vars::Variable *value, Vars::SymbolTable *sym_table) {
    if(var >= 0) {
        return sym_table->get<float>(var);
    }
    return value->get_float();
}

std::string ExprInstruction::extract_string_var(int var, Vars::Variable *value, Vars::SymbolTable *sym_table) {
    if(var >= 0) {
        return sym_table->get<std::string>(var);
    }
    return value->get_text();
}

void ADD::exec(Vars::SymbolTable *sym_table) {
    // Extract types
    IR::Type src1_type = extract_type_var(isrc1, src1, sym_table);
    IR::Type src2_type = extract_type_var(isrc2, src2, sym_table);

    // Do type checking
    assert_type(2, NAME, src1_type, {IR::Type::NUMBER, IR::Type::FLOAT});
    assert_type(3, NAME, src2_type, {IR::Type::NUMBER, IR::Type::FLOAT});
    assert_eq_type(NAME, src1_type, src2_type);

    // SRC1 and SRC2 have matching type, based on it do addition
    if(src1_type == IR::NUMBER) {
        // Extract number values
        int src1_value = extract_int_var(isrc1, src1, sym_table);
        int src2_value = extract_int_var(isrc2, src2, sym_table);
        // Compute and save to symbol table
        int result = src1_value + src2_value;
        sym_table->set<int>(dst, result);
    }
    else { // FLOAT
        // Extract number values
        float src1_value = extract_float_var(isrc1, src1, sym_table);
        float src2_value = extract_float_var(isrc2, src2, sym_table);
        // Compute and save to symbol table
        float result = src1_value + src2_value;
        sym_table->set<float>(dst, result);
    }
}

void SUB::exec(Vars::SymbolTable *sym_table) {
    // Extract types
    IR::Type src1_type = extract_type_var(isrc1, src1, sym_table);
    IR::Type src2_type = extract_type_var(isrc2, src2, sym_table);

    // Do type checking
    assert_type(2, NAME, src1_type, {IR::Type::NUMBER, IR::Type::FLOAT});
    assert_type(3, NAME, src2_type, {IR::Type::NUMBER, IR::Type::FLOAT});
    assert_eq_type(NAME, src1_type, src2_type);

    // SRC1 and SRC2 have matching type, based on it do addition
    if(src1_type == IR::NUMBER) {
        // Extract number values
        int src1_value = extract_int_var(isrc1, src1, sym_table);
        int src2_value = extract_int_var(isrc2, src2, sym_table);
        // Compute and save to symbol table
        int result = src1_value - src2_value;
        sym_table->set<int>(dst, result);
    }
    else { // FLOAT
        // Extract number values
        float src1_value = extract_float_var(isrc1, src1, sym_table);
        float src2_value = extract_float_var(isrc2, src2, sym_table);
        // Compute and save to symbol table
        float result = src1_value - src2_value;
        sym_table->set<float>(dst, result);
    }
}
