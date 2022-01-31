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
#include <cmath>
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
    long dist[ir1_size+1][ir2_size+1];
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
            if(*ir1_v[i-1] == *ir2_v[j-1] || ir1_v[i-1]->type == IR::Type::EXPRESSION || 
                ir2_v[j-1]->type == IR::Type::EXPRESSION) {
                cost = 0;
            }
            dist[i][j] = std::min({dist[i-1][j]+1, dist[i][j-1]+1, dist[i-1][j-1]+cost});
        }
    }

    auto max_l = std::max(ir1_size, ir2_size);
    auto score = dist[ir1_size-1][ir2_size-1];
    return (max_l-score)/static_cast<float>(max_l);
}

float Fitness::jaro(IR::Node *ir1, IR::Node *ir2) {
    IR::Word nl(std::string("\n"), IR::Type::DELIMITER);

    // Move IR into linear version
    std::vector<IR::Word *> ir1_v;
    auto ir1_line = ir1->nodes->begin();
    const auto& ir1_end = ir1->nodes->end();
    long ir1_size = 0;
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
    long ir2_size = 0;
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

    long max_dist = std::floor(std::max(ir1_size, ir2_size) / 2) - 1;
    long matches = 0;

    bool ir1_hash[ir1_size] = {false, };
    bool ir2_hash[ir2_size] = {false, };

    for(long i = 0; i < ir1_size; ++i) {
        for(long j = std::max(0L, i - max_dist); j < std::min(ir2_size, i + max_dist + 1); ++j) {
            if(!ir2_hash[j] && *ir1_v[i] == *ir2_v[j] 
                || (!ir2_hash[j] && ir1_v[i]->type == IR::Type::EXPRESSION)
                || (!ir2_hash[j] && ir2_v[j]->type == IR::Type::EXPRESSION)) {
                ir1_hash[i] = true;
                ir2_hash[j] = true;
                ++matches;
                break;
            }
        }
    }

    if(matches == 0)
        return 0.0f;

    long transp = 0;
    long index = 0;

    for(long i = 0; i < ir1_size; ++i) {
        if(ir1_hash[i]) {
            while(!ir2_hash[index]) {
                ++index;
            }
            if(*ir1_v[i] != *ir2_v[index] && ir1_v[i]->type != IR::Type::EXPRESSION && ir2_v[index]->type != IR::Type::EXPRESSION) {
                ++transp;
            }
            ++index;
        }
    }

    float jaro_d = (static_cast<float>(matches) / static_cast<float>(ir1_size)
                 + static_cast<float>(matches) / static_cast<float>(ir2_size)
                 + (static_cast<float>(matches) - (transp / 2.0f)) / (static_cast<float>(matches))) 
                 / 3.0f;
    return jaro_d;
}

float Fitness::jaro_winkler(IR::Node *ir1, IR::Node *ir2) {
    const static float THRESHOLD = 0.70f; 
    const static long MIN_PREFIX = 4;
    
    IR::Word nl(std::string("\n"), IR::Type::DELIMITER);

    // Move IR into linear version
    std::vector<IR::Word *> ir1_v;
    auto ir1_line = ir1->nodes->begin();
    const auto& ir1_end = ir1->nodes->end();
    long ir1_size = 0;
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
    long ir2_size = 0;
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

    long max_dist = std::floor(std::max(ir1_size, ir2_size) / 2) - 1;
    long matches = 0;

    bool ir1_hash[ir1_size] = {false, };
    bool ir2_hash[ir2_size] = {false, };

    for(long i = 0; i < ir1_size; ++i) {
        for(long j = std::max(0L, i - max_dist); j < std::min(ir2_size, i + max_dist + 1); ++j) {
            if(!ir2_hash[j] && *ir1_v[i] == *ir2_v[j] 
                || (!ir2_hash[j] && ir1_v[i]->type == IR::Type::EXPRESSION)
                || (!ir2_hash[j] && ir2_v[j]->type == IR::Type::EXPRESSION)) {
                ir1_hash[i] = true;
                ir2_hash[j] = true;
                ++matches;
                break;
            }
        }
    }

    if(matches == 0)
        return 0.0f;

    long transp = 0;
    long index = 0;

    for(long i = 0; i < ir1_size; ++i) {
        if(ir1_hash[i]) {
            while(!ir2_hash[index]) {
                ++index;
            }
            if(*ir1_v[i] != *ir2_v[index] && ir1_v[i]->type != IR::Type::EXPRESSION && ir2_v[index]->type != IR::Type::EXPRESSION) {
                ++transp;
            }
            ++index;
        }
    }

    float jaro_d = (static_cast<float>(matches) / static_cast<float>(ir1_size)
                 + static_cast<float>(matches) / static_cast<float>(ir2_size)
                 + (static_cast<float>(matches) - (transp / 2.0f)) / (static_cast<float>(matches))) 
                 / 3.0f;

    if(jaro_d < THRESHOLD || jaro_d >= 1.0f) {
        return jaro_d;
    }

    // Jaro-Winkler part
    long prefix = 0;

    for(long i = 0; i < std::min(ir1_size, ir2_size); ++i) {
        if(*ir1_v[i] == *ir2_v[i] || ir1_v[i]->type == IR::Type::EXPRESSION || ir2_v[i]->type == IR::Type::EXPRESSION) {
            ++prefix;
        }
        else {
            break;
        }
    }

    prefix = std::min(MIN_PREFIX, prefix);

    float jaro_wink_d = jaro_d + 0.1 * prefix * (1 - jaro_d);
    return jaro_wink_d;
}
