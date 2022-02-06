/**
 * Tests for argument parser
 */ 

#include <gtest/gtest.h>
#include <string>
#include <vector>
#include "arg_parser.hpp"

namespace{

// Correct arguments for ebe
TEST(ArgumentParsing, Correct){
    // Compilation all options
    std::vector<char *> args_v{(char *)"-in", (char *)"in.txt", 
                               (char *)"-out", (char *)"out.txt",
                               (char *)"-eo", (char *)"out.ebel",
                               (char *)"-it", (char *)"42",
                               (char *)"-e", (char *)"1",
                               (char *)"-E", (char *)"jenn",
                               (char *)"-f", (char *)"lev",
                               (char *)"-t", (char *)"10", 
                               (char *)"--seed", (char *)"77",
                               (char *)"--no-warn-print",
                               (char *)"--no-info-print",
                               (char *)"--no-error-print",
                               (char *)"--no-fatal-print",
                               (char *)"-expr"};

    Args::ArgOpts parser1;

    parser1.parse(args_v.size(), &args_v[0]);

    EXPECT_EQ(parser1.file_in, "in.txt");
    EXPECT_EQ(parser1.file_out, "out.txt");
    EXPECT_EQ(parser1.ebel_out, "out.ebel");
    EXPECT_EQ(parser1.iterations, 42);
    EXPECT_EQ(parser1.evolutions, 1);
    EXPECT_EQ(parser1.engine, "jenn");
    EXPECT_EQ(parser1.fit_fun, &Fitness::levenshtein);
    EXPECT_EQ(parser1.timeout, 10U);
    EXPECT_EQ(parser1.seed, 77U);
    EXPECT_EQ(parser1.no_warn_print, true);
    EXPECT_EQ(parser1.no_error_print, true);
    EXPECT_EQ(parser1.no_fatal_print, true);
    EXPECT_EQ(parser1.no_info_print, true);

    // Interpretation all options
    std::vector<char *> args_v2{(char *)"/dev/null", // Input file
                               (char *)"-i", (char *)"in.ebel", 
                               (char *)"/dev/null", // Input file
                               (char *)"--no-warn-print",
                               (char *)"--no-info-print",
                               (char *)"--no-error-print",
                               (char *)"--no-fatal-print",
                               (char *)"/dev/null", // Input file
                               (char *)"--sym-table-size", (char *)"42", 
                               (char *)"-o", (char *)"/dev/null"};

    Args::ArgOpts parser2;

    parser2.parse(args_v2.size(), &args_v2[0]);
    EXPECT_EQ(parser2.ebel_in, "in.ebel");
    EXPECT_EQ(parser2.int_files.size(), 3);
    EXPECT_EQ(std::string(parser2.int_files[0]) == std::string(parser2.int_files[1])
              && std::string(parser2.int_files[1]) == std::string(parser2.int_files[2])
              && std::string(parser2.int_files[2]) == std::string("/dev/null"), true);
    EXPECT_EQ(parser2.interpret_out, "/dev/null");
    EXPECT_EQ(parser2.no_warn_print, true);
    EXPECT_EQ(parser2.no_error_print, true);
    EXPECT_EQ(parser2.no_fatal_print, true);
    EXPECT_EQ(parser2.no_info_print, true);
}

// Correct arguments for ebe
TEST(ArgumentParsing, Incorrect){
    // Compilation incorrect options
    std::vector<char *> args_v{(char *)"-in", (char *)"in.txt", 
                               (char *)"-out"};
    Args::ArgOpts parser1;
    EXPECT_EXIT(parser1.parse(args_v.size(), &args_v[0]), testing::ExitedWithCode(Error::ErrorCode::ARGUMENTS), "");

    std::vector<char *> args_v2{(char *)"-in", (char *)"in.txt", 
                               (char *)"-out", (char *)"out.txt",
                               (char *)"-i", (char *)"e.ebel"};
    Args::ArgOpts parser2;
    EXPECT_EXIT(parser2.parse(args_v2.size(), &args_v2[0]), testing::ExitedWithCode(Error::ErrorCode::ARGUMENTS), "");

    std::vector<char *> args_v3{(char *)"--version", (char *)"-h"};
    Args::ArgOpts parser3;
    EXPECT_EXIT(parser3.parse(args_v3.size(), &args_v3[0]), testing::ExitedWithCode(Error::ErrorCode::ARGUMENTS), "");

    std::vector<char *> args_v4{(char *)"-in", (char *)"in.txt", 
                               (char *)"-out", (char *)"out.txt",
                               (char *)"e.ebel"};
    Args::ArgOpts parser4;
    EXPECT_EXIT(parser4.parse(args_v4.size(), &args_v4[0]), testing::ExitedWithCode(Error::ErrorCode::ARGUMENTS), "");

    std::vector<char *> args_v5{(char *)"-in", (char *)"in.txt", 
                               (char *)"-out", (char *)"out.txt",
                               (char *)"--sym-table-size", (char *)"42"};
    Args::ArgOpts parser5;
    EXPECT_EXIT(parser5.parse(args_v5.size(), &args_v5[0]), testing::ExitedWithCode(Error::ErrorCode::ARGUMENTS), "");

    // Interpretation incorrect options
    std::vector<char *> args_v6{(char *)"-i"};
    Args::ArgOpts parser6;
    EXPECT_EXIT(parser6.parse(args_v6.size(), &args_v6[0]), testing::ExitedWithCode(Error::ErrorCode::ARGUMENTS), "");

    std::vector<char *> args_v7{(char *)"-i", (char *)"in.ebel", 
                               (char *)"-it", (char *)"42",
                               (char *)"--sym-table-size", (char *)"42"};
    Args::ArgOpts parser7;
    EXPECT_EXIT(parser7.parse(args_v7.size(), &args_v7[0]), testing::ExitedWithCode(Error::ErrorCode::ARGUMENTS), "");

    std::vector<char *> args_v8{(char *)"-i", (char *)"in", 
                                (char *)"/dev/null",
                                (char *)"-o", (char *)"/dev/null",
                                (char *)"-p"};
    Args::ArgOpts parser8;
    EXPECT_EXIT(parser8.parse(args_v8.size(), &args_v8[0]), testing::ExitedWithCode(Error::ErrorCode::ARGUMENTS), "");

    std::vector<char *> args_v9{(char *)"-i", (char *)"in", 
                                (char *)"/dev/null",
                                (char *)"-o", (char *)"/dev/null",
                                (char *)"-f", (char *)"lev"};
    Args::ArgOpts parser9;
    EXPECT_EXIT(parser9.parse(args_v9.size(), &args_v9[0]), testing::ExitedWithCode(Error::ErrorCode::ARGUMENTS), "");
}

}