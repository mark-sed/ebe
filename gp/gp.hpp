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
#include <limits>
#include "ir.hpp"
#include "engine.hpp"

// Forward declarations
struct GPEngineParams;

namespace IR {
    class EbelNode;
    class Node;
}

/** All genetic programming related resourced */
namespace GP {

    /**
     * Candidate game representation holding its program and additional attributes
     */ 
    class Phenotype {
    private:
        friend std::ostream& operator<< (std::ostream &out, const GP::Phenotype& pheno);
    public:
        IR::EbelNode *program;  ///< Phenotype's program
        float fitness;          ///< Fitness value

        /** Constructor 
         * @param program Phenotype's program
         * @param fitness Phenotype's fitness (default value is -inf) 
         */
        Phenotype(IR::EbelNode *program, float fitness=-1*std::numeric_limits<float>::infinity());
        ~Phenotype();
    };

    /**
     * Population of phenotypes
     */ 
    class Population {
    private:
        GPEngineParams *params; ///< Evolution parameters
        friend std::ostream& operator<< (std::ostream &out, const GP::Population& popul);
    public:
        std::list<Phenotype *> *candidates;  ///< Candidate programs
        /**
         * Constructor, creates new population
         * @param params GP engine parameters
         * @param text_in Input text to get correct instruction arguments
         */ 
        Population(GPEngineParams *params, IR::Node *text_in);
        /** Destructor */
        ~Population();
    };
}

#endif//_GP_HPP_
