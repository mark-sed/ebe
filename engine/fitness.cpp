/**
 * @file fitness.cpp
 * @author Marek Sedlacek
 * @date January 2022
 * @copyright Copyright 2022 Marek Sedlacek. All rights reserved.
 * 
 * @brief Fitness functions
 * 
 * Implementations for calculation program fitness.
 */

#include <vector>
#include <algorithm>
#include "fitness.hpp"
#include "ir.hpp"

using namespace Fitness;

float Fitness::one2one(IR::Node *ir1, IR::Node *ir2) {
    // Count how many words are the same (in the same position)
    // Also count the size because size() is not constant complexity
    size_t matched = 0;
    size_t ir1_size = 0;
    size_t ir2_size = 0;
    
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
                // User defined expressions are always a match
                if((*ir1_word)->type == IR::Type::EXPRESSION || (*ir2_word)->type == IR::Type::EXPRESSION){
                    ++matched;
                }
                else if(**ir1_word == **ir2_word){
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

float Fitness::levenshtein(IR::Node *ir1, IR::Node *ir2) {
    // TODO: Move linearization into IR as a method
    // Create new line word to connect IR in matrix
    // TODO: Optimize by having the linearization a static arg in compilation
    IR::Word nl(std::string("\n"), IR::Type::DELIMITER);

    // Move IR into linear version
    std::vector<IR::Word *> ir1_v;
    auto ir1_line = ir1->nodes->begin();
    const auto& ir1_end = ir1->nodes->end();
    size_t ir1_size = 0;
    while(ir1_line != ir1_end){
        // Iterate words in lines
        auto ir1_word = (*ir1_line)->begin();
        const auto& ir1_word_end = (*ir1_line)->end();
        while(ir1_word != ir1_word_end){
            ir1_v.push_back(*ir1_word);
            ir1_word = std::next(ir1_word);
            ++ir1_size;
        }
        ir1_v.push_back(&nl);
        ++ir1_size;
        ir1_line = std::next(ir1_line);
    }

    std::vector<IR::Word *> ir2_v;
    auto ir2_line = ir2->nodes->begin();
    const auto& ir2_end = ir2->nodes->end();
    size_t ir2_size = 0;
    while(ir2_line != ir2_end){
        // Iterate words in lines
        auto ir2_word = (*ir2_line)->begin();
        const auto& ir2_word_end = (*ir2_line)->end();
        while(ir2_word != ir2_word_end){
            ir2_v.push_back(*ir2_word);
            ir2_word = std::next(ir2_word);
            ++ir2_size;
        }
        ir2_v.push_back(&nl);
        ++ir2_size;
        ir2_line = std::next(ir2_line);
    }

    if(ir1_size == 0 && ir2_size == 0) {
        return 1.0f;
    }
    if(ir1_size == 0 || ir2_size == 0) {
        return 0.0f;
    }

    // Distance matrix
    long dist[ir1_size][ir2_size];
    // Fill 1st column and row
    for(long i = 0; i < ir1_size; ++i) {
        dist[i][0] = i;
    }
    for(long i = 0; i < ir2_size; ++i) {
        dist[0][i] = i;
    }

    for(long j = 1; j < ir2_size; ++j) {
        for(long i = 1; i < ir1_size; ++i) {
            long cost = 1;
            if(ir1_v[i]->type == ir2_v[j]->type && ir1_v[i]->text == ir2_v[j]->text) {
                cost = 0;
            }
            dist[i][j] = std::min({dist[i-1][j]+1, dist[i][j-1]+1, dist[i-1][j-1]+cost});
        }
    }

    auto max_l = std::max(ir1_size, ir2_size);
    auto score = dist[ir1_size-1][ir2_size-1];
    return (max_l-score)/static_cast<float>(max_l);
}