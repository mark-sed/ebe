/**
 * @file instruction.hpp
 * @author Marek Sedlacek
 * @date July 2021
 * @copyright Copyright 2021 Marek Sedlacek. All rights reserved.
 * 
 * @brief Ebel instructions
 * 
 * Holds ebel instructions and defines their behavior
 */

#ifndef _INSTRUCTION_HPP_
#define _INSTRUCTION_HPP_

/** Namespace for instructions to not have class prefix */
namespace Inst {

    /**
     * Abstract class for all instructions
     */
    class Instruction {
    protected:
        //void exec() = 0;
    };

    class NOP : public Instruction {
    public:
        NOP();
    };

    class SWAP : public Instruction {
    private:
        unsigned int arg1;
    public:
        SWAP(unsigned int arg1);
    };

};

#endif//_INSTRUCTION_HPP_