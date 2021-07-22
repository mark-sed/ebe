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
#include <list>
#include <iterator>
#include "ir.hpp"

// Forward declarations
namespace IR{
    class Word;
    struct PassEnvironment;
}

/** 
 * Namespace for instructions to not have class prefix 
 */
namespace Inst {

    /**
     * Abstract class for all instructions
     */
    class Instruction {
    public:
        /** Destructor */ 
        virtual ~Instruction(){};

        /**
         * Returns name of the instruction
         */
        virtual const char * const get_name() = 0;

        /**
         * Outputs arguments separated by space into out
         * @param out Stream to output to
         */
        virtual void format_args(std::ostream &out);

        /**
         * Instruction execution for PassWords
         * @param word Iterator pointing to the input word in a line
         * @param line The whole line
         * @param env Pass environment
         */
        virtual void exec(std::list<IR::Word *>::iterator &word, std::list<IR::Word *> *line, IR::PassEnvironment &env) = 0;
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
        void exec(std::list<IR::Word *>::iterator &word, std::list<IR::Word *> *line, IR::PassEnvironment &env) override;
    };

    class DEL : public Instruction {
    public:
        static const char * const NAME;
        const char * const get_name() override {return NAME;}
        DEL(){}
        void exec(std::list<IR::Word *>::iterator &word, std::list<IR::Word *> *line, IR::PassEnvironment &env) override;
    };

    class LOOP : public Instruction {
    public:
        static const char * const NAME;
        const char * const get_name() override {return NAME;}
        LOOP(){}
        void exec(std::list<IR::Word *>::iterator &word, std::list<IR::Word *> *line, IR::PassEnvironment &env) override;
    };

    class NOP : public Instruction {
    public:
        static const char * const NAME;
        const char * const get_name() override {return NAME;}
        NOP(){}
        void exec(std::list<IR::Word *>::iterator &word, std::list<IR::Word *> *line, IR::PassEnvironment &env) override;
    };

    class PASS : public Instruction {
    // IR instruction, does no need to be in nodes, so no need for constructor
    public:
        static const char * const NAME;
        const char * const get_name() override {return NAME;}
        void exec(std::list<IR::Word *>::iterator &word, std::list<IR::Word *> *line, IR::PassEnvironment &env) override {}
    };

    class SWAP : public Instruction {
    private:
        unsigned int arg1;
    public:
        static const char * const NAME;
        const char * const get_name() override {return NAME;}
        void format_args(std::ostream &out);
        SWAP(unsigned int arg1) : arg1{arg1} {}
        void exec(std::list<IR::Word *>::iterator &word, std::list<IR::Word *> *line, IR::PassEnvironment &env) override;
    };

};

#endif//_INSTRUCTION_HPP_