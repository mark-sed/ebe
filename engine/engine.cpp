/**
 * @file engine.cpp
 * @author Marek Sedlacek
 * @date August 2021
 * @copyright Copyright 2021 Marek Sedlacek. All rights reserved.
 * 
 * @brief Engine abstraction for ebel generation
 * 
 * Constains abstractions for all ebel generation engines
 */

#include <stddef.h>
#include <iterator>
#include <algorithm>
#include <list>
#include <unordered_set>
#include <vector>
#include <utility>
#include "engine.hpp"
#include "ir.hpp"
#include "compiler.hpp"
#include "interpreter.hpp"
#include "rng.hpp"
#include "logging.hpp"
#include "arg_parser.hpp"

#include <iostream>

using namespace EngineUtils;

std::ostream& operator<< (std::ostream &out, const GPEngineParams& param) {
    out << "GPEngineParams:" << std::endl
        << TAB1"population_size = " << param.population_size << std::endl
        << TAB1"min_words_pass_size = " << param.min_words_pass_size << std::endl
        << TAB1"max_words_pass_size = " << param.max_words_pass_size << std::endl
        << TAB1"min_lines_pass_size = " << param.min_lines_pass_size << std::endl
        << TAB1"max_lines_pass_size = " << param.max_lines_pass_size << std::endl
        << TAB1"pheno_min_passes = " << param.pheno_min_passes << std::endl
        << TAB1"pheno_max_passes = " << param.pheno_max_passes << std::endl
        << TAB1"init_pass_words_chance = " << param.init_pass_words_chance << std::endl
        << TAB1"init_pass_lines_chance = " << param.init_pass_lines_chance << std::endl
        << TAB1"mutation_chance = " << param.mutation_chance << std::endl
        << TAB1"crossover_chance = " << param.crossover_chance << std::endl
        << TAB1"crossover_insert_chance = " << param.crossover_insert_chance << std::endl
        << TAB1"crossover_switch_chance = " << param.crossover_switch_chance << std::endl
        << TAB1"no_crossover_when_mutated = " << param.no_crossover_when_mutated << std::endl
        << TAB1"elitism = " << param.elitism << std::endl;
    return out;
}

GPEngineParams::GPEngineParams(IR::Node *f_in, IR::Node *f_out) : population_size{50},
                                                                  min_words_pass_size{1},
                                                                  max_words_pass_size{5},
                                                                  min_lines_pass_size{1},
                                                                  max_lines_pass_size{3},
                                                                  pheno_min_passes{1},
                                                                  pheno_max_passes{4},
                                                                  init_pass_words_chance{0.8f},
                                                                  init_pass_lines_chance{0.2f},
                                                                  mutation_chance{0.15f},
                                                                  crossover_chance{1.0f},    
                                                                  crossover_insert_chance{0.05f},
                                                                  crossover_switch_chance{0.6f},      
                                                                  no_crossover_when_mutated{true},
                                                                  elitism{true} {
    // Change other values if needed be
    // For one line examples, there is no need for Lines pass
    if(f_in->nodes->size() == 1 && f_out->nodes->size() == 1) {
        this->init_pass_lines_chance = 0.0f;
        this->init_pass_words_chance = 1.0f;
    }
    // Set correct lines pass arguments based on lines values
    else {
        // If there is a lot of lines, then set bigger chance for lines pass
        if(f_in->nodes->size() > 10) {
            this->init_pass_lines_chance = 0.5f;
            this->init_pass_words_chance = 0.5f;
        }
    }
    // Compare input and output to guess how many changes will be needed
    float similarity = Fitness::one2one(f_in, f_out);
    if(similarity > 0.90f) {
        pheno_max_passes = 2;
        max_words_pass_size = 3;
        max_lines_pass_size = 2;
    }
    else if(similarity > 0.75f) {
        pheno_max_passes = 3;
        max_words_pass_size = 5;
        max_lines_pass_size = 3;
    }
    else if(similarity > 0.50f) {
        pheno_max_passes = 4;
        min_words_pass_size = 4;
        max_words_pass_size = 10;
        max_lines_pass_size = 4;
    }
    else {
        pheno_max_passes = 5;
        min_words_pass_size = 5;
        max_words_pass_size = 15;
        max_lines_pass_size = 6;
    }
    // Adjust max pass size to the input (no need for more instructions than input objects)
    if(max_lines_pass_size > f_in->nodes->size()) {
        max_lines_pass_size = f_in->nodes->size();
    }
    if(max_words_pass_size > f_in->longest_line->size()) {
        max_words_pass_size = f_in->longest_line->size();
    }
    // Set population size
    if(Args::arg_opts.population_size > 0) {
        this->population_size = Args::arg_opts.population_size;
    }
}

namespace EngineUtils {
    const TEngineInfo ENGINE_NAMES = TEngineInfo{
        std::pair<EngineID, const char *>(EngineID::JENN, "Jenn"),
        std::pair<EngineID, const char *>(EngineID::MIRANDA, "MiRANDa")
    };
}

EngineUtils::EngineID EngineUtils::get_engine_id(const char *name){
    for(auto &e: EngineUtils::ENGINE_NAMES) {
        if(Utils::to_upper(e.second) == Utils::to_upper(name)){
            return e.first;
        }
    }
    return EngineID::UNKNOWN;
}

const char *EngineUtils::get_engine_name(EngineID id){
    for(auto &e: EngineUtils::ENGINE_NAMES) {
        if(e.first == id){
            return e.second;
        }
    }
    return "Unknown";
}

Engine::Engine(IR::Node *text_in, IR::Node *text_out, size_t iterations, EngineUtils::EngineID engine_id) : Compiler("Engine"),
                                                                                                            engine_id(engine_id),
                                                                                                            text_in(text_in), 
                                                                                                            text_out(text_out),
                                                                                                            iterations(iterations) {
    this->engine_name = EngineUtils::get_engine_name(this->engine_id);
}

float Engine::compare(IR::Node *ir1, IR::Node *ir2){
    return Args::arg_opts.fit_fun(ir1, ir2);
}

GPEngine::~GPEngine() {
    delete params;
    delete population;
    // Don't delete expression pass
}

void GPEngine::sort_population() {
    this->population->candidates->sort([](auto a, auto b){ return a->fitness > b->fitness; });
}

void GPEngine::mutate(GP::Phenotype *pheno) {
    // TODO: Add option to specify pass
    // TODO: Add option to mutate arguments in instructions that take them
    // TODO: Add logs
    auto rand_pass = RNG::rand_list_elem(pheno->program->nodes, nullptr);
    auto rand_inst = RNG::rand_vect_elem((*rand_pass)->pipeline, nullptr);
    /*// Dont mutate CALLs
    if((*rand_inst)->get_name() == std::string("CALL")) {
        return;
    }*/
    auto old_inst = *rand_inst;
    delete old_inst;
    auto pass_size = this->text_in->get_max_words_count();
    if((*rand_pass)->type == IR::PassType::LINES_PASS) {
        pass_size = this->text_in->get_lines_count();
    }
    *rand_inst = Inst::rand_instruction((*rand_pass)->type, pass_size);
}

void GPEngine::crossover_insert(GP::Phenotype *pheno) {
    // TODO: Add option to replace part of the pipeline not just insert
    if(pheno->program->nodes->empty()) {
        return;
    }
    std::unordered_set<GP::Phenotype *> excl{pheno};
    auto rand_pheno = RNG::rand_list_elem(population->candidates, &excl);
    if((*rand_pheno)->program->nodes->empty()) {
        return;
    }
    auto rand_pass = RNG::rand_list_elem((*rand_pheno)->program->nodes, nullptr);
    if((*rand_pass)->pipeline->empty()) {
        return;
    }
    auto rand_pos = RNG::rand_vect_elem((*rand_pass)->pipeline, nullptr);

    std::unordered_set<IR::Pass *> excl_pass{};
    auto rand_pass_og = RNG::rand_list_elem(pheno->program->nodes, (*rand_pass)->type, &excl_pass);
    if(rand_pass_og == pheno->program->nodes->end() || (*rand_pass_og)->pipeline->empty()) {
        return;
    }
    auto rand_pos_og = RNG::rand_vect_elem((*rand_pass_og)->pipeline, nullptr);
    ++rand_pos_og; // Increment iterator because insert inserts before the instruction
    // Get how many instructions to insert
    auto amount = RNG::rand_int(1, std::distance(rand_pos, (*rand_pass)->pipeline->end()));
    // TODO: Add logs for crossing
    for(int i = 0; i < amount; ++i){
        // Create copy of instruction
        auto inst_copy = (*rand_pos)->copy();
        rand_pos_og = (*rand_pass_og)->pipeline->insert(rand_pos_og, inst_copy);
        ++rand_pos;
    }
}

void GPEngine::crossover_switch(GP::Phenotype *pheno) {
    if(pheno->program->nodes->empty()) {
        return;
    }
    std::unordered_set<GP::Phenotype *> excl{pheno};
    auto rand_pheno = RNG::rand_list_elem(population->candidates, &excl);
    if((*rand_pheno)->program->nodes->empty()) {
        return;
    }
    auto rand_pass = RNG::rand_list_elem((*rand_pheno)->program->nodes, nullptr);
    if((*rand_pass)->pipeline->empty()) {
        return;
    }
    auto rand_pos = RNG::rand_vect_elem((*rand_pass)->pipeline, nullptr);
    
    std::unordered_set<IR::Pass *> excl_pass{};
    auto rand_pass_og = RNG::rand_list_elem(pheno->program->nodes, (*rand_pass)->type, &excl_pass);
    if(rand_pass_og == pheno->program->nodes->end() || (*rand_pass_og)->pipeline->empty()) {
        return;
    }
    auto rand_pos_og = RNG::rand_vect_elem((*rand_pass_og)->pipeline, nullptr);

    // Get how many instructions to insert
    auto min_len = std::min(std::distance(rand_pos, (*rand_pass)->pipeline->end()), std::distance(rand_pos_og, (*rand_pass_og)->pipeline->end()));
    auto amount = RNG::rand_int(1, min_len);
    // If the second phenotype is the elite and elitism is used then dont switch
    if(*rand_pheno == population->candidates->front()) {
        // Just copy in this case
        for(int i = 0; i < amount; ++i){
            // Create copy of instruction
            auto inst_copy = (*rand_pos)->copy();
            rand_pos_og = (*rand_pass_og)->pipeline->insert(rand_pos_og, inst_copy);
            ++rand_pos;
        }
    }
    else {
        // TODO: Add logs for crossing
        for(int i = 0; i < amount; ++i){
            // Create copy of instruction
            std::swap(*rand_pos, *rand_pos_og);
            ++rand_pos;
            ++rand_pos_og;
        }
    }
}

GPEngine::GPEngine(IR::Node *text_in, IR::Node *text_out, size_t iterations, EngineUtils::EngineID engine_id) : 
                   Engine(text_in, text_out, iterations, engine_id), expr_pass{nullptr} {
    // Checking input text if it contains expression to do those first
    if(Args::arg_opts.expr){
        bool contains_expr = false;
        auto w_pass = new IR::PassWords();
        auto line1 = (text_out->nodes)->begin();
        // Check only first line
        // FIXME: When line subpasses are implemented check more than just first line
        if(line1 != (text_out->nodes)->end()){
            int index = 0;
            for(auto word: **line1) {
                if(word->type == IR::Type::EXPRESSION) {
                    if(word->code != nullptr && word->return_inst != nullptr) {
                        w_pass->push_subpass(word->code);
                        w_pass->push_back(word->return_inst);
                        contains_expr = true;
                    }
                    else {
                        Error::error(Error::ErrorCode::INTERNAL, std::string("Somehow expression code was not"
                        " generated for '"+word->text).c_str());
                    }
                }
                else {
                    w_pass->push_back(new Inst::NOP());
                }
            }
        }
        // Append pass to phenotype
        if(contains_expr){
            this->expr_pass = w_pass;
        }
    }
}

GP::Phenotype *GPEngine::evaluate(bool run_time_optimize) {
    GP::Phenotype *perfect_program = nullptr;
    for(auto &pheno: *this->population->candidates){
        // If expression is set then insert it at the begining
        auto interpreter = new Interpreter(pheno->program);
        IR::Node *text_copy = new IR::Node(*this->text_in);
        interpreter->parse(text_copy);
        if(run_time_optimize) {
            // Run optimizations
            interpreter->optimize();
        }
        float fit = compare(text_out, text_copy);
        // Set the fitness
        pheno->fitness = fit;
        if(fit >= 1.0f){
            // Program which does what it's supposed to do
            perfect_program = pheno;
            break;
        }
        delete text_copy;
        delete interpreter;
    }
    return perfect_program;
}
