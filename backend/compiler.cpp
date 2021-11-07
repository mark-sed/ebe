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
#include "exceptions.hpp"
#include "logging.hpp"

const char *Error::get_code_name(Error::ErrorCode code){
    const char *NAMES[] = {
        "None",
        "Unknown",
        "Internal",
        "File access",
        "Arguments",
        "Syntactic",
        "Semantic",
        "Unimplemented"
    };
    constexpr int names_size = sizeof(NAMES)/sizeof(char *);
    if(static_cast<int>(code) < names_size){
        return NAMES[static_cast<int>(code)];
    }
    return "Unknown";
}

void Error::error(Error::ErrorCode code, const char *msg, Exception::EbeException *exc, bool exit){
    std::cerr << "ERROR (" << Error::get_code_name(code); 
    if(exc == nullptr) {
        std::cerr << "): " << msg << "." << std::endl;
    }
    else {
        std::cerr << exc->get_type() << "): " << msg << "." << exc->what() << "." << std::endl;
    }
    if(exit){
        Error::exit(code);
    }
}


void Compiler::error(Error::ErrorCode code, const char *file, 
                                  long line, long column, const char *msg,
                                  Exception::EbeException *exc, bool exit){
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
    std::cerr << ":[" << unit_name << "]: ERROR (" << Error::get_code_name(code);
    if(exc == nullptr) {
        std::cerr << "): " << msg << "." << std::endl;
    }
    else {
        std::cerr << ", " << exc->get_type() << "): " << msg << "! " << exc->what() << "." << std::endl;
    }
    if(exit){
        Error::exit(code);
    }
}

[[noreturn]] void Error::exit(Error::ErrorCode code) {
    LOG1("Exiting program with code " << code);
    std::exit(code);
}

Compiler::Compiler(const char *unit_name) : unit_name{unit_name} {

}
