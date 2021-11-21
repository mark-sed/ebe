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
#include "instruction.hpp"
#include "compiler.hpp"
#include "arg_parser.hpp"
#include "rng.hpp"
#include "logging.hpp"

#include <iostream>

using namespace IR;

const char *IR::get_type_name(Type type) {
    const char *NAMES[] = {
        "text",
        "number",
        "float",
        "delim",
        "symbol",
        "expression",
        "empty",
        "derived"
    };
    constexpr int names_size = sizeof(NAMES)/sizeof(char *);
    if(static_cast<int>(type) < names_size){
        return NAMES[type];
    }
    return "none";
}

Word::Word(std::string text, Type type, Expr::Expression *expr) : text{text}, type{type}, expr{expr} {

}

Word::Word(const Word &other){
    // FIXME: This might not work when expr is set (differently written expr, but same value)
    this->text = other.text;
    this->type = other.type;
}

Word::~Word() {
    if(this->expr != nullptr){
        delete this->expr;
    }
}

Word& Word::operator=(const Word &other){
    this->text = other.text;
    this->type = other.type;
    return *this;
}

bool Word::operator==(const Word &other) const {
    return this->type == other.type && this->text == other.text;
}

bool Word::operator!=(const Word &other) const {
    return !(*this == other);
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

Node::Node(const Node &other){
    this->nodes = new std::list<std::list<Word *> *>();
    for(const auto &line: *(other.nodes)){
        auto line_list = new std::list<Word *>();
        for(const auto &word: *line){
            line_list->push_back(new Word(*word));
        }
        nodes->push_back(line_list);
    }
}

Node &Node::operator=(const Node &other){
    for(const auto &line: *(other.nodes)){
        auto line_list = new std::list<Word *>();
        for(const auto &word: *line){
            line_list->push_back(new Word(*word));
        }
        nodes->push_back(line_list);
    }
    return *this;
}

bool Node::operator==(const Node &other) const {
    // Get start and end iterators
    auto start1 = this->nodes->begin();
    auto start2 = other.nodes->begin();
    auto end1 = this->nodes->end();
    auto end2 = other.nodes->end();

    // Iterate lines
    while(start1 != end1 && start2 != end2){
        // Get start and end iterators for words in a line
        auto words_start1 = (*start1)->begin();
        auto words_start2 = (*start2)->begin();
        auto words_end1 = (*start1)->end();
        auto words_end2 = (*start2)->end();
        while(words_start1 != words_end1 && words_start2 != words_end2){
            if(*(*words_start1) != *(*words_start2)){
                // Types or text does not match
                return false;
            }
            // Move to another word
            words_start1 = std::next(words_start1);
            words_start2 = std::next(words_start2);
        }
        if((words_start1 != words_end1) || (words_start2 != words_end2)){
            // Both lines did not reach the end, they are not equal
            return false;
        }

        // Advance pointers (move to another line)
        start1 = std::next(start1);
        start2 = std::next(start2);
    }
    // Make sure that both files have reached the end
    return (start1 == end1) && (start2 == end2);
}

bool Node::operator!=(const Node &other) const {
    return !(*this == other);
}

void Node::push_back(unsigned long line, Word *value){
    while(line >= this->nodes->size()){
        // Create new nodes until requested line is created
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

Pass::Pass(PassType type) : type{type}, env{}, subpass_table{nullptr} {
    if(type == PassType::EXPRESSION){
        this->pass_name = "Expression";
    }
    else if(type == PassType::WORDS) {
        this->pass_name = "Words";
    }
    else if(type == PassType::LINES) {
        this->pass_name = "Lines";
    }
    else {
        this->pass_name = "Documents";
    }
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

void Pass::push_subpass(Pass *subpass) {
    Error::error(Error::ErrorCode::INTERNAL, "Somehow subpass was pushed into non-words pass");
}

void Pass::set_pipeline(std::vector<Inst::Instruction *> *pipeline) {
    this->pipeline = pipeline;
}

PassExpression::PassExpression() : Pass(PassType::EXPRESSION) {

}

void PassExpression::process(IR::Node *text) {
    // TODO: 
}

PassWords::PassWords() : Pass(PassType::WORDS) {

}

void PassWords::push_subpass(Pass *subpass) {
    if(this->subpass_table == nullptr) {
        this->subpass_table = new std::vector<Pass *>();
    }
    // Push into pipeline call to this subpass
    this->pipeline->push_back(new Inst::CALL(this->subpass_table->size()));
    this->subpass_table->push_back(subpass);
}

void PassWords::process(IR::Node *text) {
    // TODO: Consider having similarities in one function
    // FIXME: just LOOP program should not loop infin.
    if(this->pipeline->empty()){
        return;
    }
    LOG1("Words pass processing:\n" << *text);
    // Iterate through lines of text
    for(auto line = (*text->nodes).begin(); line != (*text->nodes).end(); ++line){
        size_t column = 0;
        env.loop_inst = nullptr;
        bool checked_executable_loop = false;  // Used to detect inf loops
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
                // If it was not yet checked, make sure there are actual non-pragma instructions in the loop
                if(!checked_executable_loop){
                    bool found = false;
                    // Loop through previous instruction and check if any of them is non-pragma
                    for(auto i = pipeline->begin(); *i != this->env.loop_inst; ++i){
                        if(!(*i)->pragma){
                            found = true;
                            checked_executable_loop = true;
                        }
                    }
                    if(!found){
                        break;
                    }
                }
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
    LOG1("Word pass processing done");
}

PassLines::PassLines() : Pass(PassType::LINES) {

}

void PassLines::process(IR::Node *text) {
    if(this->pipeline->empty()){
        return;
    }
    size_t column = 0;
    env.loop_inst = nullptr;
    bool checked_executable_loop = false;
    LOG1("Lines pass processing:\n" << *text);
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
            // If it was not yet checked, make sure there are actual non-pragma instructions in the loop
            if(!checked_executable_loop){
                bool found = false;
                // Loop through previous instruction and check if any of them is non-pragma
                for(auto i = pipeline->begin(); *i != this->env.loop_inst; ++i){
                    if(!(*i)->pragma){
                        found = true;
                        checked_executable_loop = true;
                    }
                }
                if(!found){
                    break;
                }
            }
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
    LOG1("Processing done");
}

PassDocuments::PassDocuments() : Pass(PassType::DOCUMENTS) {
    Error::warning("Document pass is not yet implemented");
}

void PassDocuments::process(IR::Node *text) {

}

EbelNode::EbelNode() {
    this->nodes = new std::list<Pass *>();
}

EbelNode::EbelNode(GPEngineParams *params){
    // Generating randomly filled ebel node for GP engine
    this->nodes = new std::list<Pass *>();
    // FIXME: Work with pass chances
    auto pass = new PassWords();
    // FIXME: Get random size_t not int
    auto instrs = RNG::rand_int(params->pheno_min_pass_size, params->pheno_max_pass_size);
    for(size_t i = 0; i < static_cast<size_t>(instrs); i++){
        auto inst = Inst::rand_instruction();
        // Make sure the program does not start with loop
        // TODO: Add this to some checker so that when there are more constraints all are satisfied
        while(i == 0 && inst->get_name() == Inst::LOOP::NAME){
            delete inst;
            inst = Inst::rand_instruction();
        }
        pass->push_back(inst);
    }
    this->nodes->push_back(pass);
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


namespace IR {
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

    std::ostream& format_print_pass(std::ostream &out, const IR::Pass& pass, const char * INDENT){
        out << "PASS " << pass.pass_name << std::endl;
        for(auto inst: *pass.pipeline){
            if(inst->get_name() == std::string(Inst::CALL::NAME)){
                // Subpass printing
                size_t index = dynamic_cast<Inst::CALL*>(inst)->arg1;
                auto subpass = (*pass.subpass_table)[index];
                format_print_pass(out, *subpass, "    ");
            }
            else {
                out << INDENT << inst->get_name() << " ";
                inst->format_args(out);
                out << std::endl;
            }
        }
        return out;
    }

    std::ostream& operator<< (std::ostream &out, const IR::Pass& pass){
        const char * INDENT = "  ";
        return format_print_pass(out, pass, INDENT);
    }

    std::ostream& operator<< (std::ostream &out, const IR::EbelNode& node){
        for(auto const &pass: *node.nodes){
            out << *pass;
        }
        return out;
    }
}
