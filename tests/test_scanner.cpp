/**
 * Tests for helper util functions
 */ 

#include <gtest/gtest.h>
#include <string>
#include "scanner.hpp"
#include "arg_parser.hpp"

namespace{

TEST(Scanner, TextScanner) {
    // Set up arguments for parsing
    Args::arg_opts.alpha_num = false;
    Args::arg_opts.alpha_sym = false;
    Args::arg_opts.group_delim = false;
    Args::arg_opts.group_sym = false;
    Args::arg_opts.float_delim = '.';
    Args::arg_opts.line_delim = '\n';

    std::string in_text = "Hello 42 + 5.0e+10";
    
    auto s = new TextScanner();

    ASSERT_EQ(true, s->is_alpha('a'));
    ASSERT_EQ(false, s->is_alpha('4'));
    ASSERT_EQ(false, s->is_alpha('\t'));
    ASSERT_EQ(true, s->is_delimiter(' '));
    ASSERT_EQ(true, s->is_delimiter(','));
    ASSERT_EQ(true, s->is_delimiter(':'));
    ASSERT_EQ(false, s->is_delimiter('4'));
}

}