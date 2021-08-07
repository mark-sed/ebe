/**
 * @file engine_jenn.hpp
 * @author Marek Sedlacek
 * @date August 2021
 * @copyright Copyright 2021 Marek Sedlacek. All rights reserved.
 * 
 * @brief Jenn GP engine
 * 
 * Jenn [gen] engine using ~~jennetic~~ genetic programming for ebel generation
 */

#ifndef _ENGINE_JENN_HPP_
#define _ENGINE_JENN_HPP_

#include "engine.hpp"

/**
 * First implemented simple GP engine
 */
class EngineJenn : public GPEngine {
public:
    /**
     * Constructor
     */
    EngineJenn(IR::Node *text_in, IR::Node *text_out);
    /** Destructor */
    ~EngineJenn();

    IR::EbelNode *generate(float *precision = nullptr) override;
};

#endif//_ENGINE_JENN_HPP_