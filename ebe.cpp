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
#include "ebe.hpp"
#include "preprocessor.hpp"
#include "scanner.hpp"
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
void compile(const char *f_in, const char *f_out) {
    LOGMAX("Compilation started");
    // Preprocessing
    auto preproc = new Preprocessor(Args::arg_opts.line_delim);
    LOGMAX("Text preprocessor started");
    auto in_text = preproc->process(f_in);
    LOG_CONT_SANITIZE(2, "Processed IN text:", *in_text);
    auto out_text = preproc->process(f_out);
    LOG_CONT_SANITIZE(2, "Processed OUT text:", *out_text);
    LOGMAX("Text preprocessor finished");

    // Syntactical check
    auto scanner = new TextScanner();
    LOGMAX("Text scanner started");
    auto ir_in = scanner->process(in_text, f_in);
    LOG1("Text IN IR:\n" << *ir_in);
    auto ir_out = scanner->process(out_text, f_out);
    LOG1("Text OUT IR:\n" << *ir_out);
    LOGMAX("Text scanner finished");

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
            Error::warning("Using MiRANDa engine, which uses only pure randomness and is NOT meant for real use.");
        }
    }
    IR::EbelNode *best_program = nullptr;
    // TODO: Call initializer when implemented to set the correct number of evolutions when not set
    size_t evolutions = (Args::arg_opts.evolutions > 0) ? Args::arg_opts.evolutions : 10;
    for(size_t e = 0; e < evolutions; ++e){
        Engine *engine = nullptr;
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
            std::cout << "Perfectly fitting program found." << std::endl;
            if(best_program){
                delete best_program;
            }
            best_program = program;
            best_precision = precision;
            LOG3("Perfectly fitting program found, compilation ended");
            delete engine;
            break;
        }
        LOG4(e << ". evolution finished. Best program (with " << (precision*100) << "% precision):\n" << *program);
        // Save program if it is the best one so far
        if(!best_program || best_precision < precision){
            if(best_program){
                delete best_program;
            }
            best_program = program;
            best_precision = precision;
        }else{
            delete program;
        }
        delete engine;
    }

    if(best_program){
        // Print the best program
        std::cout << std::endl << "Best compiled program has " << (best_precision*100) << "% precision." << std::endl;

        // TODO: Create custom output method to have better control
        if(Args::arg_opts.ebel_file) {
            // Folder existence is checked in arg_parser
            std::ofstream o_file(Args::arg_opts.ebel_file);
            o_file << *best_program;
            o_file.close(); 
        }
        else {
            std::cout << *best_program;
        }
        LOG1("Best compiled program with " << (best_precision*100) << "% precision:\n" << *best_program);
        delete best_program;
    }

    // Cleanup
    delete ir_in;
    delete ir_out;
    delete in_text;
    delete out_text;
    delete scanner;
    delete preproc;
    LOGMAX("Compilation done");
}

void interpret(const char *ebel_f, std::vector<const char *> input_files){
    LOGMAX("Interpetation started");
    //TODO: Make this work for all files in input_files
    auto input_f = input_files[0];
    
    // Preprocessing
    auto ebel_preproc = new EbelPreprocessor();
    LOGMAX("Ebel preprocessor started");
    auto ebel_text = ebel_preproc->process(ebel_f);
    LOG_CONT_SANITIZE(2, "Preprocessed ebel code:", *ebel_text);
    LOGMAX("Ebel preprocessor finished");

    // Syntactical check
    auto ebel_scanner = new EbelScanner();
    LOGMAX("Ebel scanner started");
    auto ebel_ir = ebel_scanner->process(ebel_text, ebel_f);
    LOG2("Ebel IR:\n" << *ebel_ir);
    LOGMAX("Ebel scanner finished");

    // Preprocessing input file
    auto text_preproc = new Preprocessor();
    LOGMAX("Text preprocessor started");
    auto text_vect = text_preproc->process(input_f);
    LOG_CONT_SANITIZE(2, "Processed text:", *text_vect);
    LOGMAX("Text preprocessor finished");

    // Syntactical check/parse of input file
    auto text_scanner = new TextScanner();
    LOGMAX("Text scanner started");
    auto text_ir = text_scanner->process(text_vect, input_f);
    LOG1("Text IR:\n" << *text_ir);
    LOGMAX("Text scanner finished");

    // Interpret
    auto interpreter = new Interpreter(ebel_ir);
    LOGMAX("Interpreter started");
    interpreter->parse(text_ir);
    LOGMAX("Interpreter finished");
    LOG1("Interpreted text IR:\n" << *text_ir);

    std::cout << text_ir->output();

    // Cleanup
    delete text_ir;
    delete text_scanner;
    delete text_vect;
    delete text_preproc;
    delete ebel_ir;
    delete ebel_scanner;
    delete ebel_text;
    delete ebel_preproc;
    LOGMAX("Interpretation done");
}

// Main
int main(int argc, char *argv[]){
    // Parse arguments (no need to make sure there are args because help is printed if argc is low)
    Args::parse_args(argc-1, &argv[1]);
    // Inits
    // Set logging level
    Logger::get().set_logging_level(Args::arg_opts.logging_level);
    Logger::get().set_flags(std::ios_base::boolalpha);
    LOG1("Argument params: \n" << Args::arg_opts);
    RNG::init();

    // Start compilation of example input files
    if(Args::arg_opts.interpret_mode){
        interpret(Args::arg_opts.ebel_file, Args::arg_opts.int_files);
    }
    else{
        compile(Args::arg_opts.file_in, Args::arg_opts.file_out);
    }
    return 0;
}
