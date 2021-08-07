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

#include "ir.hpp"
#include "compiler.hpp"

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

};

/** Default GP engine params used in case params are not set by an engine */
extern GPEngineParams default_gpparams;

/**
 * Abstract class for all genetic programming engines
 */
class GPEngine : public Engine {
protected:
    GPEngineParams *params;

    /**
     * Constructor
     * @param engine_name Name of the specific engine
     */
    GPEngine(IR::Node *text_in, IR::Node *text_out, const char *engine_name);
    virtual ~GPEngine() {}
public:

    /* Getter and setters */
    void set_params(GPEngineParams *params) { this->params = params; }
};

#endif//_ENGINE_HPP_