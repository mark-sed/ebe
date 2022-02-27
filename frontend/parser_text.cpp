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

      case symbol_kind::S_expr: // expr
        value.copy< Node > (YY_MOVE (that.value));
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

      case symbol_kind::S_expr: // expr
        value.move< Node > (YY_MOVE (s.value));
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

      case symbol_kind::S_expr: // expr
        value.YY_MOVE_OR_COPY< Node > (YY_MOVE (that.value));
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

      case symbol_kind::S_expr: // expr
        value.move< Node > (YY_MOVE (that.value));
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

      case symbol_kind::S_expr: // expr
        value.copy< Node > (that.value);
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

      case symbol_kind::S_expr: // expr
        value.move< Node > (that.value);
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

      case symbol_kind::S_expr: // expr
        yylhs.value.emplace< Node > ();
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
#line 118 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                         { scanner->add_text(yystack_[0].value.as < std::string > ());      }
#line 871 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 7: // word: "-" NUMBER
#line 119 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                         { scanner->add_number(yystack_[1].value.as < std::string > ()+yystack_[0].value.as < std::string > ()); }
#line 877 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 8: // word: NUMBER
#line 120 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                         { scanner->add_number(yystack_[0].value.as < std::string > ());    }
#line 883 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 9: // word: "-" FLOAT
#line 121 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                         { scanner->add_float(yystack_[1].value.as < std::string > ()+yystack_[0].value.as < std::string > ());  }
#line 889 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 10: // word: FLOAT
#line 122 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                         { scanner->add_float(yystack_[0].value.as < std::string > ());     }
#line 895 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 11: // word: DELIMITER
#line 123 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                         { scanner->add_delimiter(yystack_[0].value.as < std::string > ()); }
#line 901 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 12: // word: SYMBOL
#line 124 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                         { scanner->add_symbol(yystack_[0].value.as < std::string > ());    }
#line 907 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 13: // word: NEWLINE
#line 125 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                         { scanner->add_newline();     }
#line 913 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 14: // word: "$"
#line 126 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                         { scanner->add_symbol(yystack_[0].value.as < std::string > ());    }
#line 919 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 15: // word: "+"
#line 127 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                         { scanner->add_symbol(yystack_[0].value.as < std::string > ());    }
#line 925 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 16: // word: "*"
#line 128 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                         { scanner->add_symbol(yystack_[0].value.as < std::string > ());    }
#line 931 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 17: // word: "-"
#line 129 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                         { scanner->add_symbol(yystack_[0].value.as < std::string > ());    }
#line 937 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 18: // word: "/"
#line 130 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                         { scanner->add_symbol(yystack_[0].value.as < std::string > ());    }
#line 943 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 19: // word: "%"
#line 131 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                         { scanner->add_symbol(yystack_[0].value.as < std::string > ());    }
#line 949 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 20: // word: "^"
#line 132 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                         { scanner->add_symbol(yystack_[0].value.as < std::string > ());    }
#line 955 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 21: // word: "("
#line 133 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                         { scanner->add_symbol("(");   }
#line 961 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 22: // word: ")"
#line 134 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                         { scanner->add_symbol(")");   }
#line 967 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 23: // word: "{!"
#line 135 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                             { scanner->add_symbol("{"); scanner->add_symbol("!"); }
#line 973 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 24: // word: "!}"
#line 136 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                             { scanner->add_symbol("!"); scanner->add_symbol("}"); }
#line 979 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 25: // word: "expression begin" varexpr "expression end"
#line 137 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                                        { scanner->add_expr(new Expression(Node(Type::ASSIGN, "="), std::vector<Expression>{Expression(Node(Type::VAR, "$"), std::vector<Expression>()), yystack_[1].value.as < Expr::Expression > ()}), scanner->expr_type); }
#line 985 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 26: // word: "expression begin" expr_int "expression end"
#line 138 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                                         { auto e = Expression(Node(Type::NUMBER, std::to_string(yystack_[1].value.as < int > ())), std::vector<Expression>{});
                                       scanner->add_expr(new Expression(Node(Type::ASSIGN, "="), std::vector<Expression>{Expression(Node(Type::VAR, "$"), std::vector<Expression>()), e}), IR::Type::NUMBER);}
#line 992 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 27: // word: "expression begin" expr_float "expression end"
#line 140 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                                           { auto e = Expression(Node(Type::FLOAT, std::to_string(yystack_[1].value.as < float > ())), std::vector<Expression>{});
                                       scanner->add_expr(new Expression(Node(Type::ASSIGN, "="), std::vector<Expression>{Expression(Node(Type::VAR, "$"), std::vector<Expression>()), e}), IR::Type::FLOAT);}
#line 999 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 28: // varexpr: "$"
#line 144 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                { yylhs.value.as < Expr::Expression > () = Expression(Node(Type::VAR, yystack_[0].value.as < std::string > ()), std::vector<Expression>()); }
#line 1005 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 29: // varexpr: "-" "$"
#line 145 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                                { yylhs.value.as < Expr::Expression > () = Expression(Node(Type::IMUL, "*"), std::vector<Expression>{Expression(Node(Type::NUMBER, std::string("-1")), std::vector<Expression>{}), Expression(Node(Type::VAR, yystack_[0].value.as < std::string > ()), std::vector<Expression>())}); }
#line 1011 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 30: // varexpr: "(" varexpr ")"
#line 146 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                              { yylhs.value.as < Expr::Expression > () = yystack_[1].value.as < Expr::Expression > (); }
#line 1017 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 31: // varexpr: expr "^" varexpr
#line 147 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                             { yylhs.value.as < Expr::Expression > () = Expression(Node(Type::POW, "^"), std::vector<Expression>{Expression(yystack_[2].value.as < Node > (), std::vector<Expression>{}), yystack_[0].value.as < Expr::Expression > ()}); }
#line 1023 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 32: // varexpr: expr "%" varexpr
#line 148 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                             { yylhs.value.as < Expr::Expression > () = Expression(Node(Type::MOD, "%"), std::vector<Expression>{Expression(yystack_[2].value.as < Node > (), std::vector<Expression>{}), yystack_[0].value.as < Expr::Expression > ()}); }
#line 1029 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 33: // varexpr: expr "*" varexpr
#line 149 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                              { yylhs.value.as < Expr::Expression > () = Expression(Node(Type::IMUL, "*"), std::vector<Expression>{Expression(yystack_[2].value.as < Node > (), std::vector<Expression>{}), yystack_[0].value.as < Expr::Expression > ()}); }
#line 1035 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 34: // varexpr: expr "/" varexpr
#line 150 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                              { yylhs.value.as < Expr::Expression > () = Expression(Node(Type::IDIV, "/"), std::vector<Expression>{Expression(yystack_[2].value.as < Node > (), std::vector<Expression>{}), yystack_[0].value.as < Expr::Expression > ()}); }
#line 1041 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 35: // varexpr: expr "-" varexpr
#line 151 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                               { yylhs.value.as < Expr::Expression > () = Expression(Node(Type::SUB, "-"), std::vector<Expression>{Expression(yystack_[2].value.as < Node > (), std::vector<Expression>{}), yystack_[0].value.as < Expr::Expression > ()}); }
#line 1047 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 36: // varexpr: expr "+" varexpr
#line 152 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                              { yylhs.value.as < Expr::Expression > () = Expression(Node(Type::ADD, "+"), std::vector<Expression>{Expression(yystack_[2].value.as < Node > (), std::vector<Expression>{}), yystack_[0].value.as < Expr::Expression > ()}); }
#line 1053 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 37: // varexpr: varexpr "^" expr
#line 153 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                             { yylhs.value.as < Expr::Expression > () = Expression(Node(Type::POW, "^"), std::vector<Expression>{yystack_[2].value.as < Expr::Expression > (), Expression(yystack_[0].value.as < Node > (), std::vector<Expression>{})}); }
#line 1059 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 38: // varexpr: varexpr "%" expr
#line 154 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                             { yylhs.value.as < Expr::Expression > () = Expression(Node(Type::MOD, "%"), std::vector<Expression>{yystack_[2].value.as < Expr::Expression > (), Expression(yystack_[0].value.as < Node > (), std::vector<Expression>{})}); }
#line 1065 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 39: // varexpr: varexpr "*" expr
#line 155 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                              { yylhs.value.as < Expr::Expression > () = Expression(Node(Type::IMUL, "*"), std::vector<Expression>{yystack_[2].value.as < Expr::Expression > (), Expression(yystack_[0].value.as < Node > (), std::vector<Expression>{})}); }
#line 1071 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 40: // varexpr: varexpr "/" expr
#line 156 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                              { yylhs.value.as < Expr::Expression > () = Expression(Node(Type::IDIV, "/"), std::vector<Expression>{yystack_[2].value.as < Expr::Expression > (), Expression(yystack_[0].value.as < Node > (), std::vector<Expression>{})}); }
#line 1077 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 41: // varexpr: varexpr "-" expr
#line 157 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                               { yylhs.value.as < Expr::Expression > () = Expression(Node(Type::SUB, "-"), std::vector<Expression>{yystack_[2].value.as < Expr::Expression > (), Expression(yystack_[0].value.as < Node > (), std::vector<Expression>{})}); }
#line 1083 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 42: // varexpr: varexpr "+" expr
#line 158 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                              { yylhs.value.as < Expr::Expression > () = Expression(Node(Type::ADD, "+"),  std::vector<Expression>{yystack_[2].value.as < Expr::Expression > (), Expression(yystack_[0].value.as < Node > (), std::vector<Expression>{})}); }
#line 1089 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 43: // varexpr: varexpr "^" varexpr
#line 159 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                                { yylhs.value.as < Expr::Expression > () = Expression(Node(Type::POW, "^"), std::vector<Expression>{yystack_[2].value.as < Expr::Expression > (), yystack_[0].value.as < Expr::Expression > ()}); }
#line 1095 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 44: // varexpr: varexpr "%" varexpr
#line 160 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                                { yylhs.value.as < Expr::Expression > () = Expression(Node(Type::MOD, "%"), std::vector<Expression>{yystack_[2].value.as < Expr::Expression > (), yystack_[0].value.as < Expr::Expression > ()}); }
#line 1101 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 45: // varexpr: varexpr "*" varexpr
#line 161 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                                 { yylhs.value.as < Expr::Expression > () = Expression(Node(Type::IMUL, "*"), std::vector<Expression>{yystack_[2].value.as < Expr::Expression > (), yystack_[0].value.as < Expr::Expression > ()}); }
#line 1107 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 46: // varexpr: varexpr "/" varexpr
#line 162 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                                 { yylhs.value.as < Expr::Expression > () = Expression(Node(Type::IDIV, "/"), std::vector<Expression>{yystack_[2].value.as < Expr::Expression > (), yystack_[0].value.as < Expr::Expression > ()}); }
#line 1113 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 47: // varexpr: varexpr "-" varexpr
#line 163 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                                  { yylhs.value.as < Expr::Expression > () = Expression(Node(Type::SUB, "-"), std::vector<Expression>{yystack_[2].value.as < Expr::Expression > (), yystack_[0].value.as < Expr::Expression > ()}); }
#line 1119 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 48: // varexpr: varexpr "+" varexpr
#line 164 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                                 { yylhs.value.as < Expr::Expression > () = Expression(Node(Type::ADD, "+"), std::vector<Expression>{yystack_[2].value.as < Expr::Expression > (), yystack_[0].value.as < Expr::Expression > ()}); }
#line 1125 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 49: // expr: expr_float
#line 167 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                       { yylhs.value.as < Node > () = Node(Type::FLOAT, std::to_string(yystack_[0].value.as < float > ())); scanner->deducted_expr_type(IR::Type::FLOAT); }
#line 1131 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 50: // expr: expr_int
#line 168 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                       { yylhs.value.as < Node > () = Node(Type::NUMBER, std::to_string(yystack_[0].value.as < int > ())); scanner->deducted_expr_type(IR::Type::NUMBER); }
#line 1137 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 51: // expr_float: FLOAT
#line 171 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                  { yylhs.value.as < float > () = std::stof(yystack_[0].value.as < std::string > ().c_str()); /* Atoi is safe to use because syntactical analysis was done */ }
#line 1143 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 52: // expr_float: "-" expr_float
#line 172 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                                       { yylhs.value.as < float > () = -yystack_[0].value.as < float > (); /* Unary minus */}
#line 1149 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 53: // expr_float: "(" expr_float ")"
#line 173 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                                 { yylhs.value.as < float > () = yystack_[1].value.as < float > (); }
#line 1155 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 54: // expr_float: expr_float "^" expr_float
#line 174 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                                      { yylhs.value.as < float > () = std::pow(yystack_[2].value.as < float > (), yystack_[0].value.as < float > ());}
#line 1161 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 55: // expr_float: expr_float "%" expr_float
#line 175 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                                      { yylhs.value.as < float > () = std::fmod(yystack_[2].value.as < float > (), yystack_[0].value.as < float > ());}
#line 1167 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 56: // expr_float: expr_float "*" expr_float
#line 176 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                                       { yylhs.value.as < float > () = yystack_[2].value.as < float > () * yystack_[0].value.as < float > ();}
#line 1173 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 57: // expr_float: expr_float "/" expr_float
#line 177 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                                       { yylhs.value.as < float > () = yystack_[2].value.as < float > () / yystack_[0].value.as < float > ();}
#line 1179 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 58: // expr_float: expr_float "-" expr_float
#line 178 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                                        { yylhs.value.as < float > () = yystack_[2].value.as < float > () - yystack_[0].value.as < float > ();}
#line 1185 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 59: // expr_float: expr_float "+" expr_float
#line 179 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                                       { yylhs.value.as < float > () = yystack_[2].value.as < float > () + yystack_[0].value.as < float > ();}
#line 1191 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 60: // expr_int: NUMBER
#line 182 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                   { yylhs.value.as < int > () = atoi(yystack_[0].value.as < std::string > ().c_str()); /* Atoi is safe to use because syntactical analysis was done */ }
#line 1197 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 61: // expr_int: "-" expr_int
#line 183 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                                     { yylhs.value.as < int > () = -yystack_[0].value.as < int > (); /* Unary minus */}
#line 1203 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 62: // expr_int: "(" expr_int ")"
#line 184 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                               { yylhs.value.as < int > () = yystack_[1].value.as < int > (); }
#line 1209 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 63: // expr_int: expr_int "^" expr_int
#line 185 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                                  { yylhs.value.as < int > () = static_cast<int>(std::pow(yystack_[2].value.as < int > (), yystack_[0].value.as < int > ()));}
#line 1215 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 64: // expr_int: expr_int "%" expr_int
#line 186 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                                  { yylhs.value.as < int > () = yystack_[2].value.as < int > () % yystack_[0].value.as < int > ();}
#line 1221 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 65: // expr_int: expr_int "*" expr_int
#line 187 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                                   { yylhs.value.as < int > () = yystack_[2].value.as < int > () * yystack_[0].value.as < int > ();}
#line 1227 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 66: // expr_int: expr_int "/" expr_int
#line 188 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                                   { yylhs.value.as < int > () = yystack_[2].value.as < int > () / yystack_[0].value.as < int > ();}
#line 1233 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 67: // expr_int: expr_int "-" expr_int
#line 189 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                                    { yylhs.value.as < int > () = yystack_[2].value.as < int > () - yystack_[0].value.as < int > ();}
#line 1239 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;

  case 68: // expr_int: expr_int "+" expr_int
#line 190 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
                                   { yylhs.value.as < int > () = yystack_[2].value.as < int > () + yystack_[0].value.as < int > ();}
#line 1245 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"
    break;


#line 1249 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"

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


  const signed char  ParserText ::yypact_ninf_ = -13;

  const signed char  ParserText ::yytable_ninf_ = -1;

  const short
   ParserText ::yypact_[] =
  {
      69,   -13,   -13,    -7,   -13,   -13,   -13,   -13,   -13,   -13,
     -13,   -13,   -13,   -13,   -13,   -13,     9,   -13,   -13,   -13,
       4,   101,   -13,   -13,   -13,    -7,   -13,     1,    10,   154,
     118,   124,   -13,   -13,   -13,   -13,   -13,   132,   140,   148,
     115,   -13,   115,   -13,   -13,   -13,    -7,    -7,    -7,    -7,
      -7,    -7,    -7,    -7,    -7,    -7,    -7,    -7,   -13,    79,
      79,    79,    79,    79,    79,   -13,    -6,    -6,    -6,    -6,
      -6,    -6,   -13,   -13,   -13,   140,   148,    15,   177,   160,
     166,   -12,    -4,    15,   177,   -12,    -4,   -12,    -4,   -12,
      -4,    15,   -12,    15,   -12,   -12,   -12,    79,    79,   182,
      12,   182,    12,    12,    12,    -6,    -6,   187,    32,   187,
      32,    32,    32
  };

  const signed char
   ParserText ::yydefact_[] =
  {
       0,     2,    13,     0,    23,    24,     6,     8,    11,    12,
      10,    21,    22,    14,    15,    16,    17,    18,    19,    20,
       0,     0,     4,    60,    51,     0,    28,     0,     0,     0,
       0,     0,     7,     9,     1,     3,     5,     0,     0,     0,
       0,    29,     0,    52,    61,    25,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    27,     0,
       0,     0,     0,     0,     0,    26,     0,     0,     0,     0,
       0,     0,    30,    53,    62,     0,     0,    48,    42,    49,
      50,    45,    39,    47,    41,    46,    40,    44,    38,    43,
      37,    36,    33,    35,    34,    32,    31,     0,     0,    59,
      56,    58,    57,    55,    54,     0,     0,    68,    65,    67,
      66,    64,    63
  };

  const short
   ParserText ::yypgoto_[] =
  {
     -13,   -13,   -13,    33,    -5,   142,    -2,    -3
  };

  const signed char
   ParserText ::yydefgoto_[] =
  {
       0,    20,    21,    22,    28,    29,    79,    80
  };

  const signed char
   ParserText ::yytable_[] =
  {
      31,    30,    23,    23,    34,    24,    25,   105,    26,    51,
      23,    27,   106,    24,    40,    45,    41,    57,    32,    42,
      37,    33,    39,    38,    44,    43,    46,    47,    48,    49,
      50,    51,    47,    64,    49,    50,    51,    76,    75,    44,
      43,    77,    81,    83,    85,    87,    89,    91,    92,    93,
      94,    95,    96,    71,    36,     0,     0,    99,   100,   101,
     102,   103,   104,   107,   108,   109,   110,   111,   112,     1,
       0,     0,     2,     3,     0,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    24,    97,     0,     0,    75,    43,    98,     0,     0,
       0,    35,    76,    44,     2,     3,     0,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    58,    23,     0,     0,    24,    40,    65,
       0,     0,     0,    42,    59,    60,    61,    62,    63,    64,
      66,    67,    68,    69,    70,    71,    72,     0,    46,    47,
      48,    49,    50,    51,    73,     0,    59,    60,    61,    62,
      63,    64,    74,     0,    66,    67,    68,    69,    70,    71,
      52,    53,    54,    55,    56,    57,    59,    60,    61,    62,
      63,    64,    66,    67,    68,    69,    70,    71,    78,    82,
      84,    86,    88,    90,    53,     0,    55,    56,    57,    60,
       0,    62,    63,    64,    67,     0,    69,    70,    71
  };

  const signed char
   ParserText ::yycheck_[] =
  {
       3,     3,     9,     9,     0,    12,    13,    13,    15,    21,
       9,    18,    18,    12,    13,     5,    15,    21,     9,    18,
      25,    12,    25,    25,    27,    27,    16,    17,    18,    19,
      20,    21,    17,    21,    19,    20,    21,    40,    40,    42,
      42,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    21,    21,    -1,    -1,    59,    60,    61,
      62,    63,    64,    66,    67,    68,    69,    70,    71,     0,
      -1,    -1,     3,     4,    -1,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    12,    13,    -1,    -1,    97,    98,    18,    -1,    -1,
      -1,     0,   105,   106,     3,     4,    -1,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,     5,     9,    -1,    -1,    12,    13,     5,
      -1,    -1,    -1,    18,    16,    17,    18,    19,    20,    21,
      16,    17,    18,    19,    20,    21,    14,    -1,    16,    17,
      18,    19,    20,    21,    14,    -1,    16,    17,    18,    19,
      20,    21,    14,    -1,    16,    17,    18,    19,    20,    21,
      16,    17,    18,    19,    20,    21,    16,    17,    18,    19,
      20,    21,    16,    17,    18,    19,    20,    21,    46,    47,
      48,    49,    50,    51,    17,    -1,    19,    20,    21,    17,
      -1,    19,    20,    21,    17,    -1,    19,    20,    21
  };

  const signed char
   ParserText ::yystos_[] =
  {
       0,     0,     3,     4,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      24,    25,    26,     9,    12,    13,    15,    18,    27,    28,
      29,    30,     9,    12,     0,     0,    26,    27,    29,    30,
      13,    15,    18,    29,    30,     5,    16,    17,    18,    19,
      20,    21,    16,    17,    18,    19,    20,    21,     5,    16,
      17,    18,    19,    20,    21,     5,    16,    17,    18,    19,
      20,    21,    14,    14,    14,    29,    30,    27,    28,    29,
      30,    27,    28,    27,    28,    27,    28,    27,    28,    27,
      28,    27,    27,    27,    27,    27,    27,    13,    18,    29,
      29,    29,    29,    29,    29,    13,    18,    30,    30,    30,
      30,    30,    30
  };

  const signed char
   ParserText ::yyr1_[] =
  {
       0,    23,    24,    24,    25,    25,    26,    26,    26,    26,
      26,    26,    26,    26,    26,    26,    26,    26,    26,    26,
      26,    26,    26,    26,    26,    26,    26,    26,    27,    27,
      27,    27,    27,    27,    27,    27,    27,    27,    27,    27,
      27,    27,    27,    27,    27,    27,    27,    27,    27,    28,
      28,    29,    29,    29,    29,    29,    29,    29,    29,    29,
      30,    30,    30,    30,    30,    30,    30,    30,    30
  };

  const signed char
   ParserText ::yyr2_[] =
  {
       0,     2,     1,     2,     1,     2,     1,     2,     1,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     3,     3,     1,     2,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     1,
       1,     1,     2,     3,     3,     3,     3,     3,     3,     3,
       1,     2,     3,     3,     3,     3,     3,     3,     3
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
  "\"+\"", "\"*\"", "\"-\"", "\"/\"", "\"%\"", "\"^\"", "NEG", "$accept",
  "text_file", "sentence", "word", "varexpr", "expr", "expr_float",
  "expr_int", YY_NULLPTR
  };
#endif


#if YYDEBUG
  const unsigned char
   ParserText ::yyrline_[] =
  {
       0,   108,   108,   109,   113,   114,   118,   119,   120,   121,
     122,   123,   124,   125,   126,   127,   128,   129,   130,   131,
     132,   133,   134,   135,   136,   137,   138,   140,   144,   145,
     146,   147,   148,   149,   150,   151,   152,   153,   154,   155,
     156,   157,   158,   159,   160,   161,   162,   163,   164,   167,
     168,   171,   172,   173,   174,   175,   176,   177,   178,   179,
     182,   183,   184,   185,   186,   187,   188,   189,   190
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
      15,    16,    17,    18,    19,    20,    21,    22
    };
    // Last valid token kind.
    const int code_max = 277;

    if (t <= 0)
      return symbol_kind::S_YYEOF;
    else if (t <= code_max)
      return static_cast <symbol_kind_type> (translate_table[t]);
    else
      return symbol_kind::S_YYUNDEF;
  }

#line 19 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"
} //  TextFile 
#line 1852 "/home/marek/Desktop/Skola/dp/ebe/frontend/parser_text.cpp"

#line 193 "/home/marek/Desktop/Skola/dp/ebe/frontend/grammars/parser_text.yy"


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
