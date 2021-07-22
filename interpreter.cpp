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

#include "interpreter.hpp"
#include "ir.hpp"
#include <iostream>

Interpreter::Interpreter(IR::EbelNode *ebel) : Compiler("Interpreter"), ebel{ebel} {

}

void Interpreter::parse(IR::Node *text) {
    IR::Node *output = new IR::Node;

    // Iterate through passes
    for(auto pass: (*this->ebel->nodes)){
        pass->process(text);
    }
}