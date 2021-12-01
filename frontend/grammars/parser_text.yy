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

    #include "expression.hpp"
    #include "tree.hpp"

    using namespace Expr;

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
    #include <cmath>
    #include <sstream>
    // Include compiler to use error
    #include "compiler.hpp"
    #include "scanner_text.hpp"

    // Set correct token method
    #undef yylex
    #define yylex scanner->yylex
}

%define api.value.type variant
%define parse.assert
%define parse.error verbose

/* Tokens and types */
/* String is returned by all of them because it has to be stored as a string anyway */
%token END 0 "EOF"
%token NEWLINE
%token EXPR_BEGIN "expression begin"
%token EXPR_END "expression end"
%token FALSE_EXPR_BEGIN "{!"
%token FALSE_EXPR_END "!}"

%token <std::string> TEXT
%token <std::string> NUMBER
%token <std::string> DELIMITER
%token <std::string> SYMBOL
%token <std::string> FLOAT

%token <std::string> LPAR "("
%token <std::string> RPAR ")"
%token <std::string> VAR "$"
%token <std::string> PLUS "+"
%token <std::string> IMUL "*"
%token <std::string> MINUS "-"
%token <std::string> IDIV "/"
%token <std::string> MOD "%"
%token <std::string> POW "^"

%left PLUS MINUS
%left IMUL IDIV MOD
%right POW

%type <Expr::Expression> varexpr
%type <int> expr

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
word      : TEXT       { scanner->add_text($1);      }
          | NUMBER     { scanner->add_number($1);    }
          | DELIMITER  { scanner->add_delimiter($1); }
          | SYMBOL     { scanner->add_symbol($1);    }
          | FLOAT      { scanner->add_float($1);     }
          | NEWLINE    { scanner->add_newline();     }
          | VAR        { scanner->add_symbol($1);    }
          | PLUS       { scanner->add_symbol($1);    }
          | IMUL       { scanner->add_symbol($1);    }
          | MINUS      { scanner->add_symbol($1);    }
          | IDIV       { scanner->add_symbol($1);    }
          | MOD        { scanner->add_symbol($1);    }
          | POW        { scanner->add_symbol($1);    }
          | LPAR       { scanner->add_symbol("(");   }
          | RPAR       { scanner->add_symbol(")");   }
          | FALSE_EXPR_BEGIN { scanner->add_symbol("{"); scanner->add_symbol("!"); }
          | FALSE_EXPR_END   { scanner->add_symbol("!"); scanner->add_symbol("}"); }
          | EXPR_BEGIN varexpr EXPR_END { scanner->add_expr(new Expression(Node(Type::ASSIGN, "="), std::vector<Expression>{Expression(Node(Type::VAR, "$"), std::vector<Expression>()), $2}), IR::Type::NUMBER); }
          | EXPR_BEGIN expr EXPR_END { auto e = Expression(Node(Type::NUMBER, std::to_string($2)), std::vector<Expression>{});
                                       scanner->add_expr(new Expression(Node(Type::ASSIGN, "="), std::vector<Expression>{Expression(Node(Type::VAR, "$"), std::vector<Expression>()), e}), IR::Type::NUMBER);}
          ;

varexpr   : VAR { $$ = Expression(Node(Type::VAR, $1), std::vector<Expression>()); }
          | LPAR varexpr RPAR { $$ = $2; }
          | expr POW varexpr { $$ = Expression(Node(Type::POW, "^"), std::vector<Expression>{Expression(Node(Type::NUMBER, std::to_string($1)), std::vector<Expression>{}), $3}); }
          | expr MOD varexpr { $$ = Expression(Node(Type::MOD, "%"), std::vector<Expression>{Expression(Node(Type::NUMBER, std::to_string($1)), std::vector<Expression>{}), $3}); }
          | expr IMUL varexpr { $$ = Expression(Node(Type::IMUL, "*"), std::vector<Expression>{Expression(Node(Type::NUMBER, std::to_string($1)), std::vector<Expression>{}), $3}); }
          | expr IDIV varexpr { $$ = Expression(Node(Type::IDIV, "/"), std::vector<Expression>{Expression(Node(Type::NUMBER, std::to_string($1)), std::vector<Expression>{}), $3}); }
          | expr MINUS varexpr { $$ = Expression(Node(Type::SUB, "-"), std::vector<Expression>{Expression(Node(Type::NUMBER, std::to_string($1)), std::vector<Expression>{}), $3}); }
          | expr PLUS varexpr { $$ = Expression(Node(Type::ADD, "+"), std::vector<Expression>{Expression(Node(Type::NUMBER, std::to_string($1)), std::vector<Expression>{}), $3}); }
          | varexpr POW expr { $$ = Expression(Node(Type::POW, "^"), std::vector<Expression>{$1, Expression(Node(Type::NUMBER, std::to_string($3)), std::vector<Expression>{})}); }
          | varexpr MOD expr { $$ = Expression(Node(Type::MOD, "%"), std::vector<Expression>{$1, Expression(Node(Type::NUMBER, std::to_string($3)), std::vector<Expression>{})}); }
          | varexpr IMUL expr { $$ = Expression(Node(Type::IMUL, "*"), std::vector<Expression>{$1, Expression(Node(Type::NUMBER, std::to_string($3)), std::vector<Expression>{})}); }
          | varexpr IDIV expr { $$ = Expression(Node(Type::IDIV, "/"), std::vector<Expression>{$1, Expression(Node(Type::NUMBER, std::to_string($3)), std::vector<Expression>{})}); }
          | varexpr MINUS expr { $$ = Expression(Node(Type::SUB, "-"), std::vector<Expression>{$1, Expression(Node(Type::NUMBER, std::to_string($3)), std::vector<Expression>{})}); }
          | varexpr PLUS expr { $$ = Expression(Node(Type::ADD, "+"),  std::vector<Expression>{$1, Expression(Node(Type::NUMBER, std::to_string($3)), std::vector<Expression>{})}); }
          | varexpr POW varexpr { $$ = Expression(Node(Type::POW, "^"), std::vector<Expression>{$1, $3}); }
          | varexpr MOD varexpr { $$ = Expression(Node(Type::MOD, "%"), std::vector<Expression>{$1, $3}); }
          | varexpr IMUL varexpr { $$ = Expression(Node(Type::IMUL, "*"), std::vector<Expression>{$1, $3}); }
          | varexpr IDIV varexpr { $$ = Expression(Node(Type::IDIV, "/"), std::vector<Expression>{$1, $3}); }
          | varexpr MINUS varexpr { $$ =Expression(Node(Type::SUB, "-"), std::vector<Expression>{$1, $3}); }
          | varexpr PLUS varexpr { $$ = Expression(Node(Type::ADD, "+"), std::vector<Expression>{$1, $3}); }
          ;

expr      : NUMBER { $$ = atoi($1.c_str()); /* Atoi is safe to use because syntactical analysis was done */ }
          | LPAR expr RPAR { $$ = $2; }
          | expr POW expr { $$ = static_cast<int>(std::pow($1, $3));}
          | expr MOD expr { $$ = $1 % $3;}
          | expr IMUL expr { $$ = $1 * $3;}
          | expr IDIV expr { $$ = $1 / $3;}
          | expr MINUS expr { $$ = $1 - $3;}
          | expr PLUS expr { $$ = $1 + $3;}
          ;

%%

/* Error method */
void TextFile::ParserText::error(const location_type &l, const std::string &err_message) {
    if(scanner->is_in_expr()) {
        // Error in user expression
        auto msg = err_message+". Incorrect expression";
        scanner->sub_error(Error::ErrorCode::SYNTACTIC, msg.c_str());
    }
    else {
        // Since this should never happen, there is no need for additional information
        auto msg = std::string("Somehow text file wasn't parsed correctly: \"")+err_message+"\". Please report this";
        scanner->sub_error(Error::ErrorCode::INTERNAL, msg.c_str());
    }
}
