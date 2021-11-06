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
#define YY_DECL int TextFile::ScannerText::yylex(TextFile::ParserText::semantic_type * const lval, TextFile::ParserText::location_type *location)

// Even though the input cannot be incorrect, still add location info
// Could be useful for debugging
// TODO: Remove location info?
#define YY_USER_ACTION loc->step(); loc->columns(yyleng);

// Typedef to shorten scope
using token = TextFile::ParserText::token;

// Redefine termination token to not use NULL
#define yyterminate() return (token::END)

%}

%option nodefault
%option noyywrap
%option c++

/* Define what scanner class is used */
%option yyclass="TextFile::ScannerText"


/* Macros for symbol types */
DELIMITER [ \f\r\t\v,.:;]
NUM       [0-9]
/* TODO: Add special characters from all possible languages */
ALPHANUM  [a-zA-Z0-9\_\x80-\xf3]

%%
%{
    yylval = lval;    
%}

{DELIMITER}         {   // Delimiters
                        yylval->build<std::string>(yytext);
                        return token::DELIMITER;
                    }

{NUM}+\.{NUM}+[eE][+-]?{NUM}+   {   // Float in scientific notation
                                    yylval->build<std::string>(yytext); 
                                    return token::FLOAT;
                                }

{NUM}+\.{NUM}+                  {   // Float
                                    yylval->build<std::string>(yytext); 
                                    return token::FLOAT;
                                }

{NUM}+              {   // Number
                        yylval->build<std::string>(yytext); 
                        return token::NUMBER; 
                    }

{ALPHANUM}+         {   // Text
                        yylval->build<std::string>(yytext);
                        return token::TEXT;
                    }

\n                  {   // New line
                        loc->lines();
                        return token::NEWLINE;
                    }

.                   {   // Anything else is symbol
                        yylval->build<std::string>(yytext); 
                        return token::SYMBOL; 
                    }
%%
