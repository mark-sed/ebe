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

namespace IR {
    enum Type {
        TEXT,
        NUMBER,
        FLOAT,
        DELIMITER,
        SYMBOL,
    };

    const char *get_type_name(Type code);

    class Word {
    public:
        std::string text;
        Type type;

        Word(std::string text, Type type);
    };

    class Node {
    public:
        std::list<std::list<Word> *> *nodes;

        Node();
        ~Node();

        void push_back(unsigned long line, Word value);
        void push_back(std::list<Word> *line);

        //friend std::ostream& operator<< (std::ostream &out, const Node& node);
    };
}

std::ostream& operator<< (std::ostream &out, const IR::Node& node);

#endif//_IR_HPP_