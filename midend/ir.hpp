/**
 * @file ir.hpp
 * @author Marek Sedlacek
 * @date July 2021
 * @copyright Copyright 2021 Marek Sedlacek. All rights reserved.
 * 
 * @brief Intermediate representation
 * 
 * Intermediate representation of text files.
 */

#ifndef _IR_HPP_
#define _IR_HPP_

#include <list>
#include <vector>
#include <string>
#include <ostream>
#include "engine.hpp"
#include "gp.hpp"
#include "tree.hpp"
#include "expression.hpp"

#include <iostream>

// Forward declarations
namespace Inst {
    class Instruction;
    class ExprInstruction;
}

namespace GP {
    class Population;
}

struct GPEngineParams;

/**
 * Namespace for intermediate representation (IR) resources
 */
namespace IR {

    // Forward declaration
    class PassExpression;

    /**
     * Word datatypes - types for input text file
     * @note Every new datatype's name should be added to the get_type_name function
     */
    enum Type {
        TEXT = 0,   ///< Word which is not number not special character
        NUMBER,     ///< Whole number
        FLOAT,      ///< Real number
        DELIMITER,  ///< Separating character
        SYMBOL,     ///< Symbol such as '#' for example
        EXPRESSION, ///< Expression
        EMPTY,      ///< Empty symbol for empty line
        DERIVED     ///< Type used for automatically deriving the type (for expressions)
    };

    /**
     * Getter for type's name
     * @param type IR type
     * @return Name of the passed in type
     */
    const char *get_type_name(Type type);

    /**
     * Word - text object of any type
     */
    class Word {
    private:
        friend std::ostream& operator<< (std::ostream &out, const std::list<IR::Word>& node);
        friend std::ostream& operator<< (std::ostream &out, const IR::Word& word);
    public:
        std::string text;                   ///< Text represantation of the word (as was in the file)
        Type type;                          ///< Type parsed type of the word
        Expr::Expression *expr = nullptr;   ///< Expression abstract syntax tree if type is IR::Type EXPRESSION
        IR::PassExpression *code = nullptr; ///< Code generated for the expression if type is IR::Type::EXPRESSION
        Inst::Instruction *return_inst = nullptr; ///< Return instruction of the expression

        /**
         * Constructor 
         * @param text Words text representation
         * @param type Words parsed type
         * @param expr Node's expression as a syntactic tree
         * @param code Node's expression as an ebel code
         * @param return_inst Expressions return instruction
         */
        Word(std::string text, 
             Type type, 
             Expr::Expression *expr=nullptr,
             IR::PassExpression *code=nullptr,
             Inst::Instruction *return_inst=nullptr);
        /** Copy constructor */
        Word(const Word &other);
        /** Destructor, frees expr when allocated */
        ~Word();

        /** Copy operator */
        Word& operator=(const Word &other);

        /** Comparison operator */
        bool operator==(const Word &other) const;
        bool operator!=(const Word &other) const;

        /**
         * @defgroup wordgetters Word value extractors
         * Extract values of specified type from the word
         * @return Variable's value
         * @note This calls Cast::to so it's exceptions may be raised
         * @throws EbeTypeException if incorrect type is requested
         * @{
         */  
        template<IR::Type type> int to_int();
        template<IR::Type type> float to_float();
        template<IR::Type type> std::string to_string();
        /** @} */
    };

    /**
     * Root node of the IR holding all the IR's data
     * This is not a node holding specific value, but it holds all the other nodes
     */
    class Node {
    private:
        friend std::ostream& operator<< (std::ostream &out, const IR::Node& node);
    public:
        std::list<std::list<Word *> *> *nodes;  ///< All IR nodes

        /** Constructor */
        Node();
        /** Copy constructor */
        Node(const Node &other);
        /** Destructor */
        ~Node();

        /** Copy operator */
        Node &operator=(const Node &other);

        /** Comparison operator */
        bool operator==(const Node &other) const;
        bool operator!=(const Node &other) const;

        /**
         * Pushes new word into specific line
         * @param line Number of the line
         * @param value Word to be pushed into the line
         * @note push_back(line) method is prefered to this one because of the better time complexity
         */
        void push_back(unsigned long line, Word *value);

        /**
         * Pushes new line into the nodes
         * @param line Line to be pushed
         * @note This method is prefered to push_back(line, value) because of the better time complexity
         */
        void push_back(std::list<Word *> *line);

        /**
         * Converts IR to the output format for user
         */
        std::string output();
    };

    /**
     * Holds current pass settings from instructions
     */
    struct PassEnvironment {
        Inst::Instruction *loop_inst;  ///< Pointer to loop instruction for end of loop detection 
        bool reprocess_obj;            ///< To make sure control instructions don't process an object
        PassEnvironment() : loop_inst{nullptr}, reprocess_obj{false} {};
    };

    /**
     * Pass types
     */
    enum PassType {
        EXPRESSION_PASS,
        WORDS_PASS,
        LINES_PASS,
        DOCUMENTS_PASS
    };

    /**
     * Abstract class for all passes
     */
    class Pass {
    public:
        const char *pass_name;                       ///< Name of the pass (needed for error printing)
        PassType type;                               ///< Pass type ID
        std::vector<Inst::Instruction *> *pipeline;  ///< Pipeline of instructions
        std::vector<Pass *> *subpass_table;          ///< Table of subpasses
        PassEnvironment env;                         ///< Current environment
    private:
        friend std::ostream& operator<< (std::ostream &out, const IR::Pass& pass);
    protected:
        /** 
         * Constructor
         * @param type Name of the pass that inherits this class
         */
        Pass(PassType type);
        /** Copy constructor */
        Pass(const Pass &other);
    public:
        /** Destructor */
        virtual ~Pass();
        /**
         * Pushes a new instruction into the pipeline
         * @param inst Instruction to be pushed
         */
        void push_back(Inst::Instruction *inst);

        /**
         * Pushes a subpass into the pipeline
         * @param subpass Sub pass to push
         * @note This method can only be used for pass words with expression pass at the moment
         */
        virtual void push_subpass(Pass *subpass);

        /**
         * Sets the pipeline
         * @param pipeline New pipeline
         */
        void set_pipeline(std::vector<Inst::Instruction *> *pipeline);

        /** Check for emptyness of pipeline */
        bool empty() {
            return pipeline->empty();
        }

        /**
         * Processes text through pipeline
         * @param text Text to be processed
         */
        virtual void process(IR::Node *text) = 0;

        /**
         * Getter for pass name
         */ 
        const char *get_name() { return this->pass_name; }

        /** Getter for pass type */
        PassType get_type() { return this->type; }

        /**
         * Debugging print that won't replace CALL with the subpass (unlike << does)
         * @param out Stream to print to
         * @param indent Indentation
         */ 
        std::ostream& print_pass_noinline(std::ostream &out, const char *indent);
    };

    /**
     * Pass over current word
     */
    class PassExpression : public Pass {
    public:
        Type expr_type;

        /** Constructor */
        PassExpression(Type expr_type);
        /** Copy constructor */
        PassExpression(const PassExpression &other);

        void process(IR::Node *text) override;
        void process(IR::Word *word, size_t line, size_t column);
    };

    /**
     * Pass by word
     */
    class PassWords : public Pass {
    public:
        /** Constructor */
        PassWords();
        /** Copy constructor */
        PassWords(const PassWords &other);

        void process(IR::Node *text) override;
        void push_subpass(IR::Pass *subpass) override;
    };

    /**
     * Pass by lines
     */
    class PassLines : public Pass {
    public:
        /** Constructor */
        PassLines();
        /** Copy constructor */
        PassLines(const PassLines &other);

        void process(IR::Node *text) override;
    };

    /**
     * Pass by documents
     */
    class PassDocuments : public Pass {
    public:
        /** Constructor */
        PassDocuments();
        /** Copy constructor */
        PassDocuments(const PassDocuments &other);

        void process(IR::Node *text) override;
    };

    /**
     * Root node for ebel program holding all passes
     */
    class EbelNode {
    private:
        friend std::ostream& operator<< (std::ostream &out, const IR::EbelNode& node);
    public:
        std::list<Pass *> *nodes;  ///< Passes holding instructions

        /** Constructor */
        EbelNode();
        /** Copy constructor */
        EbelNode(const EbelNode &other);

        /**
         * Constructor for generating random node
         * @param params Genetic engine parameters to know how many instructions to create
         */ 
        EbelNode(GPEngineParams *params);

        /** Destructor */
        ~EbelNode();

        /**
         * Pushes new pass into the nodes
         * @param pass Pass to be pushed
         */
        void push_back(Pass *pass);

        /**
         * Debug print for ebel code without inlining subpasses
         * @param out Output stream
         * @return The output stream
         */ 
        std::ostream &dbprint_no_inline(std::ostream &out);

        friend std::ostream& operator<< (std::ostream &out, const GP::Population& popul);
    };
}

/**
 * Overloaded operator== for 2 Words used in IR comparison
 */ 
bool operator==(IR::Word &lhs, IR::Word &rhs);

/**
 * Overloaded operator<< to print easily IR for debugging
 */
//std::ostream& operator<< (std::ostream &out, const IR::Node& node);

/**
 * Overloaded operator<< to print easily lists for debugging
 */
//std::ostream& operator<< (std::ostream &out, const std::list<IR::Word>& node);

/**
 * Overloaded operator<< to print easily passes for debugging
 */
//std::ostream& operator<< (std::ostream &out, const IR::Pass& pass);

/**
 * Overloaded operator<< to print easily IR for debugging
 */
//std::ostream& operator<< (std::ostream &out, const IR::EbelNode& node);

#endif//_IR_HPP_
