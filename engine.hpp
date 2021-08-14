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

#include <stddef.h>
#include "ir.hpp"
#include "compiler.hpp"
#include "gp.hpp"

// Forward declarations
namespace GP {
    class Population;
}
namespace IR {
    class Node;
    class EbelNode;
}

/**
 * Main abstract class that all engines should inherit
 */
class Engine : public Compiler {
public:
    const char *engine_name;  ///< Name of the engine (needed for info printing)
protected:
    IR::Node *text_in;        ///< IR of input example text
    IR::Node *text_out;       ///< IR of output example text
    
    /**
     * Constructor
     * @param engine_name Name of the specific engine
     */
    Engine(IR::Node *text_in, IR::Node *text_out, const char *engine_name);

    /**
     * Compares 2 text IRs and returns percentage-wise similarity.
     * @param ir1 First IR to compare
     * @param ir2 Second IR to comapre
     * @return How much are ir1 and ir2 similar as a percentage (0-1)
     */ 
    float compare(IR::Node *ir1, IR::Node *ir2);
public:
    /**
     * Through evolution and set params generated new ebel program for input and output passed in at creation
     * @param precision[out] This value will be set to generated code's precision on provided and generated output. 
     *                       When set to nullptr should be ignored.
     * @return Ebel program generated from text_in and text_out
     */ 
    virtual IR::EbelNode *generate(float *precision) = 0;
};

/**
 * Struct used for configuring GP engine's evolution parameters
 */
struct GPEngineParams {
    // TODO: Maybe have this struct nested with more structs and then read it from a json if needed? or perhaps save it to ebel
    size_t population_size;          ///< How many phenotypes should be in a population
    size_t pheno_min_pass_size;      ///< Minimal amount of instructions in one phenotype's pass
    size_t pheno_max_pass_size;      ///< Maximal amount of instructions in one phenotype's pass
    size_t pheno_min_passes;         ///< Minimal amount of passes in one phenotype
    size_t pheno_max_passes;         ///< Maximal amount of passes in one phenotype
    float init_pass_words_chance;    ///< Chance of generating words pass on init
    float init_pass_lines_chance;    ///< Chance of generating lines pass on init
    float init_pass_pages_chance;    ///< Chance of generating pages pass on init
};

/** Default GP engine params used in case params are not set by an engine */
extern GPEngineParams default_gpparams;

/**
 * Abstract class for all genetic programming engines
 */
class GPEngine : public Engine {
protected:
    GPEngineParams *params;
    GP::Population *population;

    /**
     * Constructor
     * @param engine_name Name of the specific engine
     */
    GPEngine(IR::Node *text_in, IR::Node *text_out, const char *engine_name);
    virtual ~GPEngine() {}


    /**
     * Evaluates all the candidates and saves their fitness to fitness list
     * @return Returns a node with 1.0f if present otherwise nullptr
     */ 
    IR::EbelNode *evaluate();
public:

    /* Getter and setters */
    void set_params(GPEngineParams *params) { this->params = params; }
};

#endif//_ENGINE_HPP_