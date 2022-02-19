// A Bison parser, made by GNU Bison 3.8.2.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2021 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.

// DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
// especially those whose name start with YY_ or yy_.  They are
// private implementation details that can be changed or removed.


// Take the name prefix into account.
#define yylex   eelex



#include "parser_ebel.hpp"


// Unqualified %code blocks.
#line 43 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_ebel.yy"

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

#line 63 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_ebel.cpp"


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif


// Whether we are compiled with exception support.
#ifndef YY_EXCEPTIONS
# if defined __GNUC__ && !defined __EXCEPTIONS
#  define YY_EXCEPTIONS 0
# else
#  define YY_EXCEPTIONS 1
# endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (false)
# endif


// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << '\n';                       \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yy_stack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YY_USE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 17 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_ebel.yy"
namespace  EbelFile  {
#line 156 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_ebel.cpp"

  /// Build a parser object.
   ParserEbel :: ParserEbel  (ScannerEbel *scanner_yyarg)
#if YYDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
#else
    :
#endif
      scanner (scanner_yyarg)
  {}

   ParserEbel ::~ ParserEbel  ()
  {}

   ParserEbel ::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------.
  | symbol.  |
  `---------*/

  // basic_symbol.
  template <typename Base>
   ParserEbel ::basic_symbol<Base>::basic_symbol (const basic_symbol& that)
    : Base (that)
    , value ()
    , location (that.location)
  {
    switch (this->kind ())
    {
      case symbol_kind::S_type: // type
        value.copy< IR::Type > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_INT: // "number"
      case symbol_kind::S_VAR: // "variable"
        value.copy< int > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_STRING: // "string"
      case symbol_kind::S_PRAGMA: // PRAGMA
        value.copy< std::string > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

  }




  template <typename Base>
   ParserEbel ::symbol_kind_type
   ParserEbel ::basic_symbol<Base>::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }


  template <typename Base>
  bool
   ParserEbel ::basic_symbol<Base>::empty () const YY_NOEXCEPT
  {
    return this->kind () == symbol_kind::S_YYEMPTY;
  }

  template <typename Base>
  void
   ParserEbel ::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move (s);
    switch (this->kind ())
    {
      case symbol_kind::S_type: // type
        value.move< IR::Type > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_INT: // "number"
      case symbol_kind::S_VAR: // "variable"
        value.move< int > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_STRING: // "string"
      case symbol_kind::S_PRAGMA: // PRAGMA
        value.move< std::string > (YY_MOVE (s.value));
        break;

      default:
        break;
    }

    location = YY_MOVE (s.location);
  }

  // by_kind.
   ParserEbel ::by_kind::by_kind () YY_NOEXCEPT
    : kind_ (symbol_kind::S_YYEMPTY)
  {}

#if 201103L <= YY_CPLUSPLUS
   ParserEbel ::by_kind::by_kind (by_kind&& that) YY_NOEXCEPT
    : kind_ (that.kind_)
  {
    that.clear ();
  }
#endif

   ParserEbel ::by_kind::by_kind (const by_kind& that) YY_NOEXCEPT
    : kind_ (that.kind_)
  {}

   ParserEbel ::by_kind::by_kind (token_kind_type t) YY_NOEXCEPT
    : kind_ (yytranslate_ (t))
  {}



  void
   ParserEbel ::by_kind::clear () YY_NOEXCEPT
  {
    kind_ = symbol_kind::S_YYEMPTY;
  }

  void
   ParserEbel ::by_kind::move (by_kind& that)
  {
    kind_ = that.kind_;
    that.clear ();
  }

   ParserEbel ::symbol_kind_type
   ParserEbel ::by_kind::kind () const YY_NOEXCEPT
  {
    return kind_;
  }


   ParserEbel ::symbol_kind_type
   ParserEbel ::by_kind::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }



  // by_state.
   ParserEbel ::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

   ParserEbel ::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
   ParserEbel ::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
   ParserEbel ::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

   ParserEbel ::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

   ParserEbel ::symbol_kind_type
   ParserEbel ::by_state::kind () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return symbol_kind::S_YYEMPTY;
    else
      return YY_CAST (symbol_kind_type, yystos_[+state]);
  }

   ParserEbel ::stack_symbol_type::stack_symbol_type ()
  {}

   ParserEbel ::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state), YY_MOVE (that.location))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_type: // type
        value.YY_MOVE_OR_COPY< IR::Type > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_INT: // "number"
      case symbol_kind::S_VAR: // "variable"
        value.YY_MOVE_OR_COPY< int > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_STRING: // "string"
      case symbol_kind::S_PRAGMA: // PRAGMA
        value.YY_MOVE_OR_COPY< std::string > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

   ParserEbel ::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s, YY_MOVE (that.location))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_type: // type
        value.move< IR::Type > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_INT: // "number"
      case symbol_kind::S_VAR: // "variable"
        value.move< int > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_STRING: // "string"
      case symbol_kind::S_PRAGMA: // PRAGMA
        value.move< std::string > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

    // that is emptied.
    that.kind_ = symbol_kind::S_YYEMPTY;
  }

#if YY_CPLUSPLUS < 201103L
   ParserEbel ::stack_symbol_type&
   ParserEbel ::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_type: // type
        value.copy< IR::Type > (that.value);
        break;

      case symbol_kind::S_INT: // "number"
      case symbol_kind::S_VAR: // "variable"
        value.copy< int > (that.value);
        break;

      case symbol_kind::S_STRING: // "string"
      case symbol_kind::S_PRAGMA: // PRAGMA
        value.copy< std::string > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    return *this;
  }

   ParserEbel ::stack_symbol_type&
   ParserEbel ::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_type: // type
        value.move< IR::Type > (that.value);
        break;

      case symbol_kind::S_INT: // "number"
      case symbol_kind::S_VAR: // "variable"
        value.move< int > (that.value);
        break;

      case symbol_kind::S_STRING: // "string"
      case symbol_kind::S_PRAGMA: // PRAGMA
        value.move< std::string > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    // that is emptied.
    that.state = empty_state;
    return *this;
  }
#endif

  template <typename Base>
  void
   ParserEbel ::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
   ParserEbel ::yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YY_USE (yyoutput);
    if (yysym.empty ())
      yyo << "empty symbol";
    else
      {
        symbol_kind_type yykind = yysym.kind ();
        yyo << (yykind < YYNTOKENS ? "token" : "nterm")
            << ' ' << yysym.name () << " ("
            << yysym.location << ": ";
        YY_USE (yykind);
        yyo << ')';
      }
  }
#endif

  void
   ParserEbel ::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
   ParserEbel ::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
   ParserEbel ::yypop_ (int n) YY_NOEXCEPT
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
   ParserEbel ::debug_stream () const
  {
    return *yycdebug_;
  }

  void
   ParserEbel ::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


   ParserEbel ::debug_level_type
   ParserEbel ::debug_level () const
  {
    return yydebug_;
  }

  void
   ParserEbel ::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

   ParserEbel ::state_type
   ParserEbel ::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - YYNTOKENS] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - YYNTOKENS];
  }

  bool
   ParserEbel ::yy_pact_value_is_default_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yypact_ninf_;
  }

  bool
   ParserEbel ::yy_table_value_is_error_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yytable_ninf_;
  }

  int
   ParserEbel ::operator() ()
  {
    return parse ();
  }

  int
   ParserEbel ::parse ()
  {
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

    /// The return value of parse ().
    int yyresult;

#if YY_EXCEPTIONS
    try
#endif // YY_EXCEPTIONS
      {
    YYCDEBUG << "Starting parse\n";


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, YY_MOVE (yyla));

  /*-----------------------------------------------.
  | yynewstate -- push a new symbol on the stack.  |
  `-----------------------------------------------*/
  yynewstate:
    YYCDEBUG << "Entering state " << int (yystack_[0].state) << '\n';
    YY_STACK_PRINT ();

    // Accept?
    if (yystack_[0].state == yyfinal_)
      YYACCEPT;

    goto yybackup;


  /*-----------.
  | yybackup.  |
  `-----------*/
  yybackup:
    // Try to take a decision without lookahead.
    yyn = yypact_[+yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token\n";
#if YY_EXCEPTIONS
        try
#endif // YY_EXCEPTIONS
          {
            yyla.kind_ = yytranslate_ (yylex (&yyla.value, &yyla.location));
          }
#if YY_EXCEPTIONS
        catch (const syntax_error& yyexc)
          {
            YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
            error (yyexc);
            goto yyerrlab1;
          }
#endif // YY_EXCEPTIONS
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    if (yyla.kind () == symbol_kind::S_YYerror)
    {
      // The scanner already issued an error message, process directly
      // to error recovery.  But do not keep the error token as
      // lookahead, it is too special and may lead us to an endless
      // loop in error recovery. */
      yyla.kind_ = symbol_kind::S_YYUNDEF;
      goto yyerrlab1;
    }

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.kind ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.kind ())
      {
        goto yydefault;
      }

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", state_type (yyn), YY_MOVE (yyla));
    goto yynewstate;


  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[+yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;


  /*-----------------------------.
  | yyreduce -- do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_ (yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
      switch (yyr1_[yyn])
    {
      case symbol_kind::S_type: // type
        yylhs.value.emplace< IR::Type > ();
        break;

      case symbol_kind::S_INT: // "number"
      case symbol_kind::S_VAR: // "variable"
        yylhs.value.emplace< int > ();
        break;

      case symbol_kind::S_STRING: // "string"
      case symbol_kind::S_PRAGMA: // PRAGMA
        yylhs.value.emplace< std::string > ();
        break;

      default:
        break;
    }


      // Default location.
      {
        stack_type::slice range (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, range, yylen);
        yyerror_range[1].location = yylhs.location;
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
#if YY_EXCEPTIONS
      try
#endif // YY_EXCEPTIONS
        {
          switch (yyn)
            {
  case 12: // pragma: PRAGMA
#line 126 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_ebel.yy"
                                    { scanner->add_pragma(yystack_[0].value.as < std::string > ());          }
#line 743 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_ebel.cpp"
    break;

  case 13: // pragma: pragma "new line" PRAGMA
#line 127 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_ebel.yy"
                                    { scanner->add_pragma(yystack_[0].value.as < std::string > ());          }
#line 749 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_ebel.cpp"
    break;

  case 20: // instruction: CONCAT "number"
#line 138 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_ebel.yy"
                                   { scanner->add_concat(yystack_[0].value.as < int > ());          }
#line 755 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_ebel.cpp"
    break;

  case 21: // instruction: DEL
#line 139 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_ebel.yy"
                                   { scanner->add_del();               }
#line 761 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_ebel.cpp"
    break;

  case 22: // instruction: LOOP
#line 140 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_ebel.yy"
                                   { scanner->add_loop();              }
#line 767 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_ebel.cpp"
    break;

  case 23: // instruction: NOP
#line 141 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_ebel.yy"
                                   { scanner->add_nop();               }
#line 773 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_ebel.cpp"
    break;

  case 24: // instruction: SWAP "number"
#line 142 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_ebel.yy"
                                   { scanner->add_swap(yystack_[0].value.as < int > ());            }
#line 779 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_ebel.cpp"
    break;

  case 25: // instruction: RETURN SWAP "number"
#line 143 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_ebel.yy"
                                   { scanner->add_return(); scanner->add_swap(yystack_[0].value.as < int > ()); }
#line 785 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_ebel.cpp"
    break;

  case 26: // instruction: RETURN DEL
#line 144 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_ebel.yy"
                                   { scanner->add_return(); scanner->add_del(); }
#line 791 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_ebel.cpp"
    break;

  case 27: // instruction: RETURN NOP
#line 145 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_ebel.yy"
                                   { scanner->add_return(); scanner->add_nop(); }
#line 797 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_ebel.cpp"
    break;

  case 28: // instruction: RETURN
#line 146 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_ebel.yy"
                                   { scanner->add_return(); scanner->add_nop(); }
#line 803 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_ebel.cpp"
    break;

  case 29: // expr_inst: ADD "variable" "," "variable" "," "variable"
#line 149 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_ebel.yy"
                                                { scanner->add_add(yystack_[4].value.as < int > (), yystack_[2].value.as < int > (), yystack_[0].value.as < int > ());                      }
#line 809 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_ebel.cpp"
    break;

  case 30: // expr_inst: ADD "variable" "," "variable" "," "number"
#line 150 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_ebel.yy"
                                                { scanner->add_add(yystack_[4].value.as < int > (), yystack_[2].value.as < int > (), new Vars::NumberVar(yystack_[0].value.as < int > ())); }
#line 815 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_ebel.cpp"
    break;

  case 31: // expr_inst: ADD "variable" "," "number" "," "variable"
#line 151 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_ebel.yy"
                                                { scanner->add_add(yystack_[4].value.as < int > (), new Vars::NumberVar(yystack_[2].value.as < int > ()), yystack_[0].value.as < int > ()); }
#line 821 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_ebel.cpp"
    break;

  case 32: // expr_inst: ADD "variable" "," "number" "," "number"
#line 152 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_ebel.yy"
                                                { scanner->add_add(yystack_[4].value.as < int > (), new Vars::NumberVar(yystack_[2].value.as < int > ()), new Vars::NumberVar(yystack_[0].value.as < int > ())); }
#line 827 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_ebel.cpp"
    break;

  case 33: // expr_inst: SUB "variable" "," "variable" "," "variable"
#line 154 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_ebel.yy"
                                                { scanner->add_sub(yystack_[4].value.as < int > (), yystack_[2].value.as < int > (), yystack_[0].value.as < int > ());                      }
#line 833 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_ebel.cpp"
    break;

  case 34: // expr_inst: SUB "variable" "," "variable" "," "number"
#line 155 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_ebel.yy"
                                                { scanner->add_sub(yystack_[4].value.as < int > (), yystack_[2].value.as < int > (), new Vars::NumberVar(yystack_[0].value.as < int > ())); }
#line 839 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_ebel.cpp"
    break;

  case 35: // expr_inst: SUB "variable" "," "number" "," "variable"
#line 156 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_ebel.yy"
                                                { scanner->add_sub(yystack_[4].value.as < int > (), new Vars::NumberVar(yystack_[2].value.as < int > ()), yystack_[0].value.as < int > ()); }
#line 845 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_ebel.cpp"
    break;

  case 36: // expr_inst: SUB "variable" "," "number" "," "number"
#line 157 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_ebel.yy"
                                                { scanner->add_sub(yystack_[4].value.as < int > (), new Vars::NumberVar(yystack_[2].value.as < int > ()), new Vars::NumberVar(yystack_[0].value.as < int > ())); }
#line 851 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_ebel.cpp"
    break;

  case 37: // expr_inst: MUL "variable" "," "variable" "," "variable"
#line 159 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_ebel.yy"
                                                { scanner->add_mul(yystack_[4].value.as < int > (), yystack_[2].value.as < int > (), yystack_[0].value.as < int > ());                      }
#line 857 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_ebel.cpp"
    break;

  case 38: // expr_inst: MUL "variable" "," "variable" "," "number"
#line 160 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_ebel.yy"
                                                { scanner->add_mul(yystack_[4].value.as < int > (), yystack_[2].value.as < int > (), new Vars::NumberVar(yystack_[0].value.as < int > ())); }
#line 863 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_ebel.cpp"
    break;

  case 39: // expr_inst: MUL "variable" "," "number" "," "variable"
#line 161 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_ebel.yy"
                                                { scanner->add_mul(yystack_[4].value.as < int > (), new Vars::NumberVar(yystack_[2].value.as < int > ()), yystack_[0].value.as < int > ()); }
#line 869 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_ebel.cpp"
    break;

  case 40: // expr_inst: MUL "variable" "," "number" "," "number"
#line 162 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_ebel.yy"
                                                { scanner->add_mul(yystack_[4].value.as < int > (), new Vars::NumberVar(yystack_[2].value.as < int > ()), new Vars::NumberVar(yystack_[0].value.as < int > ())); }
#line 875 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_ebel.cpp"
    break;

  case 41: // expr_inst: DIV "variable" "," "variable" "," "variable"
#line 164 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_ebel.yy"
                                                { scanner->add_div(yystack_[4].value.as < int > (), yystack_[2].value.as < int > (), yystack_[0].value.as < int > ());                      }
#line 881 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_ebel.cpp"
    break;

  case 42: // expr_inst: DIV "variable" "," "variable" "," "number"
#line 165 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_ebel.yy"
                                                { scanner->add_div(yystack_[4].value.as < int > (), yystack_[2].value.as < int > (), new Vars::NumberVar(yystack_[0].value.as < int > ())); }
#line 887 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_ebel.cpp"
    break;

  case 43: // expr_inst: DIV "variable" "," "number" "," "variable"
#line 166 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_ebel.yy"
                                                { scanner->add_div(yystack_[4].value.as < int > (), new Vars::NumberVar(yystack_[2].value.as < int > ()), yystack_[0].value.as < int > ()); }
#line 893 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_ebel.cpp"
    break;

  case 44: // expr_inst: DIV "variable" "," "number" "," "number"
#line 167 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_ebel.yy"
                                                { scanner->add_div(yystack_[4].value.as < int > (), new Vars::NumberVar(yystack_[2].value.as < int > ()), new Vars::NumberVar(yystack_[0].value.as < int > ())); }
#line 899 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_ebel.cpp"
    break;

  case 45: // expr_inst: MOD "variable" "," "variable" "," "variable"
#line 169 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_ebel.yy"
                                                { scanner->add_mod(yystack_[4].value.as < int > (), yystack_[2].value.as < int > (), yystack_[0].value.as < int > ());                      }
#line 905 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_ebel.cpp"
    break;

  case 46: // expr_inst: MOD "variable" "," "variable" "," "number"
#line 170 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_ebel.yy"
                                                { scanner->add_mod(yystack_[4].value.as < int > (), yystack_[2].value.as < int > (), new Vars::NumberVar(yystack_[0].value.as < int > ())); }
#line 911 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_ebel.cpp"
    break;

  case 47: // expr_inst: MOD "variable" "," "number" "," "variable"
#line 171 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_ebel.yy"
                                                { scanner->add_mod(yystack_[4].value.as < int > (), new Vars::NumberVar(yystack_[2].value.as < int > ()), yystack_[0].value.as < int > ()); }
#line 917 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_ebel.cpp"
    break;

  case 48: // expr_inst: MOD "variable" "," "number" "," "number"
#line 172 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_ebel.yy"
                                                { scanner->add_mod(yystack_[4].value.as < int > (), new Vars::NumberVar(yystack_[2].value.as < int > ()), new Vars::NumberVar(yystack_[0].value.as < int > ())); }
#line 923 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_ebel.cpp"
    break;

  case 49: // expr_inst: POW "variable" "," "variable" "," "variable"
#line 174 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_ebel.yy"
                                                { scanner->add_pow(yystack_[4].value.as < int > (), yystack_[2].value.as < int > (), yystack_[0].value.as < int > ());                      }
#line 929 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_ebel.cpp"
    break;

  case 50: // expr_inst: POW "variable" "," "variable" "," "number"
#line 175 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_ebel.yy"
                                                { scanner->add_pow(yystack_[4].value.as < int > (), yystack_[2].value.as < int > (), new Vars::NumberVar(yystack_[0].value.as < int > ())); }
#line 935 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_ebel.cpp"
    break;

  case 51: // expr_inst: POW "variable" "," "number" "," "variable"
#line 176 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_ebel.yy"
                                                { scanner->add_pow(yystack_[4].value.as < int > (), new Vars::NumberVar(yystack_[2].value.as < int > ()), yystack_[0].value.as < int > ()); }
#line 941 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_ebel.cpp"
    break;

  case 52: // expr_inst: POW "variable" "," "number" "," "number"
#line 177 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_ebel.yy"
                                                { scanner->add_pow(yystack_[4].value.as < int > (), new Vars::NumberVar(yystack_[2].value.as < int > ()), new Vars::NumberVar(yystack_[0].value.as < int > ())); }
#line 947 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_ebel.cpp"
    break;

  case 53: // expr_inst: MOVE "variable" "," "variable"
#line 179 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_ebel.yy"
                                                { scanner->add_move(yystack_[2].value.as < int > (), yystack_[0].value.as < int > ());                         }
#line 953 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_ebel.cpp"
    break;

  case 54: // expr_inst: MOVE "variable" "," "number"
#line 180 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_ebel.yy"
                                                { scanner->add_move(yystack_[2].value.as < int > (), new Vars::NumberVar(yystack_[0].value.as < int > ()));    }
#line 959 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_ebel.cpp"
    break;

  case 55: // pass: PASS type "expression"
#line 183 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_ebel.yy"
                                     { scanner->add_pass_expression(yystack_[1].value.as < IR::Type > (), std::string(""));                }
#line 965 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_ebel.cpp"
    break;

  case 56: // pass: PASS "string" "expression"
#line 184 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_ebel.yy"
                                     { scanner->add_pass_expression(IR::Type::MATCH, yystack_[1].value.as < std::string > ());                }
#line 971 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_ebel.cpp"
    break;

  case 57: // pass: PASS "expression"
#line 185 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_ebel.yy"
                                     { scanner->add_pass_expression(IR::Type::DERIVED, std::string("")); }
#line 977 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_ebel.cpp"
    break;

  case 58: // pass: PASS "words"
#line 186 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_ebel.yy"
                                     { scanner->add_pass_words();                                        }
#line 983 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_ebel.cpp"
    break;

  case 59: // pass: PASS "lines"
#line 187 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_ebel.yy"
                                     { scanner->add_pass_lines();                                        }
#line 989 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_ebel.cpp"
    break;

  case 60: // pass: PASS "documents"
#line 188 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_ebel.yy"
                                     { scanner->add_pass_documents();                                    }
#line 995 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_ebel.cpp"
    break;

  case 61: // type: TEXT
#line 191 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_ebel.yy"
                        { yylhs.value.as < IR::Type > () = IR::Type::TEXT;      }
#line 1001 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_ebel.cpp"
    break;

  case 62: // type: NUMBER
#line 192 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_ebel.yy"
                        { yylhs.value.as < IR::Type > () = IR::Type::NUMBER;    }
#line 1007 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_ebel.cpp"
    break;

  case 63: // type: FLOAT
#line 193 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_ebel.yy"
                        { yylhs.value.as < IR::Type > () = IR::Type::FLOAT;     }
#line 1013 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_ebel.cpp"
    break;

  case 64: // type: DELIMITER
#line 194 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_ebel.yy"
                        { yylhs.value.as < IR::Type > () = IR::Type::DELIMITER; }
#line 1019 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_ebel.cpp"
    break;

  case 65: // type: SYMBOL
#line 195 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_ebel.yy"
                        { yylhs.value.as < IR::Type > () = IR::Type::SYMBOL;    }
#line 1025 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_ebel.cpp"
    break;

  case 66: // type: EMPTY
#line 196 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_ebel.yy"
                        { yylhs.value.as < IR::Type > () = IR::Type::EMPTY;     }
#line 1031 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_ebel.cpp"
    break;

  case 67: // type: DERIVED
#line 197 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_ebel.yy"
                        { yylhs.value.as < IR::Type > () = IR::Type::DERIVED;   }
#line 1037 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_ebel.cpp"
    break;


#line 1041 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_ebel.cpp"

            default:
              break;
            }
        }
#if YY_EXCEPTIONS
      catch (const syntax_error& yyexc)
        {
          YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
          error (yyexc);
          YYERROR;
        }
#endif // YY_EXCEPTIONS
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, YY_MOVE (yylhs));
    }
    goto yynewstate;


  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        context yyctx (*this, yyla);
        std::string msg = yysyntax_error_ (yyctx);
        error (yyla.location, YY_MOVE (msg));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.kind () == symbol_kind::S_YYEOF)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:
    /* Pacify compilers when the user code never invokes YYERROR and
       the label yyerrorlab therefore never appears in user code.  */
    if (false)
      YYERROR;

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    YY_STACK_PRINT ();
    goto yyerrlab1;


  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    // Pop stack until we find a state that shifts the error token.
    for (;;)
      {
        yyn = yypact_[+yystack_[0].state];
        if (!yy_pact_value_is_default_ (yyn))
          {
            yyn += symbol_kind::S_YYerror;
            if (0 <= yyn && yyn <= yylast_
                && yycheck_[yyn] == symbol_kind::S_YYerror)
              {
                yyn = yytable_[yyn];
                if (0 < yyn)
                  break;
              }
          }

        // Pop the current state because it cannot handle the error token.
        if (yystack_.size () == 1)
          YYABORT;

        yyerror_range[1].location = yystack_[0].location;
        yy_destroy_ ("Error: popping", yystack_[0]);
        yypop_ ();
        YY_STACK_PRINT ();
      }
    {
      stack_symbol_type error_token;

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      error_token.state = state_type (yyn);
      yypush_ ("Shifting", YY_MOVE (error_token));
    }
    goto yynewstate;


  /*-------------------------------------.
  | yyacceptlab -- YYACCEPT comes here.  |
  `-------------------------------------*/
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;


  /*-----------------------------------.
  | yyabortlab -- YYABORT comes here.  |
  `-----------------------------------*/
  yyabortlab:
    yyresult = 1;
    goto yyreturn;


  /*-----------------------------------------------------.
  | yyreturn -- parsing is finished, return the result.  |
  `-----------------------------------------------------*/
  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    YY_STACK_PRINT ();
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
#if YY_EXCEPTIONS
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack\n";
        // Do not try to display the values of the reclaimed symbols,
        // as their printers might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
#endif // YY_EXCEPTIONS
  }

  void
   ParserEbel ::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what ());
  }

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
   ParserEbel ::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr;
        char const *yyp = yystr;

        for (;;)
          switch (*++yyp)
            {
            case '\'':
            case ',':
              goto do_not_strip_quotes;

            case '\\':
              if (*++yyp != '\\')
                goto do_not_strip_quotes;
              else
                goto append;

            append:
            default:
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }

  std::string
   ParserEbel ::symbol_name (symbol_kind_type yysymbol)
  {
    return yytnamerr_ (yytname_[yysymbol]);
  }



  //  ParserEbel ::context.
   ParserEbel ::context::context (const  ParserEbel & yyparser, const symbol_type& yyla)
    : yyparser_ (yyparser)
    , yyla_ (yyla)
  {}

  int
   ParserEbel ::context::expected_tokens (symbol_kind_type yyarg[], int yyargn) const
  {
    // Actual number of expected tokens
    int yycount = 0;

    const int yyn = yypact_[+yyparser_.yystack_[0].state];
    if (!yy_pact_value_is_default_ (yyn))
      {
        /* Start YYX at -YYN if negative to avoid negative indexes in
           YYCHECK.  In other words, skip the first -YYN actions for
           this state because they are default actions.  */
        const int yyxbegin = yyn < 0 ? -yyn : 0;
        // Stay within bounds of both yycheck and yytname.
        const int yychecklim = yylast_ - yyn + 1;
        const int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
        for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
          if (yycheck_[yyx + yyn] == yyx && yyx != symbol_kind::S_YYerror
              && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
            {
              if (!yyarg)
                ++yycount;
              else if (yycount == yyargn)
                return 0;
              else
                yyarg[yycount++] = YY_CAST (symbol_kind_type, yyx);
            }
      }

    if (yyarg && yycount == 0 && 0 < yyargn)
      yyarg[0] = symbol_kind::S_YYEMPTY;
    return yycount;
  }






  int
   ParserEbel ::yy_syntax_error_arguments_ (const context& yyctx,
                                                 symbol_kind_type yyarg[], int yyargn) const
  {
    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yyla) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yyla.  (However, yyla is currently not documented for users.)
       - Of course, the expected token list depends on states to have
         correct lookahead information, and it depends on the parser not
         to perform extra reductions after fetching a lookahead from the
         scanner and before detecting a syntax error.  Thus, state merging
         (from LALR or IELR) and default reductions corrupt the expected
         token list.  However, the list is correct for canonical LR with
         one exception: it will still contain any token that will not be
         accepted due to an error action in a later state.
    */

    if (!yyctx.lookahead ().empty ())
      {
        if (yyarg)
          yyarg[0] = yyctx.token ();
        int yyn = yyctx.expected_tokens (yyarg ? yyarg + 1 : yyarg, yyargn - 1);
        return yyn + 1;
      }
    return 0;
  }

  // Generate an error message.
  std::string
   ParserEbel ::yysyntax_error_ (const context& yyctx) const
  {
    // Its maximum.
    enum { YYARGS_MAX = 5 };
    // Arguments of yyformat.
    symbol_kind_type yyarg[YYARGS_MAX];
    int yycount = yy_syntax_error_arguments_ (yyctx, yyarg, YYARGS_MAX);

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
      default: // Avoid compiler warnings.
        YYCASE_ (0, YY_("syntax error"));
        YYCASE_ (1, YY_("syntax error, unexpected %s"));
        YYCASE_ (2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_ (3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_ (4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_ (5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    std::string yyres;
    // Argument number.
    std::ptrdiff_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += symbol_name (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const signed char  ParserEbel ::yypact_ninf_ = -19;

  const signed char  ParserEbel ::yytable_ninf_ = -1;

  const short
   ParserEbel ::yypact_[] =
  {
      29,   -19,   -18,   -19,   -19,    27,   -19,   -19,   -19,    -6,
      44,    56,    46,    42,   101,    33,   -19,   -19,   -19,   -19,
      81,   -19,   -19,   -19,   -19,   -19,   -19,   -19,   -19,   -19,
     -19,   -19,    82,   -19,   -19,   -19,   102,   -19,   -19,   106,
     107,    50,   -19,    77,    -7,   -19,   -19,   -19,    50,   -19,
     107,   -19,   108,   109,   110,   111,   112,   113,   114,   -19,
     -19,   -19,   107,   116,   117,   118,   119,   120,   121,   122,
      43,    63,    67,    68,    71,    72,    75,   123,   124,   125,
     126,   127,   128,   129,   130,   131,   132,   133,   134,   -19,
     -19,    76,    79,    80,    83,    84,    87,    88,    91,    92,
      95,    96,    99,   -19,   -19,   -19,   -19,   -19,   -19,   -19,
     -19,   -19,   -19,   -19,   -19,   -19,   -19,   -19,   -19,   -19,
     -19,   -19,   -19,   -19,   -19,   -19,   -19
  };

  const signed char
   ParserEbel ::yydefact_[] =
  {
       0,     9,     0,    10,    12,     0,    21,    22,    23,     0,
       0,    28,     0,     2,     0,     0,    14,    15,     8,    20,
       0,    58,    59,    60,    57,    61,    62,    63,    64,    65,
      66,    67,     0,    24,    26,    27,     0,     1,    11,     0,
       3,     0,     6,     0,    16,    56,    55,    25,     0,    13,
       5,     7,     0,     0,     0,     0,     0,     0,     0,    17,
      18,    19,     4,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    54,
      53,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    32,    31,    30,    29,    36,    35,    34,
      33,    40,    39,    38,    37,    44,    43,    42,    41,    48,
      47,    46,    45,    52,    51,    50,    49
  };

  const signed char
   ParserEbel ::yypgoto_[] =
  {
     -19,   -19,   -19,   100,   -13,    97,   -19,    98,   -19
  };

  const signed char
   ParserEbel ::yydefgoto_[] =
  {
       0,    12,    13,    14,    15,    16,    60,    17,    32
  };

  const signed char
   ParserEbel ::yytable_[] =
  {
      40,    20,     5,     6,     7,     8,     9,    10,    11,    52,
      53,    54,    55,    56,    57,    58,    18,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    50,     1,
       2,    19,     3,    42,    43,    62,    44,     4,     5,     6,
       7,     8,     9,    10,    11,    38,    37,    77,    33,    78,
       4,     5,     6,     7,     8,     9,    10,    11,    49,     5,
       6,     7,     8,     9,    10,    11,    34,    79,    35,    80,
      36,    81,    83,    82,    84,    85,    87,    86,    88,    89,
     103,    90,   104,   105,   107,   106,   108,   109,   111,   110,
     112,   113,   115,   114,   116,   117,   119,   118,   120,   121,
     123,   122,   124,   125,    41,   126,    47,    45,    46,    48,
      44,    51,     0,    39,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   100,   101,   102,
       0,    59,    61
  };

  const signed char
   ParserEbel ::yycheck_[] =
  {
      13,     7,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    34,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    41,     0,
       1,     4,     3,     0,     1,    48,     3,     8,     9,    10,
      11,    12,    13,    14,    15,     3,     0,     4,     4,     6,
       8,     9,    10,    11,    12,    13,    14,    15,     8,     9,
      10,    11,    12,    13,    14,    15,    10,     4,    12,     6,
      14,     4,     4,     6,     6,     4,     4,     6,     6,     4,
       4,     6,     6,     4,     4,     6,     6,     4,     4,     6,
       6,     4,     4,     6,     6,     4,     4,     6,     6,     4,
       4,     6,     6,     4,     3,     6,     4,    26,    26,     3,
       3,    34,    -1,    13,     6,     6,     6,     6,     6,     6,
       6,     5,     5,     5,     5,     5,     5,     5,     5,     5,
       5,     5,     5,     5,     5,     5,     5,     5,     5,     5,
      -1,    44,    44
  };

  const signed char
   ParserEbel ::yystos_[] =
  {
       0,     0,     1,     3,     8,     9,    10,    11,    12,    13,
      14,    15,    36,    37,    38,    39,    40,    42,    34,     4,
       7,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    43,     4,    10,    12,    14,     0,     3,    38,
      39,     3,     0,     1,     3,    26,    26,     4,     3,     8,
      39,    34,    16,    17,    18,    19,    20,    21,    22,    40,
      41,    42,    39,     6,     6,     6,     6,     6,     6,     6,
       5,     5,     5,     5,     5,     5,     5,     4,     6,     4,
       6,     4,     6,     4,     6,     4,     6,     4,     6,     4,
       6,     5,     5,     5,     5,     5,     5,     5,     5,     5,
       5,     5,     5,     4,     6,     4,     6,     4,     6,     4,
       6,     4,     6,     4,     6,     4,     6,     4,     6,     4,
       6,     4,     6,     4,     6,     4,     6
  };

  const signed char
   ParserEbel ::yyr1_[] =
  {
       0,    35,    36,    36,    36,    36,    36,    36,    36,    37,
      37,    37,    38,    38,    39,    39,    39,    39,    39,    39,
      40,    40,    40,    40,    40,    40,    40,    40,    40,    41,
      41,    41,    41,    41,    41,    41,    41,    41,    41,    41,
      41,    41,    41,    41,    41,    41,    41,    41,    41,    41,
      41,    41,    41,    41,    41,    42,    42,    42,    42,    42,
      42,    43,    43,    43,    43,    43,    43,    43
  };

  const signed char
   ParserEbel ::yyr2_[] =
  {
       0,     2,     1,     2,     4,     3,     2,     3,     2,     1,
       1,     2,     1,     3,     1,     1,     2,     3,     3,     3,
       2,     1,     1,     1,     2,     3,     2,     2,     1,     6,
       6,     6,     6,     6,     6,     6,     6,     6,     6,     6,
       6,     6,     6,     6,     6,     6,     6,     6,     6,     6,
       6,     6,     6,     4,     4,     3,     3,     2,     2,     2,
       2,     1,     1,     1,     1,     1,     1,     1
  };


#if YYDEBUG || 1
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a YYNTOKENS, nonterminals.
  const char*
  const  ParserEbel ::yytname_[] =
  {
  "\"end of file\"", "error", "\"invalid token\"", "\"new line\"",
  "\"number\"", "\",\"", "\"variable\"", "\"string\"", "PRAGMA", "CONCAT",
  "DEL", "LOOP", "NOP", "PASS", "SWAP", "RETURN", "ADD", "SUB", "MUL",
  "DIV", "MOD", "POW", "MOVE", "\"words\"", "\"lines\"", "\"documents\"",
  "\"expression\"", "TEXT", "NUMBER", "FLOAT", "DELIMITER", "SYMBOL",
  "EMPTY", "DERIVED", "'\\n'", "$accept", "program", "empty", "pragma",
  "code", "instruction", "expr_inst", "pass", "type", YY_NULLPTR
  };
#endif


#if YYDEBUG
  const unsigned char
   ParserEbel ::yyrline_[] =
  {
       0,   112,   112,   113,   114,   115,   116,   117,   118,   121,
     122,   123,   126,   127,   130,   131,   132,   133,   134,   135,
     138,   139,   140,   141,   142,   143,   144,   145,   146,   149,
     150,   151,   152,   154,   155,   156,   157,   159,   160,   161,
     162,   164,   165,   166,   167,   169,   170,   171,   172,   174,
     175,   176,   177,   179,   180,   183,   184,   185,   186,   187,
     188,   191,   192,   193,   194,   195,   196,   197
  };

  void
   ParserEbel ::yy_stack_print_ () const
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << int (i->state);
    *yycdebug_ << '\n';
  }

  void
   ParserEbel ::yy_reduce_print_ (int yyrule) const
  {
    int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):\n";
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG

   ParserEbel ::symbol_kind_type
   ParserEbel ::yytranslate_ (int t) YY_NOEXCEPT
  {
    // YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to
    // TOKEN-NUM as returned by yylex.
    static
    const signed char
    translate_table[] =
    {
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      34,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33
    };
    // Last valid token kind.
    const int code_max = 288;

    if (t <= 0)
      return symbol_kind::S_YYEOF;
    else if (t <= code_max)
      return static_cast <symbol_kind_type> (translate_table[t]);
    else
      return symbol_kind::S_YYUNDEF;
  }

#line 17 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_ebel.yy"
} //  EbelFile 
#line 1637 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_ebel.cpp"

#line 200 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_ebel.yy"


/* Error method */
void EbelFile::ParserEbel::error(const location_type &l, const std::string &err_message) {
    scanner->sub_error(Error::ErrorCode::SYNTACTIC, err_message);
}
