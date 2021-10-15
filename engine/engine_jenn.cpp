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

#include "midend/ir.hpp"
#include "engine/engine_jenn.hpp"
#include "engine/engine.hpp"
#include "gp/gp.hpp"
#include "utils/arg_parser.hpp"
#include "utils/rng.hpp"
#include "utils/logging.hpp"

#include <iostream>

EngineJenn::EngineJenn(IR::Node *text_in, IR::Node *text_out) : GPEngine(text_in, text_out, 
                                                                Args::arg_opts.iterations, 
                                                                EngineUtils::EngineID::JENN) {
    // Create params
    // TODO: Set the params for the best possible but also following ones specified by the user
    if(Args::arg_opts.iterations == 0){
        // TODO: Call initialized when implemented and set iterations in case its not set 
        // FIXME: DO NOT HAVE A CONSTANT LIKE THIS use the TODO solution
        iterations = 100;
    }
    auto params = new GPEngineParams(default_gpparams);
    set_params(params);
    LOG1("Engine Jenn params:\n" << *params << TAB1 << "iterations = " << iterations);
    // Creates and initializes a new population
    this->population = new GP::Population(params);
}

EngineJenn::~EngineJenn() {
    delete population;
    delete params;
}

/**
 * The working principle is as follows:
 *   1. Generate population
 *   2. Evaluate population
 *   3. If perfect phenotype (100 % precision), then end the program
 *   4. Sort the population based on fitness (to make following steps easier)
 *   5. If elitism is set, then leave the first phenotype untouched
 *   6. Do rolls (rng) for mutation and crossover
 *   7. Based on set chances and rolled values for mutations and crossovers do them
 *   8. If not all iterations have been done, then repeat from step 2
 *   9. Otherwise set precision (fitness) of best phenotype and return this phenotype
 */
IR::EbelNode *EngineJenn::generate(float *precision) {
    // Iterations in an evolution
    size_t cnt_insert_cross = 0;
    size_t cnt_switch_cross = 0;
    size_t cnt_mutation = 0;
    for(size_t iter = 0; iter < iterations; ++iter){
        LOG3(iter << ". iteration started");
        // Eval population
        auto perfect_pheno = this->evaluate();
        if(perfect_pheno){
            // 100 % precision found, return
            if(precision){
                *precision = perfect_pheno->fitness; 
            }
            LOG1("Perfect phenotype found in iteration " << iter << " - ending evolution");
            LOG1("Evolution statistics:\n" << TAB1 "Iterations: " << iter << "\n" TAB1 "Mutations: " << cnt_mutation 
                 << "\n" TAB1 "Insert crossovers: " << cnt_insert_cross << "\n" TAB1 "Switch crossovers: " << cnt_switch_cross);
            return perfect_pheno->program;
        }
        // Sort population based on fitness
        this->sort_population();
        // Mutate and crossover
        size_t pheno_number = 0;
        for(auto &pheno: *this->population->candidates){
            if(pheno == *this->population->candidates->begin() && params->elitism){
                // In case of elitism no modification should be done to the phenotype
                continue;
            }
            // Try mutate the phenotype
            auto mutate_roll = RNG::roll(params->mutation_chance);
            auto crossover_roll = RNG::roll(params->crossover_chance); // This might be used, depending on params
            if(mutate_roll){
                cnt_mutation++;
                mutate(pheno);
            }
            // Crossover
            if((mutate_roll && !params->no_crossover_when_mutated && crossover_roll)
              || (!mutate_roll && crossover_roll)) {
                if(RNG::roll(params->crossover_insert_chance)){
                    cnt_insert_cross++;
                    crossover_insert(pheno);
                }
                else if(RNG::roll(params->crossover_switch_chance)){
                    cnt_switch_cross++;
                    crossover_switch(pheno);
                }
            }
            pheno_number++;
        }
        // Log population every 10 %
        if(iter % iterations/10 == 0) {
            LOG4("Population after " << iter << " iteration: " << *population);
        }
    }
    this->evaluate();
    if(precision){
        // Set precision if pointer is valid
        *precision = this->population->candidates->front()->fitness; 
    }
    LOG1("Jenn engine evolution finished with best fitness " << this->population->candidates->front()->fitness
         << " on phenotype:\n" << *this->population->candidates->front()->program);
    LOG1("Evolution statistics:\n" << TAB1 "Iterations: " << iterations << "\n" TAB1 "Mutations: " << cnt_mutation 
         << "\n" TAB1 "Insert crossovers: " << cnt_insert_cross << "\n" TAB1 "Switch crossovers: " << cnt_switch_cross);
    return this->population->candidates->front()->program;
}