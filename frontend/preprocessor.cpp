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

Preprocessor::Preprocessor() : Compiler("Preprocessor") {

}

std::istream *Preprocessor::process(const char *file_name){
    if(file_name){
        auto f = new std::ifstream(file_name);
        if(f->fail()){
            error(Error::ErrorCode::FILE_ACCESS, file_name, -1, -1, "Could not open file");
        }
        return f;
    }
    else{
        return &std::cin;
    }
}
