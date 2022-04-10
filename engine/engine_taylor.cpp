/**
 * @file engine_taylor.cpp
 * @author Marek Sedlacek
 * @date April 2022
 * @copyright Copyright 2022 Marek Sedlacek. All rights reserved.
 * 
 * @brief Taylor GP engine
 * 
 * Taylor [NOP tail] engine uses genetic programming for ebel generation, 
 * but only in the form of mutations. Phenotypes start as NOP tails
 * and are mutated into desired program.
 */

#include "engine_taylor.hpp"
#include "arg_parser.hpp"
#include "logging.hpp"
#include "interpreter.hpp"
#include "rng.hpp"

EngineTaylor::EngineTaylor(IR::Node *text_in, IR::Node *text_out) : GPEngine(text_in, text_out, 
                                                                    Args::arg_opts.iterations, 
                                                                    EngineUtils::EngineID::TAYLOR) {
    // Create params
    auto params = new GPEngineParams(text_in, text_out);
    params->crossover_chance = 0.0f;
    params->mutation_chance = 0.4f;
    params->crossover_insert_chance = 0.0f;
    params->crossover_switch_chance = 0.0f;

    params->min_words_pass_size = 1;
    params->max_words_pass_size = text_in->get_max_words_count();

    params->words_occs.CONCAT = 0.0f;
    params->words_occs.DEL    = 0.0f;
    params->words_occs.LOOP   = 0.0f;
    params->words_occs.NOP    = 1.0f;
    params->words_occs.SWAP   = 0.0f;

    params->lines_occs.CONCAT = 0.0f;
    params->lines_occs.DEL    = 0.0f;
    params->lines_occs.LOOP   = 0.0f;
    params->lines_occs.NOP    = 1.0f;
    params->lines_occs.SWAP   = 0.0f;

    set_params(params);
    LOG1("Engine Taylor params:\n" << *params << TAB1 << "iterations = " << iterations);
    // Creates and initializes a new population
    this->population = new GP::Population(params, text_in);

    // Reset occurrences back
    params->words_occs = InstructionOccurrences(IR::PassType::WORDS_PASS);
    params->lines_occs = InstructionOccurrences(IR::PassType::LINES_PASS);
}

EngineTaylor::~EngineTaylor() {

}

/**
 * The process is identical to EngineJenn, but uses only mutations. 
 * 
 * The working principle is as follows:
 *   1. Generate population
 *   2. Evaluate population
 *   3. If perfect phenotype (100 % precision), then end the program
 *   4. Sort the population based on fitness (to make following steps easier)
 *   5. If elitism is set, then leave the first phenotype untouched
 *   6. Do rolls (rng) for mutation
 *   7. Perform mutations on rolled phenotypes
 *   8. If not all iterations have been done, then repeat from step 2
 *   9. Otherwise set precision (fitness) of best phenotype and return this phenotype
 */
IR::EbelNode *EngineTaylor::generate(float *precision) {
    for(size_t iter = 0; iter < iterations; ++iter){
        LOG3(iter << ". iteration started");
        // Eval population
        auto perfect_pheno = this->evaluate(false);
        if(perfect_pheno){
            // 100 % precision found, return
            if(precision){
                *precision = perfect_pheno->fitness; 
            }
            LOG1("Perfect phenotype found in iteration " << iter << " - ending evolution");
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
        STAT_LOG(Analytics::UnitNames::TAYLOR_FITNESS, std::to_string(iter), std::to_string(this->population->candidates->front()->fitness));
        // Mutate
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
            if(RNG::roll(params->mutation_chance)){
                mutate(pheno);
            }
            pheno_number++;
        }
        // Log population every 10 %
        if(iter % (iterations/10) == 0) {
            LOG4("Population after " << iter << " iteration: " << *population);
        }
    }
    this->evaluate(true);
    if(precision){
        // Set precision if pointer is valid
        *precision = this->population->candidates->front()->fitness; 
    }
    LOG1("Taylor engine evolution finished with best fitness " << this->population->candidates->front()->fitness
         << " on phenotype:\n" << *this->population->candidates->front()->program);
    auto best = this->population->candidates->front()->program;
    if(expr_pass != nullptr) {
        // Preappend user defined expressions
        best->nodes->push_front(expr_pass);
    }
    return best;
}