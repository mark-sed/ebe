/**
 * @file rng.cpp
 * @author Marek Sedlacek
 * @date August 2021
 * @copyright Copyright 2021 Marek Sedlacek. All rights reserved.
 * 
 * @brief RNG resources
 * 
 * All the resources for random number and other random objects generation
 */

#include <iterator>
#include "rng.hpp"
#include "ir.hpp"
#include "instruction.hpp"
#include "gp.hpp"

#include <iostream>

using namespace RNG;

std::list<IR::Pass *>::iterator RNG::rand_list_elem(std::list<IR::Pass *> *l, 
                                                    const std::unordered_set<IR::Pass *> *exclude) {
    auto it = l->begin();
    do{
        it = l->begin();
        auto r = rand_int(0, l->size()-1);
        std::advance(it, r);
    }while(exclude != nullptr && exclude->find(*it) != exclude->end());
    return it;
}

std::list<IR::Pass *>::iterator RNG::rand_list_elem(std::list<IR::Pass *> *l, 
                                                    IR::PassType request_type, 
                                                    std::unordered_set<IR::Pass *> *exclude) {
    
    for(auto *pass: *l) {
        if(pass->type != request_type) {
            exclude->insert(pass);
        }
    }
    if(exclude->size() == l->size())
        return l->end();
    return rand_list_elem(l, exclude);
}

std::list<GP::Phenotype *>::iterator RNG::rand_list_elem(std::list<GP::Phenotype *> *l, 
                                                         const std::unordered_set<GP::Phenotype *> *exclude) {
    auto it = l->begin();
    do{
        it = l->begin();
        auto r = rand_int(0, l->size()-1);
        std::advance(it, r);
    }while(exclude != nullptr && exclude->find(*it) != exclude->end());
    return it;
}

std::vector<Inst::Instruction *>::iterator RNG::rand_vect_elem(std::vector<Inst::Instruction *> *v, 
                                                               const std::unordered_set<Inst::Instruction *> *exclude) {
    if(v->size() == 0){
        return v->begin();
    }
    auto r = 0;
    auto elem = v->begin();
    do {
        r = rand_int(0, v->size()-1);
        elem = v->begin() + r;
    }while(exclude != nullptr && exclude->find(*elem) != exclude->end());
    return elem;
}
