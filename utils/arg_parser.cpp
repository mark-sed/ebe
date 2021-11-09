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
#include <filesystem>
#include "arg_parser.hpp"
#include "ebe.hpp"
#include "compiler.hpp"
#include "engine.hpp"
#include "logging.hpp"
#include "utils.hpp"

/** Text to be displayed to user when --help option is used */
const char *HELP_TEXT = "Usage: ebe [options] file\n"
"Options:\n"
"  --help -h                   Prints this text.\n"
"  --version                   Prints compiler's version information.\n"
"  -expr --expressions         Expressions between \"{!\" and \"!}\" will be generated into ebel code.\n"
"  -alpha-num                  Compiler will group text with numbers if they're not separated.\n"
"  -alpha-sym                  Compiler will group text with symbols if they're not separated.\n"
"  -group-delim                Multiple delimiters after each other will be parsed as one delimiter.\n"
"  -group-sym                  Multiple symbols after each other will be parsed as one symbol.\n"
"  --float-delim <character>   Character used in your locale as a floating point dot (by default this is `.`).\n"
"  -it --iterations <amount>   Number of iterations to be done in one evolution.\n"
"  -e --evolutions <amount>    Number of evolution to be done.\n"
"  -E --engine <name>          Engine to be used for compilation.\n"
"  -in <file> --input <file>   File from which will be read input example text.\n"
"  -out <file> --output <file> File from which will be read output example text.\n"
"  -o <file>                   File to which will be output program saved.\n"
"  -i <file>                   Ebel code to be interpreted over all other argument files.\n"
;
// TODO: Add delimiter definition option

using namespace Args;

/** A global variable that can be used anywhere to read user compilation options */
ArgOpts Args::arg_opts {
    .logging_level = 0,
    .interpret_mode = false,
    .file_in = nullptr,
    .file_out = nullptr,
    .ebel_file = nullptr,
    .int_files{},
    .expr = false,
    .alpha_num = false,
    .alpha_sym = false,
    .group_delim = false,
    .group_sym = false,
    .float_delim = '.',
    .leading_plus = false,
    .line_delim = '\n',
    .engine = nullptr,
    .evolutions = 0,
    .iterations = 0
};

namespace Args {
    std::ostream& operator<< (std::ostream &out, const ArgOpts& param) {
        out << "ArgOpts:" << std::endl
            << TAB1"logging_level = " << param.logging_level << std::endl
            << TAB1"interpret_mode = " << param.interpret_mode << std::endl
            << TAB1"file_in = " << (param.file_in ? param.file_in : "") << std::endl
            << TAB1"file_out = " << (param.file_out ? param.file_out : "") << std::endl
            << TAB1"ebel_file = " << (param.ebel_file ? param.ebel_file : "") << std::endl;
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
            << TAB1"iterations = " << param.iterations << std::endl;
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

/**
 * Returns value of an option
 * Inspired by https://stackoverflow.com/a/868894
 * @param begin Start of the args array
 * @param end End of the args array
 * @param opt Option name
 * @param opt_long Longer version of the option or alternative version, if it is empty then it is ignored
 * @return the option value
 */
static char *get_option_value(char **begin, char **end, const std::string &opt, const std::string &opt_long){
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
static bool exists_option(char **begin, char **end, const std::string &opt, const std::string &opt_long){
    return std::find(begin, end, opt) != end || std::find(begin, end, opt_long) != end;
}

static void parse_v(char **argv, int argc, const char *opt, const char *opt2) {
    const char *file_funcs;
    if(!(file_funcs = get_option_value(argv, argv+argc, opt, opt2))){
        Error::error(Error::ErrorCode::ARGUMENTS, "Missing functions for debug prints");
    }
    if(std::string(file_funcs) == std::string("all")){
        Logger::get().set_log_everything(true);
    } else {
        // Parse file functions to add to the logger
        Logger::get().set_enabled(Utils::split_csv(std::string(file_funcs)));
    }
}

void Args::parse_args(int argc, char *argv[]){
    static const std::set<std::string> NO_VAL_OPTS{"-alpha-num", "-alpha-sym", "-group-delim", "-group-sym"};
    // TODO: Check for unknown switches and notify
    // TODO: If -in is not specified but -out is, then read -out from stdin
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

    // Check if interpreting
    if(exists_option(argv, argv+argc, "-i", "")){
        arg_opts.interpret_mode = true;
        if(!(arg_opts.ebel_file = get_option_value(argv, argv+argc, "-i", ""))){
            Error::error(Error::ErrorCode::ARGUMENTS, "Missing value for ebel program file");
        }
    }

    // Iterations
    if(exists_option(argv, argv+argc, "--iterations", "-it")){
        char *in_value;
        if(!(in_value = get_option_value(argv, argv+argc, "--iterations", "-it"))){
            Error::error(Error::ErrorCode::ARGUMENTS, "Missing value for --iterations");
        }
        // FIXME: Value is taken as UInt not Size_t
        try{
            arg_opts.iterations = Cast::to<unsigned int>(in_value);
        } catch (Exception::EbeException e){
            Error::error(Error::ErrorCode::ARGUMENTS, "Incorrect value for --iterations", &e);
        }
    }

    // Evolutions
    if(exists_option(argv, argv+argc, "--evolutions", "-e")){
        char *in_value;
        if(!(in_value = get_option_value(argv, argv+argc, "--evolutions", "-e"))){
            Error::error(Error::ErrorCode::ARGUMENTS, "Missing value for --evolutions");
        }
        // FIXME: Value is taken as UInt not Size_t
        try{
            arg_opts.evolutions = Cast::to<unsigned int>(in_value);
        } catch (Exception::EbeException e){
            Error::error(Error::ErrorCode::ARGUMENTS, "Incorrect value for --evolutions", &e);
        }
    }

    // Engine
    if(exists_option(argv, argv+argc, "--engine", "-E")){
        if(!(arg_opts.engine = get_option_value(argv, argv+argc, "--engine", "-E"))){
            Error::error(Error::ErrorCode::ARGUMENTS, "Missing value for --engine");
        }
        // Check if engine name is correct in advance so that user does not wait till parsing is done
        if(EngineUtils::get_engine_id(Args::arg_opts.engine) == EngineUtils::EngineID::UNKNOWN){
            Error::error(Error::ErrorCode::ARGUMENTS, "Incorrect engine name");
        }
    }

    // Input file
    if(exists_option(argv, argv+argc, "-in", "--input")){
        if(arg_opts.interpret_mode){
            Error::error(Error::ErrorCode::ARGUMENTS, "-in/--input option is not supported in interpret mode");
        }
        if(!(arg_opts.file_in = get_option_value(argv, argv+argc, "-in", "--input"))){
            Error::error(Error::ErrorCode::ARGUMENTS, "Missing value for example input file");
        }
    }
    // Output file
    if(exists_option(argv, argv+argc, "-out", "--output")){
        if(arg_opts.interpret_mode){
            Error::error(Error::ErrorCode::ARGUMENTS, "-out/--output option is not supported in interpret mode");
        }
        if(!(arg_opts.file_out = get_option_value(argv, argv+argc, "-out", "--output"))){
            Error::error(Error::ErrorCode::ARGUMENTS, "Missing value for example output file");
        }
    }
    // Output ebel file
    if(exists_option(argv, argv+argc, "-o", "")){
        // TODO: Fill default file (out.ebel?) when not specified
        // TODO: Have option to use stdout
        if(!(arg_opts.ebel_file = get_option_value(argv, argv+argc, "-o", ""))){
            Error::error(Error::ErrorCode::ARGUMENTS, "Missing value for output program file");
        }
        // Because opening of the file will happen after many iterations and evolution
        // existence of its path is checked here
        auto o_path = std::filesystem::path(arg_opts.ebel_file);
        if(!o_path.remove_filename().empty() && !std::filesystem::exists(o_path.remove_filename())){
            Error::error(Error::ErrorCode::ARGUMENTS, "Path to passed in output file (-o) does not exist");
        }
    }
    // Parsing options
    if(exists_option(argv, argv+argc, "-expr", "--expressions")){
        arg_opts.expr = true;
    }
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
        Error::warning("--float-delim is not supported in this version");
    }
    if(exists_option(argv, argv+argc, "--line-delim", "")){
        if(!(arg_opts.line_delim = get_option_value(argv, argv+argc, "--line-delim", "")[0])){
            Error::error(Error::ErrorCode::ARGUMENTS, "Missing value for --line-delim");
        }
        Error::warning("--line-delim is not supported in this version");
    }

    // Verbosity logging level
    if(exists_option(argv, argv+argc, "-v", "-v1")){
        arg_opts.logging_level = 1;
        parse_v(argv, argc, "-v", "-v1");
    }
    else if(exists_option(argv, argv+argc, "-vv", "-v2")){
        arg_opts.logging_level = 2;
        parse_v(argv, argc, "-vv", "-v2");
    }
    else if(exists_option(argv, argv+argc, "-vvv", "-v3")){
        arg_opts.logging_level = 3;
        parse_v(argv, argc, "-vvv", "-v3");
    }
    else if(exists_option(argv, argv+argc, "-vvvv", "-v4")){
        arg_opts.logging_level = 4;
        parse_v(argv, argc, "-vvvv", "-v4");
    }
    else if(exists_option(argv, argv+argc, "-vvvvv", "-v5")){
        arg_opts.logging_level = 5;
        parse_v(argv, argc, "-vvvvv", "-v5");
    }

    // Check if needed switches are set
    if(!arg_opts.interpret_mode){
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
    else{
        // In interpret mode every non option argument is taken as an input file for interpreting
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
                arg_opts.int_files.push_back(argv[i]);
            }
            else{
                was_switch = false;
            }
        }
        // If there is no file, read stdin
        if(arg_opts.int_files.empty()){
            Error::error(Error::ErrorCode::UNIMPLEMENTED, "Reading input from stdin is not yet implemented, please use a file");
        }
    }
}
