/**
 * @file gp.cpp
 * @author Marek Sedlacek
 * @date August 2021
 * @copyright Copyright 2021 Marek Sedlacek. All rights reserved.
 * 
 * @brief Genetic programming
 * 
 * All the resources for genetic programming used in GP engines
 */

#include <list>
#include <iostream>
#include <limits>
#include "gp.hpp"
#include "ir.hpp"
#include "engine.hpp"

using namespace GP;

Population::Population(struct GPEngineParams *params) : params(params) {
    this->candidates = new std::list<IR::EbelNode *>();
    this->fitness = new std::list<float>();
    for(size_t i = 0; i < params->population_size; i++){
        this->candidates->push_back(new IR::EbelNode(params));
        this->fitness->push_back(-1*std::numeric_limits<float>::infinity());
    }
}

Population::~Population(){
    for(auto const &pheno: *this->candidates){
        delete pheno;
    }
    delete this->candidates;
}

namespace GP {
    std::ostream& operator<< (std::ostream &out, const GP::Population& popul){
        size_t i = 0;
        for(const auto& c: *popul.candidates){
            // TODO: Add fitness
            out << "# Phenotype " << i++ << " with fitness of << " << ":" << std::endl;
            out << *c << std::endl;
        }
        return out;
    }
}