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
#include <fstream> 
#include <vector>
#include <iomanip>
#include <filesystem>
#include "ebe.hpp"
#include "preprocessor.hpp"
#include "scanner_text.hpp"
#include "scanner_ebel.hpp"
#include "ir.hpp"
#include "interpreter.hpp"
#include "engine_jenn.hpp"
#include "engine_miRANDa.hpp"
#include "rng.hpp"
#include "logging.hpp"
#include "arg_parser.hpp"

/**
 * Initializer and handler for compilation
 */
std::pair<IR::EbelNode *, float> compile_core(IR::Node *ir_in, IR::Node *ir_out, std::ostream &out) {
    // Evolution
    float precision = -0.01f;
    float best_precision = -0.01f;
    // Get the engine ID
    // TODO: Use heuristic to decide what engine to use here
    EngineUtils::EngineID engine_id = EngineUtils::EngineID::JENN;
    if(Args::arg_opts.engine != nullptr){
        engine_id = EngineUtils::get_engine_id(Args::arg_opts.engine);
        if(engine_id == EngineUtils::EngineID::UNKNOWN) {
            // This should not happen, it should be tested in the parse_args
            Error::error(Error::ErrorCode::ARGUMENTS, "Incorrect engine name");
        }
        // In case MiRANDa is used generate a warning to let the user know
        if(engine_id == EngineUtils::EngineID::MIRANDA){
            Error::warning("Using MiRANDa engine, which uses only pure randomness and is NOT meant for real use");
        }
    }
    IR::EbelNode *best_program = nullptr;
    // TODO: Call initializer when implemented to set the correct number of evolutions when not set
    size_t evolutions = (Args::arg_opts.evolutions > 0) ? Args::arg_opts.evolutions : 10;
    Engine *engine = nullptr;
    for(size_t e = 1; e <= evolutions || Args::arg_opts.precision != 0 || Args::arg_opts.timeout != 0; ++e){
        if(best_program != nullptr) { 
            // Before deletion, best program has to be copied to not be lost
            auto best_program_copy = new IR::EbelNode(*best_program);
            best_program = best_program_copy;
            if(engine != nullptr) {
                delete engine;
            }
            engine = nullptr;
        }
        switch(engine_id){
            case EngineUtils::EngineID::MIRANDA:
                engine = new EngineMiRANDa(ir_in, ir_out);
            break;
            case EngineUtils::EngineID::JENN:
                engine = new EngineJenn(ir_in, ir_out);
            break;
            default:
                Error::error(Error::ErrorCode::INTERNAL, "Attempt to use engine unknown by the compile process");
        }
        LOGMAX("Started " << e << ". compilation with engine " << engine->engine_name);
        auto program = engine->generate(&precision);
        if(precision >= 1.0f){
            // Found perfect program, end now
            if(!Args::arg_opts.no_info_print) {
                out << "Perfectly fitting program found. ";
            }
            best_program = program;
            best_precision = precision;
            LOG3("Perfectly fitting program found, compilation ended");
            break;
        }
        else if(Utils::is_precise(precision)) {
            if(!Args::arg_opts.no_info_print) {
                out << "Minimum precision program found. ";
            }
            best_program = program;
            best_precision = precision;
            LOG3("Minimum precision program found, compilation ended");
            break;
        }
        else if(Utils::is_timeout()) {
            if(!Args::arg_opts.no_info_print) {
                out << "Timeout. ";
            }
            best_program = program;
            best_precision = precision;
            LOG3("Timeout, compilation ended");
            break;
        }
        LOG4(e << ". evolution finished. Best program (with " << (precision*100) << "% precision):\n" << *program);
        // Save program if it is the best one so far
        if(!best_program || best_precision < precision){
            best_program = program;
            best_precision = precision;
        }
    }

    // Copy best program otherwise it would be deleted
    IR::EbelNode *ebel = nullptr;
    if(best_program) {
        ebel = new IR::EbelNode(*best_program);
    }

    if(engine != nullptr) {
        delete engine; // Deletes all phenotypes
    }

    return std::make_pair(ebel, best_precision);
}

void compile(const char *f_in, const char *f_out) {
    LOGMAX("Compilation started");
    // Preprocessing
    auto preproc = new Preprocessor(Args::arg_opts.line_delim);
    LOGMAX("Text preprocessor started");
    auto in_text = preproc->process(f_in);
    auto out_text = preproc->process(f_out);
    LOGMAX("Text preprocessor finished");

    // Syntactical check
    auto scanner = new TextFile::ScannerText();
    LOGMAX("Text scanner started");
    auto ir_in = scanner->process(in_text, f_in);
    LOG1("Text IN IR:\n" << *ir_in);
    auto ir_out = scanner->process(out_text, f_out);
    LOG1("Text OUT IR:\n" << *ir_out);
    LOGMAX("Text scanner finished");

    auto compiled = compile_core(ir_in, ir_out, std::cout);
    IR::EbelNode *ebel = compiled.first;
    float precision = compiled.second;

    if(ebel) {
        // Print the best program
        std::chrono::duration<float> diff = std::chrono::steady_clock::now()-Args::arg_opts.start_time;

        std::string ebel_out;
        if(Args::arg_opts.ebel_out) {
            ebel_out = std::string(Args::arg_opts.ebel_out);
        }
        else {
            // Use input file name with .ebel as the output
            auto in_f = std::string(Args::arg_opts.file_in);
            ebel_out = (in_f.substr(0, in_f.rfind("."))+".ebel");
        }

        // Folder existence is checked in arg_parser
        std::ofstream o_file(ebel_out);
        o_file << *ebel;
        o_file.close(); 

        if(!Args::arg_opts.no_info_print) {
            std::cout << "Ebel saved to '" << ebel_out << "'." << std::endl;

            std::cout << std::endl << "Best compiled program has " << (precision*100) << "% precision ("
                    << std::fixed << std::setprecision(1) << diff.count() 
                    << " s)." << std::endl;
        }
        LOG1("Best compiled program with " << (precision*100) << "% precision:\n" << *ebel);
        delete ebel;
    }

    // Cleanup
    delete ir_in;
    delete ir_out;
    if(in_text != &std::cin) {
        delete in_text;
    }
    if(out_text != &std::cin) {
        delete out_text;
    }
    delete scanner;
    delete preproc;
    LOGMAX("Compilation done");
}

void interpret_core(IR::EbelNode *ebel, std::vector<const char *> input_files) {
    // Interpret initialization
    auto interpreter = new Interpreter(ebel);

    bool use_stdin = false;
    // If no input files are specified, use stdin
    if(input_files.empty()) {
        input_files.push_back("stdin");
        use_stdin = true;
    }
    for(auto input_f: input_files){
        // Preprocessing input file
        auto text_preproc = new Preprocessor();
        LOGMAX("Text preprocessor for " << input_f << " started");
        auto text_stream = text_preproc->process(use_stdin ? nullptr : input_f);
        LOGMAX("Text preprocessor finished");

        // Syntactical check/parse of input file
        auto text_scanner = new TextFile::ScannerText();
        LOGMAX("Text scanner started");
        auto text_ir = text_scanner->process(text_stream, input_f);
        LOG1("Text IR:\n" << *text_ir);
        LOGMAX("Text scanner finished");

        LOGMAX("Interpreter started");
        interpreter->parse(text_ir);
        LOGMAX("Interpreter finished");
        LOG1("Interpreted text IR:\n" << *text_ir);

        if(Args::arg_opts.interpret_out == nullptr) { 
            if(input_files.size() > 1) {
                std::cout << "# Interpreted " << input_f << ": " << std::endl;
            }
            std::cout << text_ir->output();
        }
        else {
            // Folder existence is checked in arg_parser
            auto f_out_name = std::string(Args::arg_opts.interpret_out);
            if(input_files.size() > 1) {
                auto file_name = std::filesystem::path(input_f);
                // Create file name if multiple files are interpreted
                f_out_name = std::string(Args::arg_opts.interpret_out) + "/edited-" + std::string(file_name.filename());
            }
            std::ofstream o_file(f_out_name);
            o_file << text_ir->output();
            o_file.close();
        }

        delete text_ir;
        delete text_scanner;
        if(!use_stdin) {
            delete text_stream;
        }
        delete text_preproc;
    }
    if(use_stdin) {
        input_files.pop_back();
    }
    delete interpreter;
}

void interpret(const char *ebel_f, std::vector<const char *> input_files){
    LOGMAX("Interpetation started");    
    // Preprocessing
    auto ebel_preproc = new Preprocessor();
    LOGMAX("Ebel preprocessor started");
    auto ebel_text = ebel_preproc->process(ebel_f);
    LOGMAX("Ebel preprocessor finished");

    // Syntactical check
    auto ebel_scanner = new EbelFile::ScannerEbel();
    LOGMAX("Ebel scanner started");
    auto ebel_ir = ebel_scanner->process(ebel_text, ebel_f);
    LOG1("Ebel IR:\n" << *ebel_ir);
    LOGMAX("Ebel scanner finished");

    interpret_core(ebel_ir, input_files);

    // Cleanup
    delete ebel_ir;
    delete ebel_scanner;
    delete ebel_text;
    delete ebel_preproc;
    LOGMAX("Interpretation done");
}

void compile_and_interpret(const char *f_in, const char *f_out, std::vector<const char *> input_files) {
    LOGMAX("Compilation and interpretation started");
    // Preprocessing
    auto preproc = new Preprocessor(Args::arg_opts.line_delim);
    LOGMAX("Text preprocessor started");
    auto in_text = preproc->process(f_in);
    auto out_text = preproc->process(f_out);
    LOGMAX("Text preprocessor finished");

    // Syntactical check
    auto scanner = new TextFile::ScannerText();
    LOGMAX("Text scanner started");
    auto ir_in = scanner->process(in_text, f_in);
    LOG1("Text IN IR:\n" << *ir_in);
    auto ir_out = scanner->process(out_text, f_out);
    LOG1("Text OUT IR:\n" << *ir_out);
    LOGMAX("Text scanner finished");

    std::stringstream ss;
    auto compiled = compile_core(ir_in, ir_out, ss);
    if(!Args::arg_opts.no_info_print) {
        std::cerr << ss.str();
    }
    IR::EbelNode *ebel = compiled.first;
    float precision = compiled.second;
    
    if(!ebel) {
        return;
    }
    // Saving the ebel if requested
    std::chrono::duration<float> diff = std::chrono::steady_clock::now()-Args::arg_opts.start_time;

    if(Args::arg_opts.ebel_out) {
        std::string ebel_out = std::string(Args::arg_opts.ebel_out);

        // Folder existence is checked in arg_parser
        std::ofstream o_file(ebel_out);
        o_file << *ebel;
        o_file.close(); 

        // Don't print if output will go to stdcout
        if(!Args::arg_opts.no_info_print) {
            std::cerr << "Ebel saved to '" << ebel_out << "'.";
        }    
    }
    else {
        if(!Args::arg_opts.no_info_print) {
            std::cerr << std::endl;
        }
    }

    if(!Args::arg_opts.no_info_print) {
        std::cerr << std::endl << "Best compiled program has " << (precision*100) << "% precision ("
                << std::fixed << std::setprecision(1) << diff.count() 
                << " s)." << std::endl;
        if(Args::arg_opts.interpret_out == nullptr) {
            std::cerr << "#--- INTERPRETER OUTPUT: ---#" << std::endl;
        }
    }
    LOG1("Best compiled program with " << (precision*100) << "% precision:\n" << *ebel);
    
    // Interpreting
    LOGMAX("Interpetation started");    
    // Preprocessing
    interpret_core(ebel, input_files);
    LOGMAX("Interpretation done");

    // Cleanup
    delete ebel;
    delete ir_in;
    delete ir_out;
    if(in_text != &std::cin) {
        delete in_text;
    }
    if(out_text != &std::cin) {
        delete out_text;
    }
    delete scanner;
    delete preproc;
    LOGMAX("Compilation and interpretation done");
}

// Main
int main(int argc, char *argv[]){
    // Parse arguments (no need to make sure there are args because help is printed if argc is low)
    Args::arg_opts.parse(argc-1, &argv[1]);
    Args::arg_opts.start_timer();
    // Inits
    // Set logging level
    Logger::get().set_logging_level(Args::arg_opts.logging_level);
    Logger::get().set_flags(std::ios_base::boolalpha);
    LOG1("Argument params: \n" << Args::arg_opts);
    Analytics::get().set_flags(std::ios_base::boolalpha);
    RNG::init(Args::arg_opts.seed);

    // Start compilation of example input files
    if(Args::arg_opts.execute_mode) {
        compile_and_interpret(Args::arg_opts.file_in, Args::arg_opts.file_out, Args::arg_opts.int_files);
    }
    else if(Args::arg_opts.interpret_mode){
        interpret(Args::arg_opts.ebel_in, Args::arg_opts.int_files);
    }
    else{
        compile(Args::arg_opts.file_in, Args::arg_opts.file_out);
    }
    return 0;
}
