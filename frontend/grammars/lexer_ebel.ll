/**
 * @author Marek Sedlacek
 * @date October 2021
 * 
 * @brief Ebel code lexems
 * Lexer file for flex tool for ebel source code.
 */

%{
    
#include <string>
#include "scanner_ebel.hpp"
#include "compiler.hpp"

// Define custom lex method
#undef YY_DECL
#define YY_DECL int EbelFile::ScannerEbel::eelex(EbelFile::ParserEbel::semantic_type * const lval, EbelFile::ParserEbel::location_type *location)

#define YY_USER_ACTION loc->step(); loc->columns(yyleng);

// Typedef to shorten scope
using token = EbelFile::ParserEbel::token;

// Redefine termination token to not use NULL
#define yyterminate() return (token::END)

%}

%option nodefault
%option noyywrap
%option c++
%option yylineno

/* Define what scanner class is used */
%option yyclass="EbelFile::ScannerEbel"

/* Ebel code is caseless, so case can be ignored */
%option caseless

/* Macros for tokens */
NUM     [0-9]
SPACE   [ \t]

%%
%{
    yylval = lval;    
%}

"#"+.*                          {   /* Line comment */       ; }
{SPACE}                         {   /* Spaces are ignored */ ; }
{NUM}+                          {   /* Integer */
                                    // TODO: Change to unsigned int and use Cast::to
                                    yylval->emplace<int>(atoi(yytext));
                                    return token::NUMBER;
                                }
"CONCAT"{SPACE}+                {   return token::CONCAT; }
"DEL"                           {   return token::DEL;    }
"LOOP"                          {   return token::LOOP;   }
"NOP"                           {   return token::NOP;    }
"PASS"{SPACE}+"WORD"[S]?        {   /* Pass words     */ return token::PASS_WORDS;     }
"PASS"{SPACE}+"LINE"[S]?        {   /* Pass lines     */ return token::PASS_LINES;     }
"PASS"{SPACE}+"DOCUMENT"[S]?    {   /* Pass documents */ return token::PASS_DOCUMENTS; }
"SWAP"{SPACE}+                  {   return token::SWAP;   }
\n                              {
                                    loc->lines();
                                    return token::NEWLINE;
                                }
[a-zA-Z0-9_]+                   {   /* Error because of unknown instruction, but don't exit yet */
                                    Error::error(Error::ErrorCode::SYNTACTIC, 
                                                 (std::string("Unknown instruction '")+std::string(yytext)
                                                 +std::string("'")).c_str(), nullptr, false);
                                    error_found(Error::ErrorCode::SYNTACTIC);
                                }
.                               {   /* Error because of unknwon symbol, but don't exit yet */
                                    Error::error(Error::ErrorCode::SYNTACTIC, 
                                                 (std::string("Unknown symbol '")+std::string(yytext)
                                                 +std::string("'")).c_str(), nullptr, false);
                                    error_found(Error::ErrorCode::SYNTACTIC);
                                }

%%