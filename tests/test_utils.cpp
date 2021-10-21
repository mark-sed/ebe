/**
 * Tests for helper util functions
 */ 

#include <gtest/gtest.h>
#include <string>
#include "utils.hpp"

namespace{

TEST(Utils, ToUpper){
    std::string text = "random text 123456 +-*/ UPPER";
    std::string expected = "RANDOM TEXT 123456 +-*/ UPPER";

    // Check if in uppercase
    EXPECT_EQ(expected, Utils::to_upper(text));
    // Check that the original variable was not changed
    // Assert, because further down text is used again
    EXPECT_EQ("random text 123456 +-*/ UPPER", text);

    // Use by reference version for vector of strings
    std::vector<std::string> v_texts{text, "abc", "def"};
    std::vector<std::string> v_expected{expected, "ABC", "DEF"};
    Utils::to_upper(&v_texts);
    for(int i = 0; i < v_expected.size(); ++i){
        EXPECT_EQ(v_expected[i], v_texts[i]) << "In void to_upper expected " << v_expected[i]  
                                             <<  " but got " << v_texts[i];
    }
}

}
