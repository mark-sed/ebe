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
#include "compiler.hpp"
#include "symbol_table.hpp"

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
        bool pragma;  ///< If true, then the instruction does not process and is used for the interpreter/compiler

        /** Destructor */ 
        virtual ~Instruction(){};

        virtual Instruction *copy() const = 0;

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

        /**
         * Instruction execution for PassLines
         * @param line Iterator pointing to the current line
         * @param doc The whole document
         * @param env Pass environment
         */
        virtual void exec(std::list<std::list<IR::Word *> *>::iterator &line, 
                          std::list<std::list<IR::Word *> *> *doc, IR::PassEnvironment &env) = 0;

        /**
         * Instruction execution for PassExpression
         * @param sym_table Symbol table which variables will be modified by the instruction
         */
        virtual void exec(Vars::SymbolTable *sym_table) {
            Error::error(Error::ErrorCode::INTERNAL, 
                         "Somehow non-expression instruction was executed in an expression pass. Please report this");
        }
    };

    /**
     * Type specialized instructions for expressions
     */ 
    class ExprInstruction : public Instruction {
    public:
        /** Destructor */ 
        virtual ~ExprInstruction(){};

        void exec(std::list<IR::Word *>::iterator &word, std::list<IR::Word *> *line, 
                  IR::PassEnvironment &env) override {
            Error::error(Error::ErrorCode::INTERNAL, 
                         "Somehow expression instruction was executed in a words pass. Please report this");
        }

        void exec(std::list<std::list<IR::Word *> *>::iterator &line, 
                  std::list<std::list<IR::Word *> *> *doc, IR::PassEnvironment &env) override {
            Error::error(Error::ErrorCode::INTERNAL, 
                        "Somehow expression instruction was executed in a lines pass. Please report this");
        }
    };

    /**
     * TODO: Take in chances for instructions
     * Generates a random instruction
     * @return A random instruction
     */ 
    Instruction *rand_instruction();

    // Sort instructions alphabetically

    class CONCAT : public Instruction {
    private:
        unsigned int arg1;
    public:
        static const char * const NAME;
        const char * const get_name() override {return NAME;}
        void format_args(std::ostream &out) override;
        CONCAT(unsigned int arg1) : arg1{arg1} { pragma = false; }
        CONCAT *copy() const override {
            return new CONCAT(arg1);
        }
        void exec(std::list<IR::Word *>::iterator &word, std::list<IR::Word *> *line, IR::PassEnvironment &env) override;
        void exec(std::list<std::list<IR::Word *> *>::iterator &line, 
                  std::list<std::list<IR::Word *> *> *doc, IR::PassEnvironment &env) override;
    };

    class DEL : public Instruction {
    public:
        static const char * const NAME;
        const char * const get_name() override {return NAME;}
        DEL(){ pragma = false; }
        virtual ~DEL() {}
        DEL *copy() const override {
            return new DEL();
        }
        void exec(std::list<IR::Word *>::iterator &word, std::list<IR::Word *> *line, IR::PassEnvironment &env) override;
        void exec(std::list<std::list<IR::Word *> *>::iterator &line, 
                  std::list<std::list<IR::Word *> *> *doc, IR::PassEnvironment &env) override;
    };

    class LOOP : public Instruction {
    public:
        static const char * const NAME;
        const char * const get_name() override {return NAME;}
        LOOP(){ pragma = true; }
        LOOP *copy() const override {
            return new LOOP();
        }
        void exec(std::list<IR::Word *>::iterator &word, std::list<IR::Word *> *line, IR::PassEnvironment &env) override;
        void exec(std::list<std::list<IR::Word *> *>::iterator &line, 
                  std::list<std::list<IR::Word *> *> *doc, IR::PassEnvironment &env) override;
    };

    class NOP : public Instruction {
    public:
        static const char * const NAME;
        const char * const get_name() override {return NAME;}
        NOP(){ pragma = false; }
        NOP *copy() const override {
            return new NOP();
        }
        void exec(std::list<IR::Word *>::iterator &word, std::list<IR::Word *> *line, IR::PassEnvironment &env) override;
        void exec(std::list<std::list<IR::Word *> *>::iterator &line, 
                  std::list<std::list<IR::Word *> *> *doc, IR::PassEnvironment &env) override;
    };

    class PASS : public Instruction {
    private:
        const char *arg1;
    public:
        static const char * const NAME;
        const char * const get_name() override {return NAME;}
        PASS(const char *arg1) { pragma = true; }
        PASS *copy() const override {
            return new PASS(arg1);
        }
        void exec(std::list<IR::Word *>::iterator &word, std::list<IR::Word *> *line, IR::PassEnvironment &env) override {}
        void exec(std::list<std::list<IR::Word *> *>::iterator &line, 
                  std::list<std::list<IR::Word *> *> *doc, IR::PassEnvironment &env) override {}
    };

    class SWAP : public Instruction {
    private:
        unsigned int arg1;
    public:
        static const char * const NAME;
        const char * const get_name() override {return NAME;}
        void format_args(std::ostream &out) override;
        SWAP(unsigned int arg1) : arg1{arg1} { pragma = false; }
        SWAP *copy() const override {
            return new SWAP(arg1);
        }
        void exec(std::list<IR::Word *>::iterator &word, std::list<IR::Word *> *line, IR::PassEnvironment &env) override;
        void exec(std::list<std::list<IR::Word *> *>::iterator &line, 
                  std::list<std::list<IR::Word *> *> *doc, IR::PassEnvironment &env) override;
    };

    // ExprInstructions

    class ADD : public ExprInstruction {
    private:
        int dst;
        int isrc1;
        int isrc2;
        Vars::Variable src1;
        Vars::Variable src2;
    public:
        static const char * const NAME;
        const char * const get_name() override { return NAME; }
        void format_args(std::ostream &out) override;
        // For custom settings, should be used only by copy
        ADD(int dst, int isrc1, int isrc2, Vars::Variable src1, Vars::Variable src2) 
            : dst{dst}, isrc1{isrc1}, isrc2{isrc2}, src1{src1}, src2{src2} { pragma = false; }
        // $, $, $
        ADD(int dst, int isrc1, int isrc2) 
            : dst{dst}, isrc1{isrc1}, isrc2{isrc2}, src1{}, src2{} { pragma = false; }
        // $, $, #
        ADD(int dst, int isrc1, Vars::Variable src2) 
            : dst{dst}, isrc1{isrc1}, isrc2{-1}, src1{}, src2{src2} { pragma = false; }
        // $, #, $
        ADD(int dst, Vars::Variable src1, int isrc2) 
            : dst{dst}, isrc1{-1}, isrc2{isrc2}, src1{src1}, src2{} { pragma = false; }
        // $, #, #
        ADD(int dst, Vars::Variable src1, Vars::Variable src2) 
            : dst{dst}, isrc1{-1}, isrc2{-1}, src1{src1}, src2{src2} { pragma = false; }
        ADD *copy() const override {
            return new ADD(dst, isrc1, isrc2, src1, src2);
        }
        void exec(Vars::SymbolTable *sym_table) override;
    };

};

#endif//_INSTRUCTION_HPP_
