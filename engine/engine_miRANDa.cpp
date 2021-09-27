/**
 * @file engine_miRANDa.cpp
 * @author Marek Sedlacek
 * @date September 2021
 * @copyright Copyright 2021 Marek Sedlacek. All rights reserved.
 * 
 * @brief MiRANDa engine
 * 
 * MiRANDa engine using RANDom walk pro generation.
 * This engine is not supposed to be used in real compilation, for it
 * should perform very badly, but it is made for the purpose of having
 * a comparision in analytics.
 */

#include "engine_miRANDa.hpp"
#include "utils/arg_parser.hpp"
#include "utils/logging.hpp"


EngineMiRANDa::EngineMiRANDa(IR::Node *text_in, IR::Node *text_out) : Engine(text_in, text_out, Args::arg_opts.iterations, "MiRANDa") {
    if(Args::arg_opts.iterations == 0){
        // TODO: Call initialized when implemented and set iterations in case its not set 
        // FIXME: DO NOT HAVE A CONSTANT LIKE THIS use the TODO solution
        iterations = 100;
    }
    LOG1("Engine MiRANDa params:\n" << TAB1 << "iterations = " << iterations);
}

EngineMiRANDa::~EngineMiRANDa() {

}

IR::EbelNode *EngineMiRANDa::generate(float *precision) {

    return new IR::EbelNode();
}