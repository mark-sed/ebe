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
#include "engine.hpp"
#include "midend/ir.hpp"
#include "backend/compiler.hpp"
#include "backend/interpreter.hpp"
#include "utils/rng.hpp"
#include "utils/logging.hpp"

#include <iostream>

GPEngineParams default_gpparams {
    .population_size = 100,
    .pheno_min_pass_size = 1,
    .pheno_max_pass_size = 3,
    .pheno_min_passes = 1,
    .pheno_max_passes = 1,
    .init_pass_words_chance = 1.0f,
    .init_pass_lines_chance = 0.0f,
    .init_pass_pages_chance = 0.0f,
    .mutation_chance = 0.15f,
    .crossover_chance = 1.0f,    
    .crossover_insert_chance = 0.05f,
    .crossover_switch_chance = 0.6f,      
    .no_crossover_when_mutated = true,
    .elitism = true
};

std::ostream& operator<< (std::ostream &out, const GPEngineParams& param) {
    out << "GPEngineParams:" << std::endl
        << TAB1"population_size = " << param.population_size << std::endl
        << TAB1"pheno_min_pass_size = " << param.pheno_min_pass_size << std::endl
        << TAB1"pheno_max_pass_size = " << param.pheno_max_pass_size << std::endl
        << TAB1"pheno_min_passes = " << param.pheno_min_passes << std::endl
        << TAB1"pheno_max_passes = " << param.pheno_max_passes << std::endl
        << TAB1"init_pass_words_chance = " << param.init_pass_words_chance << std::endl
        << TAB1"init_pass_lines_chance = " << param.init_pass_lines_chance << std::endl
        << TAB1"init_pass_pages_chance = " << param.init_pass_pages_chance << std::endl
        << TAB1"mutation_chance = " << param.mutation_chance << std::endl
        << TAB1"crossover_chance = " << param.crossover_chance << std::endl
        << TAB1"crossover_insert_chance = " << param.crossover_insert_chance << std::endl
        << TAB1"crossover_switch_chance = " << param.crossover_switch_chance << std::endl
        << TAB1"no_crossover_when_mutated = " << param.no_crossover_when_mutated << std::endl
        << TAB1"elitism = " << param.elitism << std::endl;
    return out;
}

Engine::Engine(IR::Node *text_in, IR::Node *text_out, const char *engine_name) : Compiler("Engine"),
                                                                                 engine_name(engine_name),
                                                                                 text_in(text_in), 
                                                                                 text_out(text_out){

}

float Engine::compare(IR::Node *ir1, IR::Node *ir2){
    // Count how many words are the same (in the same position)
    // Also count the size because size() is not constant complexity
    size_t matched = 0;
    size_t ir1_size = 0;
    size_t ir2_size = 0; // Sizes can differ (because of DEL)
    
    // FIXME: Being off by 1 first line makes 0 - diff like system should be used
    auto ir1_line = ir1->nodes->begin();
    auto ir2_line = ir2->nodes->begin();
    const auto& ir1_end = ir1->nodes->end();
    const auto& ir2_end = ir2->nodes->end();
    // While at leas one line is not at the end iterate
    while(!(ir1_line == ir1_end && ir2_line == ir2_end)){
        // Iterate words in lines and compare them
        if(ir1_line != ir1_end && ir2_line != ir2_end){
            auto ir1_word = (*ir1_line)->begin();
            auto ir2_word = (*ir2_line)->begin();
            const auto& ir1_word_end = (*ir1_line)->end();
            const auto& ir2_word_end = (*ir2_line)->end();
            while(ir1_word != ir1_word_end && ir2_word != ir2_word_end){
                if(**ir1_word == **ir2_word){
                    ++matched;
                }
                ir1_word = std::next(ir1_word);
                ++ir1_size;
                ir2_word = std::next(ir2_word);
                ++ir2_size;
            }
            if(ir1_word != ir1_word_end){
                // There were extra words in ir1 line
                ir1_size += std::distance(ir1_word, ir1_word_end);
            }
            else if(ir2_word != ir2_word_end){
                // There were extra words in ir2 line
                ir2_size += std::distance(ir2_word, ir2_word_end);
            }
        }
        else{
            // There are some extra lines, count words in them
            if(ir1_line != ir1_end){
                // There were extra words in ir1 line
                ir1_size += (*ir1_line)->size();
            }
            else if(ir2_line != ir2_end){
                // There were extra words in ir2 line
                ir2_size += (*ir2_line)->size();
            }
        }


        // Increment if still iterating
        if(ir1_line != ir1_end){
            ir1_line = std::next(ir1_line);
        }
        if(ir2_line != ir2_end){
            ir2_line = std::next(ir2_line);
        }
    }

    auto max_size = std::max(ir1_size, ir2_size);
    // Check for sizes so division by 0 does not happen
    if(max_size == 0){
        if(ir1_size == ir2_size){
            // Both empty
            return 1.0f;
        }
        return 0.0f;
    }

    return static_cast<float>(matched) / max_size;
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
    auto old_inst = *rand_inst;
    delete old_inst;
    // FIXME: Use exclude list or some other format when rand_instruction is properly coded
    *rand_inst = Inst::rand_instruction();
}

void GPEngine::crossover_insert(GP::Phenotype *pheno) {
    // TODO: Add option to replace part of the pipeline not just insert
    std::unordered_set<GP::Phenotype *> excl{pheno};
    auto rand_pheno = RNG::rand_list_elem(population->candidates, &excl);
    auto rand_pass = RNG::rand_list_elem((*rand_pheno)->program->nodes, nullptr);
    auto rand_pos = RNG::rand_vect_elem((*rand_pass)->pipeline, nullptr);
    auto rand_pass_og = RNG::rand_list_elem(pheno->program->nodes, nullptr);
    auto rand_pos_og = RNG::rand_vect_elem((*rand_pass_og)->pipeline, nullptr);
    ++rand_pos_og; // Increment iterator because insert inserts before the instruction
    // Get how many instructions to insert
    auto amount = RNG::rand_int(1, std::distance(rand_pos, (*rand_pass)->pipeline->end()));
    //std::cout << "DIST: " << std::distance(rand_pos, (*rand_pass)->pipeline->end()) << "  RND: " << amount << std::endl;
    // TODO: Add logs for crossing
    //std::cout << "CROSSING: \n" << *pheno << **rand_pheno << "---------\n";
    //std::cout << "BEFORE: \n" << *pheno << std::endl;
    for(int i = 0; i < amount; ++i){
        // Create copy of instruction
        auto inst_copy = (*rand_pos)->copy();
        rand_pos_og = (*rand_pass_og)->pipeline->insert(rand_pos_og, inst_copy);
        ++rand_pos;
    }
    //std::cout << "AFTER: \n" << *pheno << std::endl; 
    //std::cout << "-----------\n\n";
}

void GPEngine::crossover_switch(GP::Phenotype *pheno) {
    std::unordered_set<GP::Phenotype *> excl{pheno};
    auto rand_pheno = RNG::rand_list_elem(population->candidates, &excl);
    auto rand_pass = RNG::rand_list_elem((*rand_pheno)->program->nodes, nullptr);
    auto rand_pos = RNG::rand_vect_elem((*rand_pass)->pipeline, nullptr);
    auto rand_pass_og = RNG::rand_list_elem(pheno->program->nodes, nullptr);
    auto rand_pos_og = RNG::rand_vect_elem((*rand_pass_og)->pipeline, nullptr);
    // Get how many instructions to insert
    auto min_len = std::min(std::distance(rand_pos, (*rand_pass)->pipeline->end()), std::distance(rand_pos_og, (*rand_pass_og)->pipeline->end()));
    auto amount = RNG::rand_int(1, min_len);
    //std::cout << "DIST: " << std::distance(rand_pos, (*rand_pass)->pipeline->end()) << "  RND: " << amount << std::endl;
    // TODO: Add logs for crossing
    //std::cout << "CROSSING: \n" << *pheno << **rand_pheno << "---------\n";
    //std::cout << "BEFORE: \n" << *pheno << std::endl << **rand_pheno << "\n";
    for(int i = 0; i < amount; ++i){
        // Create copy of instruction
        std::swap(*rand_pos, *rand_pos_og);
        ++rand_pos;
        ++rand_pos_og;
    }
    //std::cout << "AFTER: \n" << *pheno << std::endl << **rand_pheno << "\n"; 
    //std::cout << "-----------\n\n";
}

GPEngine::GPEngine(IR::Node *text_in, IR::Node *text_out, const char *engine_name) : 
                   Engine(text_in, text_out, engine_name) {
    params = &default_gpparams;
}

GP::Phenotype *GPEngine::evaluate() {
    GP::Phenotype *perfect_program = nullptr;
    for(auto &pheno: *this->population->candidates){
        auto interpreter = new Interpreter(pheno->program);
        IR::Node text_copy = *this->text_in;
        interpreter->parse(&text_copy);
        float fit = compare(text_out, &text_copy);
        // Set the fitness
        pheno->fitness = fit;
        if(fit >= 1.0f){
            // Program which does what it's supposed to do
            perfect_program = pheno;
        }
    }
    return perfect_program;
}
