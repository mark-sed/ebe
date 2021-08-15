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

    inline bool roll(float chance) {
        return rand_float() <= chance;
    }
}

#endif//_RNG_HPP_