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
#include <unistd.h>
#include "exceptions.hpp"

/**
 * Namespace holding resources for error and warning handling
 */
namespace Error {
    
    /**
     * Namespace for terminal colorization
     */ 
    namespace Colors {

        extern const char * NO_COLOR;
        extern const char * BLACK;
        extern const char * GRAY;
        extern const char * RED;
        extern const char * LIGHT_RED;
        extern const char * GREEN;
        extern const char * LIGHT_GREEN;
        extern const char * BROWN;
        extern const char * YELLOW;
        extern const char * BLUE;
        extern const char * LIGHT_BLUE;
        extern const char * PURPLE;
        extern const char * LIGHT_PURPLE;
        extern const char * CYAN;
        extern const char * LIGHT_CYAN;
        extern const char * LIGHT_GRAY;
        extern const char * WHITE;
        extern const char * RESET;

        /**
         * Checks if stderr is redirected to a file
         * @return true if stderr is redirected
         */ 
        inline bool is_cerr_redirected() {
            static bool initialized(false);
            static bool is_redir;
            if (!initialized) {
                initialized = true;
                is_redir = ttyname(fileno(stderr)) == nullptr;
            }
            return is_redir;
        }

        /**
         * Returns passes in color in case the output is not redirected.
         * If output is redirected then this returns empty string ("")
         * @param color Colors to sanitize
         * @return color if output if not redirected otherwise empty string
         */ 
        inline const char *colorize(const char * color) {
            // Check if stderr is redirected
            if(is_cerr_redirected()) {
                return "";
            }
            return color;
        }

        /**
         * Resets set color to default terminal settings
         * @return Colors::RESET if output is not redirected otherwise empty string
         */ 
        inline const char *reset() {
            // Check if stderr is redirected
            if(is_cerr_redirected()) {
                return "";
            }
            return Colors::RESET;
        }
    }

    /**
     * Possible enum codes
     * @note When new code is added its string name should be added also to the get_code_name function
     */
    enum ErrorCode {
        NO_ERROR = 0,  ///< When no error occurred but program had to exit (otherwise return code would be for some error 0)
        UNKNOWN,       ///< Unknown error (shouldn't be really used)
        INTERNAL,      ///< Internal compiler error (such as unable to allocate memory)
        FILE_ACCESS,   ///< Problem opening/writing/working with users files (not internal config files)
        ARGUMENTS,     ///< Problem with user arguments
        SYNTACTIC,     ///< Syntactical error
        SEMANTIC,      ///< Semantical error
        UNIMPLEMENTED, ///< Problems with instruction
        RUNTIME,       ///< Runtime errors
        VERSION        ///< For when the version is not sufficient
    };

    /**
     * Returns name of ErrorCode
     * @param code Error code
     * @return Error code's name
     */
    const char *get_code_name(ErrorCode code);

    /**
     * Function for when fatal error occurres
     * Prints error information passed in and exits with passed in code
     * @param code Code of an error that occurred
     * @param msg Info message to be printed for the user
     * @param exc Exception that might hava accompanied this error or nullptr
     * @param exit If true (default), then after the message is printed program exits with code
     */
    void error(Error::ErrorCode code, const char *msg, Exception::EbeException *exc=nullptr, bool exit=true);

    void error(Error::ErrorCode code, const char *file, long line, long column, const char *msg, 
               Exception::EbeException *exc=nullptr, bool exit=true);

    /**
     * Prints warning to std::cerr
     * @param msg Message to print
     */ 
    void warning(const char *msg);

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
     * @param file Name of the file in which this error occurred
     * @param line Line at which the error occurred
     * @param column Column at which the error occurred
     * @param msg Message to be printed to the user
     * @param exc Exception that might hava accompanied this error or nullptr
     * @param exit If true (default), then after the message is printed program exits with code
     */
    void error(Error::ErrorCode code, const char *file, long line, long column, const char *msg, 
                Exception::EbeException *exc=nullptr, bool exit=true);
};

#endif//_COMPILER_HPP_
