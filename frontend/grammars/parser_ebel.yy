/**
 * @author Marek Sedlacek
 * @date October 2021
 * 
 * @brief Ebel code grammar
 * EBNF grammar for ebel source code files used by bison (yacc)
 * to generate parser for it.
 */

/* Since new constructs are used, newer version is needed */
%require "3.8"
/* Use C++ parser */
%skeleton "lalr1.cc"

%defines
/* Set namespace used */
%define api.namespace { EbelFile }
/* Parser class */
%define api.parser.class { ParserEbel }
%define api.location.file none

/* Forward declarations */
%code requires {
    namespace EbelFile {
        class ScannerEbel;
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
%parse-param { ScannerEbel *scanner }

/* Includes */
%code {
    // Include compiler to use error
    #include "compiler.hpp"
    #include "scanner_ebel.hpp"

    // Set correct token method
    #undef yylex
    #define yylex scanner->eelex
}

%define api.value.type variant
%define parse.assert

/* Tokens and types */
%token END 0 "end of file"
%token NEWLINE
%token <int> NUMBER
%token CONCAT
%token DEL
%token LOOP
%token NOP
%token PASS
%token PASS_WORDS
%token PASS_LINES
%token PASS_DOCUMENTS
%token SWAP

%locations

%%

program     : END 
            | code END
            ;

code        : instruction
            | NEWLINE
            | code NEWLINE
            | code NEWLINE instruction
            ;

instruction : CONCAT NUMBER     { scanner->add_concat($2);       }
            | DEL               { scanner->add_del();            }
            | LOOP              { scanner->add_loop();           }
            | NOP               { scanner->add_nop();            }
            | PASS_WORDS        { scanner->add_pass_words();     }
            | PASS_LINES        { scanner->add_pass_lines();     }
            | PASS_DOCUMENTS    { scanner->add_pass_documents(); }
            | SWAP NUMBER       { scanner->add_swap($2);         }
            ;

%%

/* Error method */
void EbelFile::ParserEbel::error(const location_type &l, const std::string &err_message) {
    Error::error(Error::ErrorCode::SYNTACTIC, err_message.c_str());
}
