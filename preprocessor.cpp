/**
 * @file preprocessor.cpp
 * @author Marek Sedlacek
 * @date July 2021
 * @copyright Copyright 2021 Marek Sedlacek. All rights reserved.
 * 
 * @brief Prerpocessor for examples
 * 
 * This section is here just in case preprocessor will be added later on
 * it also handles loading of inputs.
 */

#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "preprocessor.hpp"
#include "compiler.hpp"

#include <iostream>

Preprocessor::Preprocessor(const char *ex_in, const char *ex_out, char delim) : 
                           Compiler("Preprocessor"), ex_in{ex_in}, ex_out{ex_out} {
    this->delim = delim;
}

std::vector<std::string> *Preprocessor::read_file(const char *file_name){
    std::ifstream f(file_name);
    if(f.fail()){
        error(Error::ErrorCode::FILE_ACCESS, file_name, -1, -1, "Could not open file");
    }
    std::string l;
    auto lines = new std::vector<std::string>();
    while(std::getline(f, l, delim)){
        // Append new line to a line (for scanner to detect end easily)
        lines->push_back(l+"\n");
    }
    return lines;
}

std::vector<std::string> *Preprocessor::process_input(){
    return read_file(this->ex_in);
}

std::vector<std::string> *Preprocessor::process_output(){
    return read_file(this->ex_out);
}