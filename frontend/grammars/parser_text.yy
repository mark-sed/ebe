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

%token <std::string> QUOTE "\""

%left PLUS MINUS
%left IMUL IDIV MOD
%right POW

%precedence NUMBER
%precedence FLOAT

%precedence NEG

%type <Expr::Expression> varexpr
%type <int> expr_int
%type <float> expr_float
%type <std::string> string_v
%type <std::string> operator

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
word      : TEXT         { scanner->add_text($1);      }
          | MINUS NUMBER { scanner->add_number($1+$2); }
          | NUMBER       { scanner->add_number($1);    }
          | MINUS FLOAT  { scanner->add_float($1+$2);  }
          | FLOAT        { scanner->add_float($1);     }
          | DELIMITER    { scanner->add_delimiter($1); }
          | SYMBOL       { scanner->add_symbol($1);    }
          | NEWLINE      { scanner->add_newline();     }
          | operator     { scanner->add_symbol($1);    }
          | QUOTE        { scanner->add_symbol("\"");  }
          | FALSE_EXPR_BEGIN { scanner->add_symbol("{"); scanner->add_symbol("!"); }
          | FALSE_EXPR_END   { scanner->add_symbol("!"); scanner->add_symbol("}"); }
          | EXPR_BEGIN QUOTE string_v QUOTE EXPR_END {auto e = Expression(Node(Type::TEXT, $3), std::vector<Expression>{});
                                       scanner->add_expr(new Expression(Node(Type::ASSIGN, "="), std::vector<Expression>{Expression(Node(Type::VAR, "$"), std::vector<Expression>()), e}), IR::Type::DERIVED);}
          | EXPR_BEGIN varexpr EXPR_END { scanner->add_expr(new Expression(Node(Type::ASSIGN, "="), std::vector<Expression>{Expression(Node(Type::VAR, "$"), std::vector<Expression>()), $2}), scanner->expr_type); }
          | EXPR_BEGIN expr_int EXPR_END { auto e = Expression(Node(Type::NUMBER, std::to_string($2)), std::vector<Expression>{});
                                       scanner->add_expr(new Expression(Node(Type::ASSIGN, "="), std::vector<Expression>{Expression(Node(Type::VAR, "$"), std::vector<Expression>()), e}), IR::Type::NUMBER);}
          | EXPR_BEGIN expr_float EXPR_END { auto e = Expression(Node(Type::FLOAT, std::to_string($2)), std::vector<Expression>{});
                                       scanner->add_expr(new Expression(Node(Type::ASSIGN, "="), std::vector<Expression>{Expression(Node(Type::VAR, "$"), std::vector<Expression>()), e}), IR::Type::FLOAT);}
          ;

operator  : VAR   { $$ = $1; }
          | PLUS  { $$ = $1; }
          | IMUL  { $$ = $1; }
          | MINUS { $$ = $1; }
          | IDIV  { $$ = $1; }
          | MOD   { $$ = $1; }
          | POW   { $$ = $1; }
          | LPAR  { $$ = $1; }
          | RPAR  { $$ = $1; }
          ;

string_v  : TEXT               { $$ = $1; }
          | SYMBOL             { $$ = $1; }
          | DELIMITER          { $$ = $1; }
          | NUMBER             { $$ = $1; }
          | FLOAT              { $$ = $1; }
          | operator           { $$ = $1; }
          | string_v TEXT      { $$ = $1 + $2; }
          | string_v SYMBOL    { $$ = $1 + $2; }
          | string_v DELIMITER { $$ = $1 + $2; }
          | string_v NUMBER    { $$ = std::string($1) + $2; }
          | string_v FLOAT     { $$ = std::string($1) + $2; }
          | string_v operator  { $$ = $1 + $2; }
          ;

varexpr   : VAR { $$ = Expression(Node(Type::VAR, $1), std::vector<Expression>()); }
          | MINUS VAR %prec NEG { $$ = Expression(Node(Type::IMUL, "*"), std::vector<Expression>{Expression(Node(Type::NUMBER, std::string("-1")), std::vector<Expression>{}), Expression(Node(Type::VAR, $2), std::vector<Expression>())}); }
          | LPAR varexpr RPAR { $$ = $2; }
          
          | expr_int POW varexpr { $$ = Expression(Node(Type::POW, "^"), std::vector<Expression>{Expression(Node(Type::NUMBER, std::to_string($1)), std::vector<Expression>{}), $3}); }
          | expr_int MOD varexpr { $$ = Expression(Node(Type::MOD, "%"), std::vector<Expression>{Expression(Node(Type::NUMBER, std::to_string($1)), std::vector<Expression>{}), $3}); }
          | expr_int IMUL varexpr { $$ = Expression(Node(Type::IMUL, "*"), std::vector<Expression>{Expression(Node(Type::NUMBER, std::to_string($1)), std::vector<Expression>{}), $3}); }
          | expr_int IDIV varexpr { $$ = Expression(Node(Type::IDIV, "/"), std::vector<Expression>{Expression(Node(Type::NUMBER, std::to_string($1)), std::vector<Expression>{}), $3}); }
          | expr_int MINUS varexpr { $$ = Expression(Node(Type::SUB, "-"), std::vector<Expression>{Expression(Node(Type::NUMBER, std::to_string($1)), std::vector<Expression>{}), $3}); }
          | expr_int PLUS varexpr { $$ = Expression(Node(Type::ADD, "+"), std::vector<Expression>{Expression(Node(Type::NUMBER, std::to_string($1)), std::vector<Expression>{}), $3}); }
          
          | varexpr POW expr_int { $$ = Expression(Node(Type::POW, "^"), std::vector<Expression>{$1, Expression(Node(Type::NUMBER, std::to_string($3)), std::vector<Expression>{})}); }
          | varexpr MOD expr_int { $$ = Expression(Node(Type::MOD, "%"), std::vector<Expression>{$1, Expression(Node(Type::NUMBER, std::to_string($3)), std::vector<Expression>{})}); }
          | varexpr IMUL expr_int { $$ = Expression(Node(Type::IMUL, "*"), std::vector<Expression>{$1, Expression(Node(Type::NUMBER, std::to_string($3)), std::vector<Expression>{})}); }
          | varexpr IDIV expr_int { $$ = Expression(Node(Type::IDIV, "/"), std::vector<Expression>{$1, Expression(Node(Type::NUMBER, std::to_string($3)), std::vector<Expression>{})}); }
          | varexpr MINUS expr_int { $$ = Expression(Node(Type::SUB, "-"), std::vector<Expression>{$1, Expression(Node(Type::NUMBER, std::to_string($3)), std::vector<Expression>{})}); }
          | varexpr PLUS expr_int { $$ = Expression(Node(Type::ADD, "+"),  std::vector<Expression>{$1, Expression(Node(Type::NUMBER, std::to_string($3)), std::vector<Expression>{})}); }
          
          | expr_float POW varexpr { $$ = Expression(Node(Type::POW, "^"), std::vector<Expression>{Expression(Node(Type::FLOAT, std::to_string($1)), std::vector<Expression>{}), $3}); }
          | expr_float MOD varexpr { $$ = Expression(Node(Type::MOD, "%"), std::vector<Expression>{Expression(Node(Type::FLOAT, std::to_string($1)), std::vector<Expression>{}), $3}); }
          | expr_float IMUL varexpr { $$ = Expression(Node(Type::IMUL, "*"), std::vector<Expression>{Expression(Node(Type::FLOAT, std::to_string($1)), std::vector<Expression>{}), $3}); }
          | expr_float IDIV varexpr { $$ = Expression(Node(Type::IDIV, "/"), std::vector<Expression>{Expression(Node(Type::FLOAT, std::to_string($1)), std::vector<Expression>{}), $3}); }
          | expr_float MINUS varexpr { $$ = Expression(Node(Type::SUB, "-"), std::vector<Expression>{Expression(Node(Type::FLOAT, std::to_string($1)), std::vector<Expression>{}), $3}); }
          | expr_float PLUS varexpr { $$ = Expression(Node(Type::ADD, "+"), std::vector<Expression>{Expression(Node(Type::FLOAT, std::to_string($1)), std::vector<Expression>{}), $3}); }
          
          | varexpr POW expr_float { $$ = Expression(Node(Type::POW, "^"), std::vector<Expression>{$1, Expression(Node(Type::FLOAT, std::to_string($3)), std::vector<Expression>{})}); }
          | varexpr MOD expr_float { $$ = Expression(Node(Type::MOD, "%"), std::vector<Expression>{$1, Expression(Node(Type::FLOAT, std::to_string($3)), std::vector<Expression>{})}); }
          | varexpr IMUL expr_float { $$ = Expression(Node(Type::IMUL, "*"), std::vector<Expression>{$1, Expression(Node(Type::FLOAT, std::to_string($3)), std::vector<Expression>{})}); }
          | varexpr IDIV expr_float { $$ = Expression(Node(Type::IDIV, "/"), std::vector<Expression>{$1, Expression(Node(Type::FLOAT, std::to_string($3)), std::vector<Expression>{})}); }
          | varexpr MINUS expr_float { $$ = Expression(Node(Type::SUB, "-"), std::vector<Expression>{$1, Expression(Node(Type::FLOAT, std::to_string($3)), std::vector<Expression>{})}); }
          | varexpr PLUS expr_float { $$ = Expression(Node(Type::ADD, "+"),  std::vector<Expression>{$1, Expression(Node(Type::FLOAT, std::to_string($3)), std::vector<Expression>{})}); }
          
          | varexpr POW varexpr { $$ = Expression(Node(Type::POW, "^"), std::vector<Expression>{$1, $3}); }
          | varexpr MOD varexpr { $$ = Expression(Node(Type::MOD, "%"), std::vector<Expression>{$1, $3}); }
          | varexpr IMUL varexpr { $$ = Expression(Node(Type::IMUL, "*"), std::vector<Expression>{$1, $3}); }
          | varexpr IDIV varexpr { $$ = Expression(Node(Type::IDIV, "/"), std::vector<Expression>{$1, $3}); }
          | varexpr MINUS varexpr { $$ = Expression(Node(Type::SUB, "-"), std::vector<Expression>{$1, $3}); }
          | varexpr PLUS varexpr { $$ = Expression(Node(Type::ADD, "+"), std::vector<Expression>{$1, $3}); }
          ;

expr_float: FLOAT { $$ = std::stof($1.c_str()); /* Atoi is safe to use because syntactical analysis was done */ }
          | MINUS expr_float %prec NEG { $$ = -$2; /* Unary minus */}
          | LPAR expr_float RPAR { $$ = $2; }
          | expr_float POW expr_float { $$ = std::pow($1, $3);}
          | expr_float MOD expr_float { $$ = std::fmod($1, $3);}
          | expr_float IMUL expr_float { $$ = $1 * $3;}
          | expr_float IDIV expr_float { $$ = $1 / $3;}
          | expr_float MINUS expr_float { $$ = $1 - $3;}
          | expr_float PLUS expr_float { $$ = $1 + $3;}
          ;

expr_int  : NUMBER { $$ = atoi($1.c_str()); /* Atoi is safe to use because syntactical analysis was done */ }
          | MINUS expr_int %prec NEG { $$ = -$2; /* Unary minus */}
          | LPAR expr_int RPAR { $$ = $2; }
          | expr_int POW expr_int { $$ = static_cast<int>(std::pow($1, $3));}
          | expr_int MOD expr_int { $$ = $1 % $3;}
          | expr_int IMUL expr_int { $$ = $1 * $3;}
          | expr_int IDIV expr_int { $$ = $1 / $3;}
          | expr_int MINUS expr_int { $$ = $1 - $3;}
          | expr_int PLUS expr_int { $$ = $1 + $3;}
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
