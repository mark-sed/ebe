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
#include <string>
#include <ostream>

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
    public:
        std::list<std::list<Word> *> *nodes;  ///< All IR nodes

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
        void push_back(unsigned long line, Word value);

        /**
         * Pushes new line into the nodes
         * @param line Line to be pushed
         * @note This method is prefered to push_back(line, value) because of the better time complexity
         */
        void push_back(std::list<Word> *line);

        //friend std::ostream& operator<< (std::ostream &out, const Node& node);
    };
}

/**
 * Overloaded operator<< to print easily IR for debugging
 */
std::ostream& operator<< (std::ostream &out, const IR::Node& node);

/**
 * Overloaded operator<< to print easily lists for debugging
 */
std::ostream& operator<< (std::ostream &out, const std::list<IR::Word>& node);

#endif//_IR_HPP_