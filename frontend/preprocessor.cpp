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

Preprocessor::Preprocessor(char delim) : Compiler("Example preprocessor"), delim{delim} {

}

std::istream *Preprocessor::process(const char *file_name){
    // FIXME: delim is not used
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

EbelPreprocessor::EbelPreprocessor() : Compiler("Ebel preprocessor") {

}

std::vector<std::string> *EbelPreprocessor::process(const char *file_name){
    std::string l;
    auto lines = new std::vector<std::string>();
    if(file_name){
        std::ifstream f(file_name);
        if(f.fail()){
            error(Error::ErrorCode::FILE_ACCESS, file_name, -1, -1, "Could not open file");
        }
        while(std::getline(f, l, '\n')){
            // Append new line to a line (for scanner to detect end easily)
            lines->push_back(l+"\n");
        }
    }
    else{
        Error::error(Error::ErrorCode::INTERNAL, "Problems with ebel file");
    }
    return lines;
}