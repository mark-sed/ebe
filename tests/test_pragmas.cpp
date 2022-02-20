/**
 * Tests for pragmas
 */ 

#include <gtest/gtest.h>
#include <string>
#include "scanner_ebel.hpp"
#include "arg_parser.hpp"
#include "pragmas.hpp"

namespace{

// Text file scanner test
TEST(Pragmas, CorrectPragmas) {
    auto ebel = new IR::EbelNode();
    Pragma::Pragmas pragmas(ebel);

    pragmas.parse("sym_table_size 42");
    // No need to check, check is done by not having compiler exit
    pragmas.parse("requires 0."); // Version can be shorten and with dots
    pragmas.parse("  requires   0.2 ");
    pragmas.parse("requires  \"0.2.1\""); // Quotes can be used
    pragmas.apply();

    // TODO: Check in symbol table
    EXPECT_EQ(Args::arg_opts.sym_table_size, 42);

    delete ebel;
}

TEST(Pragmas, IncorrectPragmas) {
    auto ebel = new IR::EbelNode();
    Pragma::Pragmas pragmas(ebel);

    EXPECT_EXIT(pragmas.parse("sym_table_size 0xff"), testing::ExitedWithCode(Error::ErrorCode::SEMANTIC), "");
    EXPECT_EXIT(pragmas.parse("requires 4200.10.10"), testing::ExitedWithCode(Error::ErrorCode::VERSION), "");
    EXPECT_EXIT(pragmas.parse("notapragma"), testing::ExitedWithCode(Error::ErrorCode::SYNTACTIC), "");
    EXPECT_EXIT(pragmas.parse("requires"), testing::ExitedWithCode(Error::ErrorCode::SYNTACTIC), "");
    EXPECT_EXIT(pragmas.parse("requires 0.2.2 2"), testing::ExitedWithCode(Error::ErrorCode::SYNTACTIC), "");

    delete ebel;
}

}