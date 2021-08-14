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
#include "engine.hpp"
#include "compiler.hpp"
#include "ir.hpp"

#include <iostream>

GPEngineParams default_gpparams {
    .population_size = 10,
    .pheno_min_pass_size = 1,
    .pheno_max_pass_size = 5,
    .pheno_min_passes = 1,
    .pheno_max_passes = 1,
    .init_pass_words_chance = 1.0f,
    .init_pass_lines_chance = 0.0f,
    .init_pass_pages_chance = 0.0f,
};

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

GPEngine::GPEngine(IR::Node *text_in, IR::Node *text_out, const char *engine_name) : 
                   Engine(text_in, text_out, engine_name) {
    params = &default_gpparams;
}

IR::EbelNode *GPEngine::evaluate() {
    for(auto const *pheno: *this->population->candidates){
        
    }
}
