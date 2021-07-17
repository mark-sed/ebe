/**
 * @file compiler.cpp
 * @author Marek Sedlacek
 * @date July 2021
 * @copyright Copyright 2021 Marek Sedlacek. All rights reserved.
 * 
 * @brief Abstract data for all processing units
 * 
 * Every input processing unit should extend processor class
 * so that all needed information and methods are present in it.
 */

#include <cstdlib>
#include <iostream>
#include "compiler.hpp"

const char *Error::get_code_name(Error::ErrorCode c){
    const char *NAMES[] = {
        "None",
        "Unknown",
        "Internal",
        "File access",
        "Arguments",
        "Syntactic"
    };
    constexpr int names_size = sizeof(NAMES)/sizeof(char *);
    if(c < names_size){
        return NAMES[c];
    }
    return "Unknown";
}

[[noreturn]] void Error::error(Error::ErrorCode code, const char *msg){
    std::cerr << "ERROR (" << Error::get_code_name(code) << "): " 
              << msg << "!" << std::endl;
    std::exit(code);
}

[[noreturn]] void Compiler::error(Error::ErrorCode code, const char *file, 
                                  long line, long column, const char *msg){
    if(file)
        // Dont print name if it is nullptr
        std::cerr << file;
    if(line >= 0){
        std::cerr << ":" << line;
        if(column >= 0) {
            std::cerr << ":" << column;
        }
    }
    // FIXME: unit_name probably should not be printed to users
    std::cerr << ":[" << unit_name << "]: ERROR (" << Error::get_code_name(code) << "): " 
              << msg << "!" << std::endl;
    std::exit(code);
}

Compiler::Compiler(const char *unit_name) : unit_name{unit_name} {

}