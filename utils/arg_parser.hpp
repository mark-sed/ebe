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
#include <chrono>
#include <ostream>
#include <stddef.h>
#include "fitness.hpp"

/**
 * Namespace for all input argument related resources
 */
namespace Args {

    /**
     * Struct that holds all the compilation settings which can be changed by input arguments
     */
    struct ArgOpts {
        unsigned logging_level;///< Verbosity of logging
        unsigned timeout;      ///< Compilation timeout
        unsigned precision;    ///< Minimum compilation precision
        bool interpret_mode;   ///< Interpret mode
        bool execute_mode;     ///< Compilation and interpretation mode
        const char *file_in;   ///< Path to the input example file
        const char *file_out;  ///< Path to the output example file
        const char *ebel_in;   ///< Path to the input ebel file
        const char *ebel_out;  ///< Path to the output file where to save ebel program
        const char *interpret_out; ///< Path to a file or folder where to save interpreted output
        std::vector<const char *> int_files;  ///< Files to be processed during interpreting
        bool expr;             ///< If expressions should be parsed or not
        bool alpha_num;        ///< If alphabetical letters should be grouped with numbers when possible
        bool alpha_sym;        ///< If alphabetical letters should be grouped with symbols when possible
        bool group_delim;      ///< If multiple delimiters should be group together
        bool group_sym;        ///< If multiple symbols should be group together
        char float_delim;      ///< Delimiter for floating point numbers (42.1 vs 42,1)
        bool leading_plus;     ///< If plus sign in front of a number/float should be part of the number (+42 vs 42)
        char line_delim;       ///< Character determining the end of a line 
        char *engine;          ///< Engine to be used for compilation
        size_t evolutions;     ///< How many evolutions at most should be done
        size_t iterations;     ///< How many iterations are in one evolution
        float (*fit_fun)(IR::Node *ir1, IR::Node *ir2); ///< Fitness function to use for comparisons
        unsigned seed;         ///< Determined seed for RNG
        int sym_table_size;    ///< Symbol table size
        bool no_warn_print;    ///< If warning should be surpressed
        bool no_error_print;   ///< If non critical errors should be surpressed
        bool no_fatal_print;   ///< If all errors should be surpressed
        bool no_info_print;    ///< If info messages should be surpressed

        /** Time when Ebe was started */
        std::chrono::time_point<std::chrono::steady_clock> start_time;

        /**
         * @brief Construct a new Arg Opts object
         * Assigns default argument values
         */
        ArgOpts() : logging_level{0},
                    timeout{0},
                    precision{0},
                    interpret_mode{false},
                    execute_mode{false},
                    file_in{nullptr},
                    file_out{nullptr},
                    ebel_in{nullptr},
                    ebel_out{nullptr},
                    interpret_out{nullptr},
                    int_files{},
                    expr{false},
                    alpha_num{false},
                    alpha_sym{false},
                    group_delim{false},
                    group_sym{false},
                    float_delim{'.'},
                    leading_plus{false},
                    line_delim{'\n'},
                    engine{nullptr},
                    evolutions{0},
                    iterations{0},
                    fit_fun{nullptr},
                    seed{0},
                    sym_table_size{0},
                    no_warn_print{false},
                    no_error_print{false},
                    no_fatal_print{false},
                    no_info_print{false} {
        }

        /**
         * Function for parsing input arguments into arg_opts variable
         * @param argc Amount of arguments
         * @param argv Arguments
         * @note This function modifies arg_opts global variable
         * @warning This function should not be called multiple times on the same object
         */
        void parse(int argc, char *argv[]);

        //void parse_legacy(int argc, char *argv[]);

        /**
         * Starts timer to measure compile time
         */
        void start_timer();

        /**
         * @brief Logging of arguments
         * Outputs argument values in structured form with variable names
         * @param out 
         * @param param 
         * @return std::ostream& 
         */
        friend std::ostream& operator<< (std::ostream &out, const ArgOpts& param);
    private:
        
    };

    /** Variable that holds compile arguments */
    extern ArgOpts arg_opts;
}

#endif//_ARG_PARSER_HPP_
