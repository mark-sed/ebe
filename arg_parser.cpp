/**
 * @file arg_parser.cpp
 * @author Marek Sedlacek
 * @date July 2021
 * @copyright Copyright 2021 Marek Sedlacek. All rights reserved.
 * 
 * @brief Parser for program arguments
 * 
 */

#include "arg_parser.hpp"

ArgOpts arg_opts {
    .alpha_num = false,
    .alpha_sym = false,
    .group_delim = false,
    .group_symbol = false,
    .float_delim = '.'
};