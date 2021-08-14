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

#include <iostream>

EngineJenn::EngineJenn(IR::Node *text_in, IR::Node *text_out) : GPEngine(text_in, text_out, "Jenn") {
    // Create params
    // TODO: Set the params for the best possible but also following ones specified by the user
    auto params = new GPEngineParams(default_gpparams);
    set_params(params);
    // Creates and initializes a new population
    this->population = new GP::Population(params);
}

EngineJenn::~EngineJenn(){
    delete population;
    delete params;
}

IR::EbelNode *EngineJenn::generate(float *precision){
    // Iterations in an evolution
    for(size_t iter = 0; iter < Args::arg_opts.iterations; ++iter){
        // Eval population
        this->evaluate();
    }
    if(precision){
        //*precision = compare_val; 
    }
    return new IR::EbelNode();
}