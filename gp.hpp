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
#include <ostream>
#include "ir.hpp"
#include "engine.hpp"

struct GPEngineParams;

namespace IR {
    class EbelNode;
    class Node;
}

/** All genetic programming related resourced */
namespace GP {

    /**
     * Population of phenotypes
     */ 
    class Population {
    private:
        GPEngineParams *params;
        friend std::ostream& operator<< (std::ostream &out, const GP::Population& popul);
    public:
        std::list<IR::EbelNode *> *candidates;
        std::list<float> *fitness;
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