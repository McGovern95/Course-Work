/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 9 "lab9ast.y" /* yacc.c:339  */
	/* begin specs */

#include <stdio.h>
#include <ctype.h>
#include <malloc.h>
#include <stdlib.h>
#include "symtable.h"
#include "lab9ast.h"
#include "emit.h"


extern int mydebug;
static int level;
extern int lineno;
//offset variables
static int offset=0;
static int goffset=0;
static int maxoffset=0;

static FILE *output;

void yyerror (s)  /* Called by yyparse on error */
     char *s;
{
  printf ("%s on Line number: %d\n", s, lineno);
}



#line 96 "y.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
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
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    ID = 258,
    STRING = 259,
    NUM = 260,
    INT = 261,
    VOID = 262,
    IF = 263,
    ELSE = 264,
    WHILE = 265,
    RETURN = 266,
    READ = 267,
    WRITE = 268,
    LE = 269,
    LT = 270,
    GT = 271,
    GE = 272,
    EQ = 273,
    NE = 274,
    UMINUS = 275
  };
#endif
/* Tokens.  */
#define ID 258
#define STRING 259
#define NUM 260
#define INT 261
#define VOID 262
#define IF 263
#define ELSE 264
#define WHILE 265
#define RETURN 266
#define READ 267
#define WRITE 268
#define LE 269
#define LT 270
#define GT 271
#define GE 272
#define EQ 273
#define NE 274
#define UMINUS 275

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 43 "lab9ast.y" /* yacc.c:355  */

	int value;
	char * string;
	ASTnode *node;  /* so we can build an AST */
  	enum OPERATORS operator;

#line 183 "y.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 200 "y.tab.c" /* yacc.c:358  */

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
#else
typedef signed char yytype_int8;
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
# elif ! defined YYSIZE_T
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

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
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
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
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
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

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
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  9
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   111

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  37
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  36
/* YYNRULES -- Number of rules.  */
#define YYNRULES  72
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  119

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   275

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,    26,    21,     2,
      31,    32,    24,    22,    33,    23,     2,    25,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    28,
       2,    36,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    29,     2,    30,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    34,    20,    35,     2,     2,     2,     2,
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
      15,    16,    17,    18,    19,    27
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    68,    68,    71,    72,    76,    76,    79,    94,   110,
     111,   115,   125,   114,   144,   145,   148,   149,   153,   167,
     182,   182,   195,   196,   200,   201,   207,   208,   209,   210,
     211,   212,   213,   214,   217,   220,   228,   240,   245,   251,
     256,   258,   262,   266,   268,   275,   278,   294,   312,   314,
     329,   330,   331,   332,   333,   334,   337,   339,   356,   356,
     359,   361,   376,   376,   379,   380,   383,   384,   387,   414,
     414,   417,   424
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ID", "STRING", "NUM", "INT", "VOID",
  "IF", "ELSE", "WHILE", "RETURN", "READ", "WRITE", "LE", "LT", "GT", "GE",
  "EQ", "NE", "'|'", "'&'", "'+'", "'-'", "'*'", "'/'", "'%'", "UMINUS",
  "';'", "'['", "']'", "'('", "')'", "','", "'{'", "'}'", "'='", "$accept",
  "P", "DL", "DEC", "VARDEC", "typespec", "FUNDEC", "$@1", "$@2", "params",
  "paramlist", "param", "compoundstmt", "$@3", "localdeclarations",
  "statementlist", "statement", "expressionstmt", "assignmentstmt",
  "selectionstmt", "iterationstmt", "returnstmt", "readstmt", "writestmt",
  "expression", "var", "simpleexpression", "relop", "additiveexpression",
  "addop", "term", "multop", "factor", "call", "args", "arglist", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     124,    38,    43,    45,    42,    47,    37,   275,    59,    91,
      93,    40,    41,    44,   123,   125,    61
};
# endif

#define YYPACT_NINF -79

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-79)))

#define YYTABLE_NINF -15

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int8 yypact[] =
{
      43,   -79,   -79,     6,   -79,    43,   -79,    29,   -79,   -79,
     -79,     0,   -79,    32,   -79,    36,    45,    15,    31,    64,
     -79,   -79,    47,   -79,    40,    50,    43,    44,    49,   -79,
     -79,   -79,   -79,    43,    43,    72,    -1,   -79,    33,    11,
     -79,    48,    53,    10,    75,    13,   -79,    16,   -79,    51,
      -1,   -79,   -79,   -79,   -79,   -79,   -79,   -79,    57,    52,
      41,    42,    46,   -79,   -79,    16,    16,    16,    16,   -79,
      59,   -79,    60,    62,    63,    65,    66,   -79,   -79,   -79,
      17,   -79,   -79,   -79,   -79,   -79,   -79,    16,   -79,   -79,
      16,   -79,   -79,    16,    67,    61,    68,   -79,    69,    70,
     -79,   -79,   -79,   -79,   -79,   -79,    42,    46,   -79,   -79,
      16,   -79,    -1,    -1,   -79,    83,   -79,    -1,   -79
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     9,    10,     0,     2,     3,     5,     0,     6,     1,
       4,     0,     7,     0,    11,     0,     0,     0,    10,     0,
      12,    15,    16,     8,    18,     0,     0,     0,     0,    17,
      19,    20,    13,    22,    22,     0,    24,    23,     0,    46,
      65,     0,     0,     0,     0,     0,    34,     0,    27,     0,
      24,    26,    30,    28,    29,    31,    32,    33,     0,    66,
      45,    48,    56,    60,    67,     0,    69,     0,     0,    40,
       0,    66,    46,     0,     0,     0,     0,    21,    25,    35,
       0,    50,    51,    52,    53,    54,    55,     0,    58,    59,
       0,    62,    63,     0,     0,    71,     0,    70,     0,     0,
      41,    42,    44,    43,    64,    36,    49,    57,    61,    47,
       0,    68,     0,     0,    72,    37,    39,     0,    38
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -79,   -79,    90,   -79,    39,    20,   -79,   -79,   -79,   -79,
      73,   -79,    76,   -79,    71,    56,   -78,    23,   -79,   -79,
     -79,   -79,   -79,   -79,   -42,   -36,   -79,   -79,     9,   -79,
      18,   -79,    14,   -79,   -79,     1
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     3,     4,     5,     6,     7,     8,    16,    25,    20,
      21,    22,    48,    33,    36,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    71,    60,    87,    61,    90,
      62,    93,    63,    64,    96,    97
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      59,    70,    39,    75,    40,    76,     9,    41,    73,    42,
      43,    44,    45,    39,    59,    40,    39,    74,    40,    39,
      39,    40,    40,    94,    95,    98,    99,    46,    12,    13,
      47,    14,    11,    31,   115,   116,    19,    15,    69,   118,
      65,    47,    66,    23,    47,    46,    19,    47,    47,     1,
       2,     1,    18,    35,    35,    81,    82,    83,    84,    85,
      86,    12,    13,   -14,    88,    89,    17,    24,    95,    27,
      91,    92,    34,    34,    30,    38,    59,    59,    72,    67,
      26,    59,    28,    31,    68,    79,    77,   100,    80,    65,
     101,   102,   117,   103,   110,    10,   106,   109,   104,    29,
     111,   112,   113,   105,    32,    37,    78,   108,   107,     0,
       0,   114
};

static const yytype_int8 yycheck[] =
{
      36,    43,     3,    45,     5,    47,     0,     8,    44,    10,
      11,    12,    13,     3,    50,     5,     3,     4,     5,     3,
       3,     5,     5,    65,    66,    67,    68,    28,    28,    29,
      31,    31,     3,    34,   112,   113,    16,     5,    28,   117,
      29,    31,    31,    28,    31,    28,    26,    31,    31,     6,
       7,     6,     7,    33,    34,    14,    15,    16,    17,    18,
      19,    28,    29,    32,    22,    23,    30,     3,   110,    29,
      24,    25,    33,    34,    30,     3,   112,   113,     3,    31,
      33,   117,    32,    34,    31,    28,    35,    28,    36,    29,
      28,    28,     9,    28,    33,     5,    87,    30,    32,    26,
      32,    32,    32,    80,    28,    34,    50,    93,    90,    -1,
      -1,   110
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     6,     7,    38,    39,    40,    41,    42,    43,     0,
      39,     3,    28,    29,    31,     5,    44,    30,     7,    42,
      46,    47,    48,    28,     3,    45,    33,    29,    32,    47,
      30,    34,    49,    50,    41,    42,    51,    51,     3,     3,
       5,     8,    10,    11,    12,    13,    28,    31,    49,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    65,    67,    69,    70,    29,    31,    31,    31,    28,
      61,    62,     3,    62,     4,    61,    61,    35,    52,    28,
      36,    14,    15,    16,    17,    18,    19,    64,    22,    23,
      66,    24,    25,    68,    61,    61,    71,    72,    61,    61,
      28,    28,    28,    28,    32,    54,    65,    67,    69,    30,
      33,    32,    32,    32,    72,    53,    53,     9,    53
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    37,    38,    39,    39,    40,    40,    41,    41,    42,
      42,    44,    45,    43,    46,    46,    47,    47,    48,    48,
      50,    49,    51,    51,    52,    52,    53,    53,    53,    53,
      53,    53,    53,    53,    54,    54,    55,    56,    56,    57,
      58,    58,    59,    60,    60,    61,    62,    62,    63,    63,
      64,    64,    64,    64,    64,    64,    65,    65,    66,    66,
      67,    67,    68,    68,    69,    69,    69,    69,    70,    71,
      71,    72,    72
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     2,     1,     1,     3,     6,     1,
       1,     0,     0,     8,     1,     1,     1,     3,     2,     4,
       0,     5,     0,     2,     0,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     2,     3,     5,     7,     5,
       2,     3,     3,     3,     3,     1,     1,     4,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     3,     1,     1,
       1,     3,     1,     1,     3,     1,     1,     1,     4,     0,
       1,     1,     3
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


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
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

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
#ifndef YYINITDEPTH
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
static YYSIZE_T
yystrlen (const char *yystr)
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
static char *
yystpcpy (char *yydest, const char *yysrc)
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
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
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
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
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

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

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

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

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

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
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

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

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
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

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
      yychar = yylex ();
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
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 69 "lab9ast.y" /* yacc.c:1646  */
    {program=(yyvsp[0].node);}
#line 1360 "y.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 71 "lab9ast.y" /* yacc.c:1646  */
    {(yyval.node) = (yyvsp[0].node);}
#line 1366 "y.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 72 "lab9ast.y" /* yacc.c:1646  */
    {(yyval.node) = (yyvsp[-1].node);
			    (yyvsp[-1].node)->next=(yyvsp[0].node);}
#line 1373 "y.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 76 "lab9ast.y" /* yacc.c:1646  */
    {(yyval.node)=(yyvsp[0].node);}
#line 1379 "y.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 76 "lab9ast.y" /* yacc.c:1646  */
    {(yyval.node)=(yyvsp[0].node);}
#line 1385 "y.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 79 "lab9ast.y" /* yacc.c:1646  */
    { //struct SymbTab *p;
			  if(!Search((yyvsp[-1].string),level,0)){
			  (yyval.node)=ASTCreateNode(VARDEC);
                          (yyval.node)->operator=(yyvsp[-2].operator);
			  (yyval.node)->name=(yyvsp[-1].string);
			  (yyval.node)->symbol=Insert((yyvsp[-1].string),(yyvsp[-2].operator),0,level,1,offset,NULL);
			  (yyval.node)->value=0;
			  offset += 1;
		          } 
			  else{
			     yyerror((yyvsp[-1].string));
		             yyerror("symbol is already used");
			     exit(1);
			  } 	 				  
			 }
#line 1405 "y.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 94 "lab9ast.y" /* yacc.c:1646  */
    {struct SymbTab *p;
					       if(!Search((yyvsp[-4].string),level,0)){
					       (yyval.node)=ASTCreateNode(VARDEC); 
                                   	       (yyval.node)->name=(yyvsp[-4].string);
                                   	       (yyval.node)->operator=(yyvsp[-5].operator);
					       (yyval.node)->istype=(yyvsp[-5].operator);
                                   	       (yyval.node)->value=(yyvsp[-2].value);
					       (yyval.node)->symbol=Insert((yyvsp[-4].string),(yyvsp[-5].operator),2,level,(yyvsp[-2].value),offset,NULL);
					       offset += (yyvsp[-2].value);
					       }
					       else{yyerror((yyvsp[-4].string));
						    yyerror("symbol is already used");
			     			    exit(1);
					      }}
#line 1424 "y.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 110 "lab9ast.y" /* yacc.c:1646  */
    {(yyval.operator) = INTDEC;}
#line 1430 "y.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 111 "lab9ast.y" /* yacc.c:1646  */
    {(yyval.operator) = VOIDDEC;}
#line 1436 "y.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 115 "lab9ast.y" /* yacc.c:1646  */
    {if(!Search((yyvsp[-1].string),level,0)){
			  Insert((yyvsp[-1].string),(yyvsp[-2].operator),1,level,0,0,NULL);
			  goffset=offset;
			  offset=2;
			  maxoffset = offset;
			 }else{yyerror((yyvsp[-1].string));
				yyerror("symbol is already used");
			     	exit(1);
			  }
			}
#line 1451 "y.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 125 "lab9ast.y" /* yacc.c:1646  */
    {
			(Search((yyvsp[-3].string),0,0))->fparms = (yyvsp[0].node);
		 }
#line 1459 "y.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 130 "lab9ast.y" /* yacc.c:1646  */
    {(yyval.node)=ASTCreateNode(FUNCTDEC); 
				     (yyval.node)->operator =(yyvsp[-7].operator);
                                     (yyval.node)->name=(yyvsp[-6].string);
                                     (yyval.node)->s0 = (yyvsp[-3].node);
                                     (yyval.node)->s1 = (yyvsp[0].node);
				     (yyval.node)->istype=(yyvsp[-7].operator);
				     (yyval.node)->symbol=Search((yyvsp[-6].string),0,0);
				     offset-=Delete(1);
				     level=0;
				     offset=goffset;
			             (yyval.node)->value=maxoffset;
			            }
#line 1476 "y.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 144 "lab9ast.y" /* yacc.c:1646  */
    {(yyval.node) = NULL;}
#line 1482 "y.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 145 "lab9ast.y" /* yacc.c:1646  */
    {(yyval.node)=(yyvsp[0].node);}
#line 1488 "y.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 148 "lab9ast.y" /* yacc.c:1646  */
    {(yyval.node) = (yyvsp[0].node);}
#line 1494 "y.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 149 "lab9ast.y" /* yacc.c:1646  */
    {(yyvsp[-2].node)->next=(yyvsp[0].node);
			                       (yyval.node)=(yyvsp[-2].node);}
#line 1501 "y.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 153 "lab9ast.y" /* yacc.c:1646  */
    {if(mydebug) Display();
			if(!Search((yyvsp[0].string),level+1,0)){
			 (yyval.node)=ASTCreateNode(PARAM);
		         (yyval.node)->operator=(yyvsp[-1].operator);
                         (yyval.node)->name=(yyvsp[0].string);
			 (yyval.node)->istype=(yyvsp[-1].operator);
			 (yyval.node)->symbol=Insert((yyvsp[0].string),(yyvsp[-1].operator),0,level+1,1,offset,NULL);
		   	 if(mydebug) Display();
			 (yyval.node)->value=0;
			 offset+=1;			  
			 }else{yyerror((yyvsp[0].string));
				yyerror("symbol is already used");
			     	exit(1);
			  }}
#line 1520 "y.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 167 "lab9ast.y" /* yacc.c:1646  */
    {if(!Search((yyvsp[-2].string),level+1,0)){
					  (yyval.node)=ASTCreateNode(PARAM);
					  (yyval.node)->operator=(yyvsp[-3].operator);
					  (yyval.node)->istype=(yyvsp[-3].operator);
                               		  (yyval.node)->name=(yyvsp[-2].string);
                               		  (yyval.node)->value=-1;
					  (yyval.node)->symbol=Insert((yyvsp[-2].string),(yyvsp[-3].operator),2,level+1,1,offset,NULL);
					  offset+=1;
					  }else{yyerror((yyvsp[-2].string));
						yyerror("symbol is already used");
			     			exit(1);
			  		   }
					 }
#line 1538 "y.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 182 "lab9ast.y" /* yacc.c:1646  */
    {level++;}
#line 1544 "y.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 183 "lab9ast.y" /* yacc.c:1646  */
    {(yyval.node)=ASTCreateNode(BLOCK);
                                                        if ((yyvsp[-2].node)==NULL) 
                                                            (yyval.node)->s0=(yyvsp[-1].node);
                                                        else{  
                                                            (yyval.node)->s0=(yyvsp[-2].node);
                                                            (yyval.node)->s1=(yyvsp[-1].node);}
							//Display();
							maxoffset=max(maxoffset,offset);
						        offset-=Delete(level);
							level--;}
#line 1559 "y.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 195 "lab9ast.y" /* yacc.c:1646  */
    {(yyval.node)=NULL;}
#line 1565 "y.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 196 "lab9ast.y" /* yacc.c:1646  */
    {(yyvsp[-1].node)->next=(yyvsp[0].node);
                                      			      (yyval.node)=(yyvsp[-1].node);}
#line 1572 "y.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 200 "lab9ast.y" /* yacc.c:1646  */
    {(yyval.node)=NULL;}
#line 1578 "y.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 201 "lab9ast.y" /* yacc.c:1646  */
    {if((yyvsp[-1].node) !=NULL){
							(yyvsp[-1].node)->next=(yyvsp[0].node);
                                       			(yyval.node)=(yyvsp[-1].node);}
                                   		     else (yyval.node)=(yyvsp[0].node);}
#line 1587 "y.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 207 "lab9ast.y" /* yacc.c:1646  */
    {(yyval.node) = (yyvsp[0].node);}
#line 1593 "y.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 208 "lab9ast.y" /* yacc.c:1646  */
    {(yyval.node) = (yyvsp[0].node);}
#line 1599 "y.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 209 "lab9ast.y" /* yacc.c:1646  */
    {(yyval.node) = (yyvsp[0].node);}
#line 1605 "y.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 210 "lab9ast.y" /* yacc.c:1646  */
    {(yyval.node) = (yyvsp[0].node);}
#line 1611 "y.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 211 "lab9ast.y" /* yacc.c:1646  */
    {(yyval.node) = (yyvsp[0].node);}
#line 1617 "y.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 212 "lab9ast.y" /* yacc.c:1646  */
    {(yyval.node) = (yyvsp[0].node);}
#line 1623 "y.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 213 "lab9ast.y" /* yacc.c:1646  */
    {(yyval.node) = (yyvsp[0].node);}
#line 1629 "y.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 214 "lab9ast.y" /* yacc.c:1646  */
    {(yyval.node) = (yyvsp[0].node);}
#line 1635 "y.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 217 "lab9ast.y" /* yacc.c:1646  */
    {(yyval.node)=NULL;
		      (yyval.node)=ASTCreateNode(EXPRSTMT);
		      (yyval.node)->s0=NULL;}
#line 1643 "y.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 220 "lab9ast.y" /* yacc.c:1646  */
    {(yyval.node)=ASTCreateNode(EXPRSTMT);
	       		         (yyval.node)->s0=(yyvsp[-1].node);
				 (yyval.node)->istype=(yyvsp[-1].node)->istype;
				 (yyval.node)->name=CreateTemp();
				 (yyval.node)->symbol=Insert((yyval.node)->name,(yyval.node)->istype,0,level,1,offset,NULL);
				 offset++;}
#line 1654 "y.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 229 "lab9ast.y" /* yacc.c:1646  */
    {(yyval.node)=ASTCreateNode(ASSIGNSTMT); 
					   if(((yyvsp[-2].node)->istype ==VOIDDEC) || ((yyvsp[-2].node)->istype != (yyvsp[0].node)->istype)){
						yyerror("type error for assignment statement ");
						exit(1);
					   }
                                          (yyval.node)->s0=(yyvsp[-2].node);
                                          (yyval.node)->s1=(yyvsp[0].node);
					
                           		  }
#line 1668 "y.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 240 "lab9ast.y" /* yacc.c:1646  */
    {(yyval.node)=ASTCreateNode(IFSTMT);
                                                 (yyval.node)->s0=(yyvsp[-2].node);
                                                 (yyval.node)->s1=(yyvsp[0].node);
                                                 (yyval.node)->s2=NULL;}
#line 1677 "y.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 245 "lab9ast.y" /* yacc.c:1646  */
    {(yyval.node)=ASTCreateNode(IFSTMT);
                                                          		    (yyval.node)->s0=(yyvsp[-4].node);
                                                          	            (yyval.node)->s1=(yyvsp[-2].node);
                                                                            (yyval.node)->s2=(yyvsp[0].node);}
#line 1686 "y.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 251 "lab9ast.y" /* yacc.c:1646  */
    {(yyval.node)=ASTCreateNode(WHILESTMT);
                                                    (yyval.node)->s0=(yyvsp[-2].node);
                                                    (yyval.node)->s1=(yyvsp[0].node);}
#line 1694 "y.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 256 "lab9ast.y" /* yacc.c:1646  */
    {(yyval.node)=ASTCreateNode(RETURNSTMT);
                         (yyval.node)->s0=NULL;}
#line 1701 "y.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 258 "lab9ast.y" /* yacc.c:1646  */
    {(yyval.node)=ASTCreateNode(RETURNSTMT);
                                	    (yyval.node)->s0=(yyvsp[-1].node);}
#line 1708 "y.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 262 "lab9ast.y" /* yacc.c:1646  */
    {(yyval.node)=ASTCreateNode(READSTMT);
                         (yyval.node)->s0=(yyvsp[-1].node);}
#line 1715 "y.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 266 "lab9ast.y" /* yacc.c:1646  */
    {(yyval.node)=ASTCreateNode(WRITESTMT);
                                  (yyval.node)->s0=(yyvsp[-1].node);}
#line 1722 "y.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 268 "lab9ast.y" /* yacc.c:1646  */
    {(yyval.node)=ASTCreateNode(WRITESTMT);
				   (yyval.node)->string=CreateTemp();
                   	           (yyval.node)->name=(yyvsp[-1].string);
				  
					}
#line 1732 "y.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 275 "lab9ast.y" /* yacc.c:1646  */
    {(yyval.node)=(yyvsp[0].node);}
#line 1738 "y.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 278 "lab9ast.y" /* yacc.c:1646  */
    {struct SymbTab *p;
	   if((p=Search((yyvsp[0].string),level,1))){
			      (yyval.node)=ASTCreateNode(IDENTIFER);
			      (yyval.node)->name=(yyvsp[0].string);
			      (yyval.node)->symbol=p;
			      (yyval.node)->istype=p->Type;
			     if(p->IsAFunc==2){
				yyerror((yyvsp[0].string));
				yyerror("variable is an array, syntax error ");
				exit(1);
			      }		       
	   }
	    else{yyerror((yyvsp[0].string));
		 yyerror("undeclared variable");
		 exit(1);
	    }}
#line 1759 "y.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 294 "lab9ast.y" /* yacc.c:1646  */
    {struct SymbTab *p;
			     if((p=Search((yyvsp[-3].string),level,1))){
			     (yyval.node)=ASTCreateNode(IDENTIFER);
	                     (yyval.node)->name=(yyvsp[-3].string);
		             (yyval.node)->s0=(yyvsp[-1].node);
			     (yyval.node)->istype=p->Type;
			     if(p->IsAFunc==2) (yyval.node)->symbol=p;
			     else{yyerror((yyvsp[-3].string));
				yyerror("variable is not array, syntax error ");
				exit(1);
			     }
			     }
			    else{yyerror((yyvsp[-3].string));
		 	    yyerror("undeclared variable");
		            exit(1);
	    		    }}
#line 1780 "y.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 312 "lab9ast.y" /* yacc.c:1646  */
    {(yyval.node)=(yyvsp[0].node);}
#line 1786 "y.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 314 "lab9ast.y" /* yacc.c:1646  */
    {
					if((yyvsp[-2].node)->istype != (yyvsp[0].node)->istype){
					yyerror("simple expression type mismsatch");
					exit(1);
					}
				        (yyval.node)=ASTCreateNode(EXPR);
                                        (yyval.node)->s0=(yyvsp[-2].node);
                                        (yyval.node)->s1=(yyvsp[0].node);
                                        (yyval.node)->operator=(yyvsp[-1].operator);
				        (yyval.node)->istype=INTDEC;
					(yyval.node)->name=CreateTemp();
					(yyval.node)->symbol=Insert((yyval.node)->name,INTDEC,0,level,1,offset,NULL);
					offset++;}
#line 1804 "y.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 329 "lab9ast.y" /* yacc.c:1646  */
    {(yyval.operator)=LESSTHANEQUAL;}
#line 1810 "y.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 330 "lab9ast.y" /* yacc.c:1646  */
    {(yyval.operator)=LESSTHAN;}
#line 1816 "y.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 331 "lab9ast.y" /* yacc.c:1646  */
    {(yyval.operator)=GREATERTHAN;}
#line 1822 "y.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 332 "lab9ast.y" /* yacc.c:1646  */
    {(yyval.operator)=GREATERTHANEQUAL;}
#line 1828 "y.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 333 "lab9ast.y" /* yacc.c:1646  */
    {(yyval.operator)=EQUAL;}
#line 1834 "y.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 334 "lab9ast.y" /* yacc.c:1646  */
    {(yyval.operator)=NOTEQUAL;}
#line 1840 "y.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 337 "lab9ast.y" /* yacc.c:1646  */
    {(yyval.node)=(yyvsp[0].node);}
#line 1846 "y.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 339 "lab9ast.y" /* yacc.c:1646  */
    {
		     if((yyvsp[-2].node)->istype!=(yyvsp[0].node)->istype){
		     	yyerror("additive expression type mismatch ");
		     	exit(1); 
		     }
								
		     (yyval.node)=ASTCreateNode(EXPR);
                     (yyval.node)->s0=(yyvsp[-2].node);
                     (yyval.node)->s1=(yyvsp[0].node);
                     (yyval.node)->operator=(yyvsp[-1].operator);
		     (yyval.node)->istype=INTDEC;
		     (yyval.node)->name=CreateTemp();
		     (yyval.node)->symbol=Insert((yyval.node)->name,INTDEC,0,level,1,offset,NULL);
		     offset++;
}
#line 1866 "y.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 356 "lab9ast.y" /* yacc.c:1646  */
    {(yyval.operator)=PLUS;}
#line 1872 "y.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 356 "lab9ast.y" /* yacc.c:1646  */
    {(yyval.operator)=MINUS;}
#line 1878 "y.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 359 "lab9ast.y" /* yacc.c:1646  */
    {(yyval.node)=(yyvsp[0].node);}
#line 1884 "y.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 361 "lab9ast.y" /* yacc.c:1646  */
    { if((yyvsp[-2].node)->istype!=(yyvsp[0].node)->istype){
			    yyerror("term type mismatch ");
			    exit(1); 
			    }
		           (yyval.node)=ASTCreateNode(EXPR);
                           (yyval.node)->s0=(yyvsp[-2].node);
                           (yyval.node)->s1=(yyvsp[0].node);
                           (yyval.node)->operator=(yyvsp[-1].operator);
			   (yyval.node)->istype=INTDEC;
		           (yyval.node)->name=CreateTemp();
                           (yyval.node)->symbol=Insert((yyval.node)->name,INTDEC,0,level,1,offset,NULL);
			   offset++;}
#line 1901 "y.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 376 "lab9ast.y" /* yacc.c:1646  */
    {(yyval.operator)=TIMES;}
#line 1907 "y.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 376 "lab9ast.y" /* yacc.c:1646  */
    {(yyval.operator)=DIV;}
#line 1913 "y.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 379 "lab9ast.y" /* yacc.c:1646  */
    {(yyval.node)=(yyvsp[-1].node);}
#line 1919 "y.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 380 "lab9ast.y" /* yacc.c:1646  */
    {(yyval.node)=ASTCreateNode(NUMBER);
               (yyval.node)->value=(yyvsp[0].value);
	       (yyval.node)->istype=INTDEC;}
#line 1927 "y.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 383 "lab9ast.y" /* yacc.c:1646  */
    {(yyval.node)=(yyvsp[0].node);}
#line 1933 "y.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 384 "lab9ast.y" /* yacc.c:1646  */
    {(yyval.node)=(yyvsp[0].node);}
#line 1939 "y.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 387 "lab9ast.y" /* yacc.c:1646  */
    {struct SymbTab *p;
		if((p=Search((yyvsp[-3].string),0,0))){
			if(p->IsAFunc != 1){
				yyerror((yyvsp[-3].string));
				yyerror("Function name not defined");
				exit(1);
			}
			if(compareFormals(p->fparms,(yyvsp[-1].node)) != 1){
				yyerror((yyvsp[-3].string));
				yyerror("parameter type or length mismatch between formals and actuals");
				exit(1);
			}
			(yyval.node)=ASTCreateNode(CALL);
      			(yyval.node)->s0=(yyvsp[-1].node);
         		(yyval.node)->name=(yyvsp[-3].string);
			(yyval.node)->istype=p->Type;
			(yyval.node)->symbol=p;
		}
		else{
			yyerror((yyvsp[-3].string));
			yyerror("Function name not defined");
			exit(1);
		}
          }
#line 1968 "y.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 414 "lab9ast.y" /* yacc.c:1646  */
    {(yyval.node)=NULL;}
#line 1974 "y.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 414 "lab9ast.y" /* yacc.c:1646  */
    {(yyval.node)=(yyvsp[0].node);}
#line 1980 "y.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 417 "lab9ast.y" /* yacc.c:1646  */
    {(yyval.node)=ASTCreateNode(ARGLIST);
		      (yyval.node)->name=CreateTemp();
		      (yyval.node)->symbol=Insert((yyval.node)->name,INTDEC,0,level,1,offset,NULL);
                      (yyval.node)->s0=(yyvsp[0].node);
		      (yyval.node)->istype=(yyvsp[0].node)->istype;
                      (yyval.node)->next=NULL;
		       offset++;}
#line 1992 "y.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 424 "lab9ast.y" /* yacc.c:1646  */
    {(yyval.node)=ASTCreateNode(ARGLIST);
			           (yyval.node)->name=CreateTemp();
		      		   (yyval.node)->symbol=Insert((yyval.node)->name,INTDEC,0,level,1,offset,NULL);
                               	   (yyval.node)->next=(yyvsp[0].node);
                               	   (yyval.node)->s0=(yyvsp[-2].node);
				    offset++;}
#line 2003 "y.tab.c" /* yacc.c:1646  */
    break;


#line 2007 "y.tab.c" /* yacc.c:1646  */
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

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
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
                      yytoken, &yylval);
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

  /* Do not reclaim the symbols of the rule whose action triggered
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
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

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


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
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
  return yyresult;
}
#line 433 "lab9ast.y" /* yacc.c:1906  */
 /* end rules */

main(int argc,char *argv[])
{  

//fprintf(stderr, "The input has been syntatically checked\n");
//ASTprint(0,program);
//extra display here
//printf("Main symbol table START \n"); 
//Display();  
//printf("Main symbol table END \n");

if(argc < 2){printf("input at least 1 parameter\n");exit(0);}

if((strcmp(argv[1], "-o")==1) && (strcmp(argv[1], "-d")==1)){printf("please input either a -o or -d for first argument\n");exit(0);}

if((strcmp(argv[1],"-d")==0) && (!argv[2])){printf("more than just -d please\n");exit(0);}

else if((strcmp(argv[1],"-d")==0) && (strcmp(argv[2],"-o")==0)){
	if(argc != 4){printf("please write an output file\n");exit(0);}
	mydebug=1;
	output=fopen(argv[3],"wb");
	if(!output){printf("could not open file\n");exit(0);}
	yyparse();
	emitNASM(program,output);
	fclose(output);
	return 1;
}
else if(strcmp(argv[1],"-o")==0){
	if(argc != 3){printf("please write an output file\n");exit(0);}
	output=fopen(argv[2],"wb");
	if(!output){printf("Could not open file\n");exit(0);}
	yyparse();
	emitNASM(program,output);
	fclose(output);
	return 1;
}
 else printf("error: not correct arguments! \n");

return 0;


//yyparse();
//emitAST(program);

}//end main

