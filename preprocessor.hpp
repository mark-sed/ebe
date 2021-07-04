/**
 * @file preprocessor.hpp
 * @author Marek Sedlacek
 * @date July 2021
 * @copyright Copyright 2021 Marek Sedlacek. All rights reserved.
 * 
 * @brief Prerpocessor for examples
 * 
 * This section is here just in case preprocessor will be added later on
 * it also handles loading of inputs.
 */

#ifndef _PREPROCESSOR_HPP_
#define _PREPROCESSOR_HPP_

#include <vector>
#include "compiler.hpp"

class Preprocessor : public Compiler {
private:
    const char *ex_in;
    const char *ex_out;
    char delim;

    std::vector<std::string> *read_file(const char *file_name);
public:
    Preprocessor(const char *ex_in, const char *ex_out, char delim='\n');
    std::vector<std::string> *process_input();
    std::vector<std::string> *process_output();
};

#endif//_PREPROCESSOR_HPP_