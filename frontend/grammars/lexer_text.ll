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

#define YY_USER_ACTION loc->step(); loc->columns(yyleng);

// Typedef to shorten scope
using token = TextFile::ParserText::token;

// Redefine termination token to not use NULL
#define yyterminate() return (token::END)

%}

%option nodefault
%option noyywrap
%option c++
%option yylineno

/* Define what scanner class is used */
%option yyclass="TextFile::ScannerText"

/* Macros for symbol types */
DELIMITER [ \f\r\t\v,.:;]
NUM       [0-9]
ALPHANUM  [a-zA-Z0-9\_\x80-\xf3]


%%
%{
    yylval = lval;    
%}

"{!"                {   // Expression starts
                        expr_start();
                        // Check if expressions are allowed
                        if(is_in_expr())
                            return token::EXPR_BEGIN;
                        else
                            return token::FALSE_EXPR_BEGIN;
                    }
"!}"                {   // Expression ends
                        // Check if we even were inside of an expression
                        // Note: expr_end should not be called here, it is called after the whole expression
                        //       is parsed even inside the parser and scanner.
                        if(is_in_expr())
                            return token::EXPR_END;
                        return token::FALSE_EXPR_END;
                    }
"+"                 {   yylval->build<std::string>(yytext); return token::PLUS;  }
"^"                 {   yylval->build<std::string>(yytext); return token::POW;   }
"%"                 {   yylval->build<std::string>(yytext); return token::MOD;   }
"*"                 {   yylval->build<std::string>(yytext); return token::IMUL;  }
"-"                 {   yylval->build<std::string>(yytext); return token::MINUS; }
"/"                 {   yylval->build<std::string>(yytext); return token::IDIV;  }
"$"                 {   yylval->build<std::string>(yytext); return token::VAR;   }
"("                 {   yylval->build<std::string>(yytext); return token::LPAR;  }
")"                 {   yylval->build<std::string>(yytext); return token::RPAR;  }
"\""                {   quote_parsed(); yylval->build<std::string>(yytext); return token::QUOTE; }
[ \t]               {   // Whitespace is supposed to be ignored in expression
                        if(!is_in_expr() || is_in_str()){
                            yylval->build<std::string>(yytext);
                            return token::DELIMITER;
                        }
                    }
{DELIMITER}         {   // Delimiters
                        yylval->build<std::string>(yytext);
                        return token::DELIMITER;
                    }

{NUM}+\.{NUM}+[eE][+-]?{NUM}+       {   // Float in scientific notation
                                    yylval->build<std::string>(yytext); 
                                    return token::FLOAT;
                                    }

{NUM}+\.{NUM}+                      {   // Float
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
