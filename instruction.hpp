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

#include <vector>

/** 
 * Namespace for instructions to not have class prefix 
 */
namespace Inst {

    enum PassName {
        WORDS = 0,
        LINES,
        DOCUMENTS
    };

    PassName get_pass_name(std::string name);

    /**
     * Abstract class for all instructions
     */
    class Instruction {
    public:
        virtual const char * const get_name() = 0;
        virtual void format_args(std::ostream &out);
    };

    // Sort instructions alphabetically

    class CONCAT : public Instruction {
    private:
        unsigned int arg1;
    public:
        static const char * const NAME;
        const char * const get_name() override {return NAME;}
        void format_args(std::ostream &out) override;
        CONCAT(unsigned int arg1) : arg1{arg1} {}
    };

    class DEL : public Instruction {
    public:
        static const char * const NAME;
        const char * const get_name() override {return NAME;}
        DEL(){}
    };

    class LOOP : public Instruction {
    public:
        static const char * const NAME;
        const char * const get_name() override {return NAME;}
        LOOP(){}
    };

    class NOP : public Instruction {
    public:
        static const char * const NAME;
        const char * const get_name() override {return NAME;}
        NOP(){}
    };

    class PASS : public Instruction {
    private:
        //PassName arg1;
    public:
        static const char * const NAME;
        const char * const get_name() override {return NAME;}
        //PASS(PassName arg1) : arg1{arg1} {}
    };

    class SWAP : public Instruction {
    private:
        unsigned int arg1;
    public:
        static const char * const NAME;
        const char * const get_name() override {return NAME;}
        void format_args(std::ostream &out);
        SWAP(unsigned int arg1) : arg1{arg1} {}
    };

};

#endif//_INSTRUCTION_HPP_