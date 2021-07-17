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
#include "ir.hpp"

/**
 * Initializer and handler for compilation
 */
void compile(const char *f_in, const char *f_out) {
    // Preprocessing
    auto preproc = new Preprocessor(Args::arg_opts.line_delim);
    auto in_text = preproc->process(f_in);
    auto out_text = preproc->process(f_out);
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

void interpret(const char *ebel_f, const char *input_f, const char *output_f){
    // Preprocessing
    auto ebel_preproc = new EbelPreprocessor();
    auto ebel_text = ebel_preproc->process(ebel_f);
    //for(auto a: *ebel_text)
    //    std::cout << a;

    // Syntactical check
    auto ebel_scanner = new EbelScanner();
    auto ebel_ir = ebel_scanner->process(ebel_text, ebel_f);

    std::cout << *ebel_ir;

    // Cleanup
    delete ebel_ir;
    delete ebel_scanner;
    delete ebel_text;
    delete ebel_preproc;
}

// Main
int main(int argc, char *argv[]){
    // Parse arguments
    Args::parse_args(argc-1, &argv[1]);
    // Start compilation of example input files
    //compile(Args::arg_opts.file_in, Args::arg_opts.file_out);
    interpret(argv[1], argv[2], argv[3]);
    return 0;
}
