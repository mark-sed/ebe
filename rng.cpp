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
#include "gp.hpp"
#include "instruction.hpp"

#include <iostream>

using namespace RNG;

//FIXME: Template should be generic!!

/*template<typename T>
auto RNG::rand_list_elem(std::list<T*> *l, std::unordered_set<T*> *exclude) {
    auto it = l->begin();
    do{
        it = l->begin();
        auto r = rand_int(0, l->size());
        std::advance(it, r);
    }while(exclude != nullptr && exclude->find(*it) != exclude->end());
    return it;
}*/

//template<>
std::list<IR::Pass *>::iterator RNG::rand_list_elem(std::list<IR::Pass *> *l, const std::unordered_set<IR::Pass *> *exclude) {
    auto it = l->begin();
    do{
        it = l->begin();
        auto r = rand_int(0, l->size()-1);
        std::advance(it, r);
    }while(exclude != nullptr && exclude->find(*it) != exclude->end());
    return it;
}

std::list<GP::Phenotype *>::iterator RNG::rand_list_elem(std::list<GP::Phenotype *> *l, const std::unordered_set<GP::Phenotype *> *exclude) {
    auto it = l->begin();
    do{
        it = l->begin();
        auto r = rand_int(0, l->size()-1);
        std::advance(it, r);
    }while(exclude != nullptr && exclude->find(*it) != exclude->end());
    return it;
}

/*template<typename T>
T *RNG::rand_vect_elem(std::vector<T*> *v, std::unordered_set<T*> *exclude) {
    if(v->size() == 0){
        return nullptr;
    }
    auto r = 0;
    T *elem = nullptr;
    do {
        r = rand_int(0, v->size());
        elem = v->at(r);
    }while(exclude != nullptr && exclude->find(elem) != exclude->end());
    return elem;
}*/

//template<>
std::vector<Inst::Instruction *>::iterator RNG::rand_vect_elem(std::vector<Inst::Instruction *> *v, const std::unordered_set<Inst::Instruction *> *exclude) {
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