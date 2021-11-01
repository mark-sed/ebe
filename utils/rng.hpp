/**
 * @file rng.hpp
 * @author Marek Sedlacek
 * @date August 2021
 * @copyright Copyright 2021 Marek Sedlacek. All rights reserved.
 * 
 * @brief RNG resources
 * 
 * All the resources for random number and other random objects generation
 */

#ifndef _RNG_HPP_
#define _RNG_HPP_

#include <ctime>
#include <cstdlib>
#include <list>
#include <vector>
#include <unordered_set>
#include "ir.hpp"
#include "instruction.hpp"
#include "gp.hpp"

namespace RNG {
    /**
     * Initialized rng
     * @param seed When specified with value > 0, then this seed is used for initialization, 
     *             when left out (=0) then std::time is used to initialize.
     */ 
    inline void init(unsigned int seed=0) {
        if(seed == 0){
            std::srand(std::time(0));
        }
        else{
            std::srand(seed);
        }
    }

    // TODO: Make get template function for specified types
    /**
     * Generates random integer
     * @param min Minimal integer value
     * @param max Maximal integer value
     * @return Random number in range from min to max
     */ 
    inline int rand_int(int min=0, int max=RAND_MAX-1) {
        return (std::rand() % (max - min + 1)) + min;
    }

    /**
     * Generates random float
     * @param min Minimal float value
     * @param max Maximal float value
     * @return Random number in range from min to max
     */ 
    inline float rand_float(float min=0.0f, float max=1.0f) {
        float r = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
        return (r * (max - min)) + min;
    }

    /**
     * Bool randomizer based on chance
     * @param chance Chance for roll to succeed
     * @return true if roll succeeded otherwise false
     */ 
    inline bool roll(float chance=0.5) {
        return rand_float() <= chance;
    }

    /**
     * Template function for lists that picks random element in it and returns it
     * @param l List to pick from
     * @param exclude Set of elements to exclude from picking, if nullptr then none are excluded
     * @return Random element from list l
     */ 
    //template<typename T>
    //auto rand_list_elem(std::list<T*> *l, std::unordered_set<T*> *exclude);
    std::list<IR::Pass *>::iterator rand_list_elem(std::list<IR::Pass *> *l, const std::unordered_set<IR::Pass *> *exclude);
    std::list<GP::Phenotype *>::iterator rand_list_elem(std::list<GP::Phenotype *> *l, const std::unordered_set<GP::Phenotype *> *exclude);

    /**
     * Template function for vectors that picks random element in it and returns it
     * @param v Vector to pick from
     * @param exclude Set of elements to exclude from picking, if nullptr then none are excluded
     * @return Random element from vector v
     */ 
    //template<typename T>
    //T *rand_vect_elem(std::vector<T*> *v, std::unordered_set<T*> *exclude);
    std::vector<Inst::Instruction *>::iterator rand_vect_elem(std::vector<Inst::Instruction *> *v, const std::unordered_set<Inst::Instruction *> *exclude);
}

#endif//_RNG_HPP_
