/**
 * @file ir.cpp
 * @author Marek Sedlacek
 * @date July 2021
 * @copyright Copyright 2021 Marek Sedlacek. All rights reserved.
 * 
 * @brief Intermediate representation
 * 
 * Intermediate representation of text files.
 */

#include <list>
#include <set>
#include <iomanip>
#include "ir.hpp"

using namespace IR;

const char *IR::get_type_name(Type t) {
    const char *NAMES[] = {
        "text",
        "number",
        "float",
        "delim",
        "symbol"
    };
    constexpr int names_size = sizeof(NAMES)/sizeof(char *);
    if(t < names_size){
        return NAMES[t];
    }
    return "none";
}

Word::Word(std::string text, Type type) : text{text}, type{type} {

}

Node::Node() {
    this->nodes = new std::list<std::list<Word> *>();
}

Node::~Node() {
    for(auto const &line: *this->nodes){
        delete line;
    }
    delete nodes;
}

std::ostream& operator<< (std::ostream &out, const Node& node){
    static const std::set NOT_PRINT{' ', '\t', '\v', '\f'};
    // TODO: Add detail level (using args)
    long line_number = 1;
    for(auto const& line: *node.nodes){
        out << std::setfill('0') << std::setw(2) << line_number << ". ";
        bool first = true;
        for(auto const &word: *line){
            if(!first){
                out << " -> ";
            }
            first = false;
            out << "(" << get_type_name(word.type) << ")";
            if((word.type == IR::Type::DELIMITER || word.type == IR::Type::SYMBOL) && 
               (!std::isprint(word.text[0]) || NOT_PRINT.find(word.text[0]) != NOT_PRINT.end())){
                for(auto c: word.text){
                    out << "\\0x" << std::hex << static_cast<int>(c) << std::dec;
                }
            }else{
                out << word.text;
            }
        }
        line_number++;
        out << std::endl;
    }
    return out;
}

void Node::push_back(unsigned long line, Word value){
    if(line-1 >= this->nodes->size()){
        this->nodes->push_back(new std::list<Word>());
    }
    auto index_line = this->nodes->begin();
    std::advance(index_line, line);
    (*index_line)->push_back(value);
}

void Node::push_back(std::list<Word> *line){
    this->nodes->push_back(line);
}