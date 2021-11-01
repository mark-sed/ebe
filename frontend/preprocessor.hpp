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
     * @brief Preprocessing for file.
     * Opens passed in file as an input stream. 
     * If nullptr is passed in, then std::cin is returned.
     * @param file_name Path to the file
     * @return Passed in file or std::cin as an input stream
     */
    std::istream *process(const char *file_name);
};

#endif//_PREPROCESSOR_HPP_
