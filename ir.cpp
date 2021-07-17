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

const char *IR::get_type_name(Type type) {
    const char *NAMES[] = {
        "text",
        "number",
        "float",
        "delim",
        "symbol",
        "empty"
    };
    constexpr int names_size = sizeof(NAMES)/sizeof(char *);
    if(type < names_size){
        return NAMES[type];
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

Pass::Pass(const char *pass_name) : pass_name{pass_name} {
    this->pipeline = new std::vector<Inst::Instruction *>();
}

Pass::~Pass(){
    for(auto const &inst: *this->pipeline){
        delete inst;
    }
    delete pipeline;
}

void Pass::push_back(Inst::Instruction *inst){
    this->pipeline->push_back(inst);
}

void Pass::set_pipeline(std::vector<Inst::Instruction *> *pipeline) {
    this->pipeline = pipeline;
}

PassWords::PassWords() : Pass("Words") {

}

PassLines::PassLines() : Pass("Lines") {

}

PassDocuments::PassDocuments() : Pass("Documents") {

}

EbelNode::EbelNode() {
    this->nodes = new std::list<Pass *>();
}

EbelNode::~EbelNode(){
    for(auto const &pass: *this->nodes){
        delete pass;
    }
    // Instructons won't be deleted here, they are singletons
    delete nodes;
}

void EbelNode::push_back(Pass *pass){
    this->nodes->push_back(pass);
}

std::ostream& operator<< (std::ostream &out, const Node& node){
    static const std::set NOT_PRINT{' ', '\t', '\v', '\f', '\n'};
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
            // Print word's type and value
            out << "(" << get_type_name(word.type) << ")";
            if((word.type == IR::Type::DELIMITER || word.type == IR::Type::SYMBOL) && 
               (!std::isprint(word.text[0]) || NOT_PRINT.find(word.text[0]) != NOT_PRINT.end())){
                for(auto c: word.text){
                    // For non printable or not visible charactets print hex value
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

std::ostream& operator<< (std::ostream &out, const std::list<IR::Word>& node){
    static const std::set NOT_PRINT{' ', '\t', '\v', '\f', '\n'};
    // TODO: Add detail level (using args)
    bool first = true;
    for(auto const &word: node){
        if(!first){
            out << " -> ";
        }
        first = false;
        // Print word's type and value
        out << "(" << get_type_name(word.type) << ")";
        if((word.type == IR::Type::DELIMITER || word.type == IR::Type::SYMBOL) && 
            (!std::isprint(word.text[0]) || NOT_PRINT.find(word.text[0]) != NOT_PRINT.end())){
            for(auto c: word.text){
                // For non printable or not visible charactets print hex value
                out << "\\0x" << std::hex << static_cast<int>(c) << std::dec;
            }
        }else{
            out << word.text;
        }
    }
    return out;
}

std::ostream& operator<< (std::ostream &out, const IR::Pass& pass){
    const char * INDENT = "  ";
    out << pass.pass_name << " pass:" << std::endl;
    for(auto inst: *pass.pipeline){
        out << INDENT << inst->get_name() << " ";
        inst->format_args(out);
        out << std::endl;
    }
    return out;
}


std::ostream& operator<< (std::ostream &out, const IR::EbelNode& node){
    for(auto const &pass: *node.nodes){
        out << *pass;
    }
    return out;
}