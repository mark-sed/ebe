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
#include <sstream>
#include <string>
#include <iterator>
#include "ir.hpp"
#include "arg_parser.hpp"
#include "instruction.hpp"
#include "compiler.hpp"

#include <iostream>

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
    this->nodes = new std::list<std::list<Word *> *>();
}

Node::~Node() {
    for(auto const &line: *this->nodes){
        for(auto const &word: *line){
            delete word;
        }
        delete line;
    }
    delete nodes;
}

void Node::push_back(unsigned long line, Word *value){
    if(line-1 >= this->nodes->size()){
        this->nodes->push_back(new std::list<Word *>());
    }
    auto index_line = this->nodes->begin();
    std::advance(index_line, line);
    (*index_line)->push_back(value);
}

void Node::push_back(std::list<Word *> *line){
    this->nodes->push_back(line);
}

std::string Node::output(){
    std::stringstream out;
    for(auto const& line: *(this->nodes)){
        for(auto const *word: *line){
            out << word->text;
        }
        out << Args::arg_opts.line_delim;
    }
    return out.str();
}

Pass::Pass(const char *pass_name) : pass_name{pass_name}, env{} {
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

void PassWords::process(IR::Node *text) {
    // TODO: Consider having similarities in one function
    if(this->pipeline->empty()){
        return;
    }
    // Iterate through lines of text
    for(auto line = (*text->nodes).begin(); line != (*text->nodes).end(); ++line){
        size_t column = 0;
        env.loop_inst = nullptr;
        for(auto word = (*line)->begin(); word != (*line)->end(); ++word){
            // Break when not looping and there are no more instructions for the line
            if(!this->env.loop_inst && column >= this->pipeline->size()){
                break;
            }
            else if(this->env.loop_inst && column >= this->pipeline->size()){
                // This control has to be here in case loop is the last instruction
                column = 0;
            }
            Inst::Instruction *inst = (*this->pipeline)[column];
            // To make sure loops are not executed on the first pass the loop control is before instruction execution
            ++column;
            if(this->env.loop_inst == inst || (this->env.loop_inst && column >= this->pipeline->size())){
                // In a loop
                column = 0;
            }
            // Instruction execution
            inst->exec(word, *line, this->env);
            if(env.reprocess_obj){
                --word;
                env.reprocess_obj = false;
            }
        }
    }
}

PassLines::PassLines() : Pass("Lines") {

}

void PassLines::process(IR::Node *text) {
    if(this->pipeline->empty()){
        return;
    }
    size_t column = 0;
    env.loop_inst = nullptr;
    // Iterate through lines of text
    for(auto line = (*text->nodes).begin(); line != (*text->nodes).end(); ++line){
        // Break when not looping and there are no more instructions for the line
        if(!this->env.loop_inst && column >= this->pipeline->size()){
            break;
        }
        else if(this->env.loop_inst && column >= this->pipeline->size()){
            // This control has to be here in case loop is the last instruction
            column = 0;
        }
        Inst::Instruction *inst = (*this->pipeline)[column];
        // To make sure loops are not executed on the first pass the loop control is before instruction execution
        ++column;
        if(this->env.loop_inst == inst || (this->env.loop_inst && column >= this->pipeline->size())){
            // In a loop
            column = 0;
        }
        // Instruction execution
        inst->exec(line, text->nodes, this->env);
        if(env.reprocess_obj){
            --line;
            env.reprocess_obj = false;
        }
    }
    
}

PassDocuments::PassDocuments() : Pass("Documents") {
    //Error::warning("Document pass is not yet implemented");
}

void PassDocuments::process(IR::Node *text) {

}

EbelNode::EbelNode() {
    this->nodes = new std::list<Pass *>();
}

EbelNode::~EbelNode(){
    for(auto const &pass: *this->nodes){
        delete pass;
    }
    delete nodes;
}

void EbelNode::push_back(Pass *pass){
    this->nodes->push_back(pass);
}

bool operator==(IR::Word &lhs, IR::Word &rhs){
    return lhs.text == rhs.text;
}

std::ostream& operator<< (std::ostream &out, const Node& node){
    static const std::set<char> NOT_PRINT{' ', '\t', '\v', '\f', '\n'};
    // TODO: Add detail level (using args)
    long line_number = 1;
    for(auto const& line: *node.nodes){
        out << std::setfill('0') << std::setw(2) << line_number << ". ";
        bool first = true;
        for(auto const *word: *line){
            if(!first){
                out << " -> ";
            }
            first = false;
            // Print word's type and value
            out << "(" << get_type_name(word->type) << ")";
            if((word->type == IR::Type::DELIMITER || word->type == IR::Type::SYMBOL) && 
               (!std::isprint(word->text[0]) || NOT_PRINT.find(word->text[0]) != NOT_PRINT.end())){
                for(auto c: word->text){
                    // For non printable or not visible charactets print hex value
                    out << "\\0x" << std::hex << static_cast<int>(c) << std::dec;
                }
            }else{
                out << word->text;
            }
        }
        line_number++;
        out << std::endl;
    }
    return out;
}

std::ostream& operator<< (std::ostream &out, const std::list<IR::Word *>& node){
    static const std::set<char> NOT_PRINT{' ', '\t', '\v', '\f', '\n'};
    // TODO: Add detail level (using args)
    bool first = true;
    for(auto const *word: node){
        if(!first){
            out << " -> ";
        }
        first = false;
        // Print word's type and value
        out << "(" << get_type_name(word->type) << ")";
        if((word->type == IR::Type::DELIMITER || word->type == IR::Type::SYMBOL) && 
            (!std::isprint(word->text[0]) || NOT_PRINT.find(word->text[0]) != NOT_PRINT.end())){
            for(auto c: word->text){
                // For non printable or not visible charactets print hex value
                out << "\\0x" << std::hex << static_cast<int>(c) << std::dec;
            }
        }else{
            out << word->text;
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