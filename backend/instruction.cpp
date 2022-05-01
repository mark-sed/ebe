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
#include <cmath>
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
const char * const DIV::NAME = "DIV";
const char * const MOD::NAME = "MOD";
const char * const MOVE::NAME = "MOVE";
const char * const MUL::NAME = "MUL";
const char * const POW::NAME = "POW";
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

inline void MOVE::format_args(std::ostream &out) {
    out << "$" << this->dst << ", ";
    if(isrc1 >= 0)
        out << "$" << isrc1;
    else
        out << *src1;
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

Instruction *Inst::rand_instruction(IR::PassType, int pass_length, const InstructionOccurrences &occs) {
    // CONCAT, DEL, LOOP, NOP, SWAP
    if(pass_length < 2) {
        // It is used in rand_int so it has to be at least 2 to get 1
        pass_length = 2;
    }

    float chance = RNG::rand_float();
    if(chance < occs.CONCAT) {
        return new CONCAT(RNG::roll() ? 1 : RNG::rand_int(1, pass_length-1));
    }
    else if(chance < occs.DEL) {
        return new DEL();
    }
    else if(chance < occs.LOOP) {
        return new LOOP();
    }
    else if(chance < occs.NOP) {
        return new NOP();
    }
    else if(chance < occs.SWAP) {
        return new SWAP(RNG::rand_int(1, pass_length-1));
    }

    // Covers the case where the values don't add up to 1.0f or might not because of floating error.
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
    // Reprocess needed to work with the correct line next
    env.reprocess_obj = true;
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

void MOVE::exec(Vars::SymbolTable *sym_table) {
    if(isrc1 > -1) {
        // MOVE $, $
        if(isrc1 == dst) {
            return;
        }
        // variable
        sym_table->copy(dst, isrc1);
    }
    else {
        if(src1->type == IR::Type::NUMBER){
            sym_table->set(dst, dynamic_cast<Vars::NumberVar*>(src1));
        }
        else if(src1->type == IR::Type::FLOAT) {
            sym_table->set(dst, dynamic_cast<Vars::FloatVar*>(src1));
        }
        else if(src1->type == IR::Type::TEXT) {
            sym_table->set(dst, dynamic_cast<Vars::TextVar*>(src1));
        }
        else {
            throw Exception::EbeTypeException(std::string("Type '")+IR::get_type_name(src1->type)
                                             +"' cannot be used in MOVE instruction");
        }
    }

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

void MUL::exec(Vars::SymbolTable *sym_table) {
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
        int result = src1_value * src2_value;
        sym_table->set<int>(dst, result);
    }
    else { // FLOAT
        // Extract number values
        float src1_value = extract_float_var(isrc1, src1, sym_table);
        float src2_value = extract_float_var(isrc2, src2, sym_table);
        // Compute and save to symbol table
        float result = src1_value * src2_value;
        sym_table->set<float>(dst, result);
    }
}

void DIV::exec(Vars::SymbolTable *sym_table) {
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
        // Check division by 0
        if(src2_value == 0) {
            throw Exception::EbeDivisionByZeroException("Division by zero");
        }
        // Compute and save to symbol table
        int result = src1_value / src2_value;
        sym_table->set<int>(dst, result);
    }
    else { // FLOAT
        // Extract number values
        float src1_value = extract_float_var(isrc1, src1, sym_table);
        float src2_value = extract_float_var(isrc2, src2, sym_table);
        if(src2_value == 0.0f) {
            throw Exception::EbeDivisionByZeroException("Division by zero");
        }
        // Compute and save to symbol table
        float result = src1_value / src2_value;
        sym_table->set<float>(dst, result);
    }
}

void MOD::exec(Vars::SymbolTable *sym_table) {
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
        // Check division by 0
        if(src2_value == 0) {
            throw Exception::EbeDivisionByZeroException("Division by zero in MOD instruction");
        }
        // Compute and save to symbol table
        int result = src1_value % src2_value;
        sym_table->set<int>(dst, result);
    }
    else { // FLOAT
        // Extract number values
        float src1_value = extract_float_var(isrc1, src1, sym_table);
        float src2_value = extract_float_var(isrc2, src2, sym_table);
        if(src2_value == 0.0f) {
            throw Exception::EbeDivisionByZeroException("Division by zero in MOD instruction");
        }
        // Compute and save to symbol table
        float result = std::fmod(src1_value, src2_value);
        sym_table->set<float>(dst, result);
    }
}

void POW::exec(Vars::SymbolTable *sym_table) {
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
        // TODO: Result should possibly be float, since pow does not always have to return int (4^-2 = 0.0625)
        int result = static_cast<int>(std::pow(src1_value, src2_value));
        sym_table->set<int>(dst, result);
    }
    else { // FLOAT
        // Extract number values
        float src1_value = extract_float_var(isrc1, src1, sym_table);
        float src2_value = extract_float_var(isrc2, src2, sym_table);
        // Compute and save to symbol table
        float result = std::pow(src1_value, src2_value);
        sym_table->set<float>(dst, result);
    }
}
