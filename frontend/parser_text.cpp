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





#include "parser_text.hpp"


// Unqualified %code blocks.
#line 48 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"

    #include <cmath>
    #include <sstream>
    // Include compiler to use error
    #include "compiler.hpp"
    #include "scanner_text.hpp"

    // Set correct token method
    #undef yylex
    #define yylex scanner->yylex

#line 58 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"


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

#line 19 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
namespace  TextFile  {
#line 151 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"

  /// Build a parser object.
   ParserText :: ParserText  (ScannerText *scanner_yyarg)
#if YYDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
#else
    :
#endif
      scanner (scanner_yyarg)
  {}

   ParserText ::~ ParserText  ()
  {}

   ParserText ::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------.
  | symbol.  |
  `---------*/

  // basic_symbol.
  template <typename Base>
   ParserText ::basic_symbol<Base>::basic_symbol (const basic_symbol& that)
    : Base (that)
    , value ()
    , location (that.location)
  {
    switch (this->kind ())
    {
      case symbol_kind::S_varexpr: // varexpr
        value.copy< Expr::Expression > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_float: // expr_float
        value.copy< float > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_int: // expr_int
        value.copy< int > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_TEXT: // TEXT
      case symbol_kind::S_NUMBER: // NUMBER
      case symbol_kind::S_DELIMITER: // DELIMITER
      case symbol_kind::S_SYMBOL: // SYMBOL
      case symbol_kind::S_FLOAT: // FLOAT
      case symbol_kind::S_LPAR: // "("
      case symbol_kind::S_RPAR: // ")"
      case symbol_kind::S_VAR: // "$"
      case symbol_kind::S_PLUS: // "+"
      case symbol_kind::S_IMUL: // "*"
      case symbol_kind::S_MINUS: // "-"
      case symbol_kind::S_IDIV: // "/"
      case symbol_kind::S_MOD: // "%"
      case symbol_kind::S_POW: // "^"
      case symbol_kind::S_QUOTE: // "\""
      case symbol_kind::S_operator: // operator
      case symbol_kind::S_string_v: // string_v
        value.copy< std::string > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

  }




  template <typename Base>
   ParserText ::symbol_kind_type
   ParserText ::basic_symbol<Base>::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }


  template <typename Base>
  bool
   ParserText ::basic_symbol<Base>::empty () const YY_NOEXCEPT
  {
    return this->kind () == symbol_kind::S_YYEMPTY;
  }

  template <typename Base>
  void
   ParserText ::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move (s);
    switch (this->kind ())
    {
      case symbol_kind::S_varexpr: // varexpr
        value.move< Expr::Expression > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_expr_float: // expr_float
        value.move< float > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_expr_int: // expr_int
        value.move< int > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_TEXT: // TEXT
      case symbol_kind::S_NUMBER: // NUMBER
      case symbol_kind::S_DELIMITER: // DELIMITER
      case symbol_kind::S_SYMBOL: // SYMBOL
      case symbol_kind::S_FLOAT: // FLOAT
      case symbol_kind::S_LPAR: // "("
      case symbol_kind::S_RPAR: // ")"
      case symbol_kind::S_VAR: // "$"
      case symbol_kind::S_PLUS: // "+"
      case symbol_kind::S_IMUL: // "*"
      case symbol_kind::S_MINUS: // "-"
      case symbol_kind::S_IDIV: // "/"
      case symbol_kind::S_MOD: // "%"
      case symbol_kind::S_POW: // "^"
      case symbol_kind::S_QUOTE: // "\""
      case symbol_kind::S_operator: // operator
      case symbol_kind::S_string_v: // string_v
        value.move< std::string > (YY_MOVE (s.value));
        break;

      default:
        break;
    }

    location = YY_MOVE (s.location);
  }

  // by_kind.
   ParserText ::by_kind::by_kind () YY_NOEXCEPT
    : kind_ (symbol_kind::S_YYEMPTY)
  {}

#if 201103L <= YY_CPLUSPLUS
   ParserText ::by_kind::by_kind (by_kind&& that) YY_NOEXCEPT
    : kind_ (that.kind_)
  {
    that.clear ();
  }
#endif

   ParserText ::by_kind::by_kind (const by_kind& that) YY_NOEXCEPT
    : kind_ (that.kind_)
  {}

   ParserText ::by_kind::by_kind (token_kind_type t) YY_NOEXCEPT
    : kind_ (yytranslate_ (t))
  {}



  void
   ParserText ::by_kind::clear () YY_NOEXCEPT
  {
    kind_ = symbol_kind::S_YYEMPTY;
  }

  void
   ParserText ::by_kind::move (by_kind& that)
  {
    kind_ = that.kind_;
    that.clear ();
  }

   ParserText ::symbol_kind_type
   ParserText ::by_kind::kind () const YY_NOEXCEPT
  {
    return kind_;
  }


   ParserText ::symbol_kind_type
   ParserText ::by_kind::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }



  // by_state.
   ParserText ::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

   ParserText ::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
   ParserText ::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
   ParserText ::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

   ParserText ::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

   ParserText ::symbol_kind_type
   ParserText ::by_state::kind () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return symbol_kind::S_YYEMPTY;
    else
      return YY_CAST (symbol_kind_type, yystos_[+state]);
  }

   ParserText ::stack_symbol_type::stack_symbol_type ()
  {}

   ParserText ::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state), YY_MOVE (that.location))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_varexpr: // varexpr
        value.YY_MOVE_OR_COPY< Expr::Expression > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_float: // expr_float
        value.YY_MOVE_OR_COPY< float > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_int: // expr_int
        value.YY_MOVE_OR_COPY< int > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_TEXT: // TEXT
      case symbol_kind::S_NUMBER: // NUMBER
      case symbol_kind::S_DELIMITER: // DELIMITER
      case symbol_kind::S_SYMBOL: // SYMBOL
      case symbol_kind::S_FLOAT: // FLOAT
      case symbol_kind::S_LPAR: // "("
      case symbol_kind::S_RPAR: // ")"
      case symbol_kind::S_VAR: // "$"
      case symbol_kind::S_PLUS: // "+"
      case symbol_kind::S_IMUL: // "*"
      case symbol_kind::S_MINUS: // "-"
      case symbol_kind::S_IDIV: // "/"
      case symbol_kind::S_MOD: // "%"
      case symbol_kind::S_POW: // "^"
      case symbol_kind::S_QUOTE: // "\""
      case symbol_kind::S_operator: // operator
      case symbol_kind::S_string_v: // string_v
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

   ParserText ::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s, YY_MOVE (that.location))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_varexpr: // varexpr
        value.move< Expr::Expression > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_float: // expr_float
        value.move< float > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_int: // expr_int
        value.move< int > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_TEXT: // TEXT
      case symbol_kind::S_NUMBER: // NUMBER
      case symbol_kind::S_DELIMITER: // DELIMITER
      case symbol_kind::S_SYMBOL: // SYMBOL
      case symbol_kind::S_FLOAT: // FLOAT
      case symbol_kind::S_LPAR: // "("
      case symbol_kind::S_RPAR: // ")"
      case symbol_kind::S_VAR: // "$"
      case symbol_kind::S_PLUS: // "+"
      case symbol_kind::S_IMUL: // "*"
      case symbol_kind::S_MINUS: // "-"
      case symbol_kind::S_IDIV: // "/"
      case symbol_kind::S_MOD: // "%"
      case symbol_kind::S_POW: // "^"
      case symbol_kind::S_QUOTE: // "\""
      case symbol_kind::S_operator: // operator
      case symbol_kind::S_string_v: // string_v
        value.move< std::string > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

    // that is emptied.
    that.kind_ = symbol_kind::S_YYEMPTY;
  }

#if YY_CPLUSPLUS < 201103L
   ParserText ::stack_symbol_type&
   ParserText ::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_varexpr: // varexpr
        value.copy< Expr::Expression > (that.value);
        break;

      case symbol_kind::S_expr_float: // expr_float
        value.copy< float > (that.value);
        break;

      case symbol_kind::S_expr_int: // expr_int
        value.copy< int > (that.value);
        break;

      case symbol_kind::S_TEXT: // TEXT
      case symbol_kind::S_NUMBER: // NUMBER
      case symbol_kind::S_DELIMITER: // DELIMITER
      case symbol_kind::S_SYMBOL: // SYMBOL
      case symbol_kind::S_FLOAT: // FLOAT
      case symbol_kind::S_LPAR: // "("
      case symbol_kind::S_RPAR: // ")"
      case symbol_kind::S_VAR: // "$"
      case symbol_kind::S_PLUS: // "+"
      case symbol_kind::S_IMUL: // "*"
      case symbol_kind::S_MINUS: // "-"
      case symbol_kind::S_IDIV: // "/"
      case symbol_kind::S_MOD: // "%"
      case symbol_kind::S_POW: // "^"
      case symbol_kind::S_QUOTE: // "\""
      case symbol_kind::S_operator: // operator
      case symbol_kind::S_string_v: // string_v
        value.copy< std::string > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    return *this;
  }

   ParserText ::stack_symbol_type&
   ParserText ::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_varexpr: // varexpr
        value.move< Expr::Expression > (that.value);
        break;

      case symbol_kind::S_expr_float: // expr_float
        value.move< float > (that.value);
        break;

      case symbol_kind::S_expr_int: // expr_int
        value.move< int > (that.value);
        break;

      case symbol_kind::S_TEXT: // TEXT
      case symbol_kind::S_NUMBER: // NUMBER
      case symbol_kind::S_DELIMITER: // DELIMITER
      case symbol_kind::S_SYMBOL: // SYMBOL
      case symbol_kind::S_FLOAT: // FLOAT
      case symbol_kind::S_LPAR: // "("
      case symbol_kind::S_RPAR: // ")"
      case symbol_kind::S_VAR: // "$"
      case symbol_kind::S_PLUS: // "+"
      case symbol_kind::S_IMUL: // "*"
      case symbol_kind::S_MINUS: // "-"
      case symbol_kind::S_IDIV: // "/"
      case symbol_kind::S_MOD: // "%"
      case symbol_kind::S_POW: // "^"
      case symbol_kind::S_QUOTE: // "\""
      case symbol_kind::S_operator: // operator
      case symbol_kind::S_string_v: // string_v
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
   ParserText ::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
   ParserText ::yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const
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
   ParserText ::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
   ParserText ::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
   ParserText ::yypop_ (int n) YY_NOEXCEPT
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
   ParserText ::debug_stream () const
  {
    return *yycdebug_;
  }

  void
   ParserText ::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


   ParserText ::debug_level_type
   ParserText ::debug_level () const
  {
    return yydebug_;
  }

  void
   ParserText ::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

   ParserText ::state_type
   ParserText ::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - YYNTOKENS] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - YYNTOKENS];
  }

  bool
   ParserText ::yy_pact_value_is_default_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yypact_ninf_;
  }

  bool
   ParserText ::yy_table_value_is_error_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yytable_ninf_;
  }

  int
   ParserText ::operator() ()
  {
    return parse ();
  }

  int
   ParserText ::parse ()
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
      case symbol_kind::S_varexpr: // varexpr
        yylhs.value.emplace< Expr::Expression > ();
        break;

      case symbol_kind::S_expr_float: // expr_float
        yylhs.value.emplace< float > ();
        break;

      case symbol_kind::S_expr_int: // expr_int
        yylhs.value.emplace< int > ();
        break;

      case symbol_kind::S_TEXT: // TEXT
      case symbol_kind::S_NUMBER: // NUMBER
      case symbol_kind::S_DELIMITER: // DELIMITER
      case symbol_kind::S_SYMBOL: // SYMBOL
      case symbol_kind::S_FLOAT: // FLOAT
      case symbol_kind::S_LPAR: // "("
      case symbol_kind::S_RPAR: // ")"
      case symbol_kind::S_VAR: // "$"
      case symbol_kind::S_PLUS: // "+"
      case symbol_kind::S_IMUL: // "*"
      case symbol_kind::S_MINUS: // "-"
      case symbol_kind::S_IDIV: // "/"
      case symbol_kind::S_MOD: // "%"
      case symbol_kind::S_POW: // "^"
      case symbol_kind::S_QUOTE: // "\""
      case symbol_kind::S_operator: // operator
      case symbol_kind::S_string_v: // string_v
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
  case 6: // word: TEXT
#line 121 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                         { scanner->add_text(yystack_[0].value.as < std::string > ());      }
#line 864 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 7: // word: "-" NUMBER
#line 122 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                         { scanner->add_number(yystack_[1].value.as < std::string > ()+yystack_[0].value.as < std::string > ()); }
#line 870 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 8: // word: NUMBER
#line 123 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                         { scanner->add_number(yystack_[0].value.as < std::string > ());    }
#line 876 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 9: // word: "-" FLOAT
#line 124 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                         { scanner->add_float(yystack_[1].value.as < std::string > ()+yystack_[0].value.as < std::string > ());  }
#line 882 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 10: // word: FLOAT
#line 125 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                         { scanner->add_float(yystack_[0].value.as < std::string > ());     }
#line 888 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 11: // word: DELIMITER
#line 126 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                         { scanner->add_delimiter(yystack_[0].value.as < std::string > ()); }
#line 894 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 12: // word: SYMBOL
#line 127 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                         { scanner->add_symbol(yystack_[0].value.as < std::string > ());    }
#line 900 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 13: // word: NEWLINE
#line 128 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                         { scanner->add_newline();     }
#line 906 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 14: // word: operator
#line 129 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                         { scanner->add_symbol(yystack_[0].value.as < std::string > ());    }
#line 912 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 15: // word: "\""
#line 130 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                         { scanner->add_symbol("\"");  }
#line 918 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 16: // word: "{!"
#line 131 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                             { scanner->add_symbol("{"); scanner->add_symbol("!"); }
#line 924 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 17: // word: "!}"
#line 132 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                             { scanner->add_symbol("!"); scanner->add_symbol("}"); }
#line 930 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 18: // word: "expression begin" "\"" string_v "\"" "expression end"
#line 133 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                                                     {auto e = Expression(Node(Type::TEXT, yystack_[2].value.as < std::string > ()), std::vector<Expression>{});
                                       scanner->add_expr(new Expression(Node(Type::ASSIGN, "="), std::vector<Expression>{Expression(Node(Type::VAR, "$"), std::vector<Expression>()), e}), IR::Type::DERIVED);}
#line 937 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 19: // word: "expression begin" varexpr "expression end"
#line 135 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                                        { scanner->add_expr(new Expression(Node(Type::ASSIGN, "="), std::vector<Expression>{Expression(Node(Type::VAR, "$"), std::vector<Expression>()), yystack_[1].value.as < Expr::Expression > ()}), scanner->expr_type); }
#line 943 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 20: // word: "expression begin" expr_int "expression end"
#line 136 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                                         { auto e = Expression(Node(Type::NUMBER, std::to_string(yystack_[1].value.as < int > ())), std::vector<Expression>{});
                                       scanner->add_expr(new Expression(Node(Type::ASSIGN, "="), std::vector<Expression>{Expression(Node(Type::VAR, "$"), std::vector<Expression>()), e}), IR::Type::NUMBER);}
#line 950 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 21: // word: "expression begin" expr_float "expression end"
#line 138 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                                           { auto e = Expression(Node(Type::FLOAT, std::to_string(yystack_[1].value.as < float > ())), std::vector<Expression>{});
                                       scanner->add_expr(new Expression(Node(Type::ASSIGN, "="), std::vector<Expression>{Expression(Node(Type::VAR, "$"), std::vector<Expression>()), e}), IR::Type::FLOAT);}
#line 957 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 22: // operator: "$"
#line 142 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                  { yylhs.value.as < std::string > () = yystack_[0].value.as < std::string > (); }
#line 963 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 23: // operator: "+"
#line 143 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                  { yylhs.value.as < std::string > () = yystack_[0].value.as < std::string > (); }
#line 969 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 24: // operator: "*"
#line 144 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                  { yylhs.value.as < std::string > () = yystack_[0].value.as < std::string > (); }
#line 975 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 25: // operator: "-"
#line 145 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                  { yylhs.value.as < std::string > () = yystack_[0].value.as < std::string > (); }
#line 981 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 26: // operator: "/"
#line 146 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                  { yylhs.value.as < std::string > () = yystack_[0].value.as < std::string > (); }
#line 987 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 27: // operator: "%"
#line 147 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                  { yylhs.value.as < std::string > () = yystack_[0].value.as < std::string > (); }
#line 993 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 28: // operator: "^"
#line 148 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                  { yylhs.value.as < std::string > () = yystack_[0].value.as < std::string > (); }
#line 999 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 29: // operator: "("
#line 149 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                  { yylhs.value.as < std::string > () = yystack_[0].value.as < std::string > (); }
#line 1005 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 30: // operator: ")"
#line 150 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                  { yylhs.value.as < std::string > () = yystack_[0].value.as < std::string > (); }
#line 1011 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 31: // string_v: TEXT
#line 153 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                               { yylhs.value.as < std::string > () = yystack_[0].value.as < std::string > (); }
#line 1017 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 32: // string_v: SYMBOL
#line 154 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                               { yylhs.value.as < std::string > () = yystack_[0].value.as < std::string > (); }
#line 1023 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 33: // string_v: DELIMITER
#line 155 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                               { yylhs.value.as < std::string > () = yystack_[0].value.as < std::string > (); }
#line 1029 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 34: // string_v: NUMBER
#line 156 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                               { yylhs.value.as < std::string > () = yystack_[0].value.as < std::string > (); }
#line 1035 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 35: // string_v: FLOAT
#line 157 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                               { yylhs.value.as < std::string > () = yystack_[0].value.as < std::string > (); }
#line 1041 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 36: // string_v: operator
#line 158 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                               { yylhs.value.as < std::string > () = yystack_[0].value.as < std::string > (); }
#line 1047 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 37: // string_v: string_v TEXT
#line 159 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                               { yylhs.value.as < std::string > () = yystack_[1].value.as < std::string > () + yystack_[0].value.as < std::string > (); }
#line 1053 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 38: // string_v: string_v SYMBOL
#line 160 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                               { yylhs.value.as < std::string > () = yystack_[1].value.as < std::string > () + yystack_[0].value.as < std::string > (); }
#line 1059 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 39: // string_v: string_v DELIMITER
#line 161 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                               { yylhs.value.as < std::string > () = yystack_[1].value.as < std::string > () + yystack_[0].value.as < std::string > (); }
#line 1065 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 40: // string_v: string_v NUMBER
#line 162 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                               { yylhs.value.as < std::string > () = std::string(yystack_[1].value.as < std::string > ()) + yystack_[0].value.as < std::string > (); }
#line 1071 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 41: // string_v: string_v FLOAT
#line 163 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                               { yylhs.value.as < std::string > () = std::string(yystack_[1].value.as < std::string > ()) + yystack_[0].value.as < std::string > (); }
#line 1077 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 42: // string_v: string_v operator
#line 164 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                               { yylhs.value.as < std::string > () = yystack_[1].value.as < std::string > () + yystack_[0].value.as < std::string > (); }
#line 1083 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 43: // varexpr: "$"
#line 167 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                { yylhs.value.as < Expr::Expression > () = Expression(Node(Type::VAR, yystack_[0].value.as < std::string > ()), std::vector<Expression>()); }
#line 1089 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 44: // varexpr: "-" "$"
#line 168 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                                { yylhs.value.as < Expr::Expression > () = Expression(Node(Type::IMUL, "*"), std::vector<Expression>{Expression(Node(Type::NUMBER, std::string("-1")), std::vector<Expression>{}), Expression(Node(Type::VAR, yystack_[0].value.as < std::string > ()), std::vector<Expression>())}); }
#line 1095 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 45: // varexpr: "(" varexpr ")"
#line 169 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                              { yylhs.value.as < Expr::Expression > () = yystack_[1].value.as < Expr::Expression > (); }
#line 1101 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 46: // varexpr: expr_int "^" varexpr
#line 171 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                                 { yylhs.value.as < Expr::Expression > () = Expression(Node(Type::POW, "^"), std::vector<Expression>{Expression(Node(Type::NUMBER, std::to_string(yystack_[2].value.as < int > ())), std::vector<Expression>{}), yystack_[0].value.as < Expr::Expression > ()}); }
#line 1107 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 47: // varexpr: expr_int "%" varexpr
#line 172 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                                 { yylhs.value.as < Expr::Expression > () = Expression(Node(Type::MOD, "%"), std::vector<Expression>{Expression(Node(Type::NUMBER, std::to_string(yystack_[2].value.as < int > ())), std::vector<Expression>{}), yystack_[0].value.as < Expr::Expression > ()}); }
#line 1113 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 48: // varexpr: expr_int "*" varexpr
#line 173 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                                  { yylhs.value.as < Expr::Expression > () = Expression(Node(Type::IMUL, "*"), std::vector<Expression>{Expression(Node(Type::NUMBER, std::to_string(yystack_[2].value.as < int > ())), std::vector<Expression>{}), yystack_[0].value.as < Expr::Expression > ()}); }
#line 1119 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 49: // varexpr: expr_int "/" varexpr
#line 174 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                                  { yylhs.value.as < Expr::Expression > () = Expression(Node(Type::IDIV, "/"), std::vector<Expression>{Expression(Node(Type::NUMBER, std::to_string(yystack_[2].value.as < int > ())), std::vector<Expression>{}), yystack_[0].value.as < Expr::Expression > ()}); }
#line 1125 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 50: // varexpr: expr_int "-" varexpr
#line 175 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                                   { yylhs.value.as < Expr::Expression > () = Expression(Node(Type::SUB, "-"), std::vector<Expression>{Expression(Node(Type::NUMBER, std::to_string(yystack_[2].value.as < int > ())), std::vector<Expression>{}), yystack_[0].value.as < Expr::Expression > ()}); }
#line 1131 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 51: // varexpr: expr_int "+" varexpr
#line 176 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                                  { yylhs.value.as < Expr::Expression > () = Expression(Node(Type::ADD, "+"), std::vector<Expression>{Expression(Node(Type::NUMBER, std::to_string(yystack_[2].value.as < int > ())), std::vector<Expression>{}), yystack_[0].value.as < Expr::Expression > ()}); }
#line 1137 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 52: // varexpr: varexpr "^" expr_int
#line 178 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                                 { yylhs.value.as < Expr::Expression > () = Expression(Node(Type::POW, "^"), std::vector<Expression>{yystack_[2].value.as < Expr::Expression > (), Expression(Node(Type::NUMBER, std::to_string(yystack_[0].value.as < int > ())), std::vector<Expression>{})}); }
#line 1143 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 53: // varexpr: varexpr "%" expr_int
#line 179 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                                 { yylhs.value.as < Expr::Expression > () = Expression(Node(Type::MOD, "%"), std::vector<Expression>{yystack_[2].value.as < Expr::Expression > (), Expression(Node(Type::NUMBER, std::to_string(yystack_[0].value.as < int > ())), std::vector<Expression>{})}); }
#line 1149 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 54: // varexpr: varexpr "*" expr_int
#line 180 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                                  { yylhs.value.as < Expr::Expression > () = Expression(Node(Type::IMUL, "*"), std::vector<Expression>{yystack_[2].value.as < Expr::Expression > (), Expression(Node(Type::NUMBER, std::to_string(yystack_[0].value.as < int > ())), std::vector<Expression>{})}); }
#line 1155 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 55: // varexpr: varexpr "/" expr_int
#line 181 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                                  { yylhs.value.as < Expr::Expression > () = Expression(Node(Type::IDIV, "/"), std::vector<Expression>{yystack_[2].value.as < Expr::Expression > (), Expression(Node(Type::NUMBER, std::to_string(yystack_[0].value.as < int > ())), std::vector<Expression>{})}); }
#line 1161 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 56: // varexpr: varexpr "-" expr_int
#line 182 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                                   { yylhs.value.as < Expr::Expression > () = Expression(Node(Type::SUB, "-"), std::vector<Expression>{yystack_[2].value.as < Expr::Expression > (), Expression(Node(Type::NUMBER, std::to_string(yystack_[0].value.as < int > ())), std::vector<Expression>{})}); }
#line 1167 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 57: // varexpr: varexpr "+" expr_int
#line 183 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                                  { yylhs.value.as < Expr::Expression > () = Expression(Node(Type::ADD, "+"),  std::vector<Expression>{yystack_[2].value.as < Expr::Expression > (), Expression(Node(Type::NUMBER, std::to_string(yystack_[0].value.as < int > ())), std::vector<Expression>{})}); }
#line 1173 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 58: // varexpr: expr_float "^" varexpr
#line 185 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                                   { yylhs.value.as < Expr::Expression > () = Expression(Node(Type::POW, "^"), std::vector<Expression>{Expression(Node(Type::FLOAT, std::to_string(yystack_[2].value.as < float > ())), std::vector<Expression>{}), yystack_[0].value.as < Expr::Expression > ()}); }
#line 1179 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 59: // varexpr: expr_float "%" varexpr
#line 186 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                                   { yylhs.value.as < Expr::Expression > () = Expression(Node(Type::MOD, "%"), std::vector<Expression>{Expression(Node(Type::FLOAT, std::to_string(yystack_[2].value.as < float > ())), std::vector<Expression>{}), yystack_[0].value.as < Expr::Expression > ()}); }
#line 1185 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 60: // varexpr: expr_float "*" varexpr
#line 187 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                                    { yylhs.value.as < Expr::Expression > () = Expression(Node(Type::IMUL, "*"), std::vector<Expression>{Expression(Node(Type::FLOAT, std::to_string(yystack_[2].value.as < float > ())), std::vector<Expression>{}), yystack_[0].value.as < Expr::Expression > ()}); }
#line 1191 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 61: // varexpr: expr_float "/" varexpr
#line 188 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                                    { yylhs.value.as < Expr::Expression > () = Expression(Node(Type::IDIV, "/"), std::vector<Expression>{Expression(Node(Type::FLOAT, std::to_string(yystack_[2].value.as < float > ())), std::vector<Expression>{}), yystack_[0].value.as < Expr::Expression > ()}); }
#line 1197 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 62: // varexpr: expr_float "-" varexpr
#line 189 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                                     { yylhs.value.as < Expr::Expression > () = Expression(Node(Type::SUB, "-"), std::vector<Expression>{Expression(Node(Type::FLOAT, std::to_string(yystack_[2].value.as < float > ())), std::vector<Expression>{}), yystack_[0].value.as < Expr::Expression > ()}); }
#line 1203 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 63: // varexpr: expr_float "+" varexpr
#line 190 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                                    { yylhs.value.as < Expr::Expression > () = Expression(Node(Type::ADD, "+"), std::vector<Expression>{Expression(Node(Type::FLOAT, std::to_string(yystack_[2].value.as < float > ())), std::vector<Expression>{}), yystack_[0].value.as < Expr::Expression > ()}); }
#line 1209 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 64: // varexpr: varexpr "^" expr_float
#line 192 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                                   { yylhs.value.as < Expr::Expression > () = Expression(Node(Type::POW, "^"), std::vector<Expression>{yystack_[2].value.as < Expr::Expression > (), Expression(Node(Type::FLOAT, std::to_string(yystack_[0].value.as < float > ())), std::vector<Expression>{})}); }
#line 1215 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 65: // varexpr: varexpr "%" expr_float
#line 193 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                                   { yylhs.value.as < Expr::Expression > () = Expression(Node(Type::MOD, "%"), std::vector<Expression>{yystack_[2].value.as < Expr::Expression > (), Expression(Node(Type::FLOAT, std::to_string(yystack_[0].value.as < float > ())), std::vector<Expression>{})}); }
#line 1221 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 66: // varexpr: varexpr "*" expr_float
#line 194 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                                    { yylhs.value.as < Expr::Expression > () = Expression(Node(Type::IMUL, "*"), std::vector<Expression>{yystack_[2].value.as < Expr::Expression > (), Expression(Node(Type::FLOAT, std::to_string(yystack_[0].value.as < float > ())), std::vector<Expression>{})}); }
#line 1227 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 67: // varexpr: varexpr "/" expr_float
#line 195 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                                    { yylhs.value.as < Expr::Expression > () = Expression(Node(Type::IDIV, "/"), std::vector<Expression>{yystack_[2].value.as < Expr::Expression > (), Expression(Node(Type::FLOAT, std::to_string(yystack_[0].value.as < float > ())), std::vector<Expression>{})}); }
#line 1233 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 68: // varexpr: varexpr "-" expr_float
#line 196 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                                     { yylhs.value.as < Expr::Expression > () = Expression(Node(Type::SUB, "-"), std::vector<Expression>{yystack_[2].value.as < Expr::Expression > (), Expression(Node(Type::FLOAT, std::to_string(yystack_[0].value.as < float > ())), std::vector<Expression>{})}); }
#line 1239 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 69: // varexpr: varexpr "+" expr_float
#line 197 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                                    { yylhs.value.as < Expr::Expression > () = Expression(Node(Type::ADD, "+"),  std::vector<Expression>{yystack_[2].value.as < Expr::Expression > (), Expression(Node(Type::FLOAT, std::to_string(yystack_[0].value.as < float > ())), std::vector<Expression>{})}); }
#line 1245 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 70: // varexpr: varexpr "^" varexpr
#line 199 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                                { yylhs.value.as < Expr::Expression > () = Expression(Node(Type::POW, "^"), std::vector<Expression>{yystack_[2].value.as < Expr::Expression > (), yystack_[0].value.as < Expr::Expression > ()}); }
#line 1251 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 71: // varexpr: varexpr "%" varexpr
#line 200 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                                { yylhs.value.as < Expr::Expression > () = Expression(Node(Type::MOD, "%"), std::vector<Expression>{yystack_[2].value.as < Expr::Expression > (), yystack_[0].value.as < Expr::Expression > ()}); }
#line 1257 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 72: // varexpr: varexpr "*" varexpr
#line 201 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                                 { yylhs.value.as < Expr::Expression > () = Expression(Node(Type::IMUL, "*"), std::vector<Expression>{yystack_[2].value.as < Expr::Expression > (), yystack_[0].value.as < Expr::Expression > ()}); }
#line 1263 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 73: // varexpr: varexpr "/" varexpr
#line 202 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                                 { yylhs.value.as < Expr::Expression > () = Expression(Node(Type::IDIV, "/"), std::vector<Expression>{yystack_[2].value.as < Expr::Expression > (), yystack_[0].value.as < Expr::Expression > ()}); }
#line 1269 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 74: // varexpr: varexpr "-" varexpr
#line 203 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                                  { yylhs.value.as < Expr::Expression > () = Expression(Node(Type::SUB, "-"), std::vector<Expression>{yystack_[2].value.as < Expr::Expression > (), yystack_[0].value.as < Expr::Expression > ()}); }
#line 1275 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 75: // varexpr: varexpr "+" varexpr
#line 204 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                                 { yylhs.value.as < Expr::Expression > () = Expression(Node(Type::ADD, "+"), std::vector<Expression>{yystack_[2].value.as < Expr::Expression > (), yystack_[0].value.as < Expr::Expression > ()}); }
#line 1281 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 76: // expr_float: FLOAT
#line 207 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                  { yylhs.value.as < float > () = std::stof(yystack_[0].value.as < std::string > ().c_str()); /* Atoi is safe to use because syntactical analysis was done */ }
#line 1287 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 77: // expr_float: "-" expr_float
#line 208 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                                       { yylhs.value.as < float > () = -yystack_[0].value.as < float > (); /* Unary minus */}
#line 1293 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 78: // expr_float: "(" expr_float ")"
#line 209 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                                 { yylhs.value.as < float > () = yystack_[1].value.as < float > (); }
#line 1299 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 79: // expr_float: expr_float "^" expr_float
#line 210 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                                      { yylhs.value.as < float > () = std::pow(yystack_[2].value.as < float > (), yystack_[0].value.as < float > ());}
#line 1305 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 80: // expr_float: expr_float "%" expr_float
#line 211 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                                      { yylhs.value.as < float > () = std::fmod(yystack_[2].value.as < float > (), yystack_[0].value.as < float > ());}
#line 1311 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 81: // expr_float: expr_float "*" expr_float
#line 212 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                                       { yylhs.value.as < float > () = yystack_[2].value.as < float > () * yystack_[0].value.as < float > ();}
#line 1317 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 82: // expr_float: expr_float "/" expr_float
#line 213 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                                       { yylhs.value.as < float > () = yystack_[2].value.as < float > () / yystack_[0].value.as < float > ();}
#line 1323 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 83: // expr_float: expr_float "-" expr_float
#line 214 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                                        { yylhs.value.as < float > () = yystack_[2].value.as < float > () - yystack_[0].value.as < float > ();}
#line 1329 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 84: // expr_float: expr_float "+" expr_float
#line 215 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                                       { yylhs.value.as < float > () = yystack_[2].value.as < float > () + yystack_[0].value.as < float > ();}
#line 1335 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 85: // expr_int: NUMBER
#line 218 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                   { yylhs.value.as < int > () = atoi(yystack_[0].value.as < std::string > ().c_str()); /* Atoi is safe to use because syntactical analysis was done */ }
#line 1341 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 86: // expr_int: "-" expr_int
#line 219 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                                     { yylhs.value.as < int > () = -yystack_[0].value.as < int > (); /* Unary minus */}
#line 1347 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 87: // expr_int: "(" expr_int ")"
#line 220 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                               { yylhs.value.as < int > () = yystack_[1].value.as < int > (); }
#line 1353 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 88: // expr_int: expr_int "^" expr_int
#line 221 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                                  { yylhs.value.as < int > () = static_cast<int>(std::pow(yystack_[2].value.as < int > (), yystack_[0].value.as < int > ()));}
#line 1359 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 89: // expr_int: expr_int "%" expr_int
#line 222 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                                  { yylhs.value.as < int > () = yystack_[2].value.as < int > () % yystack_[0].value.as < int > ();}
#line 1365 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 90: // expr_int: expr_int "*" expr_int
#line 223 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                                   { yylhs.value.as < int > () = yystack_[2].value.as < int > () * yystack_[0].value.as < int > ();}
#line 1371 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 91: // expr_int: expr_int "/" expr_int
#line 224 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                                   { yylhs.value.as < int > () = yystack_[2].value.as < int > () / yystack_[0].value.as < int > ();}
#line 1377 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 92: // expr_int: expr_int "-" expr_int
#line 225 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                                    { yylhs.value.as < int > () = yystack_[2].value.as < int > () - yystack_[0].value.as < int > ();}
#line 1383 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 93: // expr_int: expr_int "+" expr_int
#line 226 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                                   { yylhs.value.as < int > () = yystack_[2].value.as < int > () + yystack_[0].value.as < int > ();}
#line 1389 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;


#line 1393 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"

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
   ParserText ::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what ());
  }

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
   ParserText ::yytnamerr_ (const char *yystr)
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
   ParserText ::symbol_name (symbol_kind_type yysymbol)
  {
    return yytnamerr_ (yytname_[yysymbol]);
  }



  //  ParserText ::context.
   ParserText ::context::context (const  ParserText & yyparser, const symbol_type& yyla)
    : yyparser_ (yyparser)
    , yyla_ (yyla)
  {}

  int
   ParserText ::context::expected_tokens (symbol_kind_type yyarg[], int yyargn) const
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
   ParserText ::yy_syntax_error_arguments_ (const context& yyctx,
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
   ParserText ::yysyntax_error_ (const context& yyctx) const
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


  const signed char  ParserText ::yypact_ninf_ = -30;

  const signed char  ParserText ::yytable_ninf_ = -1;

  const short
   ParserText ::yypact_[] =
  {
     148,   -30,   -30,   237,   -30,   -30,   -30,   -30,   -30,   -30,
     -30,   -30,   -30,   -30,   -30,   -30,    -5,   -30,   -30,   -30,
     -30,    10,   177,   -30,   -30,   -30,   -30,    -7,   -30,    31,
     224,    -2,    15,   195,   -30,   -30,   -30,   -30,   -30,   187,
     244,   252,    94,   -30,    94,   -30,   -30,   -30,   -30,   -30,
     -30,   -30,   -30,   -30,   209,   -30,    -7,    -7,    -7,    -7,
      -7,    -7,   -30,    -7,    -7,    -7,    -7,    -7,    -7,   -30,
      -7,    -7,    -7,    -7,    -7,    -7,   -30,   -30,   -30,   260,
     268,     9,     9,     9,     9,     9,     9,    29,    29,    29,
      29,    29,    29,   -30,   -30,   -30,   -30,   -30,     4,   -30,
      45,    60,   279,    -9,    -8,     2,    45,    60,   279,    -9,
      -8,     2,    -9,    -8,     2,    -9,    -8,     2,    45,    60,
     155,    -9,    -8,    45,    60,    -9,    -8,    -9,    -8,    -9,
      -8,    45,   274,   279,    -9,     2,    45,   279,    -9,     2,
      -9,     2,    -9,     2,     9,     9,   284,     7,   284,     7,
       7,     7,    29,    29,   289,     8,   289,     8,     8,     8,
     -30
  };

  const signed char
   ParserText ::yydefact_[] =
  {
       0,     2,    13,     0,    16,    17,     6,     8,    11,    12,
      10,    29,    30,    22,    23,    24,    25,    26,    27,    28,
      15,     0,     0,     4,    14,    85,    76,     0,    43,     0,
       0,     0,     0,     0,     7,     9,     1,     3,     5,     0,
       0,     0,     0,    44,     0,    77,    86,    31,    34,    33,
      32,    35,    25,    36,     0,    19,     0,     0,     0,     0,
       0,     0,    21,     0,     0,     0,     0,     0,     0,    20,
       0,     0,     0,     0,     0,     0,    45,    78,    87,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    37,    40,    39,    38,    41,     0,    42,
      75,    69,    57,    72,    66,    54,    74,    68,    56,    73,
      67,    55,    71,    65,    53,    70,    64,    52,    63,    84,
       0,    60,    81,    62,    83,    61,    82,    59,    80,    58,
      79,    51,     0,    93,    48,    90,    50,    92,    49,    91,
      47,    89,    46,    88,     0,     0,    84,    81,    83,    82,
      80,    79,     0,     0,    93,    90,    92,    91,    89,    88,
      18
  };

  const signed char
   ParserText ::yypgoto_[] =
  {
     -30,   -30,   -30,    23,   -29,   -30,    69,    34,    -3
  };

  const unsigned char
   ParserText ::yydefgoto_[] =
  {
       0,    21,    22,    23,    24,    54,    31,   132,   120
  };

  const unsigned char
   ParserText ::yytable_[] =
  {
      33,    53,    25,    55,    34,    26,    27,    35,    28,   160,
      36,    29,    61,    68,    56,    57,    58,    59,    60,    61,
      62,    26,   144,    75,    41,    99,    46,   145,    86,    92,
       0,    63,    64,    65,    66,    67,    68,    32,    25,    80,
      25,    46,   152,    26,    42,    38,    43,   153,     0,    44,
       0,     0,     0,   102,   105,   108,   111,   114,   117,     0,
       0,    40,    57,    45,    59,    60,    61,   133,   135,   137,
     139,   141,   143,     0,     0,     0,    79,    64,    45,    66,
      67,    68,     0,     0,   154,   155,   156,   157,   158,   159,
     101,   104,   107,   110,   113,   116,    39,   119,   122,   124,
     126,   128,   130,    25,     0,     0,    26,    42,     0,     0,
       0,     0,    44,     0,     0,   146,   147,   148,   149,   150,
     151,     0,     0,     0,     0,   100,   103,   106,   109,   112,
     115,     0,   118,   121,   123,   125,   127,   129,     0,   131,
     134,   136,   138,   140,   142,     0,     0,     0,     1,    80,
      46,     2,     3,     0,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    70,    71,    72,    73,    74,    75,    37,    79,    45,
       2,     3,     0,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      69,    76,     0,    56,    57,    58,    59,    60,    61,     0,
       0,    70,    71,    72,    73,    74,    75,    93,    94,    95,
      96,    97,    11,    12,    13,    14,    15,    52,    17,    18,
      19,    98,    47,    48,    49,    50,    51,    11,    12,    13,
      14,    15,    52,    17,    18,    19,    25,     0,     0,    26,
      27,     0,    28,     0,     0,    29,     0,     0,    77,    30,
      63,    64,    65,    66,    67,    68,    78,     0,    70,    71,
      72,    73,    74,    75,    77,     0,    81,    82,    83,    84,
      85,    86,    78,     0,    87,    88,    89,    90,    91,    92,
      63,    64,    65,    66,    67,    68,    71,     0,    73,    74,
      75,    82,     0,    84,    85,    86,    88,     0,    90,    91,
      92
  };

  const short
   ParserText ::yycheck_[] =
  {
       3,    30,     9,     5,     9,    12,    13,    12,    15,     5,
       0,    18,    21,    21,    16,    17,    18,    19,    20,    21,
       5,    12,    13,    21,    27,    54,    29,    18,    21,    21,
      -1,    16,    17,    18,    19,    20,    21,     3,     9,    42,
       9,    44,    13,    12,    13,    22,    15,    18,    -1,    18,
      -1,    -1,    -1,    56,    57,    58,    59,    60,    61,    -1,
      -1,    27,    17,    29,    19,    20,    21,    70,    71,    72,
      73,    74,    75,    -1,    -1,    -1,    42,    17,    44,    19,
      20,    21,    -1,    -1,    87,    88,    89,    90,    91,    92,
      56,    57,    58,    59,    60,    61,    27,    63,    64,    65,
      66,    67,    68,     9,    -1,    -1,    12,    13,    -1,    -1,
      -1,    -1,    18,    -1,    -1,    81,    82,    83,    84,    85,
      86,    -1,    -1,    -1,    -1,    56,    57,    58,    59,    60,
      61,    -1,    63,    64,    65,    66,    67,    68,    -1,    70,
      71,    72,    73,    74,    75,    -1,    -1,    -1,     0,   152,
     153,     3,     4,    -1,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    16,    17,    18,    19,    20,    21,     0,   144,   145,
       3,     4,    -1,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
       5,    14,    -1,    16,    17,    18,    19,    20,    21,    -1,
      -1,    16,    17,    18,    19,    20,    21,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,     9,    -1,    -1,    12,
      13,    -1,    15,    -1,    -1,    18,    -1,    -1,    14,    22,
      16,    17,    18,    19,    20,    21,    14,    -1,    16,    17,
      18,    19,    20,    21,    14,    -1,    16,    17,    18,    19,
      20,    21,    14,    -1,    16,    17,    18,    19,    20,    21,
      16,    17,    18,    19,    20,    21,    17,    -1,    19,    20,
      21,    17,    -1,    19,    20,    21,    17,    -1,    19,    20,
      21
  };

  const signed char
   ParserText ::yystos_[] =
  {
       0,     0,     3,     4,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    25,    26,    27,    28,     9,    12,    13,    15,    18,
      22,    30,    31,    32,     9,    12,     0,     0,    27,    30,
      31,    32,    13,    15,    18,    31,    32,     8,     9,    10,
      11,    12,    18,    28,    29,     5,    16,    17,    18,    19,
      20,    21,     5,    16,    17,    18,    19,    20,    21,     5,
      16,    17,    18,    19,    20,    21,    14,    14,    14,    31,
      32,    16,    17,    18,    19,    20,    21,    16,    17,    18,
      19,    20,    21,     8,     9,    10,    11,    12,    22,    28,
      30,    31,    32,    30,    31,    32,    30,    31,    32,    30,
      31,    32,    30,    31,    32,    30,    31,    32,    30,    31,
      32,    30,    31,    30,    31,    30,    31,    30,    31,    30,
      31,    30,    31,    32,    30,    32,    30,    32,    30,    32,
      30,    32,    30,    32,    13,    18,    31,    31,    31,    31,
      31,    31,    13,    18,    32,    32,    32,    32,    32,    32,
       5
  };

  const signed char
   ParserText ::yyr1_[] =
  {
       0,    24,    25,    25,    26,    26,    27,    27,    27,    27,
      27,    27,    27,    27,    27,    27,    27,    27,    27,    27,
      27,    27,    28,    28,    28,    28,    28,    28,    28,    28,
      28,    29,    29,    29,    29,    29,    29,    29,    29,    29,
      29,    29,    29,    30,    30,    30,    30,    30,    30,    30,
      30,    30,    30,    30,    30,    30,    30,    30,    30,    30,
      30,    30,    30,    30,    30,    30,    30,    30,    30,    30,
      30,    30,    30,    30,    30,    30,    31,    31,    31,    31,
      31,    31,    31,    31,    31,    32,    32,    32,    32,    32,
      32,    32,    32,    32
  };

  const signed char
   ParserText ::yyr2_[] =
  {
       0,     2,     1,     2,     1,     2,     1,     2,     1,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     5,     3,
       3,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     2,     2,     2,
       2,     2,     2,     1,     2,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     1,     2,     3,     3,
       3,     3,     3,     3,     3,     1,     2,     3,     3,     3,
       3,     3,     3,     3
  };


#if YYDEBUG || 1
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a YYNTOKENS, nonterminals.
  const char*
  const  ParserText ::yytname_[] =
  {
  "\"EOF\"", "error", "\"invalid token\"", "NEWLINE",
  "\"expression begin\"", "\"expression end\"", "\"{!\"", "\"!}\"", "TEXT",
  "NUMBER", "DELIMITER", "SYMBOL", "FLOAT", "\"(\"", "\")\"", "\"$\"",
  "\"+\"", "\"*\"", "\"-\"", "\"/\"", "\"%\"", "\"^\"", "\"\\\"\"", "NEG",
  "$accept", "text_file", "sentence", "word", "operator", "string_v",
  "varexpr", "expr_float", "expr_int", YY_NULLPTR
  };
#endif


#if YYDEBUG
  const unsigned char
   ParserText ::yyrline_[] =
  {
       0,   111,   111,   112,   116,   117,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   135,
     136,   138,   142,   143,   144,   145,   146,   147,   148,   149,
     150,   153,   154,   155,   156,   157,   158,   159,   160,   161,
     162,   163,   164,   167,   168,   169,   171,   172,   173,   174,
     175,   176,   178,   179,   180,   181,   182,   183,   185,   186,
     187,   188,   189,   190,   192,   193,   194,   195,   196,   197,
     199,   200,   201,   202,   203,   204,   207,   208,   209,   210,
     211,   212,   213,   214,   215,   218,   219,   220,   221,   222,
     223,   224,   225,   226
  };

  void
   ParserText ::yy_stack_print_ () const
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
   ParserText ::yy_reduce_print_ (int yyrule) const
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

   ParserText ::symbol_kind_type
   ParserText ::yytranslate_ (int t) YY_NOEXCEPT
  {
    // YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to
    // TOKEN-NUM as returned by yylex.
    static
    const signed char
    translate_table[] =
    {
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23
    };
    // Last valid token kind.
    const int code_max = 278;

    if (t <= 0)
      return symbol_kind::S_YYEOF;
    else if (t <= code_max)
      return static_cast <symbol_kind_type> (translate_table[t]);
    else
      return symbol_kind::S_YYUNDEF;
  }

#line 19 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
} //  TextFile 
#line 2042 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"

#line 229 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"


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
