/**
 * Tests for helper util functions
 */ 

#include <gtest/gtest.h>
#include <string>
#include "scanner_text.hpp"
#include "scanner_ebel.hpp"
#include "arg_parser.hpp"
#include "ir.hpp"

namespace{

// Text file scanner test
TEST(Scanner, ScannerText) {
    // Set up arguments for parsing
    Args::arg_opts.alpha_num = false;
    Args::arg_opts.alpha_sym = false;
    Args::arg_opts.group_delim = false;
    Args::arg_opts.group_sym = false;
    Args::arg_opts.float_delim = '.';
    Args::arg_opts.line_delim = '\n';
    
    auto s = new TextFile::ScannerText();
    
    // Test parsing text
    auto *in_text = new std::istringstream("Hello 42+5.0e+10\n78\n\n3e,66f\t00001");
    auto in_types = std::vector<std::vector<IR::Type>>{
        {IR::Type::TEXT, IR::Type::DELIMITER, IR::Type::NUMBER, IR::Type::SYMBOL, IR::Type::FLOAT},
        {IR::Type::NUMBER},
        {IR::Type::EMPTY},
        {IR::Type::TEXT, IR::Type::DELIMITER, IR::Type::TEXT, IR::Type::DELIMITER, IR::Type::NUMBER}
    };
    auto in_values = std::vector<std::vector<std::string>>{
        {"Hello", " ", "42", "+", "5.0e+10"},
        {"78"},
        {""},
        {"3e", ",", "66f", "\t", "00001"}
    };
    auto node = s->process(in_text, "tests_file");

    int i = 0;
    for(auto line: *node->nodes) {
        ASSERT_EQ(true, (i < in_types.size())) << "Somehow scanner created more lines then there were";
        int j = 0;
        for(auto word: *line){
            ASSERT_EQ(true, (j < in_types[i].size())) << "Somehow scanner created more words then there were";
            EXPECT_EQ(word->type, in_types[i][j]) << "Parsed and expected types do not match for " << word->text;
            EXPECT_EQ(word->text, in_values[i][j]) << "Parsed and expected values do not match for " << word->text;
            ++j;
        }
        ++i;
    }

    delete in_text;
    delete node;
    delete s;
}

TEST(CodeScanner, ScannerEbel) {
    auto s = new EbelFile::ScannerEbel();

    // Test parsing incorrect code
    std::istringstream in_text("unknown");
    /*EXPECT_EXIT(s->process(&in_text, ""), testing::ExitedWithCode(Error::ErrorCode::SYNTACTIC), 
                "Correct syntax error exit");*/

    delete s;
}

}