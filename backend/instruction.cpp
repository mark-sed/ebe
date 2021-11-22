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


inline void Instruction::format_args(std::ostream &out){
    
}

inline void ADD::format_args(std::ostream &out) {
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

void ADD::exec(Vars::SymbolTable *sym_table) {
    IR::Type src1_type;
    IR::Type src2_type;
    // Check if src1 is variable or constant and get its type
    if(isrc1 >= 0) {
        src1_type = sym_table->type_at(isrc1);
    }
    else {
        src1_type = src1->type;
    }
    // Check also for src2
    if(isrc2 >= 0) {
        src2_type = sym_table->type_at(isrc2);
    }
    else {
        src2_type = src2->type;
    }

    // Do type checking
    if(src1_type != src2_type) {
        throw Exception::EbeSymTableTypeException("Mismatched argument types in ADD instruction");
    }
    if(src1_type != IR::Type::NUMBER && src1_type != IR::Type::FLOAT) {
        throw Exception::EbeSymTableTypeException("Incorrect 2nd argument type in ADD instruction");
    }
    if(src2_type != IR::Type::NUMBER && src2_type != IR::Type::FLOAT) {
        throw Exception::EbeSymTableTypeException("Incorrect 3rd argument type in ADD instruction");
    }
    // SRC1 and SRC2 have matching type, based on it do addition
    if(src1_type == IR::NUMBER) {
        int src1_value;
        int src2_value;
        // Extract int values either from symbol table or Variable
        if(isrc1 >= 0) {
            src1_value = sym_table->get<int>(isrc1);
        }
        else {
            src1_value = src1->get_number();
        }

        if(isrc2 >= 0) {
            src2_value = sym_table->get<int>(isrc2);
        }
        else {
            src2_value = src2->get_number();
        }
        int result = src1_value + src2_value;
        sym_table->set<int>(dst, result);
    }
    else { // FLOAT
        int src1_value;
        int src2_value;
        if(isrc1 >= 0) {
            src1_value = sym_table->get<float>(isrc1);
        }
        else {
            src1_value = src1->get_float();
        }

        if(isrc2 >= 0) {
            src2_value = sym_table->get<float>(isrc2);
        }
        else {
            src2_value = src2->get_float();
        }
        int result = src1_value + src2_value;
        sym_table->set<float>(dst, result);
    }
}
