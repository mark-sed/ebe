// A Bison parser, made by GNU Bison 3.7.6.

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

  /*---------------.
  | symbol kinds.  |
  `---------------*/

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

      default:
        break;
    }

    location = YY_MOVE (s.location);
  }

  // by_kind.
   ParserEbel ::by_kind::by_kind ()
    : kind_ (symbol_kind::S_YYEMPTY)
  {}

#if 201103L <= YY_CPLUSPLUS
   ParserEbel ::by_kind::by_kind (by_kind&& that)
    : kind_ (that.kind_)
  {
    that.clear ();
  }
#endif

   ParserEbel ::by_kind::by_kind (const by_kind& that)
    : kind_ (that.kind_)
  {}

   ParserEbel ::by_kind::by_kind (token_kind_type t)
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
   ParserEbel ::yypop_ (int n)
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
   ParserEbel ::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  bool
   ParserEbel ::yy_table_value_is_error_ (int yyvalue)
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
  case 13: // instruction: CONCAT "number"
#line 116 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_ebel.yy"
                                   { scanner->add_concat(yystack_[0].value.as < int > ());          }
#line 702 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_ebel.cpp"
    break;

  case 14: // instruction: DEL
#line 117 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_ebel.yy"
                                   { scanner->add_del();               }
#line 708 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_ebel.cpp"
    break;

  case 15: // instruction: LOOP
#line 118 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_ebel.yy"
                                   { scanner->add_loop();              }
#line 714 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_ebel.cpp"
    break;

  case 16: // instruction: NOP
#line 119 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_ebel.yy"
                                   { scanner->add_nop();               }
#line 720 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_ebel.cpp"
    break;

  case 17: // instruction: SWAP "number"
#line 120 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_ebel.yy"
                                   { scanner->add_swap(yystack_[0].value.as < int > ());            }
#line 726 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_ebel.cpp"
    break;

  case 18: // instruction: RETURN SWAP "number"
#line 121 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_ebel.yy"
                                   { scanner->add_return(); scanner->add_swap(yystack_[0].value.as < int > ()); }
#line 732 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_ebel.cpp"
    break;

  case 19: // instruction: RETURN DEL
#line 122 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_ebel.yy"
                                   { scanner->add_return(); scanner->add_del(); }
#line 738 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_ebel.cpp"
    break;

  case 20: // instruction: RETURN NOP
#line 123 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_ebel.yy"
                                   { scanner->add_return(); scanner->add_nop(); }
#line 744 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_ebel.cpp"
    break;

  case 21: // instruction: RETURN
#line 124 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_ebel.yy"
                                   { scanner->add_return(); scanner->add_nop(); }
#line 750 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_ebel.cpp"
    break;

  case 22: // expr_inst: ADD "variable" "," "variable" "," "variable"
#line 127 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_ebel.yy"
                                                { scanner->add_add(yystack_[4].value.as < int > (), yystack_[2].value.as < int > (), yystack_[0].value.as < int > ()); }
#line 756 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_ebel.cpp"
    break;

  case 23: // expr_inst: ADD "variable" "," "variable" "," "number"
#line 128 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_ebel.yy"
                                                { scanner->add_add(yystack_[4].value.as < int > (), yystack_[2].value.as < int > (), new Vars::NumberVar(yystack_[0].value.as < int > ())); }
#line 762 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_ebel.cpp"
    break;

  case 24: // expr_inst: ADD "variable" "," "number" "," "variable"
#line 129 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_ebel.yy"
                                                { scanner->add_add(yystack_[4].value.as < int > (), new Vars::NumberVar(yystack_[2].value.as < int > ()), yystack_[0].value.as < int > ()); }
#line 768 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_ebel.cpp"
    break;

  case 25: // expr_inst: ADD "variable" "," "number" "," "number"
#line 130 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_ebel.yy"
                                                { scanner->add_add(yystack_[4].value.as < int > (), new Vars::NumberVar(yystack_[2].value.as < int > ()), new Vars::NumberVar(yystack_[0].value.as < int > ())); }
#line 774 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_ebel.cpp"
    break;

  case 26: // pass: PASS type "expression"
#line 133 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_ebel.yy"
                                   { scanner->add_pass_expression(yystack_[1].value.as < IR::Type > ()); }
#line 780 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_ebel.cpp"
    break;

  case 27: // pass: PASS "expression"
#line 134 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_ebel.yy"
                                   { scanner->add_pass_expression(IR::Type::DERIVED); }
#line 786 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_ebel.cpp"
    break;

  case 28: // pass: PASS "words"
#line 135 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_ebel.yy"
                                   { scanner->add_pass_words();        }
#line 792 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_ebel.cpp"
    break;

  case 29: // pass: PASS "lines"
#line 136 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_ebel.yy"
                                   { scanner->add_pass_lines();        }
#line 798 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_ebel.cpp"
    break;

  case 30: // pass: PASS "documents"
#line 137 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_ebel.yy"
                                   { scanner->add_pass_documents();    }
#line 804 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_ebel.cpp"
    break;

  case 31: // type: TEXT
#line 139 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_ebel.yy"
                        { yylhs.value.as < IR::Type > () = IR::Type::TEXT;      }
#line 810 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_ebel.cpp"
    break;

  case 32: // type: NUMBER
#line 140 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_ebel.yy"
                        { yylhs.value.as < IR::Type > () = IR::Type::NUMBER;    }
#line 816 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_ebel.cpp"
    break;

  case 33: // type: FLOAT
#line 141 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_ebel.yy"
                        { yylhs.value.as < IR::Type > () = IR::Type::FLOAT;     }
#line 822 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_ebel.cpp"
    break;

  case 34: // type: DELIMITER
#line 142 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_ebel.yy"
                        { yylhs.value.as < IR::Type > () = IR::Type::DELIMITER; }
#line 828 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_ebel.cpp"
    break;

  case 35: // type: SYMBOL
#line 143 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_ebel.yy"
                        { yylhs.value.as < IR::Type > () = IR::Type::SYMBOL;    }
#line 834 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_ebel.cpp"
    break;

  case 36: // type: EMPTY
#line 144 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_ebel.yy"
                        { yylhs.value.as < IR::Type > () = IR::Type::EMPTY;     }
#line 840 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_ebel.cpp"
    break;


#line 844 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_ebel.cpp"

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

    int yyn = yypact_[+yyparser_.yystack_[0].state];
    if (!yy_pact_value_is_default_ (yyn))
      {
        /* Start YYX at -YYN if negative to avoid negative indexes in
           YYCHECK.  In other words, skip the first -YYN actions for
           this state because they are default actions.  */
        int yyxbegin = yyn < 0 ? -yyn : 0;
        // Stay within bounds of both yycheck and yytname.
        int yychecklim = yylast_ - yyn + 1;
        int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
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


  const signed char  ParserEbel ::yypact_ninf_ = -21;

  const signed char  ParserEbel ::yytable_ninf_ = -1;

  const signed char
   ParserEbel ::yypact_[] =
  {
       0,   -21,   -20,   -21,    37,   -21,   -21,   -21,    -1,    38,
      -6,    43,    32,   -21,   -21,   -21,   -21,   -21,   -21,   -21,
     -21,   -21,   -21,   -21,   -21,   -21,   -21,    26,   -21,   -21,
     -21,    41,   -21,   -21,    21,    17,   -21,   -21,   -21,    42,
     -21,   -21,   -21,    44,    30,    45,    46,    33,    34,   -21,
     -21,   -21,   -21
  };

  const signed char
   ParserEbel ::yydefact_[] =
  {
       0,     2,     0,     8,     0,    14,    15,    16,     0,     0,
      21,     0,     0,     6,     7,     5,    13,    28,    29,    30,
      27,    31,    32,    33,    34,    35,    36,     0,    17,    19,
      20,     0,     1,     3,     0,     9,    26,    18,     4,     0,
      10,    11,    12,     0,     0,     0,     0,     0,     0,    25,
      24,    23,    22
  };

  const signed char
   ParserEbel ::yypgoto_[] =
  {
     -21,   -21,   -21,    12,   -21,    18,   -21
  };

  const signed char
   ParserEbel ::yydefgoto_[] =
  {
       0,    11,    12,    13,    41,    14,    27
  };

  const signed char
   ParserEbel ::yytable_[] =
  {
       1,     2,    29,     3,    30,    15,    31,     4,     5,     6,
       7,     8,     9,    10,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,     4,     5,     6,     7,     8,     9,
      10,    39,    33,    34,    45,    35,    46,    49,    51,    50,
      52,    16,    28,    32,    36,    37,    38,    40,    43,    44,
      47,    48,     0,    42
  };

  const signed char
   ParserEbel ::yycheck_[] =
  {
       0,     1,     8,     3,    10,    25,    12,     7,     8,     9,
      10,    11,    12,    13,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,     7,     8,     9,    10,    11,    12,
      13,    14,     0,     1,     4,     3,     6,     4,     4,     6,
       6,     4,     4,     0,    18,     4,    25,    35,     6,     5,
       5,     5,    -1,    35
  };

  const signed char
   ParserEbel ::yystos_[] =
  {
       0,     0,     1,     3,     7,     8,     9,    10,    11,    12,
      13,    27,    28,    29,    31,    25,     4,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    32,     4,     8,
      10,    12,     0,     0,     1,     3,    18,     4,    25,    14,
      29,    30,    31,     6,     5,     4,     6,     5,     5,     4,
       6,     4,     6
  };

  const signed char
   ParserEbel ::yyr1_[] =
  {
       0,    26,    27,    27,    27,    27,    28,    28,    28,    28,
      28,    28,    28,    29,    29,    29,    29,    29,    29,    29,
      29,    29,    30,    30,    30,    30,    31,    31,    31,    31,
      31,    32,    32,    32,    32,    32,    32
  };

  const signed char
   ParserEbel ::yyr2_[] =
  {
       0,     2,     1,     2,     3,     2,     1,     1,     1,     2,
       3,     3,     3,     2,     1,     1,     1,     2,     3,     2,
       2,     1,     6,     6,     6,     6,     3,     2,     2,     2,
       2,     1,     1,     1,     1,     1,     1
  };


#if YYDEBUG || 1
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a YYNTOKENS, nonterminals.
  const char*
  const  ParserEbel ::yytname_[] =
  {
  "\"end of file\"", "error", "\"invalid token\"", "\"new line\"",
  "\"number\"", "\",\"", "\"variable\"", "CONCAT", "DEL", "LOOP", "NOP",
  "PASS", "SWAP", "RETURN", "ADD", "\"words\"", "\"lines\"",
  "\"documents\"", "\"expression\"", "TEXT", "NUMBER", "FLOAT",
  "DELIMITER", "SYMBOL", "EMPTY", "'\\n'", "$accept", "program", "code",
  "instruction", "expr_inst", "pass", "type", YY_NULLPTR
  };
#endif


#if YYDEBUG
  const unsigned char
   ParserEbel ::yyrline_[] =
  {
       0,   101,   101,   102,   103,   104,   107,   108,   109,   110,
     111,   112,   113,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   127,   128,   129,   130,   133,   134,   135,   136,
     137,   139,   140,   141,   142,   143,   144
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
   ParserEbel ::yytranslate_ (int t)
  {
    // YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to
    // TOKEN-NUM as returned by yylex.
    static
    const signed char
    translate_table[] =
    {
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      25,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24
    };
    // Last valid token kind.
    const int code_max = 279;

    if (t <= 0)
      return symbol_kind::S_YYEOF;
    else if (t <= code_max)
      return YY_CAST (symbol_kind_type, translate_table[t]);
    else
      return symbol_kind::S_YYUNDEF;
  }

#line 17 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_ebel.yy"
} //  EbelFile 
#line 1387 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_ebel.cpp"

#line 147 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_ebel.yy"


/* Error method */
void EbelFile::ParserEbel::error(const location_type &l, const std::string &err_message) {
    scanner->sub_error(Error::ErrorCode::SYNTACTIC, err_message);
}
