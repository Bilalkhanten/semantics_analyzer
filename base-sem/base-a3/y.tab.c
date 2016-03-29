/* A Bison parser, made by GNU Bison 2.6.4.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2012 Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.6.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
/* Line 358 of yacc.c  */
#line 14 "parser.y"


/* Just like lex, the text within this first region delimited by %{ and %}
 * is assumed to be C/C++ code and will be copied verbatim to the y.tab.c
 * file ahead of the definitions of the yyparse() function. Add other header
 * file inclusions or C++ variable declarations/prototypes that are needed
 * by your code here.
 */
#include "scanner.h" // for yylex
#include "parser.h"
#include "errors.h"

void yyerror(const char *msg); // standard error-handling routine


/* Line 358 of yacc.c  */
#line 84 "y.tab.c"

# ifndef YY_NULL
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULL nullptr
#  else
#   define YY_NULL 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "y.tab.h".  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     T_Void = 258,
     T_Bool = 259,
     T_Int = 260,
     T_Double = 261,
     T_String = 262,
     T_Class = 263,
     T_LessEqual = 264,
     T_GreaterEqual = 265,
     T_Equal = 266,
     T_NotEqual = 267,
     T_Dims = 268,
     T_And = 269,
     T_Or = 270,
     T_Null = 271,
     T_Extends = 272,
     T_This = 273,
     T_Interface = 274,
     T_Implements = 275,
     T_While = 276,
     T_For = 277,
     T_If = 278,
     T_Else = 279,
     T_Return = 280,
     T_Break = 281,
     T_New = 282,
     T_NewArray = 283,
     T_Print = 284,
     T_ReadInteger = 285,
     T_ReadLine = 286,
     T_Increment = 287,
     T_Decrement = 288,
     T_Switch = 289,
     T_Case = 290,
     T_Default = 291,
     T_Identifier = 292,
     T_StringConstant = 293,
     T_IntConstant = 294,
     T_DoubleConstant = 295,
     T_BoolConstant = 296,
     NoElse = 297
   };
#endif
/* Tokens.  */
#define T_Void 258
#define T_Bool 259
#define T_Int 260
#define T_Double 261
#define T_String 262
#define T_Class 263
#define T_LessEqual 264
#define T_GreaterEqual 265
#define T_Equal 266
#define T_NotEqual 267
#define T_Dims 268
#define T_And 269
#define T_Or 270
#define T_Null 271
#define T_Extends 272
#define T_This 273
#define T_Interface 274
#define T_Implements 275
#define T_While 276
#define T_For 277
#define T_If 278
#define T_Else 279
#define T_Return 280
#define T_Break 281
#define T_New 282
#define T_NewArray 283
#define T_Print 284
#define T_ReadInteger 285
#define T_ReadLine 286
#define T_Increment 287
#define T_Decrement 288
#define T_Switch 289
#define T_Case 290
#define T_Default 291
#define T_Identifier 292
#define T_StringConstant 293
#define T_IntConstant 294
#define T_DoubleConstant 295
#define T_BoolConstant 296
#define NoElse 297



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{
/* Line 374 of yacc.c  */
#line 44 "parser.y"

    int integerConstant;
    bool boolConstant;
    char *stringConstant;
    double doubleConstant;
    char identifier[MaxIdentLen+1]; // +1 for terminating null
    Decl *decl;
    List<Decl*> *declList;
    VarDecl *varDecl;
    FnDecl *fnDecl;
    ClassDecl *classDecl;
    InterfaceDecl *interfaceDecl;
    VarDecl *var;
    List<VarDecl*> *varList;
    Type *type;
    StmtBlock *stmtBlock;
    List<Identifier*> *identifierList;
    NamedType *namedType;
    List<NamedType*> *namedTypeList;
    List<Stmt*> *stmtList;
    Stmt *stmt;
    Expr *expr;
    List<Expr*> *exprList;
    IfStmt *ifStmt;
    WhileStmt *whileStmt;
    ForStmt *forStmt;
    ReturnStmt *returnStmt;
    BreakStmt *breakStmt;
    PrintStmt *printStmt;
    Case *caseStmt;
    List<Case*> *caseList;
    Default *defaultStmt;
    SwitchStmt *switchStmt;
    LValue *lvalue;


/* Line 374 of yacc.c  */
#line 248 "y.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
} YYLTYPE;
# define yyltype YYLTYPE /* obsolescent; will be withdrawn */
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;
extern YYLTYPE yylloc;
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

/* Line 377 of yacc.c  */
#line 289 "y.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(N) (N)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
	     && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  21
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1015

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  62
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  43
/* YYNRULES -- Number of rules.  */
#define YYNRULES  124
/* YYNRULES -- Number of states.  */
#define YYNSTATES  247

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   297

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    51,     2,     2,     2,    49,     2,     2,
      56,    57,    50,    47,    58,    46,    52,    48,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    61,    55,
      44,    43,    45,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    53,     2,    54,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    59,     2,    60,     2,     2,     2,     2,
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
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     8,    10,    12,    14,    16,    18,
      21,    25,    28,    30,    32,    34,    36,    38,    41,    48,
      55,    62,    69,    73,    75,    77,    78,    82,    84,    87,
      88,    91,    92,    95,    96,   104,   106,   108,   111,   112,
     118,   125,   132,   139,   146,   149,   151,   154,   156,   161,
     165,   169,   172,   174,   175,   178,   182,   184,   186,   188,
     190,   192,   194,   196,   198,   201,   202,   209,   216,   222,
     232,   236,   239,   243,   245,   251,   254,   255,   260,   263,
     265,   269,   271,   272,   281,   285,   287,   289,   291,   293,
     297,   301,   305,   309,   313,   317,   320,   324,   328,   332,
     336,   340,   344,   348,   352,   355,   359,   363,   366,   373,
     376,   379,   381,   385,   390,   395,   400,   407,   414,   416,
     417,   419,   421,   423,   425
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      63,     0,    -1,    64,    -1,    64,    65,    -1,    65,    -1,
      66,    -1,    69,    -1,    76,    -1,    79,    -1,    67,    55,
      -1,    67,     1,    55,    -1,    68,    37,    -1,     5,    -1,
       6,    -1,     4,    -1,     7,    -1,    37,    -1,    68,    13,
      -1,    68,    37,    56,    71,    57,    83,    -1,    68,    37,
      56,     1,    57,    83,    -1,     3,    37,    56,    71,    57,
      83,    -1,     3,    37,    56,     1,    57,    83,    -1,    70,
      58,    67,    -1,    67,    -1,    70,    -1,    -1,    72,    58,
      37,    -1,    37,    -1,    17,    37,    -1,    -1,    20,    72,
      -1,    -1,    75,    77,    -1,    -1,     8,    37,    73,    74,
      59,    75,    60,    -1,    66,    -1,    69,    -1,    78,    80,
      -1,    -1,    19,    37,    59,    78,    60,    -1,    68,    37,
      56,    71,    57,    55,    -1,    68,    37,    56,     1,    57,
      55,    -1,     3,    37,    56,    71,    57,    55,    -1,     3,
      37,    56,     1,    57,    55,    -1,    81,    85,    -1,    85,
      -1,    82,    66,    -1,    66,    -1,    59,    82,    81,    60,
      -1,    59,    82,    60,    -1,    59,    81,    60,    -1,    59,
      60,    -1,   100,    -1,    -1,    84,    55,    -1,   100,     1,
      55,    -1,    87,    -1,    88,    -1,    89,    -1,    91,    -1,
      90,    -1,    93,    -1,    99,    -1,    83,    -1,    24,    85,
      -1,    -1,    23,    56,   100,    57,    85,    86,    -1,    23,
      56,     1,    57,    85,    86,    -1,    21,    56,   100,    57,
      85,    -1,    22,    56,    84,    55,   100,    55,    84,    57,
      85,    -1,    25,    84,    55,    -1,    26,    55,    -1,    92,
      58,   100,    -1,   100,    -1,    29,    56,    92,    57,    55,
      -1,    94,    85,    -1,    -1,    35,    39,    61,    94,    -1,
      96,    95,    -1,    95,    -1,    36,    61,    94,    -1,    97,
      -1,    -1,    34,    56,   100,    57,    59,    96,    98,    60,
      -1,   101,    43,   100,    -1,   104,    -1,   101,    -1,    18,
      -1,   102,    -1,    56,   100,    57,    -1,   100,    47,   100,
      -1,   100,    46,   100,    -1,   100,    50,   100,    -1,   100,
      48,   100,    -1,   100,    49,   100,    -1,    46,   100,    -1,
     100,    44,   100,    -1,   100,     9,   100,    -1,   100,    45,
     100,    -1,   100,    10,   100,    -1,   100,    11,   100,    -1,
     100,    12,   100,    -1,   100,    14,   100,    -1,   100,    15,
     100,    -1,    51,   100,    -1,    30,    56,    57,    -1,    31,
      56,    57,    -1,    27,    37,    -1,    28,    56,   100,    58,
      68,    57,    -1,   100,    32,    -1,   100,    33,    -1,    37,
      -1,   100,    52,    37,    -1,   100,    53,   100,    54,    -1,
      37,    56,   103,    57,    -1,    37,    56,     1,    57,    -1,
     100,    52,    37,    56,   103,    57,    -1,   100,    52,    37,
      56,     1,    57,    -1,    92,    -1,    -1,    39,    -1,    40,
      -1,    41,    -1,    38,    -1,    16,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   193,   193,   208,   209,   212,   213,   214,   215,   218,
     219,   222,   227,   228,   229,   230,   231,   233,   236,   241,
     244,   250,   255,   256,   259,   260,   263,   267,   272,   276,
     279,   284,   287,   288,   291,   298,   299,   302,   303,   306,
     312,   316,   319,   324,   329,   330,   333,   334,   337,   338,
     341,   344,   350,   351,   354,   355,   356,   357,   358,   359,
     360,   361,   362,   363,   366,   367,   370,   371,   374,   377,
     382,   385,   388,   389,   392,   395,   396,   399,   405,   406,
     409,   412,   413,   416,   421,   424,   425,   426,   427,   428,
     429,   432,   435,   438,   441,   444,   447,   450,   454,   457,
     461,   464,   467,   470,   473,   476,   477,   478,   482,   485,
     486,   489,   492,   496,   499,   503,   506,   510,   515,   516,
     519,   520,   521,   522,   523
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "T_Void", "T_Bool", "T_Int", "T_Double",
  "T_String", "T_Class", "T_LessEqual", "T_GreaterEqual", "T_Equal",
  "T_NotEqual", "T_Dims", "T_And", "T_Or", "T_Null", "T_Extends", "T_This",
  "T_Interface", "T_Implements", "T_While", "T_For", "T_If", "T_Else",
  "T_Return", "T_Break", "T_New", "T_NewArray", "T_Print", "T_ReadInteger",
  "T_ReadLine", "T_Increment", "T_Decrement", "T_Switch", "T_Case",
  "T_Default", "T_Identifier", "T_StringConstant", "T_IntConstant",
  "T_DoubleConstant", "T_BoolConstant", "NoElse", "'='", "'<'", "'>'",
  "'-'", "'+'", "'/'", "'%'", "'*'", "'!'", "'.'", "'['", "']'", "';'",
  "'('", "')'", "','", "'{'", "'}'", "':'", "$accept", "Program", "DeclP",
  "Decl", "VarDecl", "Var", "Type", "FnDecl", "VarPC", "Formals",
  "IdentifierPC", "ExtendsO", "ImplementsO", "FieldS", "ClassDecl",
  "Field", "PrototypeS", "InterfaceDecl", "Prototype", "StmtP", "VarDeclP",
  "StmtBlock", "ExprO", "Stmt", "ElseO", "IfStmt", "WhileStmt", "ForStmt",
  "ReturnStmt", "BreakStmt", "ExprPC", "PrintStmt", "StmtS", "Case",
  "CaseP", "Default", "DefaultO", "SwitchStmt", "Expr", "LValue", "Call",
  "Actuals", "Constant", YY_NULL
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,    61,    60,    62,    45,    43,    47,    37,
      42,    33,    46,    91,    93,    59,    40,    41,    44,   123,
     125,    58
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    62,    63,    64,    64,    65,    65,    65,    65,    66,
      66,    67,    68,    68,    68,    68,    68,    68,    69,    69,
      69,    69,    70,    70,    71,    71,    72,    72,    73,    73,
      74,    74,    75,    75,    76,    77,    77,    78,    78,    79,
      80,    80,    80,    80,    81,    81,    82,    82,    83,    83,
      83,    83,    84,    84,    85,    85,    85,    85,    85,    85,
      85,    85,    85,    85,    86,    86,    87,    87,    88,    89,
      90,    91,    92,    92,    93,    94,    94,    95,    96,    96,
      97,    98,    98,    99,   100,   100,   100,   100,   100,   100,
     100,   100,   100,   100,   100,   100,   100,   100,   100,   100,
     100,   100,   100,   100,   100,   100,   100,   100,   100,   100,
     100,   101,   101,   101,   102,   102,   102,   102,   103,   103,
     104,   104,   104,   104,   104
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     1,     1,     2,
       3,     2,     1,     1,     1,     1,     1,     2,     6,     6,
       6,     6,     3,     1,     1,     0,     3,     1,     2,     0,
       2,     0,     2,     0,     7,     1,     1,     2,     0,     5,
       6,     6,     6,     6,     2,     1,     2,     1,     4,     3,
       3,     2,     1,     0,     2,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     2,     0,     6,     6,     5,     9,
       3,     2,     3,     1,     5,     2,     0,     4,     2,     1,
       3,     1,     0,     8,     3,     1,     1,     1,     1,     3,
       3,     3,     3,     3,     3,     2,     3,     3,     3,     3,
       3,     3,     3,     3,     2,     3,     3,     2,     6,     2,
       2,     1,     3,     4,     4,     4,     6,     6,     1,     0,
       1,     1,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,    14,    12,    13,    15,     0,     0,    16,     0,
       2,     4,     5,     0,     0,     6,     7,     8,     0,    29,
       0,     1,     3,     0,     9,    17,    11,     0,     0,    31,
      38,    10,     0,     0,    23,     0,    24,     0,    28,     0,
       0,     0,     0,     0,     0,    11,     0,     0,    27,    30,
      33,     0,    39,     0,    37,     0,     0,    53,    21,    22,
      20,     0,     0,     0,     0,    19,    18,   124,    87,     0,
       0,     0,    53,     0,     0,     0,     0,     0,     0,     0,
     111,   123,   120,   121,   122,     0,     0,     0,    51,    47,
      53,    53,    63,     0,    45,    56,    57,    58,    60,    59,
      61,    62,     0,    86,    88,    85,    26,    34,    35,    36,
      32,     0,     0,     0,    53,     0,   111,     0,    52,    71,
     107,     0,     0,     0,     0,     0,     0,    95,   104,     0,
      50,    44,    49,    46,    53,    54,     0,     0,     0,     0,
       0,     0,     0,   109,   110,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    70,     0,     0,    73,   105,   106,     0,
       0,   118,     0,    89,    48,    55,    97,    99,   100,   101,
     102,   103,    96,    98,    91,    90,    93,    94,    92,   112,
       0,    84,     0,     0,     0,     0,    53,     0,    53,    53,
       0,     0,     0,     0,   115,   114,     0,   113,    43,    42,
      41,    40,    68,     0,    65,    65,     0,    74,    72,     0,
       0,     0,    53,    53,    67,    66,   108,     0,    79,    82,
     117,   116,     0,    64,     0,     0,    78,    81,     0,    53,
      76,    76,    83,    69,    77,    53,    75
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     9,    10,    11,    12,    13,    35,    15,    36,    37,
      49,    29,    40,    62,    16,   110,    41,    17,    54,    90,
      91,    92,    93,    94,   224,    95,    96,    97,    98,    99,
     171,   100,   244,   228,   229,   237,   238,   101,   102,   103,
     104,   172,   105
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -90
static const yytype_int16 yypact[] =
{
     108,   -22,   -90,   -90,   -90,   -90,   -18,   -13,   -90,    35,
     108,   -90,   -90,     3,     5,   -90,   -90,   -90,    -3,    29,
       4,   -90,   -90,    39,   -90,   -90,    40,    22,    61,    84,
     -90,   -90,    96,    51,   -90,    41,    59,    67,   -90,    91,
      70,    27,    74,    83,    71,   -90,    33,    71,   -90,    93,
     -90,   105,   -90,    58,   -90,    71,    71,   142,   -90,   -90,
     -90,   106,    62,    88,    98,   -90,   -90,   -90,   -90,   103,
     110,   118,   952,   107,   124,   119,   121,   122,   130,   131,
      -1,   -90,   -90,   -90,   -90,   952,   952,   952,   -90,   -90,
     569,   190,   -90,   134,   -90,   -90,   -90,   -90,   -90,   -90,
     -90,   -90,   349,   147,   -90,   -90,   -90,   -90,   -90,   -90,
     -90,   283,   298,   952,   952,   306,   135,   137,   692,   -90,
     -90,   952,   952,   146,   150,   952,   224,   962,   152,   401,
     -90,   -90,   -90,   -90,   614,   -90,   144,   952,   952,   952,
     952,   952,   952,   -90,   -90,   952,   952,   952,   952,   952,
     952,   952,   172,   952,   952,   153,   157,   165,   166,   427,
     171,   175,   453,   -90,   374,    -6,   692,   -90,   -90,   479,
     176,   177,   180,   -90,   -90,   -90,   904,   790,   757,   321,
     747,   702,   802,   914,   962,   265,    86,    73,   152,   178,
     530,   692,   183,   184,   188,   189,   882,   952,   882,   882,
      33,   192,   952,   186,   -90,   -90,   255,   -90,   -90,   -90,
     -90,   -90,   -90,   505,   229,   229,   -10,   -90,   692,   213,
     200,   201,   952,   882,   -90,   -90,   -90,   220,   -90,    85,
     -90,   -90,   203,   -90,   205,   206,   -90,   -90,   208,   882,
     -90,   -90,   -90,   -90,   840,   659,   -90
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -90,   -90,   -90,   259,   -48,   -21,     0,   210,   -90,   -19,
     -90,   -90,   -90,   -90,   -90,   -90,   -90,   -90,   -90,   185,
     -90,   -39,   -70,   -89,    63,   -90,   -90,   -90,   -90,   -90,
     155,   -90,    38,    45,   -90,   -90,   -90,   -90,   -65,   -90,
     -90,    94,   -90
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -120
static const yytype_int16 yytable[] =
{
      14,   131,   117,    25,    23,    58,    34,   118,    60,    89,
      14,    34,   -16,    43,   108,    18,    65,    66,    25,    19,
     127,   128,   129,    33,    20,    59,     2,     3,     4,     5,
      51,     2,     3,     4,     5,    21,   -16,     2,     3,     4,
       5,    53,    26,   133,   160,   131,    28,   226,   159,   118,
     162,   201,   202,    27,    25,   126,   164,   166,    24,     8,
     169,   166,    14,    30,     8,     1,     2,     3,     4,     5,
       8,    25,   176,   177,   178,   179,   180,   181,    45,   -25,
     182,   183,   184,   185,   186,   187,   188,    52,   190,   191,
      34,    34,   156,   158,    31,    64,    32,    42,    38,     8,
       2,     3,     4,     5,    39,   143,   144,   212,    44,   214,
     215,     1,     2,     3,     4,     5,     6,    46,   143,   144,
     227,   235,   107,   151,    47,   152,   153,     7,    48,    50,
      57,    55,   213,     8,   233,   150,   151,   218,   152,   153,
      56,   166,    63,   106,   111,     8,     2,     3,     4,     5,
     243,    61,   232,   -25,   112,   246,   246,   118,    67,   113,
      68,   120,   119,    69,    70,    71,   114,    72,    73,    74,
      75,    76,    77,    78,   115,   121,    79,   122,   123,    80,
      81,    82,    83,    84,   143,   144,   124,   125,    85,   135,
     154,   126,   163,    86,     2,     3,     4,     5,    87,   175,
     216,    57,    88,   167,   152,   153,    67,   168,    68,   189,
     192,    69,    70,    71,   193,    72,    73,    74,    75,    76,
      77,    78,   194,   195,    79,   170,   197,    80,    81,    82,
      83,    84,   198,   204,   206,   202,    85,   205,   208,   209,
      67,    86,    68,   210,   211,   219,    87,   217,   227,    57,
     132,    74,    75,   223,    77,    78,   220,   230,   231,   234,
     239,   116,    81,    82,    83,    84,   240,   241,   242,    22,
      85,    67,   109,    68,   236,    86,   134,   165,   225,   245,
      87,  -119,    74,    75,   155,    77,    78,     2,     3,     4,
       5,     0,   116,    81,    82,    83,    84,   143,   144,   157,
     221,    85,     2,     3,     4,     5,    86,   161,     0,     0,
       0,    87,  -119,   149,   150,   151,     0,   152,   153,     0,
       8,     0,    67,     0,    68,     0,     0,     0,     0,     0,
     137,   138,     0,    74,    75,     8,    77,    78,     0,     0,
     -25,     0,     0,   116,    81,    82,    83,    84,     0,     0,
     136,     0,    85,   143,   144,   -25,     0,    86,   137,   138,
     139,   140,    87,   141,   142,   145,   146,   147,   148,   149,
     150,   151,     0,   152,   153,     0,     0,     0,     0,     0,
       0,   143,   144,   137,   138,   139,   140,     0,   141,   142,
       0,     0,     0,   145,   146,   147,   148,   149,   150,   151,
       0,   152,   153,     0,   -52,     0,   143,   144,     0,     0,
     137,   138,   139,   140,     0,   141,   142,     0,   145,   146,
     147,   148,   149,   150,   151,     0,   152,   153,     0,     0,
       0,     0,   200,   143,   144,     0,   137,   138,   139,   140,
       0,   141,   142,     0,     0,   145,   146,   147,   148,   149,
     150,   151,     0,   152,   153,     0,     0,     0,   173,   143,
     144,     0,   137,   138,   139,   140,     0,   141,   142,     0,
       0,   145,   146,   147,   148,   149,   150,   151,     0,   152,
     153,     0,     0,     0,   196,   143,   144,     0,   137,   138,
     139,   140,     0,   141,   142,     0,     0,   145,   146,   147,
     148,   149,   150,   151,     0,   152,   153,     0,     0,     0,
     199,   143,   144,     0,   137,   138,   139,   140,     0,   141,
     142,     0,     0,   145,   146,   147,   148,   149,   150,   151,
       0,   152,   153,     0,     0,     0,   203,   143,   144,   137,
     138,   139,   140,     0,   141,   142,     0,     0,     0,   145,
     146,   147,   148,   149,   150,   151,     0,   152,   153,     0,
     222,     0,   143,   144,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   145,   146,   147,   148,   149,   150,
     151,     0,   152,   153,   207,    67,     0,    68,     0,     0,
      69,    70,    71,     0,    72,    73,    74,    75,    76,    77,
      78,     0,     0,    79,     0,     0,   116,    81,    82,    83,
      84,     0,     0,     0,     0,    85,     0,     0,     0,     0,
      86,     0,     0,     0,     0,    87,     0,     0,    57,   130,
      67,     0,    68,     0,     0,    69,    70,    71,     0,    72,
      73,    74,    75,    76,    77,    78,     0,     0,    79,     0,
       0,   116,    81,    82,    83,    84,     0,     0,     0,     0,
      85,     0,     0,     0,     0,    86,     0,     0,     0,     0,
      87,     0,     0,    57,   174,    67,     0,    68,     0,     0,
      69,    70,    71,     0,    72,    73,    74,    75,    76,    77,
      78,     0,     0,    79,     0,     0,   116,    81,    82,    83,
      84,   137,   138,   139,   140,    85,   141,   142,     0,     0,
      86,   137,   138,   139,   140,    87,   141,     0,    57,   -80,
       0,     0,     0,     0,   143,   144,     0,     0,     0,     0,
       0,     0,     0,     0,   143,   144,   145,   146,   147,   148,
     149,   150,   151,     0,   152,   153,   145,   146,   147,   148,
     149,   150,   151,     0,   152,   153,   137,   138,   139,   140,
       0,     0,     0,     0,     0,     0,   137,   138,     0,   140,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   143,
     144,     0,     0,     0,     0,     0,     0,     0,     0,   143,
     144,   145,   146,   147,   148,   149,   150,   151,     0,   152,
     153,   145,   146,   147,   148,   149,   150,   151,     0,   152,
     153,   137,   138,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   143,   144,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   143,   144,   147,   148,   149,   150,
     151,     0,   152,   153,     0,     0,     0,   146,   147,   148,
     149,   150,   151,     0,   152,   153,    67,     0,    68,     0,
       0,    69,    70,    71,     0,    72,    73,    74,    75,    76,
      77,    78,     0,     0,    79,     0,     0,   116,    81,    82,
      83,    84,     0,     0,     0,     0,    85,     0,     0,     0,
       0,    86,     0,     0,     0,   -53,    87,     0,    67,    57,
      68,     0,     0,    69,    70,    71,     0,    72,    73,    74,
      75,    76,    77,    78,   138,     0,    79,     0,     0,   116,
      81,    82,    83,    84,   138,     0,     0,     0,    85,     0,
       0,     0,     0,    86,     0,     0,   143,   144,    87,     0,
       0,    57,     0,     0,     0,     0,   143,   144,     0,   146,
     147,   148,   149,   150,   151,     0,   152,   153,     0,     0,
     147,   148,   149,   150,   151,     0,   152,   153,    67,     0,
      68,     0,     0,     0,     0,     0,     0,     0,     0,    74,
      75,     0,    77,    78,     0,     0,     0,     0,     0,   116,
      81,    82,    83,    84,   143,   144,     0,     0,    85,     0,
       0,     0,     0,    86,     0,     0,     0,     0,    87,   148,
     149,   150,   151,     0,   152,   153
};

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-90)))

#define yytable_value_is_error(Yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
       0,    90,    72,    13,     1,    44,    27,    72,    47,    57,
      10,    32,    13,    32,    62,    37,    55,    56,    13,    37,
      85,    86,    87,     1,    37,    46,     4,     5,     6,     7,
       3,     4,     5,     6,     7,     0,    37,     4,     5,     6,
       7,    41,    37,    91,   114,   134,    17,    57,   113,   114,
     115,    57,    58,    56,    13,    56,   121,   122,    55,    37,
     125,   126,    62,    59,    37,     3,     4,     5,     6,     7,
      37,    13,   137,   138,   139,   140,   141,   142,    37,    57,
     145,   146,   147,   148,   149,   150,   151,    60,   153,   154,
     111,   112,   111,   112,    55,    37,    56,     1,    37,    37,
       4,     5,     6,     7,    20,    32,    33,   196,    57,   198,
     199,     3,     4,     5,     6,     7,     8,    58,    32,    33,
      35,    36,    60,    50,    57,    52,    53,    19,    37,    59,
      59,    57,   197,    37,   223,    49,    50,   202,    52,    53,
      57,   206,    37,    37,    56,    37,     4,     5,     6,     7,
     239,    58,   222,    57,    56,   244,   245,   222,    16,    56,
      18,    37,    55,    21,    22,    23,    56,    25,    26,    27,
      28,    29,    30,    31,    56,    56,    34,    56,    56,    37,
      38,    39,    40,    41,    32,    33,    56,    56,    46,    55,
      43,    56,    55,    51,     4,     5,     6,     7,    56,    55,
     200,    59,    60,    57,    52,    53,    16,    57,    18,    37,
      57,    21,    22,    23,    57,    25,    26,    27,    28,    29,
      30,    31,    57,    57,    34,     1,    55,    37,    38,    39,
      40,    41,    57,    57,    56,    58,    46,    57,    55,    55,
      16,    51,    18,    55,    55,    59,    56,    55,    35,    59,
      60,    27,    28,    24,    30,    31,     1,    57,    57,    39,
      57,    37,    38,    39,    40,    41,    61,    61,    60,    10,
      46,    16,    62,    18,   229,    51,    91,   122,   215,   241,
      56,    57,    27,    28,     1,    30,    31,     4,     5,     6,
       7,    -1,    37,    38,    39,    40,    41,    32,    33,     1,
     206,    46,     4,     5,     6,     7,    51,     1,    -1,    -1,
      -1,    56,    57,    48,    49,    50,    -1,    52,    53,    -1,
      37,    -1,    16,    -1,    18,    -1,    -1,    -1,    -1,    -1,
       9,    10,    -1,    27,    28,    37,    30,    31,    -1,    -1,
      57,    -1,    -1,    37,    38,    39,    40,    41,    -1,    -1,
       1,    -1,    46,    32,    33,    57,    -1,    51,     9,    10,
      11,    12,    56,    14,    15,    44,    45,    46,    47,    48,
      49,    50,    -1,    52,    53,    -1,    -1,    -1,    -1,    -1,
      -1,    32,    33,     9,    10,    11,    12,    -1,    14,    15,
      -1,    -1,    -1,    44,    45,    46,    47,    48,    49,    50,
      -1,    52,    53,    -1,    55,    -1,    32,    33,    -1,    -1,
       9,    10,    11,    12,    -1,    14,    15,    -1,    44,    45,
      46,    47,    48,    49,    50,    -1,    52,    53,    -1,    -1,
      -1,    -1,    58,    32,    33,    -1,     9,    10,    11,    12,
      -1,    14,    15,    -1,    -1,    44,    45,    46,    47,    48,
      49,    50,    -1,    52,    53,    -1,    -1,    -1,    57,    32,
      33,    -1,     9,    10,    11,    12,    -1,    14,    15,    -1,
      -1,    44,    45,    46,    47,    48,    49,    50,    -1,    52,
      53,    -1,    -1,    -1,    57,    32,    33,    -1,     9,    10,
      11,    12,    -1,    14,    15,    -1,    -1,    44,    45,    46,
      47,    48,    49,    50,    -1,    52,    53,    -1,    -1,    -1,
      57,    32,    33,    -1,     9,    10,    11,    12,    -1,    14,
      15,    -1,    -1,    44,    45,    46,    47,    48,    49,    50,
      -1,    52,    53,    -1,    -1,    -1,    57,    32,    33,     9,
      10,    11,    12,    -1,    14,    15,    -1,    -1,    -1,    44,
      45,    46,    47,    48,    49,    50,    -1,    52,    53,    -1,
      55,    -1,    32,    33,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    44,    45,    46,    47,    48,    49,
      50,    -1,    52,    53,    54,    16,    -1,    18,    -1,    -1,
      21,    22,    23,    -1,    25,    26,    27,    28,    29,    30,
      31,    -1,    -1,    34,    -1,    -1,    37,    38,    39,    40,
      41,    -1,    -1,    -1,    -1,    46,    -1,    -1,    -1,    -1,
      51,    -1,    -1,    -1,    -1,    56,    -1,    -1,    59,    60,
      16,    -1,    18,    -1,    -1,    21,    22,    23,    -1,    25,
      26,    27,    28,    29,    30,    31,    -1,    -1,    34,    -1,
      -1,    37,    38,    39,    40,    41,    -1,    -1,    -1,    -1,
      46,    -1,    -1,    -1,    -1,    51,    -1,    -1,    -1,    -1,
      56,    -1,    -1,    59,    60,    16,    -1,    18,    -1,    -1,
      21,    22,    23,    -1,    25,    26,    27,    28,    29,    30,
      31,    -1,    -1,    34,    -1,    -1,    37,    38,    39,    40,
      41,     9,    10,    11,    12,    46,    14,    15,    -1,    -1,
      51,     9,    10,    11,    12,    56,    14,    -1,    59,    60,
      -1,    -1,    -1,    -1,    32,    33,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    32,    33,    44,    45,    46,    47,
      48,    49,    50,    -1,    52,    53,    44,    45,    46,    47,
      48,    49,    50,    -1,    52,    53,     9,    10,    11,    12,
      -1,    -1,    -1,    -1,    -1,    -1,     9,    10,    -1,    12,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    32,
      33,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    32,
      33,    44,    45,    46,    47,    48,    49,    50,    -1,    52,
      53,    44,    45,    46,    47,    48,    49,    50,    -1,    52,
      53,     9,    10,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    32,    33,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    32,    33,    46,    47,    48,    49,
      50,    -1,    52,    53,    -1,    -1,    -1,    45,    46,    47,
      48,    49,    50,    -1,    52,    53,    16,    -1,    18,    -1,
      -1,    21,    22,    23,    -1,    25,    26,    27,    28,    29,
      30,    31,    -1,    -1,    34,    -1,    -1,    37,    38,    39,
      40,    41,    -1,    -1,    -1,    -1,    46,    -1,    -1,    -1,
      -1,    51,    -1,    -1,    -1,    55,    56,    -1,    16,    59,
      18,    -1,    -1,    21,    22,    23,    -1,    25,    26,    27,
      28,    29,    30,    31,    10,    -1,    34,    -1,    -1,    37,
      38,    39,    40,    41,    10,    -1,    -1,    -1,    46,    -1,
      -1,    -1,    -1,    51,    -1,    -1,    32,    33,    56,    -1,
      -1,    59,    -1,    -1,    -1,    -1,    32,    33,    -1,    45,
      46,    47,    48,    49,    50,    -1,    52,    53,    -1,    -1,
      46,    47,    48,    49,    50,    -1,    52,    53,    16,    -1,
      18,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    27,
      28,    -1,    30,    31,    -1,    -1,    -1,    -1,    -1,    37,
      38,    39,    40,    41,    32,    33,    -1,    -1,    46,    -1,
      -1,    -1,    -1,    51,    -1,    -1,    -1,    -1,    56,    47,
      48,    49,    50,    -1,    52,    53
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     5,     6,     7,     8,    19,    37,    63,
      64,    65,    66,    67,    68,    69,    76,    79,    37,    37,
      37,     0,    65,     1,    55,    13,    37,    56,    17,    73,
      59,    55,    56,     1,    67,    68,    70,    71,    37,    20,
      74,    78,     1,    71,    57,    37,    58,    57,    37,    72,
      59,     3,    60,    68,    80,    57,    57,    59,    83,    67,
      83,    58,    75,    37,    37,    83,    83,    16,    18,    21,
      22,    23,    25,    26,    27,    28,    29,    30,    31,    34,
      37,    38,    39,    40,    41,    46,    51,    56,    60,    66,
      81,    82,    83,    84,    85,    87,    88,    89,    90,    91,
      93,    99,   100,   101,   102,   104,    37,    60,    66,    69,
      77,    56,    56,    56,    56,    56,    37,    84,   100,    55,
      37,    56,    56,    56,    56,    56,    56,   100,   100,   100,
      60,    85,    60,    66,    81,    55,     1,     9,    10,    11,
      12,    14,    15,    32,    33,    44,    45,    46,    47,    48,
      49,    50,    52,    53,    43,     1,    71,     1,    71,   100,
      84,     1,   100,    55,   100,    92,   100,    57,    57,   100,
       1,    92,   103,    57,    60,    55,   100,   100,   100,   100,
     100,   100,   100,   100,   100,   100,   100,   100,   100,    37,
     100,   100,    57,    57,    57,    57,    57,    55,    57,    57,
      58,    57,    58,    57,    57,    57,    56,    54,    55,    55,
      55,    55,    85,   100,    85,    85,    68,    55,   100,    59,
       1,   103,    55,    24,    86,    86,    57,    35,    95,    96,
      57,    57,    84,    85,    39,    36,    95,    97,    98,    57,
      61,    61,    60,    85,    94,    94,    85
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256

/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (YYID (N))                                                     \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (YYID (0))
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])



/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value, Location); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
#endif
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
  YYUSE (yylocationp);
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep, yylocationp)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yylsp, yyrule)
    YYSTYPE *yyvsp;
    YYLTYPE *yylsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       , &(yylsp[(yyi + 1) - (yynrhs)])		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, yylsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
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
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULL, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  YYSIZE_T yysize1;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULL;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                yysize1 = yysize + yytnamerr (YY_NULL, yytname[yyx]);
                if (! (yysize <= yysize1
                       && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                  return 2;
                yysize = yysize1;
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  yysize1 = yysize + yystrlen (yyformat);
  if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
    return 2;
  yysize = yysize1;

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
#else
static void
yydestruct (yymsg, yytype, yyvaluep, yylocationp)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
    YYLTYPE *yylocationp;
#endif
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}




/* The lookahead symbol.  */
int yychar;


#ifndef YYLVAL_INITIALIZE
# define YYLVAL_INITIALIZE()
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Location data for the lookahead symbol.  */
YYLTYPE yylloc;

/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.
       `yyls': related to locations.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[3];

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyss = yyssa;
  yyvs = yyvsa;
  yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;
  yylsp = yyls;

  YYLVAL_INITIALIZE ();
#if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  /* Initialize the default location before parsing starts.  */
  yylloc.first_line   = yylloc.last_line   = 1;
  yylloc.first_column = yylloc.last_column = 1;
#endif
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;
	YYLTYPE *yyls1 = yyls;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yyls1, yysize * sizeof (*yylsp),
		    &yystacksize);

	yyls = yyls1;
	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
	YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location.  */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
/* Line 1813 of yacc.c  */
#line 193 "parser.y"
    {
                                      (yylsp[(1) - (1)]);
                                      Program *program = new Program((yyvsp[(1) - (1)].declList));
                                      // if no errors, advance to next phase
                                      if (ReportError::NumErrors() == 0)
                                          program->Check();

                                      /* Below is the Assignment 2
                                         call (which you can uncomment
                                         to verify the AST) */
                                      // if (ReportError::NumErrors() == 0)
                                      //     program->Print(0);
                                    }
    break;

  case 3:
/* Line 1813 of yacc.c  */
#line 208 "parser.y"
    { ((yyval.declList)=(yyvsp[(1) - (2)].declList))->Append((yyvsp[(2) - (2)].decl)); }
    break;

  case 4:
/* Line 1813 of yacc.c  */
#line 209 "parser.y"
    { ((yyval.declList) = new List<Decl*>)->Append((yyvsp[(1) - (1)].decl)); }
    break;

  case 5:
/* Line 1813 of yacc.c  */
#line 212 "parser.y"
    { (yyval.decl) = (yyvsp[(1) - (1)].varDecl); }
    break;

  case 6:
/* Line 1813 of yacc.c  */
#line 213 "parser.y"
    { (yyval.decl) = (yyvsp[(1) - (1)].fnDecl); }
    break;

  case 7:
/* Line 1813 of yacc.c  */
#line 214 "parser.y"
    { (yyval.decl) = (yyvsp[(1) - (1)].classDecl); }
    break;

  case 8:
/* Line 1813 of yacc.c  */
#line 215 "parser.y"
    { (yyval.decl) = (yyvsp[(1) - (1)].interfaceDecl); }
    break;

  case 9:
/* Line 1813 of yacc.c  */
#line 218 "parser.y"
    { (yyval.varDecl) = (yyvsp[(1) - (2)].var); }
    break;

  case 10:
/* Line 1813 of yacc.c  */
#line 219 "parser.y"
    { (yyval.varDecl) = new VarDeclError(); }
    break;

  case 11:
/* Line 1813 of yacc.c  */
#line 222 "parser.y"
    { Identifier *id = new Identifier((yylsp[(2) - (2)]), (yyvsp[(2) - (2)].identifier));
                                      (yyval.var) = new VarDecl(id, (yyvsp[(1) - (2)].type));
                                    }
    break;

  case 12:
/* Line 1813 of yacc.c  */
#line 227 "parser.y"
    { (yyval.type) = new Type(*Type::intType); }
    break;

  case 13:
/* Line 1813 of yacc.c  */
#line 228 "parser.y"
    { (yyval.type) = new Type(*Type::doubleType); }
    break;

  case 14:
/* Line 1813 of yacc.c  */
#line 229 "parser.y"
    { (yyval.type) = new Type(*Type::boolType); }
    break;

  case 15:
/* Line 1813 of yacc.c  */
#line 230 "parser.y"
    { (yyval.type) = new Type(*Type::stringType); }
    break;

  case 16:
/* Line 1813 of yacc.c  */
#line 231 "parser.y"
    { Identifier *id = new Identifier((yylsp[(1) - (1)]), (yyvsp[(1) - (1)].identifier));
                                      (yyval.type) = new NamedType(id); }
    break;

  case 17:
/* Line 1813 of yacc.c  */
#line 233 "parser.y"
    { (yyval.type) = new ArrayType((yylsp[(1) - (2)]), (yyvsp[(1) - (2)].type)); }
    break;

  case 18:
/* Line 1813 of yacc.c  */
#line 236 "parser.y"
    {
                                      Identifier *id = new Identifier((yylsp[(2) - (6)]), (yyvsp[(2) - (6)].identifier));
                                      (yyval.fnDecl) = new FnDecl(id, (yyvsp[(1) - (6)].type), (yyvsp[(4) - (6)].varList));
                                      (yyval.fnDecl)->SetFunctionBody((yyvsp[(6) - (6)].stmtBlock));
                                    }
    break;

  case 19:
/* Line 1813 of yacc.c  */
#line 241 "parser.y"
    {
                                      (yyval.fnDecl) = new FormalsError();
                                    }
    break;

  case 20:
/* Line 1813 of yacc.c  */
#line 244 "parser.y"
    {
                                      Identifier *id = new Identifier((yylsp[(2) - (6)]), (yyvsp[(2) - (6)].identifier));
                                      Type *tp = new Type(*Type::voidType);
                                      (yyval.fnDecl) = new FnDecl(id, tp, (yyvsp[(4) - (6)].varList));
                                      (yyval.fnDecl)->SetFunctionBody((yyvsp[(6) - (6)].stmtBlock));
                                    }
    break;

  case 21:
/* Line 1813 of yacc.c  */
#line 250 "parser.y"
    {
                                      (yyval.fnDecl) = new FormalsError();
                                    }
    break;

  case 22:
/* Line 1813 of yacc.c  */
#line 255 "parser.y"
    { ((yyval.varList)=(yyvsp[(1) - (3)].varList))->Append((yyvsp[(3) - (3)].var)); }
    break;

  case 23:
/* Line 1813 of yacc.c  */
#line 256 "parser.y"
    { ((yyval.varList) = new List<VarDecl*>)->Append((yyvsp[(1) - (1)].var)); }
    break;

  case 24:
/* Line 1813 of yacc.c  */
#line 259 "parser.y"
    { (yyval.varList) = (yyvsp[(1) - (1)].varList); }
    break;

  case 25:
/* Line 1813 of yacc.c  */
#line 260 "parser.y"
    { (yyval.varList) = new List<VarDecl*>; }
    break;

  case 26:
/* Line 1813 of yacc.c  */
#line 263 "parser.y"
    {
                                      Identifier *id = new Identifier((yylsp[(3) - (3)]), (yyvsp[(3) - (3)].identifier));
                                      ((yyval.identifierList)=(yyvsp[(1) - (3)].identifierList))->Append(id);
                                    }
    break;

  case 27:
/* Line 1813 of yacc.c  */
#line 267 "parser.y"
    { Identifier *id = new Identifier((yylsp[(1) - (1)]), (yyvsp[(1) - (1)].identifier));
                                      ((yyval.identifierList) = new List<Identifier*>)->Append(id);
                                    }
    break;

  case 28:
/* Line 1813 of yacc.c  */
#line 272 "parser.y"
    {
                                      Identifier *id = new Identifier((yylsp[(2) - (2)]), (yyvsp[(2) - (2)].identifier));
                                      (yyval.namedType) = new NamedType(id);
                                    }
    break;

  case 29:
/* Line 1813 of yacc.c  */
#line 276 "parser.y"
    { (yyval.namedType) = NULL; }
    break;

  case 30:
/* Line 1813 of yacc.c  */
#line 279 "parser.y"
    {
                                      (yyval.namedTypeList) = new List<NamedType*>;
                                      for (int i = 0; i < (yyvsp[(2) - (2)].identifierList)->NumElements(); i++ )
                                        (yyval.namedTypeList)->Append(new NamedType((yyvsp[(2) - (2)].identifierList)->Nth(i)));
                                    }
    break;

  case 31:
/* Line 1813 of yacc.c  */
#line 284 "parser.y"
    { (yyval.namedTypeList) = new List<NamedType*>; }
    break;

  case 32:
/* Line 1813 of yacc.c  */
#line 287 "parser.y"
    { ((yyval.declList) = (yyvsp[(1) - (2)].declList))->Append((yyvsp[(2) - (2)].decl)); }
    break;

  case 33:
/* Line 1813 of yacc.c  */
#line 288 "parser.y"
    { (yyval.declList) = new List<Decl*>; }
    break;

  case 34:
/* Line 1813 of yacc.c  */
#line 292 "parser.y"
    {
                                      Identifier *id = new Identifier((yylsp[(2) - (7)]), (yyvsp[(2) - (7)].identifier));
                                      (yyval.classDecl) = new ClassDecl(id, (yyvsp[(3) - (7)].namedType), (yyvsp[(4) - (7)].namedTypeList), (yyvsp[(6) - (7)].declList));
                                    }
    break;

  case 35:
/* Line 1813 of yacc.c  */
#line 298 "parser.y"
    { (yyval.decl) = (yyvsp[(1) - (1)].varDecl); }
    break;

  case 36:
/* Line 1813 of yacc.c  */
#line 299 "parser.y"
    { (yyval.decl) = (yyvsp[(1) - (1)].fnDecl); }
    break;

  case 37:
/* Line 1813 of yacc.c  */
#line 302 "parser.y"
    { ((yyval.declList) = (yyvsp[(1) - (2)].declList))->Append((yyvsp[(2) - (2)].decl)); }
    break;

  case 38:
/* Line 1813 of yacc.c  */
#line 303 "parser.y"
    { (yyval.declList) = new List<Decl*>; }
    break;

  case 39:
/* Line 1813 of yacc.c  */
#line 306 "parser.y"
    {
                                      Identifier *id = new Identifier((yylsp[(2) - (5)]), (yyvsp[(2) - (5)].identifier));
                                      (yyval.interfaceDecl)  = new InterfaceDecl(id, (yyvsp[(4) - (5)].declList));
                                    }
    break;

  case 40:
/* Line 1813 of yacc.c  */
#line 312 "parser.y"
    {
                                      Identifier *id = new Identifier((yylsp[(2) - (6)]), (yyvsp[(2) - (6)].identifier));
                                      (yyval.decl) = new FnDecl(id, (yyvsp[(1) - (6)].type), (yyvsp[(4) - (6)].varList));
                                    }
    break;

  case 41:
/* Line 1813 of yacc.c  */
#line 316 "parser.y"
    {
                                      (yyval.decl) = new FormalsError();
                                    }
    break;

  case 42:
/* Line 1813 of yacc.c  */
#line 319 "parser.y"
    {
                                      Identifier *id = new Identifier((yylsp[(2) - (6)]), (yyvsp[(2) - (6)].identifier));
                                      Type *tp = new Type(*Type::voidType);
                                      (yyval.decl) = new FnDecl(id, tp, (yyvsp[(4) - (6)].varList));
                                    }
    break;

  case 43:
/* Line 1813 of yacc.c  */
#line 324 "parser.y"
    {
                                      (yyval.decl) = new FormalsError();
                                    }
    break;

  case 44:
/* Line 1813 of yacc.c  */
#line 329 "parser.y"
    { ((yyval.stmtList) = (yyvsp[(1) - (2)].stmtList))->Append((yyvsp[(2) - (2)].stmt)); }
    break;

  case 45:
/* Line 1813 of yacc.c  */
#line 330 "parser.y"
    { ((yyval.stmtList) = new List<Stmt*>)->Append((yyvsp[(1) - (1)].stmt)); }
    break;

  case 46:
/* Line 1813 of yacc.c  */
#line 333 "parser.y"
    { ((yyval.varList) = (yyvsp[(1) - (2)].varList))->Append((yyvsp[(2) - (2)].varDecl)); }
    break;

  case 47:
/* Line 1813 of yacc.c  */
#line 334 "parser.y"
    { ((yyval.varList) = new List<VarDecl*>)->Append((yyvsp[(1) - (1)].varDecl)); }
    break;

  case 48:
/* Line 1813 of yacc.c  */
#line 337 "parser.y"
    { (yyval.stmtBlock) = new StmtBlock((yyvsp[(2) - (4)].varList), (yyvsp[(3) - (4)].stmtList)); }
    break;

  case 49:
/* Line 1813 of yacc.c  */
#line 338 "parser.y"
    { List<Stmt*> *s = new List<Stmt*>;
                                        (yyval.stmtBlock) = new StmtBlock((yyvsp[(2) - (3)].varList), s);
                                      }
    break;

  case 50:
/* Line 1813 of yacc.c  */
#line 341 "parser.y"
    { List<VarDecl*> *d = new List<VarDecl*>;
                                       (yyval.stmtBlock) = new StmtBlock(d, (yyvsp[(2) - (3)].stmtList));
                                      }
    break;

  case 51:
/* Line 1813 of yacc.c  */
#line 344 "parser.y"
    { List<VarDecl*> *d = new List<VarDecl*>;
                                        List<Stmt*> *s = new List<Stmt*>;
                                       (yyval.stmtBlock) = new StmtBlock(d, s);
                                      }
    break;

  case 52:
/* Line 1813 of yacc.c  */
#line 350 "parser.y"
    { (yyval.expr) = (yyvsp[(1) - (1)].expr); }
    break;

  case 53:
/* Line 1813 of yacc.c  */
#line 351 "parser.y"
    { (yyval.expr) = new EmptyExpr; }
    break;

  case 54:
/* Line 1813 of yacc.c  */
#line 354 "parser.y"
    { (yyval.stmt) = (yyvsp[(1) - (2)].expr); }
    break;

  case 55:
/* Line 1813 of yacc.c  */
#line 355 "parser.y"
    { (yyval.stmt) = new ExprError(); }
    break;

  case 56:
/* Line 1813 of yacc.c  */
#line 356 "parser.y"
    { (yyval.stmt) = (yyvsp[(1) - (1)].ifStmt); }
    break;

  case 57:
/* Line 1813 of yacc.c  */
#line 357 "parser.y"
    { (yyval.stmt) = (yyvsp[(1) - (1)].whileStmt); }
    break;

  case 58:
/* Line 1813 of yacc.c  */
#line 358 "parser.y"
    { (yyval.stmt) = (yyvsp[(1) - (1)].forStmt); }
    break;

  case 59:
/* Line 1813 of yacc.c  */
#line 359 "parser.y"
    { (yyval.stmt) = (yyvsp[(1) - (1)].breakStmt); }
    break;

  case 60:
/* Line 1813 of yacc.c  */
#line 360 "parser.y"
    { (yyval.stmt) = (yyvsp[(1) - (1)].returnStmt); }
    break;

  case 61:
/* Line 1813 of yacc.c  */
#line 361 "parser.y"
    { (yyval.stmt) = (yyvsp[(1) - (1)].printStmt); }
    break;

  case 62:
/* Line 1813 of yacc.c  */
#line 362 "parser.y"
    { (yyval.stmt) = (yyvsp[(1) - (1)].switchStmt); }
    break;

  case 63:
/* Line 1813 of yacc.c  */
#line 363 "parser.y"
    { (yyval.stmt) = (yyvsp[(1) - (1)].stmtBlock); }
    break;

  case 64:
/* Line 1813 of yacc.c  */
#line 366 "parser.y"
    { (yyval.stmt) = (yyvsp[(2) - (2)].stmt); }
    break;

  case 65:
/* Line 1813 of yacc.c  */
#line 367 "parser.y"
    { (yyval.stmt) = NULL; }
    break;

  case 66:
/* Line 1813 of yacc.c  */
#line 370 "parser.y"
    { (yyval.ifStmt) = new IfStmt((yyvsp[(3) - (6)].expr), (yyvsp[(5) - (6)].stmt), (yyvsp[(6) - (6)].stmt)); }
    break;

  case 67:
/* Line 1813 of yacc.c  */
#line 371 "parser.y"
    { (yyval.ifStmt) = new IfStmtExprError(); }
    break;

  case 68:
/* Line 1813 of yacc.c  */
#line 374 "parser.y"
    { (yyval.whileStmt) = new WhileStmt((yyvsp[(3) - (5)].expr), (yyvsp[(5) - (5)].stmt)); }
    break;

  case 69:
/* Line 1813 of yacc.c  */
#line 377 "parser.y"
    {
                                      (yyval.forStmt) = new ForStmt((yyvsp[(3) - (9)].expr), (yyvsp[(5) - (9)].expr), (yyvsp[(7) - (9)].expr), (yyvsp[(9) - (9)].stmt));
                                    }
    break;

  case 70:
/* Line 1813 of yacc.c  */
#line 382 "parser.y"
    { (yyval.returnStmt) = new ReturnStmt((yylsp[(1) - (3)]), (yyvsp[(2) - (3)].expr)); }
    break;

  case 71:
/* Line 1813 of yacc.c  */
#line 385 "parser.y"
    { (yyval.breakStmt) = new BreakStmt((yylsp[(1) - (2)])); }
    break;

  case 72:
/* Line 1813 of yacc.c  */
#line 388 "parser.y"
    { ((yyval.exprList) = (yyvsp[(1) - (3)].exprList))->Append((yyvsp[(3) - (3)].expr)); }
    break;

  case 73:
/* Line 1813 of yacc.c  */
#line 389 "parser.y"
    { ((yyval.exprList) = new List<Expr*>)->Append((yyvsp[(1) - (1)].expr)); }
    break;

  case 74:
/* Line 1813 of yacc.c  */
#line 392 "parser.y"
    { (yyval.printStmt) = new PrintStmt((yyvsp[(3) - (5)].exprList)); }
    break;

  case 75:
/* Line 1813 of yacc.c  */
#line 395 "parser.y"
    { ((yyval.stmtList) = (yyvsp[(1) - (2)].stmtList))->Append((yyvsp[(2) - (2)].stmt)); }
    break;

  case 76:
/* Line 1813 of yacc.c  */
#line 396 "parser.y"
    { (yyval.stmtList) = new List<Stmt*>; }
    break;

  case 77:
/* Line 1813 of yacc.c  */
#line 399 "parser.y"
    {
                                     IntConstant *i = new IntConstant((yylsp[(2) - (4)]), (yyvsp[(2) - (4)].integerConstant));
                                      (yyval.caseStmt) = new Case(i, (yyvsp[(4) - (4)].stmtList));
                                    }
    break;

  case 78:
/* Line 1813 of yacc.c  */
#line 405 "parser.y"
    { ((yyval.caseList) = (yyvsp[(1) - (2)].caseList))->Append((yyvsp[(2) - (2)].caseStmt)); }
    break;

  case 79:
/* Line 1813 of yacc.c  */
#line 406 "parser.y"
    { ((yyval.caseList) = new List<Case*>)->Append((yyvsp[(1) - (1)].caseStmt)); }
    break;

  case 80:
/* Line 1813 of yacc.c  */
#line 409 "parser.y"
    { (yyval.defaultStmt) = new Default((yyvsp[(3) - (3)].stmtList)); }
    break;

  case 81:
/* Line 1813 of yacc.c  */
#line 412 "parser.y"
    { (yyval.defaultStmt) = (yyvsp[(1) - (1)].defaultStmt); }
    break;

  case 82:
/* Line 1813 of yacc.c  */
#line 413 "parser.y"
    { (yyval.defaultStmt) = NULL; }
    break;

  case 83:
/* Line 1813 of yacc.c  */
#line 416 "parser.y"
    {
                                      (yyval.switchStmt) = new SwitchStmt((yyvsp[(3) - (8)].expr), (yyvsp[(6) - (8)].caseList), (yyvsp[(7) - (8)].defaultStmt));
                                    }
    break;

  case 84:
/* Line 1813 of yacc.c  */
#line 421 "parser.y"
    { Operator *op = new Operator((yylsp[(2) - (3)]), "=");
                                      (yyval.expr) = new AssignExpr((yyvsp[(1) - (3)].lvalue), op, (yyvsp[(3) - (3)].expr));
                                    }
    break;

  case 85:
/* Line 1813 of yacc.c  */
#line 424 "parser.y"
    { (yyval.expr) = (yyvsp[(1) - (1)].expr); }
    break;

  case 86:
/* Line 1813 of yacc.c  */
#line 425 "parser.y"
    { (yyval.expr) = (yyvsp[(1) - (1)].lvalue); }
    break;

  case 87:
/* Line 1813 of yacc.c  */
#line 426 "parser.y"
    { (yyval.expr) = new This((yylsp[(1) - (1)])); }
    break;

  case 88:
/* Line 1813 of yacc.c  */
#line 427 "parser.y"
    { (yyval.expr) = (yyvsp[(1) - (1)].expr); }
    break;

  case 89:
/* Line 1813 of yacc.c  */
#line 428 "parser.y"
    { (yyval.expr) = (yyvsp[(2) - (3)].expr); }
    break;

  case 90:
/* Line 1813 of yacc.c  */
#line 429 "parser.y"
    { Operator *op = new Operator((yylsp[(2) - (3)]), "+");
                                      (yyval.expr) = new ArithmeticExpr((yyvsp[(1) - (3)].expr), op, (yyvsp[(3) - (3)].expr));
                                    }
    break;

  case 91:
/* Line 1813 of yacc.c  */
#line 432 "parser.y"
    { Operator *op = new Operator((yylsp[(2) - (3)]), "-");
                                      (yyval.expr) = new ArithmeticExpr((yyvsp[(1) - (3)].expr), op, (yyvsp[(3) - (3)].expr));
                                    }
    break;

  case 92:
/* Line 1813 of yacc.c  */
#line 435 "parser.y"
    { Operator *op = new Operator((yylsp[(2) - (3)]), "*");
                                      (yyval.expr) = new ArithmeticExpr((yyvsp[(1) - (3)].expr), op, (yyvsp[(3) - (3)].expr));
                                    }
    break;

  case 93:
/* Line 1813 of yacc.c  */
#line 438 "parser.y"
    { Operator *op = new Operator((yylsp[(2) - (3)]), "/");
                                      (yyval.expr) = new ArithmeticExpr((yyvsp[(1) - (3)].expr), op, (yyvsp[(3) - (3)].expr));
                                    }
    break;

  case 94:
/* Line 1813 of yacc.c  */
#line 441 "parser.y"
    { Operator *op = new Operator((yylsp[(2) - (3)]), "%");
                                      (yyval.expr) = new ArithmeticExpr((yyvsp[(1) - (3)].expr), op, (yyvsp[(3) - (3)].expr));
                                    }
    break;

  case 95:
/* Line 1813 of yacc.c  */
#line 444 "parser.y"
    { Operator *op = new Operator((yylsp[(1) - (2)]), "-");
                                      (yyval.expr) = new ArithmeticExpr(op, (yyvsp[(2) - (2)].expr));
                                    }
    break;

  case 96:
/* Line 1813 of yacc.c  */
#line 447 "parser.y"
    { Operator *op = new Operator((yylsp[(2) - (3)]), "<");
                                      (yyval.expr) = new RelationalExpr((yyvsp[(1) - (3)].expr), op, (yyvsp[(3) - (3)].expr));
                                    }
    break;

  case 97:
/* Line 1813 of yacc.c  */
#line 450 "parser.y"
    {
                                      Operator *op = new Operator((yylsp[(2) - (3)]), "<=");
                                      (yyval.expr) = new RelationalExpr((yyvsp[(1) - (3)].expr), op, (yyvsp[(3) - (3)].expr));
                                    }
    break;

  case 98:
/* Line 1813 of yacc.c  */
#line 454 "parser.y"
    { Operator *op = new Operator((yylsp[(2) - (3)]), ">");
                                      (yyval.expr) = new RelationalExpr((yyvsp[(1) - (3)].expr), op, (yyvsp[(3) - (3)].expr));
                                    }
    break;

  case 99:
/* Line 1813 of yacc.c  */
#line 457 "parser.y"
    {
                                      Operator *op = new Operator((yylsp[(2) - (3)]), ">=");
                                      (yyval.expr) = new RelationalExpr((yyvsp[(1) - (3)].expr), op, (yyvsp[(3) - (3)].expr));
                                    }
    break;

  case 100:
/* Line 1813 of yacc.c  */
#line 461 "parser.y"
    { Operator *op = new Operator((yylsp[(2) - (3)]), "==");
                                      (yyval.expr) = new EqualityExpr((yyvsp[(1) - (3)].expr), op, (yyvsp[(3) - (3)].expr));
                                    }
    break;

  case 101:
/* Line 1813 of yacc.c  */
#line 464 "parser.y"
    { Operator *op = new Operator((yylsp[(2) - (3)]), "!=");
                                      (yyval.expr) = new EqualityExpr((yyvsp[(1) - (3)].expr), op, (yyvsp[(3) - (3)].expr));
                                    }
    break;

  case 102:
/* Line 1813 of yacc.c  */
#line 467 "parser.y"
    { Operator *op = new Operator((yylsp[(2) - (3)]), "&&");
                                      (yyval.expr) = new LogicalExpr((yyvsp[(1) - (3)].expr), op, (yyvsp[(3) - (3)].expr));
                                    }
    break;

  case 103:
/* Line 1813 of yacc.c  */
#line 470 "parser.y"
    { Operator *op = new Operator((yylsp[(2) - (3)]), "||");
                                      (yyval.expr) = new LogicalExpr((yyvsp[(1) - (3)].expr), op, (yyvsp[(3) - (3)].expr));
                                    }
    break;

  case 104:
/* Line 1813 of yacc.c  */
#line 473 "parser.y"
    { Operator *op = new Operator((yylsp[(1) - (2)]), "!");
                                      (yyval.expr) = new LogicalExpr(op, (yyvsp[(2) - (2)].expr));
                                    }
    break;

  case 105:
/* Line 1813 of yacc.c  */
#line 476 "parser.y"
    { (yyval.expr) = new ReadIntegerExpr((yylsp[(1) - (3)])); }
    break;

  case 106:
/* Line 1813 of yacc.c  */
#line 477 "parser.y"
    { (yyval.expr) = new ReadLineExpr((yylsp[(1) - (3)])); }
    break;

  case 107:
/* Line 1813 of yacc.c  */
#line 478 "parser.y"
    { Identifier *id = new Identifier((yylsp[(2) - (2)]), (yyvsp[(2) - (2)].identifier));
                                      NamedType *nt = new NamedType(id);
                                      (yyval.expr) = new NewExpr((yylsp[(1) - (2)]), nt);
                                    }
    break;

  case 108:
/* Line 1813 of yacc.c  */
#line 482 "parser.y"
    {
                                      (yyval.expr) = new NewArrayExpr((yylsp[(1) - (6)]), (yyvsp[(3) - (6)].expr), (yyvsp[(5) - (6)].type));
                                    }
    break;

  case 109:
/* Line 1813 of yacc.c  */
#line 485 "parser.y"
    { (yyval.expr) = new PostfixExpr((yyvsp[(1) - (2)].expr),new Operator((yylsp[(2) - (2)]),"++")); }
    break;

  case 110:
/* Line 1813 of yacc.c  */
#line 486 "parser.y"
    { (yyval.expr) = new PostfixExpr((yyvsp[(1) - (2)].expr),new Operator((yylsp[(2) - (2)]),"--")); }
    break;

  case 111:
/* Line 1813 of yacc.c  */
#line 489 "parser.y"
    { Identifier *id = new Identifier((yylsp[(1) - (1)]), (yyvsp[(1) - (1)].identifier));
                                      (yyval.lvalue) = new FieldAccess(NULL, id);
                                    }
    break;

  case 112:
/* Line 1813 of yacc.c  */
#line 492 "parser.y"
    {
                                      Identifier *id = new Identifier((yylsp[(3) - (3)]), (yyvsp[(3) - (3)].identifier));
                                      (yyval.lvalue) = new FieldAccess((yyvsp[(1) - (3)].expr), id);
                                    }
    break;

  case 113:
/* Line 1813 of yacc.c  */
#line 496 "parser.y"
    { (yyval.lvalue) = new ArrayAccess((yylsp[(1) - (4)]), (yyvsp[(1) - (4)].expr), (yyvsp[(3) - (4)].expr)); }
    break;

  case 114:
/* Line 1813 of yacc.c  */
#line 499 "parser.y"
    {
                                      Identifier *id = new Identifier((yylsp[(1) - (4)]), (yyvsp[(1) - (4)].identifier));
                                      (yyval.expr) = new Call((yylsp[(1) - (4)]), NULL, id, (yyvsp[(3) - (4)].exprList));
                                    }
    break;

  case 115:
/* Line 1813 of yacc.c  */
#line 503 "parser.y"
    {
                                      (yyval.expr) = new ActualsError();
                                    }
    break;

  case 116:
/* Line 1813 of yacc.c  */
#line 506 "parser.y"
    {
                                      Identifier *id = new Identifier((yylsp[(3) - (6)]), (yyvsp[(3) - (6)].identifier));
                                      (yyval.expr) = new Call((yylsp[(2) - (6)]), (yyvsp[(1) - (6)].expr), id, (yyvsp[(5) - (6)].exprList));
                                    }
    break;

  case 117:
/* Line 1813 of yacc.c  */
#line 510 "parser.y"
    {
                                      (yyval.expr) = new ActualsError();
                                    }
    break;

  case 118:
/* Line 1813 of yacc.c  */
#line 515 "parser.y"
    { (yyval.exprList) = (yyvsp[(1) - (1)].exprList); }
    break;

  case 119:
/* Line 1813 of yacc.c  */
#line 516 "parser.y"
    { (yyval.exprList) = new List<Expr*>; }
    break;

  case 120:
/* Line 1813 of yacc.c  */
#line 519 "parser.y"
    { (yyval.expr) = new IntConstant((yylsp[(1) - (1)]), (yyvsp[(1) - (1)].integerConstant)); }
    break;

  case 121:
/* Line 1813 of yacc.c  */
#line 520 "parser.y"
    { (yyval.expr) = new DoubleConstant((yylsp[(1) - (1)]), (yyvsp[(1) - (1)].doubleConstant)); }
    break;

  case 122:
/* Line 1813 of yacc.c  */
#line 521 "parser.y"
    { (yyval.expr) = new BoolConstant((yylsp[(1) - (1)]), (yyvsp[(1) - (1)].boolConstant)); }
    break;

  case 123:
/* Line 1813 of yacc.c  */
#line 522 "parser.y"
    { (yyval.expr) = new StringConstant((yylsp[(1) - (1)]), (yyvsp[(1) - (1)].stringConstant)); }
    break;

  case 124:
/* Line 1813 of yacc.c  */
#line 523 "parser.y"
    { (yyval.expr) = new NullConstant((yylsp[(1) - (1)])); }
    break;


/* Line 1813 of yacc.c  */
#line 2804 "y.tab.c"
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }

  yyerror_range[1] = yylloc;

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval, &yylloc);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  yyerror_range[1] = yylsp[1-yylen];
  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
  *++yylsp = yyloc;

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
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

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


/* Line 2076 of yacc.c  */
#line 527 "parser.y"


/* The closing %% above marks the end of the Rules section and the beginning
 * of the User Subroutines section. All text from here to the end of the
 * file is copied verbatim to the end of the generated y.tab.c file.
 * This section is where you put definitions of helper functions.
 */

/* Function: InitParser
 * --------------------
 * This function will be called before any calls to yyparse().  It is designed
 * to give you an opportunity to do anything that must be done to initialize
 * the parser (set global variables, configure starting state, etc.). One
 * thing it already does for you is assign the value of the global variable
 * yydebug that controls whether yacc prints debugging information about
 * parser actions (shift/reduce) and contents of state stack during parser.
 * If set to false, no information is printed. Setting it to true will give
 * you a running trail that might be helpful when debugging your parser.
 * Please be sure the variable is set to false when submitting your final
 * version.
 */
void InitParser()
{
   PrintDebug("parser", "Initializing parser");
   yydebug = false;
}
