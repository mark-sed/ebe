/**
 * @file engine_taylor.hpp
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

#ifndef _ENGINE_TAYLOR_HPP_
#define _ENGINE_TAYLOR_HPP_

#include "engine.hpp"

/**
 * NOP tail GP engine
 */
class EngineTaylor : public GPEngine {
public:
    /**
     * Constructor
     */
    EngineTaylor(IR::Node *text_in, IR::Node *text_out);
    /** Destructor */
    ~EngineTaylor();

    IR::EbelNode *generate(float *precision = nullptr) override;
};

#endif//_ENGINE_TAYLOR_HPP_