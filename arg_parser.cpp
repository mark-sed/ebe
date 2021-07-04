/**
 * @file arg_parser.cpp
 * @author Marek Sedlacek
 * @date July 2021
 * @copyright Copyright 2021 Marek Sedlacek. All rights reserved.
 * 
 * @brief Parser for program arguments
 * 
 * Compiler takes these arguments
 * -h --help: Prints help text
 * -o: Output file name, if not specified then stdout is used
 * -in --input [no switch]: Example input file
 * -out --output: Example output file, if not specified then stdin is used
 * 
 */

#include <cstdlib>
#include <algorithm>
#include <iostream>
#include "arg_parser.hpp"
#include "compiler.hpp"

using namespace Args;

ArgOpts arg_opts {
    .file_in = nullptr,
    .file_out = nullptr,
    .alpha_num = false,
    .alpha_sym = false,
    .group_delim = false,
    .group_symbol = false,
    .float_delim = '.'
};

void print_help(){
    // TODO: Print help
    std::cerr << "Here will be help text" << std::endl;
    std::exit(0);
}

// Inspired by https://stackoverflow.com/a/868894
char *get_switch_value(char **begin, char **end, const std::string &opt, const std::string &opt_long){
    char **it = std::find(begin, end, opt);
    if(it != end && ++it != end){
        return *it;
    }
    if(!opt_long.empty()){
        it = std::find(begin, end, opt_long);
        if(it != end && ++it != end){
            return *it;
        }
    }
    return nullptr;
}

bool exists_switch(char **begin, char **end, const std::string &opt, const std::string &opt_long){
    return std::find(begin, end, opt) != end || std::find(begin, end, opt_long) != end;
}

void Args::parse_args(int argc, char *argv[]){
    // TODO: Check for unknown switches
    // TODO: If -in is not specified but -out is, then read -out from stdin
    if(argc == 0){
        print_help();
    }
    // Help
    if(exists_switch(argv, argv+argc, "-h", "--help")){
        print_help();
    }
    // Input file
    if(exists_switch(argv, argv+argc, "-in", "--input")){
        if(!(arg_opts.file_in = get_switch_value(argv, argv+argc, "-in", "--input"))){
            Error::error(Error::ErrorCode::ARGUMENTS, "Missing value for example input file");
        }
    }
    // Output file
    if(exists_switch(argv, argv+argc, "-out", "--output")){
        if(!(arg_opts.file_out = get_switch_value(argv, argv+argc, "-out", "--output"))){
            Error::error(Error::ErrorCode::ARGUMENTS, "Missing value for example output file");
        }
    }

    // Check if needed switches are set
    if(!arg_opts.file_in){
        bool was_switch = false;
        for(int i = 0; i < argc; i++){
            if(argv[i][0] == '-'){
                was_switch = true;
            }
            else if(!was_switch){
                arg_opts.file_in = argv[i];
            }
            else{
                was_switch = false;
            }
        }
        if(!arg_opts.file_in && !arg_opts.file_out){
            // If none of the files was passed in, print error
            Error::error(Error::ErrorCode::ARGUMENTS, "Missing value for example input file");
        }
    }
}

