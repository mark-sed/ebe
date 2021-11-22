/**
 * @author Marek Sedlacek
 * @date October 2021
 * 
 * @brief Ebel code grammar
 * EBNF grammar for ebel source code files used by bison (yacc)
 * to generate parser for it.
 */

/* Since new constructs are used, newer version is needed */
%require "3.7"
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

    #include "ir.hpp"

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
    #include <sstream>
    #include <cctype>
    #include "compiler.hpp"
    #include "scanner_ebel.hpp"
    #include "symbol_table.hpp"

    #include <iostream>

    // Set correct token method
    #undef yylex
    #define yylex scanner->eelex
}

%define api.value.type variant
%define parse.assert
%define parse.error verbose

/* Tokens and types */
%token END 0 "end of file"
%token NEWLINE "new line"
%token <int> INT "number"
%token COMMA ","
%token <int> VAR "variable"

/* Instructions */
%token CONCAT
%token DEL
%token LOOP
%token NOP
%token PASS
%token SWAP
%token RETURN

/* Expression instructions */
%token ADD

/* Passes */
%token WORDS "words"
%token LINES "lines"
%token DOCUMENTS "documents"
%token EXPRESSION "expression"

/* Word types */
%token TEXT
%token NUMBER
%token FLOAT
%token DELIMITER
%token SYMBOL
%token EMPTY

%type <IR::Type> type

%locations

%%

program     : END 
            | code END
            | code error '\n'
            | error '\n'
            ;

code        : instruction
            | pass
            | NEWLINE
            | code NEWLINE
            | code NEWLINE instruction
            | code NEWLINE expr_inst
            | code NEWLINE pass
            ;

instruction : CONCAT INT           { scanner->add_concat($2);          }
            | DEL                  { scanner->add_del();               }
            | LOOP                 { scanner->add_loop();              }
            | NOP                  { scanner->add_nop();               }
            | SWAP INT             { scanner->add_swap($2);            }
            | RETURN SWAP INT      { scanner->add_return(); scanner->add_swap($3); }
            | RETURN DEL           { scanner->add_return(); scanner->add_del(); }
            | RETURN NOP           { scanner->add_return(); scanner->add_nop(); }
            | RETURN               { scanner->add_return(); scanner->add_nop(); }
            ;

expr_inst   : ADD VAR COMMA VAR COMMA VAR       { scanner->add_add($2, $4, $6); }
            | ADD VAR COMMA VAR COMMA INT       { scanner->add_add($2, $4, new Vars::NumberVar($6)); }
            | ADD VAR COMMA INT COMMA VAR       { scanner->add_add($2, new Vars::NumberVar($4), $6); }
            | ADD VAR COMMA INT COMMA INT       { scanner->add_add($2, new Vars::NumberVar($4), new Vars::NumberVar($6)); }
            ;

pass        : PASS type EXPRESSION { scanner->add_pass_expression($2); }
            | PASS EXPRESSION      { scanner->add_pass_expression(IR::Type::DERIVED); }
            | PASS WORDS           { scanner->add_pass_words();        }
            | PASS LINES           { scanner->add_pass_lines();        }
            | PASS DOCUMENTS       { scanner->add_pass_documents();    }

type        : TEXT      { $$ = IR::Type::TEXT;      }
            | NUMBER    { $$ = IR::Type::NUMBER;    }
            | FLOAT     { $$ = IR::Type::FLOAT;     }
            | DELIMITER { $$ = IR::Type::DELIMITER; }
            | SYMBOL    { $$ = IR::Type::SYMBOL;    }
            | EMPTY     { $$ = IR::Type::EMPTY;     }
            ;

%%

/* Error method */
void EbelFile::ParserEbel::error(const location_type &l, const std::string &err_message) {
    scanner->sub_error(Error::ErrorCode::SYNTACTIC, err_message);
}
