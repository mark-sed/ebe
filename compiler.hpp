/**
 * @file compiler.hpp
 * @author Marek Sedlacek
 * @date July 2021
 * @copyright Copyright 2021 Marek Sedlacek. All rights reserved.
 * 
 * @brief Abstract data for all processing units
 * 
 * Every input processing unit should extend processor class
 * so that all needed information and methods are present in it.
 */

#ifndef _COMPILER_HPP_
#define _COMPILER_HPP_

namespace Error {
    enum ErrorCode {
        NO_ERROR = 0,
        UNKNOWN,
        INTERNAL,
        FILE_ACCESS,
        ARGUMENTS
    };

    const char *get_code_name(ErrorCode code);

    [[noreturn]] void error(Error::ErrorCode code, const char *msg);
}

class Compiler {
public:
    const char *unit_name;
protected:
    Compiler(const char *unit_name);
    void error(Error::ErrorCode code, const char *file, long line, 
               long column, const char *msg);
public:
    //virtual void process() = 0;
};

#endif//_COMPILER_HPP_