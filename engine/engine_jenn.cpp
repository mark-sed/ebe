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
#include "logging.hpp"
#include "interpreter.hpp"

#include <iostream>

EngineJenn::EngineJenn(IR::Node *text_in, IR::Node *text_out) : GPEngine(text_in, text_out, 
                                                                Args::arg_opts.iterations, 
                                                                EngineUtils::EngineID::JENN) {
    // Create params
    auto params = new GPEngineParams(text_in, text_out);
    set_params(params);
    LOG1("Engine Jenn params:\n" << *params << TAB1 << "iterations = " << iterations);
    // Creates and initializes a new population
    this->population = new GP::Population(params, text_in);
}

EngineJenn::~EngineJenn() {
    // Params and population is deleted in GPEngine destructor
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
        // Prune
        for(auto p: *this->population->candidates) {
            for(auto pass: *p->program->nodes) {
                if(pass->pipeline->size() > 2*this->text_in->nodes->front()->size()) {
                    // Free instructions
                    for(size_t i = pass->pipeline->size()/2; i < pass->pipeline->size(); ++i){
                        delete (*pass->pipeline)[i];
                    }
                    pass->pipeline->resize(pass->pipeline->size()/2);
                }
            }
        }
        // Eval population
        auto perfect_pheno = this->evaluate(false);
        if(perfect_pheno){
            // 100 % precision found, return
            if(precision){
                *precision = perfect_pheno->fitness; 
            }
            LOG1("Perfect phenotype found in iteration " << iter << " - ending evolution");
            LOG1("Evolution statistics:\n" << TAB1 "Iterations: " << iter << "\n" TAB1 "Mutations: " << cnt_mutation 
                 << "\n" TAB1 "Insert crossovers: " << cnt_insert_cross << "\n" TAB1 "Switch crossovers: " << cnt_switch_cross);
            if(expr_pass != nullptr) {
                // Preappend user defined expressions
                perfect_pheno->program->nodes->push_front(expr_pass);
            }
            // Reinterpret to optimize
            auto interpreter = new Interpreter(perfect_pheno->program);
            auto text_in_copy = *text_in;
            interpreter->parse(&text_in_copy);
            interpreter->optimize();
            delete interpreter;
            return perfect_pheno->program;
        }
        // Sort population based on fitness
        this->sort_population();
        // Log best fitness
        STAT_LOG(Analytics::UnitNames::JENN_FITNESS, std::to_string(iter), std::to_string(this->population->candidates->front()->fitness));
        // Mutate and crossover
        size_t pheno_number = 0;
        for(auto *pheno: *this->population->candidates){
            if(pheno == *this->population->candidates->begin() && params->elitism){
                // In case of elitism no modification should be done to the phenotype
                continue;
            }
            // Check if fitness matches desired minimum precission
            if(Utils::is_precise(pheno->fitness) || Utils::is_timeout()) {
                if(precision){
                    *precision = pheno->fitness; 
                }
                LOG1("Timeout or phenotype with minimum precision found in iteration " << iter << " - ending evolution");
                LOG1("Evolution statistics:\n" << TAB1 "Iterations: " << iter << "\n" TAB1 "Mutations: " << cnt_mutation 
                    << "\n" TAB1 "Insert crossovers: " << cnt_insert_cross << "\n" TAB1 "Switch crossovers: " << cnt_switch_cross);
                if(expr_pass != nullptr) {
                    // Preappend user defined expressions
                    pheno->program->nodes->push_front(expr_pass);
                }
                // Reinterpret to optimize
                auto interpreter = new Interpreter(pheno->program);
                auto text_in_copy = *text_in;
                interpreter->parse(&text_in_copy);
                interpreter->optimize();
                delete interpreter;
                return pheno->program;
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
    this->evaluate(true);
    if(precision){
        // Set precision if pointer is valid
        *precision = this->population->candidates->front()->fitness; 
    }
    LOG1("Jenn engine evolution finished with best fitness " << this->population->candidates->front()->fitness
         << " on phenotype:\n" << *this->population->candidates->front()->program);
    LOG1("Evolution statistics:\n" << TAB1 "Iterations: " << iterations << "\n" TAB1 "Mutations: " << cnt_mutation 
         << "\n" TAB1 "Insert crossovers: " << cnt_insert_cross << "\n" TAB1 "Switch crossovers: " << cnt_switch_cross);
    auto best = this->population->candidates->front()->program;
    if(expr_pass != nullptr) {
        // Preappend user defined expressions
        best->nodes->push_front(expr_pass);
    }
    return best;
}
