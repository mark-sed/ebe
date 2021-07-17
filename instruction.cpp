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

#include "instruction.hpp"

using namespace Inst;

NOP::NOP(){

}

SWAP::SWAP(unsigned int arg1) : arg1{arg1} {

}