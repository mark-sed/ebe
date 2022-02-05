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

Word::Word(std::string text, 
           Type type, 
           Expr::Expression *expr, 
           IR::PassExpression *code, 
           Inst::Instruction *return_inst) 
          : text{text}, type{type}, expr{expr}, code{code}, return_inst{return_inst} {

}

Word::Word(const Word &other){
    // FIXME: Copy the expression as well?
    this->text = other.text;
    this->type = other.type;
}

Word::~Word() {
    if(this->expr != nullptr) {
        delete this->expr;
    }
}

Word& Word::operator=(const Word &other){
    // FIXME: This might not work when expr is set (differently written expr, but same value)
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

template <> int Word::to_int<IR::Type::NUMBER>() {
    return Cast::to<int>(this->text.c_str());
}

template <> float Word::to_float<IR::Type::FLOAT>() {
    return Cast::to<float>(this->text);
}

Node::Node() {
    this->nodes = new std::list<std::list<Word *> *>();
    this->longest_line = nullptr;
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
        if(line == other.longest_line) {
            this->longest_line = line_list;
        }
        nodes->push_back(line_list);
    }
}

Node &Node::operator=(const Node &other){
    this->nodes = new std::list<std::list<Word *> *>();
    for(const auto &line: *(other.nodes)){
        auto line_list = new std::list<Word *>();
        for(const auto &word: *line){
            line_list->push_back(new Word(*word));
        }
        if(line == other.longest_line) {
            this->longest_line = line_list;
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
    if(this->longest_line == nullptr || (*index_line)->size() > this->longest_line->size()) {
        this->longest_line = (*index_line);
    }
}

void Node::push_back(std::list<Word *> *line){
    size_t length = line->size();
    if(this->longest_line == nullptr || length > this->longest_line->size()) {
        this->longest_line = line;
    }
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

Pass::Pass(PassType type) : type{type}, env{}, subpass_table{nullptr}, last_executed_index{-1} {
    if(type == PassType::EXPRESSION_PASS){
        this->pass_name = "Expression";
    }
    else if(type == PassType::WORDS_PASS) {
        this->pass_name = "Words";
    }
    else if(type == PassType::LINES_PASS) {
        this->pass_name = "Lines";
    }
    else {
        this->pass_name = "Documents";
    }
    this->pipeline = new std::vector<Inst::Instruction *>();
}

Pass::Pass(const Pass &other) {
    this->pass_name = other.pass_name;
    this->type = other.type;
    this->env = other.env;
    this->subpass_table = nullptr;
    // Copy subpasses
    if(other.subpass_table != nullptr) {
        subpass_table = new std::vector<IR::Pass *>();
        for(auto subpass: *other.subpass_table){
            IR::Pass *subpass_copy = nullptr;
            if(subpass->get_type() == IR::PassType::EXPRESSION_PASS) {
                subpass_copy = new IR::PassExpression(*dynamic_cast<IR::PassExpression *>(subpass));
            }
            else if(subpass->get_type() == IR::PassType::WORDS_PASS) {
                subpass_copy = new IR::PassWords(*dynamic_cast<IR::PassWords *>(subpass));
            }
            else if(subpass->get_type() == IR::PassType::LINES_PASS) {
                subpass_copy = new IR::PassLines(*dynamic_cast<IR::PassLines *>(subpass));
            }
            else if(subpass->get_type() == IR::PassType::DOCUMENTS_PASS) {
                subpass_copy = new IR::PassDocuments(*dynamic_cast<IR::PassDocuments *>(subpass));
            }
            else {
                Error::error(Error::ErrorCode::INTERNAL, (std::string("Pass of type '")
                            +std::to_string(subpass->get_type())+"' cannot be copies").c_str());
            }
            // Just push_back into vector, push_subpass is only for new ones, because it creates CALL instruction
            subpass_table->push_back(subpass_copy);
        }
    }
    // Copy instructions
    this->pipeline = new std::vector<Inst::Instruction *>();
    for(auto inst: *other.pipeline) {
        this->pipeline->push_back(inst->copy());
    }
    this->last_executed_index = -1;
}

Pass::~Pass(){
    for(auto const &inst: *this->pipeline){
        //delete inst;
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

PassExpression::PassExpression(IR::Type expr_type) : Pass(PassType::EXPRESSION_PASS), expr_type{expr_type} {

}

PassExpression::PassExpression(const PassExpression &other) : Pass(other), expr_type{other.expr_type} {
    
}

void PassExpression::process(IR::Node *text) {

}

void PassExpression::process(IR::Word *word, size_t line, size_t column) {
    auto sym_table = new Vars::SymbolTable(word);
    try {
        for(auto inst: (*this->pipeline)){
            ++line;
            inst->exec(sym_table);
        }
        word->type = sym_table->type_at(0);
        word->text = sym_table->to_string(0);
    } catch (Exception::EbeException *e) {
        Error::error(Error::ErrorCode::RUNTIME, (std::string("Word '")+word->text+"' (line "+std::to_string(line)
            +", column "+ std::to_string(column) +") won't be modified").c_str(), e, false);
    } catch (Exception::EbeException &e) {
        Error::error(Error::ErrorCode::RUNTIME, (std::string("Word '")+word->text+"' (line "+std::to_string(line)
            +", column "+ std::to_string(column) +") won't be modified").c_str(), &e, false);
    }
}

PassWords::PassWords() : Pass(PassType::WORDS_PASS) {

}

PassWords::PassWords(const PassWords &other) : Pass(other) {
    
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
    LOG4("Words pass processing:\n" << *text);
    LOG5("Processing over: " << *this);
    // Reset optimization variables
    this->last_executed_index = -1;
    // Iterate through lines of text
    size_t line_number = 0;
    for(auto line = (*text->nodes).begin(); line != (*text->nodes).end(); ++line){
        ssize_t column = 0;
        env.loop_inst = nullptr;
        bool checked_executable_loop = false;  // Used to detect inf loops
        auto word = (*line)->begin();
        auto prev = word;
        while(word != (*line)->end()) {
            //LOGMAX("Processing word '" << (*word)->text << "'");
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
            // Save column if its bigger than biggest column number so far (for optimization)
            if(static_cast<ssize_t>(column) > this->last_executed_index) {
                this->last_executed_index = column;
            }
            if(this->env.loop_inst == inst || (this->env.loop_inst && column >= this->pipeline->size())){
                // If it was not yet checked, make sure there are actual non-controll instructions in the loop
                if(!checked_executable_loop){
                    bool found = false;
                    // Loop through previous instruction and check if any of them is non-controll
                    for(auto i = pipeline->begin(); *i != this->env.loop_inst; ++i){
                        if(!(*i)->control){
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
            LOGMAX("Current instruction: " << inst->get_name() << "; Current word: " << **word);
            // Check if instruction is subprocess call
            if(inst->get_name() == std::string("CALL")){
                auto index = dynamic_cast<Inst::CALL *>(inst)->get_arg1();
                auto subpass = dynamic_cast<PassExpression *>((*this->subpass_table)[index]);
                // Check if type matches pass type
                if(subpass->expr_type == (*word)->type || subpass->expr_type == IR::Type::DERIVED) {
                    // FIXME: Column isn't letter column, but word number
                    subpass->process(*word, line_number, column);
                    // Reprocess so that return instruction can be executed
                }
                else {
                    // Skip return instruction
                    ++column;
                }
                env.reprocess_obj = true;
            }
            else {
                // Instruction execution
                inst->exec(word, *line, this->env);
            }
            if(!env.reprocess_obj){
                ++word;
            }
            env.reprocess_obj = false;
        }
        ++line_number;
    }
    LOG4("Word pass processing done");
}

PassLines::PassLines() : Pass(PassType::LINES_PASS) {

}

PassLines::PassLines(const PassLines &other) : Pass(other) {

}

void PassLines::process(IR::Node *text) {
    if(this->pipeline->empty()){
        return;
    }
    // Reset optimization variables
    this->last_executed_index = -1;
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
        // Save the biggest instruction index executed for optimizations
        if(static_cast<ssize_t>(column) > this->last_executed_index) {
            this->last_executed_index = column;
        }
        if(this->env.loop_inst == inst || (this->env.loop_inst && column >= this->pipeline->size())){
            // If it was not yet checked, make sure there are actual non-pragma instructions in the loop
            if(!checked_executable_loop){
                bool found = false;
                // Loop through previous instruction and check if any of them is non-pragma
                for(auto i = pipeline->begin(); *i != this->env.loop_inst; ++i){
                    if(!(*i)->control){
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

PassDocuments::PassDocuments() : Pass(PassType::DOCUMENTS_PASS) {
    Error::warning("Document pass is not yet implemented");
}

PassDocuments::PassDocuments(const PassDocuments &other) : Pass(other) {

}

void PassDocuments::process(IR::Node *text) {

}

EbelNode::EbelNode() {
    this->nodes = new std::list<Pass *>();
}

EbelNode::EbelNode(GPEngineParams *params, IR::Node *text_in){
    // Generating randomly filled ebel node for GP engine
    this->nodes = new std::list<Pass *>();

    // Generate amount of passes, if only 1 line is in text_in, then no lines passes are needed
    float lines_pass_chance = text_in->get_lines_count() == 1 ? 0.0f : params->init_pass_lines_chance;
    float words_pass_chance = 1.0f - lines_pass_chance;
    int pass_amount = RNG::rand_int(params->pheno_min_passes, params->pheno_max_passes);

    // Generate passes and its instructions
    for(int i = 0; i < pass_amount; ++i) {
        IR::Pass *pass = nullptr;
        if(RNG::roll(words_pass_chance)) {
            pass = new PassWords();
        }
        else {
            pass = new PassLines();
        }
        int instrs = 0;
        if(pass->type == IR::PassType::WORDS_PASS) {
            instrs = RNG::rand_int(params->min_words_pass_size, params->max_words_pass_size);
        }
        else {
            instrs = RNG::rand_int(params->min_lines_pass_size, params->max_lines_pass_size);
        }
        for(size_t i = 0; i < static_cast<size_t>(instrs); i++){
            auto size = pass->type == IR::PassType::WORDS_PASS ? text_in->get_max_words_count() : text_in->get_lines_count();
            auto inst = Inst::rand_instruction(pass->type, size);
            // Make sure the program does not start with loop
            while(i == 0 && inst->get_name() == Inst::LOOP::NAME){
                delete inst;
                inst = Inst::rand_instruction(pass->type, size);
            }
            pass->push_back(inst);
        }
        this->nodes->push_back(pass);
    }
    LOGMAX("Generated EbelNode: " << *this);
}

EbelNode::EbelNode(const EbelNode &other) {
    this->nodes = new std::list<Pass *>();
    for(auto pass: *other.nodes) {
        // Copy pass
        IR::Pass *pass_copy = nullptr;
        if(pass->get_type() == IR::PassType::WORDS_PASS) {
            pass_copy = new IR::PassWords(*dynamic_cast<IR::PassWords *>(pass));
        }
        else if(pass->get_type() == IR::PassType::LINES_PASS) {
            pass_copy = new IR::PassLines(*dynamic_cast<IR::PassLines *>(pass));
        }
        else if(pass->get_type() == IR::PassType::DOCUMENTS_PASS) {
            pass_copy = new IR::PassDocuments(*dynamic_cast<IR::PassDocuments *>(pass));
        }
        else if(pass->get_type() == IR::PassType::EXPRESSION_PASS) {
            pass_copy = new IR::PassExpression(*dynamic_cast<IR::PassExpression *>(pass));
        }
        else {
            Error::error(Error::ErrorCode::INTERNAL, (std::string("Pass of type '")
                        +std::to_string(pass->get_type())+"' cannot be copies").c_str());
        }
        this->nodes->push_back(pass_copy);
    }
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
        // TODO: Add detail level (using args)
        bool first = true;
        for(auto const *word: node){
            if(!first){
                out << " -> ";
            }
            first = false;
            // Print word's type and value
            out << *word;
        }
        return out;
    }

    std::ostream& format_print_pass(std::ostream &out, const IR::Pass& pass, const char * INDENT){
        out << "PASS ";
        if(pass.type == IR::PassType::EXPRESSION_PASS){
            out << IR::get_type_name(dynamic_cast<const IR::PassExpression &>(pass).expr_type) << " ";
        }
        out << pass.pass_name << std::endl;
        for(auto inst: *pass.pipeline){
            if(inst->get_name() == std::string(Inst::CALL::NAME)){
                out << INDENT;
                // Subpass printing
                size_t index = dynamic_cast<Inst::CALL*>(inst)->get_arg1();
                auto subpass = (*pass.subpass_table)[index];
                format_print_pass(out, *subpass, "    ");
            }
            else {
                out << INDENT << inst->get_name() << " ";
                inst->format_args(out);
                out << std::endl;
            }
        }
        if(pass.type == IR::PassType::EXPRESSION_PASS){
            out << INDENT << "RETURN";
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

    std::ostream& Pass::print_pass_noinline(std::ostream &out, const char *indent) {
        out << "PASS ";
        if(type == IR::PassType::EXPRESSION_PASS){
            out << IR::get_type_name(dynamic_cast<const IR::PassExpression *>(this)->expr_type) << " ";
        }
        out << pass_name << std::endl;
        for(auto inst: *pipeline){
            out << indent << inst->get_name() << " ";
            inst->format_args(out);
            out << std::endl;
        }
        return out;
    }

    std::ostream &IR::EbelNode::dbprint_no_inline(std::ostream &out) {
        for(auto const &pass: *this->nodes){
            pass->print_pass_noinline(out, "  ");
        }
        return out;
    }


    std::ostream& operator<< (std::ostream &out, const IR::Word& word){
        static const std::set<char> NOT_PRINT{' ', '\t', '\v', '\f', '\n'};
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
        return out;
    }
}
