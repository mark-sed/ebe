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

#include <iostream>

using namespace Inst;

// TODO: Convert to macro extracting class name
const char * const CONCAT::NAME = "CONCAT";
const char * const DEL::NAME = "DEL";
const char * const LOOP::NAME = "LOOP";
const char * const NOP::NAME = "NOP";
const char * const PASS::NAME = "PASS";
const char * const SWAP::NAME = "SWAP";

inline void Instruction::format_args(std::ostream &out){
    
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
    delete *word;
    word = line->erase(word);
    // Word was deleted, make sure to not skip word
    env.reprocess_obj = true;
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
