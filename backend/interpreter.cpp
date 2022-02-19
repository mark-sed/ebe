/**
 * @file interpreter.cpp
 * @author Marek Sedlacek
 * @date July 2021
 * @copyright Copyright 2021 Marek Sedlacek. All rights reserved.
 * 
 * @brief Interpreter for ebel
 * 
 * Holds resources for interpreter for ebel program over input text
 */

#include <iostream>
#include <iterator>
#include "interpreter.hpp"
#include "logging.hpp"
#include "ir.hpp"
#include "instruction.hpp"
#include "pragmas.hpp"

Interpreter::Interpreter(IR::EbelNode *ebel) : Compiler("Interpreter"), ebel{ebel} {

}

void Interpreter::parse(IR::Node *text) {
    // Apply pragmas
    this->ebel->pragmas->apply();
    // Iterate through passes
    for(auto pass: (*this->ebel->nodes)) {
        pass->process(text);
    }
}

void Interpreter::eliminate_dead_code() {
    for(auto pass: (*this->ebel->nodes)) {
        if(pass->last_executed_index != -1 && pass->pipeline->size() != pass->last_executed_index) {
            LOG5("Eliminated dead code from: \n" << *pass);
            pass->pipeline->resize(pass->last_executed_index);
            LOG5("..to: \n" << *pass);
        }
    }
}

void Interpreter::eliminate_redundat_code() {
    // Remove redundat LOOPs (all LOOP instructions before the last one)
    for(auto pass: (*this->ebel->nodes)) {
        if(pass->env.loop_inst != nullptr) {
            for(auto inst_i = pass->pipeline->begin(); inst_i != pass->pipeline->end(); ) {
                if(*inst_i == pass->env.loop_inst) {
                    // Last loop was reached, no need to go further
                    if(inst_i == pass->pipeline->begin()) {
                        // Check if this is not the first loop, if so, then remove it
                        // because it has no instructions to loop over
                        pass->pipeline->erase(inst_i);
                        pass->env.loop_inst = nullptr;
                    }
                    break;
                }
                if((*inst_i)->get_name() == std::string("LOOP")) {
                    // LOOP before env.loop_inst, can be removed or LOOP on the first line
                    pass->pipeline->erase(inst_i);
                }
                else {
                    ++inst_i;
                }
            }
        }
    }
}

void Interpreter::optimize() {
    // Dead code elimination
    this->eliminate_dead_code();
    // Removing code that is not needed
    this->eliminate_redundat_code();
}
