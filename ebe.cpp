/**
 * @file ebe.cpp
 * @author Marek Sedlacek
 * @date July 2021
 * @copyright Copyright 2021 Marek Sedlacek. All rights reserved.
 * 
 * @brief Entry point of the ebe compiler
 * 
 * Ebe (Edit By Example) compiler can create text editing programs
 * based on example (original program and wanted output on small scale).
 */

#include <iostream> 
#include "ebe.hpp"
#include "preprocessor.hpp"
#include "arg_parser.hpp"
#include "scanner.hpp"

/**
 * Initializer and handler for compilation
 */
void compile(const char *f_in, const char *f_out) {
    // Preprocessing
    auto preproc = new Preprocessor(f_in, f_out, Args::arg_opts.line_delim);
    auto in_text = preproc->process_input();
    auto out_text = preproc->process_output();
    //for(auto a: *in_text)
    //    std::cout << a;

    // Syntactical check
    auto scanner = new Scanner();
    auto ir_in = scanner->process(in_text, f_in);
    auto ir_out = scanner->process(out_text, f_out);

    std::cout << *ir_in;

    // Cleanup
    delete ir_in;
    delete ir_out;
    delete in_text;
    delete out_text;
    delete scanner;
    delete preproc;
}

// Main
int main(int argc, char *argv[]){
    Args::parse_args(argc-1, &argv[1]);
    compile(Args::arg_opts.file_in, Args::arg_opts.file_out);
    return 0;
}
