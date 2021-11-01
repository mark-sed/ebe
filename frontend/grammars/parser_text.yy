/**
 * @author Marek Sedlacek
 * @date October 2021
 * 
 * @brief Text file grammar
 * EBNF grammar for text files used by bison (yacc)
 * to generate parser for it.
 * 
 * File setup was inspired by http://www.jonathanbeard.io/tutorials/FlexBisonC++
 */

/* Since new constructs are used, newer version is needed */
%require "3.7"
/* Use C++ parser */
%skeleton "lalr1.cc"

%defines
/* Set namespace used */
%define api.namespace { TextFile }
/* Parser class */
%define api.parser.class { ParserText }
%define api.location.file none

/* Forward declarations */
%code requires {
    namespace TextFile {
        class ScannerText;
    }

    #ifndef YY_NULLPTR
        #if defined __cplusplus && 201103L <= __cplusplus
            #define YY_NULLPTR nullptr
        #else
            #define YY_NULLPTR 0
        #endif
    #endif
}

/* Setup parser params */
%parse-param { ScannerText *scanner }

/* Includes */
%code {
    // Include compiler to use error
    #include "compiler.hpp"
    #include "scanner_text.hpp"

    // Set correct token method
    #undef yylex
    #define yylex scanner->yylex
}

%define api.value.type variant
%define parse.assert

/* Tokens and types */
/* String is returned by all of them because it has to be stored as a string anyway */
%token END 0 "EOF"
%token NEWLINE
%token <std::string> TEXT
%token <std::string> NUMBER
%token <std::string> DELIMITER
%token <std::string> SYMBOL
%token <std::string> FLOAT

%locations

%%

/* File can be empty or contain text */
text_file : END
          | sentence END
          ;

/* Sentence can contain just one word or multiple */
sentence  : word
          | sentence word
          ;

/* Word can be of many types */
word      : TEXT      { scanner->add_text($1);      }
          | NUMBER    { scanner->add_number($1);    }
          | DELIMITER { scanner->add_delimiter($1); }
          | SYMBOL    { scanner->add_symbol($1);    }
          | FLOAT     { scanner->add_float($1);     }
          | NEWLINE   { scanner->add_newline();   }
          ;

%%

/* Error method */
void TextFile::ParserText::error(const location_type &l, const std::string &err_message) {
    // Since this should never happen, there is no need for additional information
    Error::error(Error::ErrorCode::INTERNAL, "Somehow input file was parsed as incorrect. Please report this.");
}