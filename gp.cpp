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
#include "gp.hpp"
#include "engine.hpp"

using namespace GP;

Population::Population(struct GPEngineParams *params) : params(params) {
    this->candidates = new std::list<IR::EbelNode *>(params->population_size);
}

Population::~Population(){
    for(auto const &pheno: *this->candidates){
        delete pheno;
    }
    delete this->candidates;
}