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
","                             {   return token::COMMA      ;  }
[-]?{NUM}+                      {   /* Integer */
                                    // atoi can be used since syntactical analysis was done here
                                    yylval->emplace<int>(atoi(yytext));
                                    return token::INT;
                                }
[-]?{NUM}+\.{NUM}+[eE][+-]?{NUM}+ {   // Float in scientific notation
                                    yylval->build<float>(std::stof(yytext)); 
                                    return token::CONST_FLOAT;
                                }
[-]?{NUM}+\.{NUM}+              {   // Float
                                    yylval->build<float>(std::stof(yytext)); 
                                    return token::CONST_FLOAT;
                                }
"$"[0-9]+                       {   /* Variable */
                                    // atoi can be used since syntactical analysis was done here
                                    yylval->emplace<int>(atoi(&yytext[1]));
                                    return token::VAR;
                                }
"$"                             {   /* $0 variable */
                                    yylval->emplace<int>(0);
                                    return token::VAR;
                                }
"CONCAT"{SPACE}+                {   return token::CONCAT;     }
"DEL"                           {   return token::DEL;        }
"LOOP"                          {   return token::LOOP;       }
"NOP"                           {   return token::NOP;        }
"PASS"{SPACE}+                  {   return token::PASS;       }
"WORD"[S]?                      {   return token::WORDS;      }
"LINE"[S]?                      {   return token::LINES;      }
"DOCUMENT"[S]?                  {   return token::DOCUMENTS;  }
"EXPRESSION"[S]?                {   return token::EXPRESSION; }
"SWAP"{SPACE}+                  {   return token::SWAP;       }
"RETURN"                        {   return token::RETURN;     }

"ADD"{SPACE}+                   {   return token::ADD;        }
"SUB"{SPACE}+                   {   return token::SUB;        }
"MUL"{SPACE}+                   {   return token::MUL;        }
"DIV"{SPACE}+                   {   return token::DIV;        }
"MOD"{SPACE}+                   {   return token::MOD;        }
"POW"{SPACE}+                   {   return token::POW;        }
"MOVE"{SPACE}+                  {   return token::MOVE;       }

"TEXT"{SPACE}+                  {   return token::TEXT;       }
"NUMBER"{SPACE}+                {   return token::NUMBER;     }
"FLOAT"{SPACE}+                 {   return token::FLOAT;      }
"DELIMITER"{SPACE}+             {   return token::DELIMITER;  }
"SYMBOL"{SPACE}+                {   return token::SYMBOL;     }
"EMPTY"{SPACE}+                 {   return token::EMPTY;      }
"DERIVED"{SPACE}+               {   return token::DERIVED;    }

\".*\"                          {   
                                    remove_quotes(&yytext);
                                    yylval->build<std::string>(yytext);
                                    return token::STRING;     
                                }

"@pragma"{SPACE}+[^\n]+         {   
                                    yylval->build<std::string>(&yytext[8]);
                                    return token::PRAGMA;     
                                }

\n                              {
                                    loc->lines();
                                    return token::NEWLINE;
                                }
[a-zA-Z0-9_]+                   {   /* Error because of unknown instruction, but don't exit yet */
                                    sub_error(Error::ErrorCode::SYNTACTIC, std::string("Unknown instruction '")
                                                +std::string(yytext) +std::string("'"));
                                }
.                               {   /* Error because of unknwon symbol, but don't exit yet */
                                    sub_error(Error::ErrorCode::SYNTACTIC, std::string("Unknown symbol '")
                                                +std::string(yytext)+std::string("'"));
                                }

%%