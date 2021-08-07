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

EngineJenn::EngineJenn(IR::Node *text_in, IR::Node *text_out) : GPEngine(text_in, text_out, "Jenn") {
    // Create params
    auto params = new GPEngineParams{
        
    };
    set_params(params);
}

EngineJenn::~EngineJenn(){
    delete params;
}

IR::EbelNode *EngineJenn::generate(float *precision){
    auto program = new IR::EbelNode();
    
    //auto compare_val = compare();
    if(precision){
        //*precision = compare_val; 
    }
    return program;
}