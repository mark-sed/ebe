/**
 * @file engine_jenn.cpp
 * @author Marek Sedlacek
 * @date August 2021
 * @copyright Copyright 2021 Marek Sedlacek. All rights reserved.
 * 
 * @brief Jenn GP engine
 * 
 * Jenn [gen] engine using ~~jennetic~~ genetic programming for ebel generation
 */

#include "engine_jenn.hpp"
#include "ir.hpp"
#include "engine.hpp"
#include "gp.hpp"
#include "arg_parser.hpp"
#include "rng.hpp"

#include <iostream>

EngineJenn::EngineJenn(IR::Node *text_in, IR::Node *text_out) : GPEngine(text_in, text_out, "Jenn") {
    // Create params
    // TODO: Set the params for the best possible but also following ones specified by the user
    auto params = new GPEngineParams(default_gpparams);
    set_params(params);
    // Creates and initializes a new population
    this->population = new GP::Population(params);
}

EngineJenn::~EngineJenn() {
    delete population;
    delete params;
}

void EngineJenn::mutate(GP::Phenotype *pheno) {
    // TODO: Implement
}

IR::EbelNode *EngineJenn::generate(float *precision) {
    // Iterations in an evolution
    for(size_t iter = 0; iter < Args::arg_opts.iterations; ++iter){
        // Eval population
        auto perfect_pheno = this->evaluate();
        if(perfect_pheno){
            // 100 % precision found, return
            if(precision){
                *precision = perfect_pheno->fitness; 
            }
            return perfect_pheno->program;
        }
        // Mutate and crossover
        for(auto &pheno: *this->population->candidates){
            // Try mutate the phenotype
            if(RNG::roll(params->mutation_chance)){
                mutate(pheno);
            }
        }
    }
    std::cout << *population;
    if(precision){
        //*precision = compare_val; 
    }
    return new IR::EbelNode();
}