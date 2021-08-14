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
    inline int rand_int(int min=0, int max=RAND_MAX-1){
        return (std::rand() % (max - min + 1)) + min;
    }
}

#endif//_RNG_HPP_