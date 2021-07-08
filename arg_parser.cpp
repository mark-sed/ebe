/**
 * @file arg_parser.cpp
 * @author Marek Sedlacek
 * @date July 2021
 * @copyright Copyright 2021 Marek Sedlacek. All rights reserved.
 * 
 * @brief Parser for program arguments
 * 
 * For arguments which the program takes, check out HELP_TEXT variable content.
 * @note In this file there is no difference when using word "option" or "switch", both mean an option/switch passed to the
 *       program by the user.
 */

#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <set>
#include <string>
#include "arg_parser.hpp"
#include "compiler.hpp"
#include "ebe.hpp"

/** Text to be displayed to user when --help option is used */
const char *HELP_TEXT = "Usage: ebe [options] file\n"\
"Options:\n"\
"  --help -h                   Prints this text.\n"\
"  --version                   Prints compiler's version information.\n"\
"  -alpha-num                  Compiler will group text with numbers if they're not separated.\n"\
"  -alpha-sym                  Compiler will group text with symbols if they're not separated.\n"\
"  -group-delim                Multiple delimiters after each other will be parsed as one delimiter.\n"\
"  -group-sym                  Multiple symbols after each other will be parsed as one symbol.\n"\
"  --float-delim <character>   Character used in your locale as a floating point dot (by default this is `.`).\n"\
"  -in <file> --input <file>   File from which will be read input example text.\n"\
"  -out <file> --output <file> File from which will be read output example text.\n"\
"  -o <file>                   File to which will be output program saved.";
// TODO: Add delimiter definition option

using namespace Args;

/** A global variable that can be used anywhere to read user compilation options */
ArgOpts arg_opts {
    .file_in = nullptr,
    .file_out = nullptr,
    .alpha_num = false,
    .alpha_sym = false,
    .group_delim = false,
    .group_sym = false,
    .float_delim = '.'
};

/**
 * Prints help text and exits with success
 */
[[noreturn]] void print_help(){
    std::cout << HELP_TEXT << std::endl;
    std::exit(0);
}

/**
 * Prints version text and exits with success
 */
[[noreturn]] void print_version(){
    std::cout << "ebe " << EBE_VERSION_MAJOR << "." << EBE_VERSION_MINOR << "." << EBE_VERSION_PATCH << std::endl;
    std::exit(0);
}

/**
 * Returns value of an option
 * Inspired by https://stackoverflow.com/a/868894
 * @param begin Start of the args array
 * @param end End of the args array
 * @param opt Option name
 * @param opt_long Longer version of the option or alternative version, if it is empty then it is ignored
 * @return the option value
 */
char *get_option_value(char **begin, char **end, const std::string &opt, const std::string &opt_long){
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

/**
 * Checks if an option exists
 * @param begin Start of the args array
 * @param end End of the args array
 * @param opt Option name
 * @param opt_long Longer version of the option or alternative version, if it is empty then it is ignored
 * @return if the option is present
 */
bool exists_option(char **begin, char **end, const std::string &opt, const std::string &opt_long){
    return std::find(begin, end, opt) != end || std::find(begin, end, opt_long) != end;
}

void Args::parse_args(int argc, char *argv[]){
    static const std::set<std::string> NO_VAL_OPTS{"-alpha-num", "-alpha-sym", "-group-delim", "-group-sym"};
    // TODO: Check for unknown switches and notify
    // TODO: If -in is not specified but -out is, then read -out from stdin
    // TODO: Implement -o
    if(argc == 0){
        print_help();
    }
    // Help
    if(exists_option(argv, argv+argc, "-h", "--help")){
        print_help();
    }
    // Version
    if(exists_option(argv, argv+argc, "--version", "")){
        print_version();
    }
    // Input file
    if(exists_option(argv, argv+argc, "-in", "--input")){
        if(!(arg_opts.file_in = get_option_value(argv, argv+argc, "-in", "--input"))){
            Error::error(Error::ErrorCode::ARGUMENTS, "Missing value for example input file");
        }
    }
    // Output file
    if(exists_option(argv, argv+argc, "-out", "--output")){
        if(!(arg_opts.file_out = get_option_value(argv, argv+argc, "-out", "--output"))){
            Error::error(Error::ErrorCode::ARGUMENTS, "Missing value for example output file");
        }
    }
    // Parsing options
    if(exists_option(argv, argv+argc, "-alpha-num", "")){
        arg_opts.alpha_num = true;
    }
    if(exists_option(argv, argv+argc, "-alpha-sym", "")){
        arg_opts.alpha_sym = true;
    }
    if(exists_option(argv, argv+argc, "-group-delim", "")){
        arg_opts.group_delim = true;
    }
    if(exists_option(argv, argv+argc, "-group-sym", "")){
        arg_opts.group_sym = true;
    }
    if(exists_option(argv, argv+argc, "--float-delim", "")){
        if(!(arg_opts.float_delim = get_option_value(argv, argv+argc, "--float-delim", "")[0])){
            Error::error(Error::ErrorCode::ARGUMENTS, "Missing value for --float-delim");
        }
    }

    // Check if needed switches are set
    if(!arg_opts.file_in){
        bool was_switch = false;
        for(int i = 0; i < argc; i++){
            if(argv[i][0] == '-'){
                if(NO_VAL_OPTS.find(std::string(argv[i])) == NO_VAL_OPTS.end()){
                    // Check for options without values
                    was_switch = true;
                }
                else{
                    was_switch = false;
                }
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

