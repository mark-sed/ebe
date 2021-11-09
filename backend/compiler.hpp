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

#include <iostream>
#include "exceptions.hpp"

/**
 * Namespace holding resources for error and warning handling
 */
namespace Error {

    /**
     * Possible enum codes
     * @note When new code is added its string name should be added also to the get_code_name function
     */
    enum ErrorCode {
        NO_ERROR = 0,  ///< When no error occured but program had to exit (otherwise return code would be for some error 0)
        UNKNOWN,       ///< Unknown error (shouldn't be really used)
        INTERNAL,      ///< Internal compiler error (such as unable to allocate memory)
        FILE_ACCESS,   ///< Problem opening/writing/working with users files (not internal config files)
        ARGUMENTS,     ///< Problem with user arguments
        SYNTACTIC,     ///< Syntactical error
        SEMANTIC,      ///< Semantical error
        UNIMPLEMENTED, ///< Problems with instruction
        RUNTIME        ///< Runtime errors
    };

    /**
     * Returns name of ErrorCode
     * @param code Error code
     * @return Error code's name
     */
    const char *get_code_name(ErrorCode code);

    /**
     * Function for when fatal error occures
     * Prints error information passed in and exits with passed in code
     * @param code Code of an error that occured
     * @param msg Info message to be printed for the user
     * @param exc Exception that might hava accompanied this error or nullptr
     * @param exit If true (default), then after the message is printed program exits with code
     */
    void error(Error::ErrorCode code, const char *msg, Exception::EbeException *exc=nullptr, bool exit=true);

    /**
     * Prints warning to std::cerr
     * @param msg Message to print
     */ 
    inline void warning(const char *msg) {
        std::cerr << "WARNING: " << msg << std::endl;
    }

    /**
     * Exits program with passed in code
     * @param code Error code to exit with
     */ 
    [[noreturn]] void exit(Error::ErrorCode code);
}

/**
 * Base class for all compiler components
 * @note Every compilation pass should extend this class
 */
class Compiler {
public:
    const char *unit_name;  ///< Name of the compilation unit (needed for error printing)
protected:
    /**
     * Constructor
     * @param unit_name Name of unit which extends this class
     */
    Compiler(const char *unit_name);
    
    /**
     * Prints error to the user and exits
     * @param code Error code to exit with
     * @param file Name of the file in which this error occured
     * @param line Line at which the error occured
     * @param column Column at which the error occured
     * @param msg Message to be printed to the user
     * @param exc Exception that might hava accompanied this error or nullptr
     * @param exit If true (default), then after the message is printed program exits with code
     */
    void error(Error::ErrorCode code, const char *file, long line, long column, const char *msg, 
                Exception::EbeException *exc=nullptr, bool exit=true);
};

#endif//_COMPILER_HPP_
