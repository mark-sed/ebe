/**
 * @file engine.hpp
 * @author Marek Sedlacek
 * @date August 2021
 * @copyright Copyright 2021 Marek Sedlacek. All rights reserved.
 * 
 * @brief Engine abstraction for ebel generation
 * 
 * Constains abstractions for all ebel generation engines
 */

#ifndef _ENGINE_HPP_
#define _ENGINE_HPP_

/**
 * Main abstract class that all engines should inherit
 */
class Engine {
public:
    const char *engine_name;  ///< Name of the engine (needed for info printing)
protected:
    /**
     * Constructor
     * @param engine_name Name of the specific engine
     */
    Engine(const char *engine_name);
};

#endif//_ENGINE_HPP_