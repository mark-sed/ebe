/**
 * Tests for interpreter
 */ 

#include <gtest/gtest.h>
#include <string>
#include "scanner.hpp"
#include "arg_parser.hpp"
#include "interpreter.hpp"
#include "ir.hpp"
#include "instruction.hpp"

namespace{

// TODO: Add more interpreter tests - for lines and documents

// Testing if interpretation is correct
TEST(Interpreter, SimpleWordPassCode) {
    // Create text to interpret
    auto text = new IR::Node();
    // Line 1
    text->push_back(0, new IR::Word("foo", IR::Type::TEXT));
    text->push_back(0, new IR::Word(" ", IR::Type::DELIMITER));
    text->push_back(0, new IR::Word("bar", IR::Type::TEXT));
    text->push_back(0, new IR::Word(":", IR::Type::SYMBOL));
    text->push_back(0, new IR::Word("42", IR::Type::NUMBER));
    // Line 2
    text->push_back(1, new IR::Word("baz", IR::Type::TEXT));
    text->push_back(1, new IR::Word(",", IR::Type::DELIMITER));
    text->push_back(0, new IR::Word("3.14159", IR::Type::FLOAT));

    // Copy the text
    auto text_copy = new IR::Node(*text);
    
    // Create program to interpret on
    auto prog = new IR::EbelNode();
    auto pass = new IR::PassWords();

    // Simple NOP program
    pass->push_back(new Inst::NOP());
    prog->push_back(pass);

    auto inter = new Interpreter(prog);
    inter->parse(text);

    EXPECT_EQ(*text_copy, *text);

    // Use out of bound instruction
    pass->push_back(new Inst::SWAP(10));
    // Introduce loop which should not change anything
    pass->push_back(new Inst::LOOP());
    delete inter;
    inter = new Interpreter(prog);
    inter->parse(text);

    EXPECT_EQ(*text_copy, *text);

    // Test empty program
    delete prog;
    prog = new IR::EbelNode();
    delete inter;
    inter = new Interpreter(prog);
    inter->parse(text);

    EXPECT_EQ(*text_copy, *text);

    // Put in modifying program
    pass = new IR::PassWords();
    pass->push_back(new Inst::DEL());
    prog->push_back(pass);
    delete inter;
    inter = new Interpreter(prog);
    inter->parse(text);

    // Check 1st and 2nd word
    EXPECT_EQ(" ", (*(*text->nodes->begin())->begin())->text);
    EXPECT_EQ("bar", (*std::next((*text->nodes->begin())->begin()))->text);
    // Check 1st word on 2nd line
    EXPECT_EQ(",", (*(*std::next(text->nodes->begin()))->begin())->text);

    // Del with loop
    pass->push_back(new Inst::LOOP());
    delete inter;
    inter = new Interpreter(prog);
    inter->parse(text);

    auto text_2_empty_lines = new IR::Node();
    text_2_empty_lines->push_back(0, new IR::Word("", IR::Type::EMPTY));
    text_2_empty_lines->push_back(1, new IR::Word("", IR::Type::EMPTY));
    EXPECT_EQ(*text_2_empty_lines, *text);

    // TODO: Add some more complex ones

    delete text_2_empty_lines;
    delete text;
    delete text_copy;
    delete prog;
    delete inter;
}

}
