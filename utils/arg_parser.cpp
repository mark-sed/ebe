/**
 * @file arg_parser.cpp
 * @author Marek Sedlacek
 * @date July 2021
 * @copyright Copyright 2021 Marek Sedlacek. All rights reserved.
 * 
 * @brief Parser for program arguments
 * 
 * For arguments which the program takes, check out HELP_TEXT variable content.
 * @note In this file there is no difference when using word "option" or "switch", 
 *       both mean an an argument with '-' or '--' passed to the program by the user.
 */

#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <set>
#include <string>
#include <filesystem>
#include <chrono>
#include "arg_parser.hpp"
#include "ebe.hpp"
#include "compiler.hpp"
#include "engine.hpp"
#include "logging.hpp"
#include "utils.hpp"
#include "fitness.hpp"

/** Text to be displayed to user when --help option is used */
const char *HELP_TEXT = 
"Compile:   ebe -in <input_example> -out <output_exmaple> -o <output_ebel>\n"
"Interpret: ebe -i <ebel_file> <file1> <file2> ... <fileN>\n"
"Options:\n"
"  -in --example-input <file>   File from which will be read input example text.\n"
"  -out --example-output <file> File from which will be read output example text.\n"
"  -eo --ebel-output <file>     File to which will be output program saved.\n"
"  -i --interpret <file>        Ebel code to be interpreted over all other argument files.\n"
"  -o --interpret-output <file> File or folder where will be transfomed file(s) saved.\n"
"  -expr --expressions          Expressions between \"{!\" and \"!}\" will be generated\n"
"                               into ebel code.\n"
"  -it --iterations <amount>    Number of iterations to be done in one evolution.\n"
"  -e --evolutions <amount>     Number of evolution to be done.\n"
"  -E --engine <name>           Engine to be used for compilation.\n"
"  -f --fitness <name>          Fitness function to be used for compilation\n"
"  -p --precision <1-100>       Minimal compilation precision, if omitted then 100.\n"
"  -t --timeout <s>             Compilation timeout (in seconds).\n"
//"  -alpha-num                  Group text with numbers if they're not separated.\n"
//"  -alpha-sym                  Group text with symbols if they're not separated.\n"
//"  -group-delim                Multiple delimiters after each other will be parsed as one.\n"
//"  -group-sym                  Multiple symbols after each other will be parsed as one.\n"
//"  --float-delim <character>   Character used in your locale as a floating point dot (by default this is `.`).\n"
"  --version                    Prints compiler's version.\n"
"  --help -h                    Prints this text.\n"
;
// TODO: Add delimiter definition option

using namespace Args;

/** A global variable that can be used anywhere to read user compilation options */
ArgOpts Args::arg_opts{};

namespace Args {
    std::chrono::time_point<std::chrono::steady_clock> start_time;


    std::ostream& operator<< (std::ostream &out, const ArgOpts& param) {
        out << "ArgOpts:" << std::endl
            << TAB1"logging_level = " << param.logging_level << std::endl
            << TAB1"interpret_mode = " << param.interpret_mode << std::endl
            << TAB1"execute_mode = " << param.execute_mode << std::endl
            << TAB1"file_in = " << (param.file_in ? param.file_in : "") << std::endl
            << TAB1"file_out = " << (param.file_out ? param.file_out : "") << std::endl
            << TAB1"ebel_in = " << (param.ebel_in ? param.ebel_in : "") << std::endl
            << TAB1"interpret_out = " << (param.interpret_out ? param.interpret_out : "") << std::endl
            << TAB1"ebel_out = " << (param.ebel_out ? param.ebel_out : "") << std::endl;
        out << TAB1"int_files = [" << std::endl;
        for(auto f: param.int_files) {
            out << TAB2 << f << ";" << std::endl;
        }
        out << TAB1"]" << std::endl;
        out << TAB1"alpha_num = " << param.alpha_num << std::endl
            << TAB1"alpha_sym = " << param.alpha_sym << std::endl
            << TAB1"group_delim = " << param.group_delim << std::endl
            << TAB1"group_sym = " << param.group_sym << std::endl
            << TAB1"float_delim = " << param.float_delim << std::endl
            << TAB1"line_delim = " << static_cast<int>(param.line_delim) << std::endl
            << TAB1"engine = " << (param.engine ? param.engine : "") << std::endl
            << TAB1"evolutions = " << param.evolutions << std::endl
            << TAB1"iterations = " << param.iterations << std::endl
            << TAB1"timeout = " << param.timeout << std::endl
            << TAB1"precision = " << param.precision << std::endl
            << TAB1"fitness = " << Fitness::get_name(param.fit_fun) << std::endl
            << TAB1"seed = " << param.seed << std::endl
            << TAB1"no_warn_print = " << param.no_warn_print << std::endl
            << TAB1"no_error_print = " << param.no_error_print << std::endl
            << TAB1"no_info_print = " << param.no_info_print << std::endl
            ;
        return out;
    }
}

/**
 * Prints help text and exits with success
 */
[[noreturn]] static void print_help(){
    std::cout << HELP_TEXT << std::endl;
    std::exit(0);
}

/**
 * Prints version text and exits with success
 */
[[noreturn]] static void print_version(){
    std::cout << "Ebe " << EBE_VERSION_MAJOR << "." << EBE_VERSION_MINOR << "." << EBE_VERSION_PATCH << std::endl;
    std::exit(0);
}

void Args::ArgOpts::parse(int argc, char *argv[]) {
    bool changed_analytics = false;
    bool changed_aout = false;
    bool changed_v = false;

    if(argc == 0){
        print_help();
    }

    for(int i = 0; i < argc; ++i) {
        auto arg = std::string(argv[i]);
        if(arg[0] == '-') {
            // Dash option
            if(arg == "-x" || arg == "--execute") {
                this->execute_mode = true;
            }
            else if(arg == "-in" || arg == "--example-input") {
                if(this->file_in != nullptr) {
                    Error::error(Error::ErrorCode::UNIMPLEMENTED,
                                 "Support for multiple example input files is not yet implemented");
                }
                if(argc > i+1) {
                    this->file_in = argv[++i];
                }
                else {
                    Error::error(Error::ErrorCode::ARGUMENTS, 
                                "Missing value for --example-input (-in) option");
                }
            }
            else if(arg == "-out" || arg == "--example-output") {
                if(this->file_out != nullptr) {
                    Error::error(Error::ErrorCode::UNIMPLEMENTED,
                                 "Support for multiple example output files is not yet implemented");
                }
                if(argc > i+1) {
                    this->file_out = argv[++i];
                }
                else {
                    Error::error(Error::ErrorCode::ARGUMENTS, 
                                "Missing value for --example-output (-out) option");
                }
            }
            else if(arg == "-i" || arg == "--interpret") {
                if(this->ebel_in != nullptr) {
                    Error::error(Error::ErrorCode::ARGUMENTS,
                                 "Only one --interpret (-i) file can be specified");
                }
                if(argc > i+1) {
                    this->interpret_mode = true;
                    this->ebel_in = argv[++i];
                }
                else {
                    Error::error(Error::ErrorCode::ARGUMENTS, 
                                "Missing value for --interpret (-i) option");
                }
            }
            else if(arg == "-eo" || arg == "--ebel-output") {
                if(this->ebel_out != nullptr) {
                    Error::error(Error::ErrorCode::ARGUMENTS,
                                 "Only one -eo (--ebel-output) file can be specified");
                }
                if(argc > i+1) {
                    this->ebel_out = argv[++i];
                }
                else {
                    Error::error(Error::ErrorCode::ARGUMENTS, 
                                "Missing value for -eo (--ebel-output) option");
                }
            }
            else if(arg == "-o" || arg == "--interpret-output") {
                if(this->ebel_out != nullptr) {
                    Error::error(Error::ErrorCode::ARGUMENTS,
                                 "Only one -o (--interpret-output) file can be specified");
                }
                if(argc > i+1) {
                    this->interpret_out = argv[++i];
                }
                else {
                    Error::error(Error::ErrorCode::ARGUMENTS, 
                                "Missing value for -o (--interpret-output) option");
                }
            }
            else if(arg == "-expr" || arg == "--expressions") {
                this->expr = true;
            }
            else if(arg == "-it" || arg == "--iterations") {
                if(this->iterations > 0) {
                    Error::error(Error::ErrorCode::ARGUMENTS,
                                 "Multiple --iteraions (-it) values were specified");
                }
                if(argc > i+1) {
                    try{
                        this->iterations = Cast::to<unsigned int>(argv[++i]);
                        if(this->iterations == 0) {
                            Error::error(Error::ErrorCode::ARGUMENTS, 
                               "Incorrect value for --iterations (-it). Value has to be bigger than 0");
                        }
                    } catch (Exception::EbeException e){
                        Error::error(Error::ErrorCode::ARGUMENTS, "Incorrect value for --iterations (-it)", &e);
                    }
                }
                else {
                    Error::error(Error::ErrorCode::ARGUMENTS, 
                                "Missing value for --iterations (-it) option");
                }
            }
            else if(arg == "-e" || arg == "--evolutions") {
                if(this->evolutions > 0) {
                    Error::error(Error::ErrorCode::ARGUMENTS,
                                 "Multiple --evolutions (-e) values were specified");
                }
                if(argc > i+1) {
                    try{
                        this->evolutions = Cast::to<unsigned int>(argv[++i]);
                        if(this->evolutions == 0) {
                            Error::error(Error::ErrorCode::ARGUMENTS, 
                               "Incorrect value for --evolutions (-e). Value has to be bigger than 0");
                        }
                    } catch (Exception::EbeException e){
                        Error::error(Error::ErrorCode::ARGUMENTS, "Incorrect value for --evolutions (-e)", &e);
                    }
                }
                else {
                    Error::error(Error::ErrorCode::ARGUMENTS, 
                                "Missing value for --evolutions (-e) option");
                }
            }
            else if(arg == "-E" || arg == "--engine") {
                if(this->engine != nullptr) {
                    Error::error(Error::ErrorCode::ARGUMENTS,
                                 "Multiple --engine (-E) values were specified");
                }
                if(argc > i+1) {
                    this->engine = argv[++i];
                }
                else {
                    Error::error(Error::ErrorCode::ARGUMENTS, 
                                "Missing value for --engine (-E) option");
                }
                // Check if engine name is correct in advance so that user does not wait till parsing is done
                if(EngineUtils::get_engine_id(this->engine) == EngineUtils::EngineID::UNKNOWN){
                    Error::error(Error::ErrorCode::ARGUMENTS, "Incorrect engine name");
                }
            }
            else if(arg == "-f" || arg == "--fitness") {
                if(this->fit_fun != nullptr) {
                    Error::error(Error::ErrorCode::ARGUMENTS,
                                 "Multiple --fitness (-f) values were specified");
                }
                if(argc > i+1) {
                    // Check if engine name is correct in advance so that user does not wait until parsing is done
                    try{
                        auto f_name = Utils::to_lower(std::string(argv[++i]));
                        this->fit_fun = Fitness::get_function(f_name);
                    } catch(Exception::EbeUnknownFunction e) {
                        Error::error(Error::ErrorCode::ARGUMENTS, "Incorrect fitness function name", &e);
                    }
                }
                else {
                    Error::error(Error::ErrorCode::ARGUMENTS, 
                                "Missing value for --fitness (-f) option");
                }
            }
            else if(arg == "-p" || arg == "--precision") {
                if(this->evolutions > 0) {
                    Error::error(Error::ErrorCode::ARGUMENTS,
                                 "Multiple --precision (-p) values were specified");
                }
                if(argc > i+1) {
                    try{
                        this->precision = Cast::to<unsigned int>(argv[++i]);
                        if(this->precision < 1 || this->precision > 100) {
                            Error::error(Error::ErrorCode::ARGUMENTS, 
                               "Incorrect value for --precision (-p). Value has to be from 1 to 100");
                        }
                    } catch (Exception::EbeException e){
                        this->precision = 100;
                        --i;
                    }
                }
                else {
                    this->precision = 100;
                }
            }
            else if(arg == "-t" || arg == "--timeout") {
                if(this->timeout > 0) {
                    Error::error(Error::ErrorCode::ARGUMENTS,
                                 "Multiple --timeout (-t) values were specified");
                }
                if(argc > i+1) {
                    try{
                        this->timeout = Cast::to<unsigned int>(argv[++i]);
                        if(this->timeout == 0) {
                            Error::error(Error::ErrorCode::ARGUMENTS, 
                               "Incorrect value for --timeout (-t). Value has to be bigger than 0");
                        }
                    } catch (Exception::EbeException e){
                        Error::error(Error::ErrorCode::ARGUMENTS, "Incorrect value for --timeout (-t)", &e);
                    }
                }
                else {
                    Error::error(Error::ErrorCode::ARGUMENTS, 
                                "Missing value for --timeout (-t) option");
                }
            }
            else if(arg == "-a" || arg == "--analytics") {
                if(changed_analytics) {
                    Error::error(Error::ErrorCode::ARGUMENTS,
                                 "Multiple --analytics (-a) values were specified");
                }
                if(argc > i+1) {
                    const char *unit_names = argv[++i];
                    if(std::string(unit_names) == std::string("all")){
                        Analytics::get().set_log_everything(true);
                    } else {
                        // Parse file functions to add to the logger
                        Analytics::get().set_enabled(Utils::split_csv(std::string(unit_names)));
                    }
                }
                else {
                    Error::error(Error::ErrorCode::ARGUMENTS, 
                                "Missing value for --analytics (-a) option");
                }
                changed_analytics = true;
            }
            else if(arg == "-aout" || arg == "--analytics-output") {
                if(changed_aout) {
                    Error::error(Error::ErrorCode::ARGUMENTS,
                                 "Multiple --analytics-output (-aout) values were specified");
                }
                if(argc > i+1) {
                    const char *path = argv[++i];
                    // Check existence of the folder
                    auto o_path = std::filesystem::path(path);
                    if(!o_path.empty() && !std::filesystem::exists(o_path)){
                        Error::error(Error::ErrorCode::ARGUMENTS, "Folder for analytics output does not exist");
                    }
                    // Remove possible trailing slash
                    // TODO: Remove \, but only on Windows (?)
                    if(o_path.string().back() == '/') {
                        o_path.string().pop_back();
                    }
                    Analytics::get().set_folder_path(path);
                }
                else {
                    Error::error(Error::ErrorCode::ARGUMENTS, 
                                "Missing value for --analytics-output (-aout) option");
                }
                changed_aout = true;
            }
            else if(arg == "-v" || arg == "-v1" 
                   || arg == "-vv" || arg == "-v2"
                   || arg == "-vvv" || arg == "-v3"
                   || arg == "-vvvv" || arg == "-v4"
                   || arg == "-vvvvv" || arg == "-v5") {
                if(changed_v) {
                    Error::error(Error::ErrorCode::ARGUMENTS,
                                 "Multiple -v values were specified");
                }
                if(arg.size() == 2) {
                    // -v
                    this->logging_level = 1;
                }
                else if(arg.size() == 3) {
                    // -vN or -vv
                    if(arg[2] == 'v') {
                        this->logging_level = 2;
                    }
                    else {
                        // No need to check for correct value, since it was pattern matched
                        this->logging_level = static_cast<unsigned int>(arg[2] - '0');
                    }
                } else {
                    this->logging_level = arg.size()-1;
                }
                if(argc > i+1) {
                    const char *file_funcs = argv[++i];
                    if(std::string(file_funcs) == std::string("all")){
                        Logger::get().set_log_everything(true);
                    } else {
                        // Parse file functions to add to the logger
                        Logger::get().set_enabled(Utils::split_csv(std::string(file_funcs)));
                    }
                }
                else {
                    Error::error(Error::ErrorCode::ARGUMENTS, 
                                "Missing value for -v option");
                }
                changed_v = true;
            }
            else if(arg == "--seed") {
                if(this->seed > 0) {
                    Error::error(Error::ErrorCode::ARGUMENTS,
                                 "Multiple --seed values were specified");
                }
                if(argc > i+1) {
                    try{
                        this->seed = Cast::to<unsigned int>(argv[++i]);
                        if(this->seed == 0) {
                            Error::error(Error::ErrorCode::ARGUMENTS, 
                               "Incorrect value for --seed. Value has to be bigger than 0");
                        }
                    } catch (Exception::EbeException e){
                        Error::error(Error::ErrorCode::ARGUMENTS, "Incorrect value for --seed", &e);
                    }
                }
                else {
                    Error::error(Error::ErrorCode::ARGUMENTS, 
                                "Missing value for --seed option");
                }
            }
            else if(arg == "--sym-table-size") {
                if(this->sym_table_size > 0) {
                    Error::error(Error::ErrorCode::ARGUMENTS,
                                 "Multiple --sym-table-size values were specified");
                }
                if(argc > i+1) {
                    try{
                        this->sym_table_size = Cast::to<unsigned int>(argv[++i]);
                        if(this->sym_table_size == 0) {
                            Error::error(Error::ErrorCode::ARGUMENTS, 
                               "Incorrect value for --sym-table-size. Value has to be bigger than 0");
                        }
                    } catch (Exception::EbeException e){
                        Error::error(Error::ErrorCode::ARGUMENTS, "Incorrect value for --sym-table-size", &e);
                    }
                }
                else {
                    Error::error(Error::ErrorCode::ARGUMENTS, 
                                "Missing value for --sym-table-size option");
                }
            }
            else if(arg == "--no-warn-print") {
                this->no_warn_print = true;
            }
            else if(arg == "--no-error-print") {
                this->no_error_print = true;
            }
            else if(arg == "--no-info-print") {
                this->no_info_print = true;
            }
            else if(arg == "--version") {
                if(argc > 1) {
                    Error::error(Error::ErrorCode::ARGUMENTS, 
                                "Option --version cannot be used with other arguments");
                } 
                else {
                    print_version();
                }
            }
            else if(arg == "-h" || arg == "--help") {
                if(argc > 1) {
                    Error::error(Error::ErrorCode::ARGUMENTS, 
                                "Option --help (-h) cannot be used with other arguments");
                } 
                else {
                    print_help();
                }
            }
            else {
                Error::error(Error::ErrorCode::ARGUMENTS, ("Unkwnown option "+arg).c_str());
            }
        }
        else {
            // Interpret input files
            this->int_files.push_back(argv[i]);
        }
    }

    // Open analytics streams
    if(changed_analytics) {
        Analytics::get().open_streams();
    }

    // Check constraints
    if(this->interpret_mode) {
        // Only interpret mode
        if(this->execute_mode) {
            Error::error(Error::ErrorCode::ARGUMENTS, 
                         "Option --execute (-x) and --interpret (-i) are not compatible");
        }
        if(this->file_in != nullptr) {
            Error::error(Error::ErrorCode::ARGUMENTS, 
                         "Option --example-input (-in) and --interpret (-i) are not compatible. Perhaps you meant to add -x");
        }
        if(this->file_out != nullptr) {
            Error::error(Error::ErrorCode::ARGUMENTS, 
                         "Option --example-output (-out) and --interpret (-i) are not compatible. Perhaps you meant to add -x");
        }
        if(this->expr) {
            Error::error(Error::ErrorCode::ARGUMENTS, 
                         "Option --expressions (-expr) is for compilation");
        }
        if(this->iterations > 0) {
            Error::error(Error::ErrorCode::ARGUMENTS, 
                         "Option --iterations (-it) is for compilation");
        }
        if(this->evolutions > 0) {
            Error::error(Error::ErrorCode::ARGUMENTS, 
                         "Option --evolutions (-e) is for compilation");
        }
        if(this->engine != nullptr) {
            Error::error(Error::ErrorCode::ARGUMENTS, 
                         "Option --engine (-E) is for compilation");
        }
        if(this->fit_fun != nullptr) {
            Error::error(Error::ErrorCode::ARGUMENTS, 
                         "Option --fitness (-f) is for compilation");
        }
        if(this->precision > 0) {
            Error::error(Error::ErrorCode::ARGUMENTS, 
                         "Option --precision (-p) is for compilation");
        }
        if(this->timeout > 0) {
            Error::error(Error::ErrorCode::ARGUMENTS, 
                         "Option --timeout (-t) is for compilation");
        }
        if(this->seed > 0) {
            Error::error(Error::ErrorCode::ARGUMENTS, 
                         "Option --seed is for compilation");
        }
    } 
    else if(!this->interpret_mode && !this->execute_mode) {
        // Only compile mode
        if(this->interpret_out != nullptr) {
            Error::error(Error::ErrorCode::ARGUMENTS, 
                         "Option --interpret-output (-o) cannot be used in compilation");
        }
        if(!this->int_files.empty()) {
            Error::error(Error::ErrorCode::ARGUMENTS, 
                         "Input files can be passed in for interpretation only (-i or -x)");
        }
        if(this->sym_table_size > 0) {
            Error::error(Error::ErrorCode::ARGUMENTS, 
                         "Option --sym-table-size is for interpretation");
        }
    }

    if(this->evolutions > 0 && this->precision > 0) {
        Error::error(Error::ErrorCode::ARGUMENTS, 
                     "Option --precision (-p) and --evolutions (-e) are not compatible");
    }

    // Check for missing values, fill implicit ones
    if(!this->interpret_mode || this->execute_mode) {
        // Compilation mode
        if(this->file_in == nullptr) {
            Error::error(Error::ErrorCode::ARGUMENTS, 
                     "Missing input example file (-in)");
        }
        if(this->file_out == nullptr) {
            Error::error(Error::ErrorCode::ARGUMENTS, 
                     "Missing output example file (-out)");
        }
        if(this->ebel_out != nullptr) {
            auto parent_path = std::filesystem::path(this->ebel_out).parent_path();
            if(!parent_path.empty() && !std::filesystem::exists(parent_path)){
                Error::error(Error::ErrorCode::FILE_ACCESS, "Ebel output parent folder does not exit");
            }
        }
    }
    if(this->interpret_mode || this->execute_mode){
        // Interpretation mode
        if(this->interpret_out != nullptr) {
            if(this->int_files.size() > 1) {
                // Folder expected, create the folder
                auto o_path = std::filesystem::path(interpret_out);
                if(!std::filesystem::exists(o_path)){
                    try {
                        std::filesystem::create_directory(o_path);
                    } catch(std::exception e) {
                        Error::error(Error::ErrorCode::FILE_ACCESS, 
                                     "Cannot create folder (nested folder creation is not supported or insufficient permissions)");
                    }
                }
                // Remove possible trailing slash
                // TODO: Remove \, but only on Windows (?)
                if(o_path.string().back() == '/') {
                    o_path.string().pop_back();
                }
            }
            else {
                // File expected, check if base path exists
                auto path = std::filesystem::path(interpret_out);
                if(std::filesystem::exists(path)) {
                    // If exists check if file
                    if(std::filesystem::is_directory(path)) {
                        Error::error(Error::ErrorCode::FILE_ACCESS, "Output is a directory not a file");
                    }
                }
                auto parent_path = path.parent_path();
                if(!parent_path.empty() && !std::filesystem::exists(parent_path)){
                    Error::error(Error::ErrorCode::FILE_ACCESS, "Output parent folder does not exit");
                }
            }
        }
    }
    if(this->execute_mode) {
        if(this->precision == 0) {
            this->precision = 100;
        }
    }

    // Check if interpret input file exist, to not get error after interpretation
    for(auto f: this->int_files) {
        auto path = std::filesystem::path(f);
        if(!std::filesystem::exists(path)){
            Error::error(Error::ErrorCode::FILE_ACCESS, ("Input file "+std::string(f)+" does not exit").c_str());
        }
    }

    // Set implicit values
    if(this->fit_fun == nullptr) {
        this->fit_fun = &Fitness::one2one;
    }
    if(this->sym_table_size == 0) {
        this->sym_table_size = 64;
    }
}

void Args::ArgOpts::start_timer() {
    this->start_time = std::chrono::steady_clock::now();
}
