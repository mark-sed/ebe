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
#include "ir.hpp"
#include "engine.hpp"
#include "gp.hpp"

using namespace GP;

Phenotype::Phenotype(IR::EbelNode *program, float fitness) : program{program}, fitness{fitness} {

}

Population::Population(GPEngineParams *params) : params(params) {
    this->candidates = new std::list<Phenotype *>();
    for(size_t i = 0; i < this->params->population_size; i++){
        this->candidates->push_back(new Phenotype(new IR::EbelNode(this->params)));
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
            out << "# Phenotype " << i++ << " ";
            out << *c;
        }
        return out;
    }

    std::ostream& operator<< (std::ostream &out, const GP::Phenotype& pheno){
        out << "fitness " << pheno.fitness << ":" << std::endl;
        out << *(pheno.program) << std::endl;
        return out;
    }
}
