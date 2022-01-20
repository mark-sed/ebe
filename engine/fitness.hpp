/**
 * @file fitness.hpp
 * @author Marek Sedlacek
 * @date January 2022
 * @copyright Copyright 2022 Marek Sedlacek. All rights reserved.
 * 
 * @brief Fitness functions
 * 
 * Implementations for calculation program fitness.
 */

#ifndef _FITNESS_HPP_
#define _FITNESS_HPP_

#include "ir.hpp"

/** Fitness functions */
namespace Fitness {
    
    /**
     * @brief One-to-one mapping 
     * Files are compared word by word in a single pass.
     * Theta(n) complexity.
     * @param ir1 IR of first file
     * @param ir2 IR of second file
     * @return How much are the 2 file similar where 1.0 is identical
     */
    float one2one(IR::Node *ir1, IR::Node *ir2);

    /**
     * @brief Levenshtein distance 
     * Files are compared using Levenshtein distance algorithm
     * Original algorithm - http://www.mathnet.ru/php/archive.phtml?wshow=paper&jrnid=dan&paperid=31411&option_lang=eng
     * @param ir1 IR of first file
     * @param ir2 IR of second file
     * @return How much are the 2 file similar where 1.0 is identical
     */
    float levenshtein(IR::Node *ir1, IR::Node *ir2);

    /**
     * @brief Jaro-Winkler similarity
     * Files are compared using Jaro-Winkler algorithm
     * @param ir1 IR of first file
     * @param ir2 IR of second file
     * @return How much are the 2 file similar where 1.0 is identical
     */
    float jaro_winkler(IR::Node *ir1, IR::Node *ir2);
}

#endif//_FITNESS_HPP_