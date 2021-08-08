/**
 * @file gp.hpp
 * @author Marek Sedlacek
 * @date August 2021
 * @copyright Copyright 2021 Marek Sedlacek. All rights reserved.
 * 
 * @brief Genetic programming
 * 
 * All the resources for genetic programming used in GP engines
 */

#ifndef _GP_HPP_
#define _GP_HPP_

#include <list>
#include <stddef.h>
#include "ir.hpp"
#include "engine.hpp"

struct GPEngineParams;

/** All genetic programming related resourced */
namespace GP {

    /**
     * Population of phenotypes
     */ 
    class Population {
    private:
        GPEngineParams *params;
        std::list<IR::EbelNode *> *candidates;
    public:
        /**
         * Constructor, creates new population
         * @param params GP engine parameters
         */ 
        Population(GPEngineParams *params);
        /** Destructor */
        ~Population();
    };
}

#endif//_GP_HPP_