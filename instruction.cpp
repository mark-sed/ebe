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
#include "instruction.hpp"
#include "utils.hpp"
#include "compiler.hpp"
#include "ir.hpp"

#include <iostream>

using namespace Inst;

// TODO: Convert to macro extracting class name
const char * const CONCAT::NAME = "CONCAT";
const char * const DEL::NAME = "DEL";
const char * const LOOP::NAME = "LOOP";
const char * const NOP::NAME = "NOP";
const char * const PASS::NAME = "PASS";
const char * const SWAP::NAME = "SWAP";

/*Inst::PassName Inst::get_pass_name(std::string name){
    auto up_name = Utils::to_upper(name);
    if(up_name == "WORDS"){
        return PassName::WORDS;
    }
    if(up_name == "LINES"){
        return PassName::LINES;
    }
    if(up_name == "DOCUMENTS"){
        return PassName::DOCUMENTS;
    }
    Error::error(Error::ErrorCode::INTERNAL, "Unknown pass name conversion");
}*/

inline void Instruction::format_args(std::ostream &out){
    
}

void Instruction::exec(std::list<IR::Word *>::iterator &word, std::list<IR::Word *> *line, IR::PassEnvironment &env) {
    
}

void CONCAT::exec(std::list<IR::Word *>::iterator &word, std::list<IR::Word *> *line, IR::PassEnvironment &env){
    
}

void DEL::exec(std::list<IR::Word *>::iterator &word, std::list<IR::Word *> *line, IR::PassEnvironment &env){
    // FIXME: Erase makes sigsegv 
    //line->erase(word);
}

void LOOP::exec(std::list<IR::Word *>::iterator &word, std::list<IR::Word *> *line, IR::PassEnvironment &env){
    
}

void NOP::exec(std::list<IR::Word *>::iterator &word, std::list<IR::Word *> *line, IR::PassEnvironment &env){
    
}

void SWAP::exec(std::list<IR::Word *>::iterator &word, std::list<IR::Word *> *line, IR::PassEnvironment &env){
    // FIXME: Check if advanced iterator is correct
    auto src = word;
    std::advance(word, this->arg1);
    std::iter_swap(src, word);
}

inline void CONCAT::format_args(std::ostream &out){
    out << this->arg1;
}

inline void SWAP::format_args(std::ostream &out){
    out << this->arg1;
}
