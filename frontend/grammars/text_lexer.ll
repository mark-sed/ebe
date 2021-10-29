/**
 * @author Marek Sedlacek
 * @date October 2021
 * 
 * @brief Text file lexems
 * Lexer file for flex tool for text file format.
 */

%{

#include <string>
#include "scanner_text.hpp"

// Define get token method
#undef  YY_DECL
#define YY_DECL int Parsing::ScannerText::yylex(Parsing::ParserText::semantic_type * const lval, Parsing::ParserText::location_type *location)

// Redefine termination token to not use NULL
#define yyterminate() return (token::END)

// Even though the input cannot be incorrect, still add location info
// Could be useful for debugging
// TODO: Remove location info?
#define YY_USER_ACTION loc->step(); loc->columns(yyleng);

// Typedef to shorten scope
using token = Parsing::ParserText::token;

%}

%option nodefault
%option noyywrap
%option c++

/* Define what scanner class is used */
%option yyclass="Parsing::ScannerText"


/* Macros for symbol types */
DELIMITER [ \f\r\t\v,.:;]
NUM       [0-9]
/* TODO: Add special characters from all possible languages */
ALPHANUM  [a-zA-Z0-9\_ěščřžýáíéúů]

%%
%{
    yylval = lval;    
%}

/* DELIMITERS */
{DELIMITER}         {
                        yylval->build<std::string>(yytext);
                        return token::DELIMITER;
                    }

/* FLOATS */
{NUM}+\.{NUM}+[eE][+-]?{NUM}+   {
                                    yylval->build<std::string>(yytext); 
                                    return token::FLOAT;
                                }

{NUM}+\.{NUM}+                  {
                                    yylval->build<std::string>(yytext); 
                                    return token::FLOAT;
                                }

/* NUMBERS */
{NUM}+              {
                        yylval->build<std::string>(yytext); 
                        return token::NUMBER; 
                    }

/* WORDS */
{ALPHANUM}+         {
                        yylval->build<std::string>(yytext);
                        return token::TEXT;
                    }

/* NEW LINE */
\n                  {
                        loc->lines();
                        return token::NEWLINE;
                    }

/* SYMBOLS */
.                   {  
                        yylval->build<std::string>(yytext); 
                        return token::SYMBOL; 
                    }
%%
