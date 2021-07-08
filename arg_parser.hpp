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

namespace Args {
    struct ArgOpts {
        const char *file_in;
        const char *file_out;
        bool alpha_num;
        bool alpha_sym;
        bool group_delim;
        bool group_sym;
        char float_delim;
    };

    void parse_args(int argc, char *argv[]);
}

extern Args::ArgOpts arg_opts; // Default arguments

#endif//_ARG_PARSER_HPP_