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
#include "instruction.hpp"
#include "engine.hpp"
#include "gp.hpp"

// Forward declarations
namespace Inst {
    class Instruction;
}

namespace GP {
    class Population;
}

struct GPEngineParams;

/**
 * Namespace for intermediate representation (IR) resources
 */
namespace IR {

    /**
     * Word datatypes - types for input text file
     * @note Every new datatype's name should be added to the get_type_name function
     */
    enum Type {
        TEXT,       ///< Word which is not number not special character
        NUMBER,     ///< Whole number
        FLOAT,      ///< Real number
        DELIMITER,  ///< Separating character
        SYMBOL,     ///< Symbol such as '$' for example
        EMPTY,      ///< Empty symbol for empty line
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
    public:
        std::string text;  ///< Text represantation of the word (as was in the file)
        Type type;         ///< Type parsed type of the word

        /**
         * Constructor
         * @param text Words text representation
         * @param type Words parsed type
         */
        Word(std::string text, Type type);
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
        /** Destructor */
        ~Node();

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
     * Abstract class for all passes
     */
    class Pass {
    public:
        const char *pass_name;                       ///< Name of the pass (needed for error printing)
        std::vector<Inst::Instruction *> *pipeline;  ///< Pipeline of instructions
        PassEnvironment env;
    private:
        friend std::ostream& operator<< (std::ostream &out, const IR::Pass& pass);
    protected:
        /** 
         * Constructor
         * @param pass_name Name of the pass that inherits this class
         */
        Pass(const char *pass_name);
    public:
        /** Destructor */
        virtual ~Pass();
        /**
         * Pushes a new instruction into the pipeline
         * @param inst Instruction to be pushed
         */
        void push_back(Inst::Instruction *inst);

        /**
         * Sets the pipeline
         * @param pipeline New pipeline
         */
        void set_pipeline(std::vector<Inst::Instruction *> *pipeline);

        /**
         * Processes text through pipeline
         * @param text Text to be processed
         */
        virtual void process(IR::Node *text) = 0;
    };

    /**
     * Pass by word
     */
    class PassWords : public Pass {
    public:
        /** Constructor */
        PassWords();

        void process(IR::Node *text) override;
    };

    /**
     * Pass by lines
     */
    class PassLines : public Pass {
    public:
        /** Constructor */
        PassLines();

        void process(IR::Node *text) override;
    };

    /**
     * Pass by documents
     */
    class PassDocuments : public Pass {
    public:
        /** Constructor */
        PassDocuments();

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