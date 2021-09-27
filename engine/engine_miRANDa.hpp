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

    /**
     * Generates random program based on engine params
     * @return Valid ebel program which is random
     */ 
    IR::EbelNode *random_program();
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
