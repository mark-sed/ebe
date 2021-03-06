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

    // Correct code with weird but allowed lexems
    std::istringstream corr_code(" \
        PASS    documents\n\
            NOP\n\
            SWAP 0001  # Leading zeros and comments are allowd\n\
            \n\
        # Comment again\n\
        PASS word # Singular is allowed\n\
        pass lINEs\n\
        LooP\n\
            CONCAT 3    # Concat is in lines, so its fine\n\
    ");
    auto program = s->process(&corr_code, "");
    // Test for 3 passes
    EXPECT_EQ(true, program->nodes->size() == 3);
    delete program;

    // Testing all possible passes
    std::istringstream passes_code(" \
        NOP \n\
        PASS LINE # No need for s\n\
            SWAP 2\n\
        PASS DOCUMENT\n\
            NOP\n\
        PASS documents\n\
            NOP\n\
        PASS words\n\
            NOP\n\
        PASS NUMBER expression\n\
            RETURN NOP\n\
        PASS EMPTY expression\n\
            RETURN NOP\n\
        PASS FLOAT expression\n\
            RETURN SWAP 2\n\
        PASS TEXT expression\n\
            RETURN\n\
        PASS expression\n\
            RETURN DEL\n\
    ");
    auto p_passes = s->process(&passes_code, "");
    EXPECT_EQ(true, p_passes != nullptr);
    delete p_passes;

    // Test parsing incorrect code
    std::istringstream incor_code1("unknown");
    EXPECT_EXIT(s->process(&incor_code1, ""), testing::ExitedWithCode(Error::ErrorCode::SYNTACTIC), "");

    // Test instruction context check
    std::istringstream incor_code2("PASS words\nCONCAT 2\n");
    EXPECT_EXIT(s->process(&incor_code2, ""), testing::ExitedWithCode(Error::ErrorCode::SEMANTIC), "");

    delete s;
}

}
