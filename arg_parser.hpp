/**
 * @file arg_parser.hpp
 * @author Marek Sedlacek
 * @date July 2021
 * @copyright Copyright 2021 Marek Sedlacek. All rights reserved.
 * 
 * @brief Parser for program arguments
 * 
 * For arguments which the program takes, check out HELP_TEXT variable content in source file.
 */

#ifndef _ARG_PARSER_HPP_
#define _ARG_PARSER_HPP_

#include <vector>

/**
 * Namespace for all input argument related resources
 */
namespace Args {

    /**
     * Struct that holds all the compilation settings which can be changed by input arguments
     */
    struct ArgOpts {
        bool interpret_mode;   ///< Interpret mode
        const char *file_in;   ///< Path to the input example file
        const char *file_out;  ///< Path to the output example file
        const char *ebel_file; ///< Path to the output file where to save ebel program
        std::vector<const char *> int_files;  ///< Files to be processed during interpreting
        bool alpha_num;        ///< If alphabetical letters should be grouped with numbers when possible
        bool alpha_sym;        ///< If alphabetical letters should be grouped with symbols when possible
        bool group_delim;      ///< If multiple delimiters should be group together
        bool group_sym;        ///< If multiple symbols should be group together
        char float_delim;      ///< Delimiter for floating point numbers (42.1 vs 42,1)
        char line_delim;       ///< Character determining the end of a line
    };

    /**
     * Function for parsing input arguments into arg_opts variable
     * @param argc Amount of arguments
     * @param argv Arguments
     * @note This function modifies arg_opts global variable
     */
    void parse_args(int argc, char *argv[]);

    /** Variable that holds compile arguments */
    extern ArgOpts arg_opts;
}

#endif//_ARG_PARSER_HPP_