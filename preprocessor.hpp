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

#include <vector>
#include "compiler.hpp"

/**
 * Preprocessor of the exampe files
 */
class Preprocessor : public Compiler {
private:
    char delim;          ///< Line delimiter 

    /**
     * Reads file into vector of lines, where delim variable is used to determine the end of a line
     * @param file_name Path to the file, if this is nullptr then stdin is used
     * @return File's content parsed into vector of lines with "\n" appended at the end of each line (for later parsing)
     */
    std::vector<std::string> *read_file(const char *file_name);
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
     */
    std::vector<std::string> *process(const char *file_name);
};

#endif//_PREPROCESSOR_HPP_