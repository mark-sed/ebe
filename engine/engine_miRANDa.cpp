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
#include "backend/interpreter.hpp"
#include "arg_parser.hpp"
#include "logging.hpp"
#include "rng.hpp"


EngineMiRANDa::EngineMiRANDa(IR::Node *text_in, IR::Node *text_out) : Engine(text_in, text_out, 
                                                                      Args::arg_opts.iterations, 
                                                                      EngineUtils::EngineID::MIRANDA),
                                                                      lines_occs{IR::PassType::LINES_PASS},
                                                                      words_occs{IR::PassType::WORDS_PASS} {
    if(Args::arg_opts.iterations == 0){
        // TODO: Call initialized when implemented and set iterations in case its not set 
        // FIXME: DO NOT HAVE A CONSTANT LIKE THIS use the TODO solution
        iterations = 100;
    }
    if(Args::arg_opts.expr){
        // TODO: This should be printed only once
        Error::warning("MiRANDa does not support expressions");
    }
    lines_occs.CONCAT =                     0.20f;
    lines_occs.DEL    = lines_occs.CONCAT + 0.20f;
    lines_occs.LOOP   = lines_occs.DEL    + 0.20f;
    lines_occs.NOP    = lines_occs.LOOP   + 0.20f;
    lines_occs.SWAP   = lines_occs.NOP    + 0.20f;

    words_occs.CONCAT =                     0.00f;
    words_occs.DEL    = words_occs.CONCAT + 0.25f;
    words_occs.LOOP   = words_occs.DEL    + 0.25f;
    words_occs.NOP    = words_occs.LOOP   + 0.25f;
    words_occs.SWAP   = words_occs.NOP    + 0.25f;

    // TODO: Set params with initializer when implemented
    this->min_program_size = 0;
    this->max_program_size = 30;
    this->min_passes = 1;
    this->max_passes = 5;
    LOG1(*this);
}

EngineMiRANDa::~EngineMiRANDa() {

}

void EngineMiRANDa::fill_pass(IR::Pass *pass, int size, size_t arg_max) {
    // Get random amount of instructions to generate
    for(int i = 0; i < size; ++i) {
        // Add random instructions
        if(pass->type == IR::PassType::WORDS_PASS) {
            pass->push_back(Inst::rand_instruction(IR::PassType::WORDS_PASS, arg_max, words_occs));
        }
        else {
            pass->push_back(Inst::rand_instruction(IR::PassType::LINES_PASS, arg_max, lines_occs));
        }
    }
} 

IR::EbelNode *EngineMiRANDa::random_program() {
    IR::EbelNode *rnd_prog = new IR::EbelNode();
    auto pass_amount = RNG::rand_int(min_passes, max_passes);
    for(int i = 0; i < pass_amount; ++i) {
        // Generate words pass?
        if(RNG::roll()){
            auto pass = new IR::PassWords();
            fill_pass(pass, RNG::rand_int(min_program_size, max_program_size), this->text_in->get_max_words_count());
            rnd_prog->push_back(pass);
        }
        else {
            // Generate lines pass
            auto pass = new IR::PassLines();
            fill_pass(pass, RNG::rand_int(min_program_size, max_program_size), this->text_in->get_lines_count());
            rnd_prog->push_back(pass);
        }
    }
    return rnd_prog;
}

std::ostream& operator<<(std::ostream &out, const EngineMiRANDa& param) {
    out << "Engine MiRANDa params:" << std::endl
        << TAB1 "iterations = " << param.iterations << std::endl
        << TAB1 "min_program_size = " << param.min_program_size << std::endl
        << TAB1 "max_program_size = " << param.max_program_size << std::endl
        << TAB1 "min_passes = " << param.min_passes << std::endl
        << TAB1 "max_passes = " << param.max_passes << std::endl;
    return out;
}

/**
 * The working principle is as follows:
 *   1. Create new program using random_program method
 *      This method just uses rng to decide on length and instructions in the program
 *   2. Interpret this program
 *   3. Compare how precise is this program
 *   4. If the precision is 100 % return this program
 *   5. Otherwise compare this program to currently the best one and save it if it's better
 *   6. If not all iterations are done, then continue from step 1
 *   7. After all iterations return the best program
 */ 
IR::EbelNode *EngineMiRANDa::generate(float *precision) {
    IR::EbelNode *best_program = nullptr;
    float best_fitness = -1.0f;
    for(size_t iter = 0; iter < iterations; ++iter){
        auto program = random_program();
        // Create interpreter
        auto interpreter = new Interpreter(program);
        IR::Node text_copy = *this->text_in;
        // Interpret
        interpreter->parse(&text_copy);
        delete interpreter;
        float fitness = compare(text_out, &text_copy);
        STAT_LOG(Analytics::UnitNames::MIRANDA_FITNESS, std::to_string(iter), std::to_string(fitness));
        // Check if current program is better than currently the best one
        if(best_program == nullptr || fitness > best_fitness){
            if(best_program != nullptr){
                delete best_program;
            }
            best_program = program;
            best_fitness = fitness;
        }
        else {
            delete program;
        }
        // Log best program every 10 %
        if(iter % iterations/10 == 0) {
            LOG4("Best program with fitness " << best_fitness << " after " << iter << " iteration: " << *best_program);
        }
        if(fitness >= 1.0f){
            // Perfect program found, end generation
            LOG1("Perfect program found in iteration " << iter << " - ending generation");
            break;
        }
    }
    if(precision != nullptr){
        // Set precision if requested
        *precision = best_fitness;
    }
    return best_program;
}
