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

#include <istream>
#include <vector>
#include "compiler.hpp"

/**
 * Preprocessor of the exampe files
 */
class Preprocessor : public Compiler {
private:
    char delim;          ///< Line delimiter 
public:
    /**
     * Constructor
     * @param delim Symbol determining the end of a line
     */
    Preprocessor(char delim='\n');

    /**
     * Preprocessing for example file
     * @param file_name Path to the file
     * @return Processed example file in vector form
     * @note New line symbol is left in
     */
    std::istream *process(const char *file_name);
};

/**
 * Preprocessor for ebel source files
 */
class EbelPreprocessor : public Compiler {
public:
    /** Constructor **/
    EbelPreprocessor();

    /**
     * Preprocessing for ebel file
     * @param file_name Path to the file
     * @return Processed ebel file in vector form
     */
    std::vector<std::string> *process(const char *file_name);
};

#endif//_PREPROCESSOR_HPP_