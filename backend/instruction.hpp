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
#include <initializer_list>
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
    protected:
        /**
         * Asserts that argument's type is matching to expected one
         * @param arg_num Number of the argument, for error printing
         * @param inst_name Instruction name, for error printing
         * @param type Type of the argument
         * @param allowed Allowed values
         */ 
        void assert_type(int arg_num, const char *inst_name, IR::Type type, std::initializer_list<IR::Type> allowed);

        /**
         * Asserts that 2 argument have matching types
         * @param inst_name Instruction name, for error printing
         * @param t1 Type of the first argument
         * @param t2 Type of the second argument
         */ 
        void assert_eq_type(const char *inst_name, IR::Type t1, IR::Type t2);

        /**
         * Extracts type from variable/value
         * @param var Var index (if -1 then it won't be used)
         * @param value Value argument or nullptr
         * @param sym_table Symbol table to lookup variable
         * @return Variable's type
         */  
        IR::Type extract_type_var(int var, Vars::Variable *value, Vars::SymbolTable *sym_table);

        /**
         * Extracts value from integer (NUMBER) variable/value
         * @param var Var index (if -1 then it won't be used)
         * @param value Value argument or nullptr
         * @param sym_table Symbol table to lookup variable
         * @return Variable's value
         */  
        int extract_int_var(int var, Vars::Variable *value, Vars::SymbolTable *sym_table);

        /**
         * Extracts value from FLOAT variable/value
         * @param var Var index (if -1 then it won't be used)
         * @param value Value argument or nullptr
         * @param sym_table Symbol table to lookup variable
         * @return Variable's value
         */  
        float extract_float_var(int var, Vars::Variable *value, Vars::SymbolTable *sym_table);

        /**
         * Extracts value from TEXT variable/value
         * @param var Var index (if -1 then it won't be used)
         * @param value Value argument or nullptr
         * @param sym_table Symbol table to lookup variable
         * @return Variable's value
         */  
        std::string extract_string_var(int var, Vars::Variable *value, Vars::SymbolTable *sym_table);

    public:
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

        void exec(Vars::SymbolTable *sym_table) override {
            Error::error(Error::ErrorCode::INTERNAL, 
                         "Somehow non-expression instruction was executed in an expression pass. Please report this");
        }
    };

    /**
     * Class for arithmetic instructions
     */ 
    class ArithmeticInstruction : public ExprInstruction {
    protected:
        int dst;                ///< Destination address (variable index)
        int isrc1;              ///< 1st argument source address
        int isrc2;              ///< 2nd argument source address
        Vars::Variable *src1;   ///< 1st argument value
        Vars::Variable *src2;   ///< 2nd argument value
    public:
        void format_args(std::ostream &out) override;

        ArithmeticInstruction(int dst, int isrc1, int isrc2, Vars::Variable *src1, Vars::Variable *src2) 
            : dst{dst}, isrc1{isrc1}, isrc2{isrc2}, src1{src1}, src2{src2} { pragma = false; }
        /** 
         * Constructor for instruction signature:
         * $, $, $
         */ 
        ArithmeticInstruction(int dst, int isrc1, int isrc2) 
            : dst{dst}, isrc1{isrc1}, isrc2{isrc2}, src1{nullptr}, src2{nullptr} { pragma = false; }
        /** 
         * Constructor for instruction signature:
         * $, $, #
         */ 
        ArithmeticInstruction(int dst, int isrc1, Vars::Variable *src2) 
            : dst{dst}, isrc1{isrc1}, isrc2{-1}, src1{nullptr}, src2{src2} { pragma = false; }
        /** 
         * Constructor for instruction signature:
         * $, #, $
         */ 
        ArithmeticInstruction(int dst, Vars::Variable *src1, int isrc2) 
            : dst{dst}, isrc1{-1}, isrc2{isrc2}, src1{src1}, src2{nullptr} { pragma = false; }
        /** 
         * Constructor for instruction signature:
         * $, #, #
         */ 
        ArithmeticInstruction(int dst, Vars::Variable *src1, Vars::Variable *src2) 
            : dst{dst}, isrc1{-1}, isrc2{-1}, src1{src1}, src2{src2} { pragma = false; }

        ~ArithmeticInstruction() {
            if(src1 != nullptr) {
                delete src1;
            }
            if(src2 != nullptr) {
                delete src2;
            }
        }
    };

    /**
     * TODO: Take in chances for instructions
     * Generates a random instruction
     * @return A random instruction
     */ 
    Instruction *rand_instruction();

    // Sort instructions alphabetically

    class CALL : public Instruction {
    public:
        size_t arg1;
        static const char * const NAME;
        const char * const get_name() override {return NAME;}
        void format_args(std::ostream &out) override;
        CALL(size_t arg1) { pragma = true; }
        CALL *copy() const override {
            return new CALL(arg1);
        }
        void exec(std::list<IR::Word *>::iterator &word, std::list<IR::Word *> *line, IR::PassEnvironment &env) override;
        void exec(std::list<std::list<IR::Word *> *>::iterator &line, 
                  std::list<std::list<IR::Word *> *> *doc, IR::PassEnvironment &env) override;
    };

    class CONCAT : public Instruction {
    private:
        int arg1;
    public:
        static const char * const NAME;
        const char * const get_name() override {return NAME;}
        void format_args(std::ostream &out) override;
        CONCAT(int arg1) : arg1{arg1} { pragma = false; }
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
        int arg1;
    public:
        static const char * const NAME;
        const char * const get_name() override {return NAME;}
        void format_args(std::ostream &out) override;
        SWAP(int arg1) : arg1{arg1} { pragma = false; }
        SWAP *copy() const override {
            return new SWAP(arg1);
        }
        void exec(std::list<IR::Word *>::iterator &word, std::list<IR::Word *> *line, IR::PassEnvironment &env) override;
        void exec(std::list<std::list<IR::Word *> *>::iterator &line, 
                  std::list<std::list<IR::Word *> *> *doc, IR::PassEnvironment &env) override;
    };

    // ExprInstructions

    class ADD : public ArithmeticInstruction {
    public:
        static const char * const NAME;
        const char * const get_name() override { return NAME; }
        // For custom settings, should be used only by copy
        ADD(int dst, int isrc1, int isrc2, Vars::Variable *src1, Vars::Variable *src2) 
            : ArithmeticInstruction(dst, isrc1, isrc2, src1, src2) {}
        // $, $, $
        ADD(int dst, int isrc1, int isrc2) : ArithmeticInstruction(dst, isrc1, isrc2) {}
        // $, $, #
        ADD(int dst, int isrc1, Vars::Variable *src2) : ArithmeticInstruction(dst, isrc1, src2) {}
        // $, #, $
        ADD(int dst, Vars::Variable *src1, int isrc2) : ArithmeticInstruction(dst, src1, isrc2) {}
        // $, #, #
        ADD(int dst, Vars::Variable *src1, Vars::Variable *src2) : ArithmeticInstruction(dst, src1, src2) {}
        ADD *copy() const override {
            return new ADD(dst, isrc1, isrc2, src1, src2);
        }
        void exec(Vars::SymbolTable *sym_table) override;
    };

    class SUB : public ArithmeticInstruction {
    public:
        static const char * const NAME;
        const char * const get_name() override { return NAME; }
        // For custom settings, should be used only by copy
        SUB(int dst, int isrc1, int isrc2, Vars::Variable *src1, Vars::Variable *src2) 
            : ArithmeticInstruction(dst, isrc1, isrc2, src1, src2) {}
        // $, $, $
        SUB(int dst, int isrc1, int isrc2) : ArithmeticInstruction(dst, isrc1, isrc2) {}
        // $, $, #
        SUB(int dst, int isrc1, Vars::Variable *src2) : ArithmeticInstruction(dst, isrc1, src2) {}
        // $, #, $
        SUB(int dst, Vars::Variable *src1, int isrc2) : ArithmeticInstruction(dst, src1, isrc2) {}
        // $, #, #
        SUB(int dst, Vars::Variable *src1, Vars::Variable *src2) : ArithmeticInstruction(dst, src1, src2) {}
        SUB *copy() const override {
            return new SUB(dst, isrc1, isrc2, src1, src2);
        }
        void exec(Vars::SymbolTable *sym_table) override;
    };

    class MUL : public ArithmeticInstruction {
    public:
        static const char * const NAME;
        const char * const get_name() override { return NAME; }
        // For custom settings, should be used only by copy
        MUL(int dst, int isrc1, int isrc2, Vars::Variable *src1, Vars::Variable *src2) 
            : ArithmeticInstruction(dst, isrc1, isrc2, src1, src2) {}
        // $, $, $
        MUL(int dst, int isrc1, int isrc2) : ArithmeticInstruction(dst, isrc1, isrc2) {}
        // $, $, #
        MUL(int dst, int isrc1, Vars::Variable *src2) : ArithmeticInstruction(dst, isrc1, src2) {}
        // $, #, $
        MUL(int dst, Vars::Variable *src1, int isrc2) : ArithmeticInstruction(dst, src1, isrc2) {}
        // $, #, #
        MUL(int dst, Vars::Variable *src1, Vars::Variable *src2) : ArithmeticInstruction(dst, src1, src2) {}
        MUL *copy() const override {
            return new MUL(dst, isrc1, isrc2, src1, src2);
        }
        void exec(Vars::SymbolTable *sym_table) override;
    };

    class DIV : public ArithmeticInstruction {
    public:
        static const char * const NAME;
        const char * const get_name() override { return NAME; }
        // For custom settings, should be used only by copy
        DIV(int dst, int isrc1, int isrc2, Vars::Variable *src1, Vars::Variable *src2) 
            : ArithmeticInstruction(dst, isrc1, isrc2, src1, src2) {}
        // $, $, $
        DIV(int dst, int isrc1, int isrc2) : ArithmeticInstruction(dst, isrc1, isrc2) {}
        // $, $, #
        DIV(int dst, int isrc1, Vars::Variable *src2) : ArithmeticInstruction(dst, isrc1, src2) {}
        // $, #, $
        DIV(int dst, Vars::Variable *src1, int isrc2) : ArithmeticInstruction(dst, src1, isrc2) {}
        // $, #, #
        DIV(int dst, Vars::Variable *src1, Vars::Variable *src2) : ArithmeticInstruction(dst, src1, src2) {}
        DIV *copy() const override {
            return new DIV(dst, isrc1, isrc2, src1, src2);
        }
        void exec(Vars::SymbolTable *sym_table) override;
    };

    class MOD : public ArithmeticInstruction {
    public:
        static const char * const NAME;
        const char * const get_name() override { return NAME; }
        // For custom settings, should be used only by copy
        MOD(int dst, int isrc1, int isrc2, Vars::Variable *src1, Vars::Variable *src2) 
            : ArithmeticInstruction(dst, isrc1, isrc2, src1, src2) {}
        // $, $, $
        MOD(int dst, int isrc1, int isrc2) : ArithmeticInstruction(dst, isrc1, isrc2) {}
        // $, $, #
        MOD(int dst, int isrc1, Vars::Variable *src2) : ArithmeticInstruction(dst, isrc1, src2) {}
        // $, #, $
        MOD(int dst, Vars::Variable *src1, int isrc2) : ArithmeticInstruction(dst, src1, isrc2) {}
        // $, #, #
        MOD(int dst, Vars::Variable *src1, Vars::Variable *src2) : ArithmeticInstruction(dst, src1, src2) {}
        MOD *copy() const override {
            return new MOD(dst, isrc1, isrc2, src1, src2);
        }
        void exec(Vars::SymbolTable *sym_table) override;
    };

    class POW : public ArithmeticInstruction {
    public:
        static const char * const NAME;
        const char * const get_name() override { return NAME; }
        // For custom settings, should be used only by copy
        POW(int dst, int isrc1, int isrc2, Vars::Variable *src1, Vars::Variable *src2) 
            : ArithmeticInstruction(dst, isrc1, isrc2, src1, src2) {}
        // $, $, $
        POW(int dst, int isrc1, int isrc2) : ArithmeticInstruction(dst, isrc1, isrc2) {}
        // $, $, #
        POW(int dst, int isrc1, Vars::Variable *src2) : ArithmeticInstruction(dst, isrc1, src2) {}
        // $, #, $
        POW(int dst, Vars::Variable *src1, int isrc2) : ArithmeticInstruction(dst, src1, isrc2) {}
        // $, #, #
        POW(int dst, Vars::Variable *src1, Vars::Variable *src2) : ArithmeticInstruction(dst, src1, src2) {}
        POW *copy() const override {
            return new POW(dst, isrc1, isrc2, src1, src2);
        }
        void exec(Vars::SymbolTable *sym_table) override;
    };

};

#endif//_INSTRUCTION_HPP_
