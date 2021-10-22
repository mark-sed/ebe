/**
 * Tests for helper util functions
 */ 

#include <gtest/gtest.h>
#include <string>
#include "utils.hpp"
#include "exceptions.hpp"

namespace{

// String conversions
TEST(StringConversions, ToUpper){
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

// Casting from some type (string) to another
TEST(Casts, To){
    unsigned int number = 42;
    std::string number_s = "42";

    // Cast to uint
    try{
        EXPECT_EQ(number, Cast::to<unsigned int>(number_s));
    } catch (...) {
        FAIL() << "Cast::to<unsigned int> threw and exception when it should have not.";
    }

    try{
        EXPECT_EQ(0, Cast::to<unsigned int>("00"));
    } catch (Exception::EbeTypeException &e) {
        FAIL() << "Cast::to<unsigned int> threw and exception when it should have not.";
    }

    // Check fail throws exception
    try{
        Cast::to<unsigned int>("42akg");
        FAIL() << "Cast::to<unsigned int> did not throw an exception";
    } catch (Exception::EbeTypeException &e) {
    }

    try{
        Cast::to<unsigned int>("0_");
        FAIL() << "Cast::to<unsigned int> did not throw an exception";
    } catch (Exception::EbeTypeException &e) {
    }

    // Default base is 10, so it should use it
    try{
        Cast::to<unsigned int>("ff");
        FAIL() << "Cast::to<unsigned int> did not throw an exception";
    } catch (Exception::EbeTypeException &e) {
    }
}

}
