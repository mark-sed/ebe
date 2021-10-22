/**
 * @file interpreter.hpp
 * @author Marek Sedlacek
 * @date July 2021
 * @copyright Copyright 2021 Marek Sedlacek. All rights reserved.
 * 
 * @brief Interpreter for ebel
 * 
 * Holds resources for interpreter for ebel program over input text
 */

#ifndef _INTERPRETER_HPP_
#define _INTERPRETER_HPP_

#include "ir.hpp"
#include "compiler.hpp"

/**
 * Interpreter for ebel code
 */
class Interpreter : public Compiler {
private:
    IR::EbelNode *ebel;
public:
    /**
     * Constructor
     * @param ebel Parsed ebel code in IR form
     */
    Interpreter(IR::EbelNode *ebel);

    /**
     * Parses scanned text into new text using ebel code from initialization
     * @param text Input text to be parsed
     */
    void parse(IR::Node *text);
};

#endif//_INTERPRETER_HPP_