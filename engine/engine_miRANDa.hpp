/**
 * @file engine_miRANDa.hpp
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

#ifndef _ENGINE_MIRANDA_HPP_
#define _ENGINE_MIRANDA_HPP_

#include "engine.hpp"

class EngineMiRANDa : public Engine {
private:
    size_t min_program_size;
    size_t max_program_size;
    size_t min_passes;
    size_t max_passes;

    InstructionOccurrences lines_occs;
    InstructionOccurrences words_occs;

    /**
     * Generates random program based on engine params
     * @return Valid ebel program which is random
     */ 
    IR::EbelNode *random_program();
    /**
     * @brief Fills pass with instructions
     * @param pass Pass type
     * @param size Size of the pass
     * @param arg_max Maximum argument value
     */
    void fill_pass(IR::Pass *pass, int size, size_t arg_max);
public:
    /**
     * Constructor
     */
    EngineMiRANDa(IR::Node *text_in, IR::Node *text_out);
    /** Destructor */
    ~EngineMiRANDa();

    IR::EbelNode *generate(float *precision = nullptr) override;

    friend std::ostream& operator<< (std::ostream &out, const EngineMiRANDa& param);
};

#endif//_ENGINE_MIRANDA_HPP_
