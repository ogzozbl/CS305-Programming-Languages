/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     tNUMBER = 258,
     tIDENT = 259,
     tCALC = 260,
     tDERIV = 261,
     tINTEG = 262,
     tASSIGN = 263,
     tPLUS = 264,
     tMINUS = 265,
     tMULT = 266,
     tDIV = 267,
     tPOWER = 268,
     tCOMMA = 269,
     tLPAR = 270,
     tRPAR = 271,
     tSEMI = 272,
     tIMPLICIT = 273,
     tUMINUS = 274
   };
#endif
/* Tokens.  */
#define tNUMBER 258
#define tIDENT 259
#define tCALC 260
#define tDERIV 261
#define tINTEG 262
#define tASSIGN 263
#define tPLUS 264
#define tMINUS 265
#define tMULT 266
#define tDIV 267
#define tPOWER 268
#define tCOMMA 269
#define tLPAR 270
#define tRPAR 271
#define tSEMI 272
#define tIMPLICIT 273
#define tUMINUS 274




/* Copy the first part of user declarations.  */
#line 1 "oguz.ozbal-hw3.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "oguz.ozbal-hw3.h"

extern int lineCount;
int currentCalcLine = 1;
int lastLPARLine = 1;
int lastRPARLine = 1; 
int firstMissingFuncLine = 0; 
void yyerror(const char *msg) {} 
int yylex();

FuncNode *funcsHead = NULL;
ErrorNode *errsHead = NULL;
OutputNode *outHead = NULL;
OutputNode *outTail = NULL; 
int hasSemanticErrors = 0;

// ArgPolyStore: Argümanların GERÇEK poly değerlerini saklar
typedef struct ArgPolyStore {
    ParseObj *arg;
    PolyNode *poly;
    char *str;
    struct ArgPolyStore *next;
} ArgPolyStore;
ArgPolyStore *argPolyStore = NULL;

void addError(int line, const char *msg);
void addOutput(char *lhs, PolyNode *rhs);
void addFunction(char *name, VarNode *params, PolyNode *body);
FuncNode* getFunction(char *name);
FuncNode* getFunctionWithArity(char *name, int arity);
int isFunctionRedefined(char *name);

Fraction makeFrac(int n, int d);
Fraction addFrac(Fraction a, Fraction b);
Fraction mulFrac(Fraction a, Fraction b);
Fraction simplifyFrac(Fraction f);
PolyNode* createPolyFromNum(int n);
PolyNode* createPolyFromVar(char *name, int line);
PolyNode* addPoly(PolyNode *p1, PolyNode *p2, int subtract);
PolyNode* mulPoly(PolyNode *p1, PolyNode *p2);
PolyNode* powerPoly(PolyNode *p, int pow);
PolyNode* copyPoly(PolyNode *p);
PolyNode* derivePoly(PolyNode *p, char var, int order);
PolyNode* integratePoly(PolyNode *p, char var, int order);
PolyNode* substituteFunc(FuncNode *fn, int argCount);

PolyVar* copyVars(PolyVar *v);
PolyVar* mergeVars(PolyVar *v1, PolyVar *v2);
Term* copyTerm(Term *t);
VarNode* createVarNode(char *name);
VarNode* appendVarNode(VarNode *head, VarNode *node);
int countVars(VarNode *head);
char* concat(const char *s1, const char *s2, const char *s3);
char* buildFuncCallString(char *funcName, int argCount);

PolyNode* simplifyPoly(PolyNode *p);
int compareTerms(Term *t1, Term *t2);
char* formatPoly(PolyNode *p);
char* formatTerm(Term *t);
char* removeWhitespace(const char *str);

void printSortedErrors();
void printReport();
void clearArgStore();


/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 71 "oguz.ozbal-hw3.y"
{
    int iVal;
    struct IdInfo idInfo; 
    struct VarNode *varList;
    struct ParseObj pObj;  
    struct ParseObj *argList; 
}
/* Line 193 of yacc.c.  */
#line 212 "oguz.ozbal-hw3.tab.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 225 "oguz.ozbal-hw3.tab.c"

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
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
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
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
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
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
  yytype_int16 yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   78

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  20
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  13
/* YYNRULES -- Number of rules.  */
#define YYNRULES  33
/* YYNRULES -- Number of states.  */
#define YYNSTATES  70

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   274

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
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
      15,    16,    17,    18,    19
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     6,     7,    10,    18,    19,    21,    25,
      26,    29,    33,    35,    39,    43,    45,    49,    53,    56,
      58,    61,    63,    67,    72,    74,    76,    80,    84,    89,
      95,   104,   113,   115
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      21,     0,    -1,    22,    25,    -1,    -1,    22,    23,    -1,
       4,    15,    24,    16,     8,    27,    17,    -1,    -1,     4,
      -1,    24,    14,     4,    -1,    -1,    25,    26,    -1,     5,
      27,    17,    -1,    28,    -1,    27,     9,    28,    -1,    27,
      10,    28,    -1,    29,    -1,    28,    11,    29,    -1,    28,
      12,    29,    -1,    28,    30,    -1,    30,    -1,    10,    29,
      -1,    31,    -1,    31,    13,     3,    -1,    31,    13,    10,
       3,    -1,     3,    -1,     4,    -1,    15,    27,    16,    -1,
       4,    15,    16,    -1,     4,    15,    32,    16,    -1,    15,
      27,    14,    32,    16,    -1,     6,    15,     4,    14,     4,
      14,     3,    16,    -1,     7,    15,     4,    14,     4,    14,
       3,    16,    -1,    27,    -1,    32,    14,    27,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   100,   100,   103,   105,   109,   139,   140,   141,   144,
     146,   150,   158,   160,   165,   173,   175,   180,   185,   193,
     195,   204,   206,   212,   221,   227,   232,   237,   267,   340,
     351,   372,   396,   410
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "tNUMBER", "tIDENT", "tCALC", "tDERIV",
  "tINTEG", "tASSIGN", "tPLUS", "tMINUS", "tMULT", "tDIV", "tPOWER",
  "tCOMMA", "tLPAR", "tRPAR", "tSEMI", "tIMPLICIT", "tUMINUS", "$accept",
  "program", "def_block", "func_def", "param_list", "calc_block",
  "calc_stmt", "expr", "term", "factor", "power", "atom", "func_args", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    20,    21,    22,    22,    23,    24,    24,    24,    25,
      25,    26,    27,    27,    27,    28,    28,    28,    28,    29,
      29,    30,    30,    30,    31,    31,    31,    31,    31,    31,
      31,    31,    32,    32
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     0,     2,     7,     0,     1,     3,     0,
       2,     3,     1,     3,     3,     1,     3,     3,     2,     1,
       2,     1,     3,     4,     1,     1,     3,     3,     4,     5,
       8,     8,     1,     3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     9,     1,     0,     4,     2,     6,     0,    10,
       7,     0,    24,    25,     0,     0,     0,     0,     0,    12,
      15,    19,    21,     0,     0,     0,     0,     0,    20,     0,
       0,     0,    11,     0,     0,    18,     0,     8,     0,    27,
      32,     0,     0,     0,     0,    26,    13,    14,    16,    17,
      22,     0,     0,     0,    28,     0,     0,     0,    23,     5,
      33,     0,     0,    29,     0,     0,     0,     0,    30,    31
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     1,     2,     5,    11,     6,     9,    40,    19,    20,
      21,    22,    41
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -19
static const yytype_int8 yypact[] =
{
     -19,    11,    18,   -19,    -7,   -19,    44,    34,    33,   -19,
     -19,    28,   -19,    26,    45,    46,    33,    33,     4,    20,
     -19,   -19,    42,    55,    54,     0,    59,    60,   -19,    37,
      33,    33,   -19,    33,    33,   -19,     2,   -19,    33,   -19,
      24,    36,    51,    52,    33,   -19,    20,    20,   -19,   -19,
     -19,    64,     8,    33,   -19,    65,    66,    40,   -19,   -19,
      24,    57,    58,   -19,    70,    71,    61,    62,   -19,   -19
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -19,   -19,   -19,   -19,   -19,   -19,   -19,    -8,    27,   -14,
     -18,   -19,    31
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      18,    35,    28,    12,    13,    50,    14,    15,     7,    29,
      16,     3,    51,    30,    31,    17,    39,    30,    31,    48,
      49,    32,     4,    12,    13,    59,    14,    15,    35,    35,
      52,    33,    34,    30,    31,    17,    12,    13,    10,    14,
      15,    25,    23,    16,    24,    60,    30,    31,    17,     8,
      53,    44,    54,    45,    53,    36,    63,    46,    47,    37,
      26,    27,    38,    42,    43,    55,    56,    58,     0,    61,
      62,    64,    65,    66,    67,    57,     0,    68,    69
};

static const yytype_int8 yycheck[] =
{
       8,    19,    16,     3,     4,     3,     6,     7,    15,    17,
      10,     0,    10,     9,    10,    15,    16,     9,    10,    33,
      34,    17,     4,     3,     4,    17,     6,     7,    46,    47,
      38,    11,    12,     9,    10,    15,     3,     4,     4,     6,
       7,    15,    14,    10,    16,    53,     9,    10,    15,     5,
      14,    14,    16,    16,    14,    13,    16,    30,    31,     4,
      15,    15,     8,     4,     4,    14,    14,     3,    -1,     4,
       4,    14,    14,     3,     3,    44,    -1,    16,    16
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    21,    22,     0,     4,    23,    25,    15,     5,    26,
       4,    24,     3,     4,     6,     7,    10,    15,    27,    28,
      29,    30,    31,    14,    16,    15,    15,    15,    29,    27,
       9,    10,    17,    11,    12,    30,    13,     4,     8,    16,
      27,    32,     4,     4,    14,    16,    28,    28,    29,    29,
       3,    10,    27,    14,    16,    14,    14,    32,     3,    17,
      27,     4,     4,    16,    14,    14,     3,     3,    16,    16
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
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


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
		  Type, Value); \
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
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
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
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
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
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
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
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
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

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

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



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

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
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

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
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

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

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
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
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

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


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 5:
#line 110 "oguz.ozbal-hw3.y"
    {
        if (getFunction((yyvsp[(1) - (7)].idInfo).name)) {
            char buf[100]; sprintf(buf, "REDEFINED_FUNCTION_(%s)", (yyvsp[(1) - (7)].idInfo).name);
            addError((yyvsp[(1) - (7)].idInfo).line, buf);
        }
        PolyNode *body = (yyvsp[(6) - (7)].pObj).poly;
        if (body) {
             Term *t = body->head;
             while(t) {
                 PolyVar *v = t->vars;
                 while(v) {
                     int found = 0;
                     VarNode *p = (yyvsp[(3) - (7)].varList);
                     while(p) { if(p->name[0] == v->name) found=1; p=p->next; }
                     if(!found) {
                        char buf[100]; char n[2] = {v->name, 0};
                        sprintf(buf, "UNDEFINED_FUNCTION_PARAMETER_(%s)", n);
                        addError(v->line, buf); 
                     }
                     v = v->next;
                 }
                 t = t->next;
             }
        }
        addFunction((yyvsp[(1) - (7)].idInfo).name, (yyvsp[(3) - (7)].varList), body);
    ;}
    break;

  case 6:
#line 139 "oguz.ozbal-hw3.y"
    { (yyval.varList) = NULL; ;}
    break;

  case 7:
#line 140 "oguz.ozbal-hw3.y"
    { (yyval.varList) = createVarNode((yyvsp[(1) - (1)].idInfo).name); ;}
    break;

  case 8:
#line 141 "oguz.ozbal-hw3.y"
    { (yyval.varList) = appendVarNode((yyvsp[(1) - (3)].varList), createVarNode((yyvsp[(3) - (3)].idInfo).name)); ;}
    break;

  case 11:
#line 151 "oguz.ozbal-hw3.y"
    {
        addOutput((yyvsp[(2) - (3)].pObj).str, (yyvsp[(2) - (3)].pObj).poly);
        firstMissingFuncLine = 0; 
    ;}
    break;

  case 12:
#line 159 "oguz.ozbal-hw3.y"
    { (yyval.pObj) = (yyvsp[(1) - (1)].pObj); ;}
    break;

  case 13:
#line 161 "oguz.ozbal-hw3.y"
    { 
        (yyval.pObj).poly = addPoly((yyvsp[(1) - (3)].pObj).poly, (yyvsp[(3) - (3)].pObj).poly, 0); 
        (yyval.pObj).str = concat((yyvsp[(1) - (3)].pObj).str, "+", (yyvsp[(3) - (3)].pObj).str);
    ;}
    break;

  case 14:
#line 166 "oguz.ozbal-hw3.y"
    { 
        (yyval.pObj).poly = addPoly((yyvsp[(1) - (3)].pObj).poly, (yyvsp[(3) - (3)].pObj).poly, 1); 
        (yyval.pObj).str = concat((yyvsp[(1) - (3)].pObj).str, "-", (yyvsp[(3) - (3)].pObj).str);
    ;}
    break;

  case 15:
#line 174 "oguz.ozbal-hw3.y"
    { (yyval.pObj) = (yyvsp[(1) - (1)].pObj); ;}
    break;

  case 16:
#line 176 "oguz.ozbal-hw3.y"
    { 
        (yyval.pObj).poly = mulPoly((yyvsp[(1) - (3)].pObj).poly, (yyvsp[(3) - (3)].pObj).poly); 
        (yyval.pObj).str = concat((yyvsp[(1) - (3)].pObj).str, "*", (yyvsp[(3) - (3)].pObj).str);
    ;}
    break;

  case 17:
#line 181 "oguz.ozbal-hw3.y"
    {
        (yyval.pObj).poly = NULL;
        (yyval.pObj).str = concat((yyvsp[(1) - (3)].pObj).str, "/", (yyvsp[(3) - (3)].pObj).str);
    ;}
    break;

  case 18:
#line 186 "oguz.ozbal-hw3.y"
    {
        (yyval.pObj).poly = mulPoly((yyvsp[(1) - (2)].pObj).poly, (yyvsp[(2) - (2)].pObj).poly);
        (yyval.pObj).str = concat((yyvsp[(1) - (2)].pObj).str, "", (yyvsp[(2) - (2)].pObj).str); 
    ;}
    break;

  case 19:
#line 194 "oguz.ozbal-hw3.y"
    { (yyval.pObj) = (yyvsp[(1) - (1)].pObj); ;}
    break;

  case 20:
#line 196 "oguz.ozbal-hw3.y"
    {
        PolyNode *neg1 = createPolyFromNum(-1);
        (yyval.pObj).poly = mulPoly(neg1, (yyvsp[(2) - (2)].pObj).poly);
        (yyval.pObj).str = concat("-", (yyvsp[(2) - (2)].pObj).str, "");
    ;}
    break;

  case 21:
#line 205 "oguz.ozbal-hw3.y"
    { (yyval.pObj) = (yyvsp[(1) - (1)].pObj); ;}
    break;

  case 22:
#line 207 "oguz.ozbal-hw3.y"
    { 
        (yyval.pObj).poly = powerPoly((yyvsp[(1) - (3)].pObj).poly, (yyvsp[(3) - (3)].iVal)); 
        char buf[32]; sprintf(buf, "^%d", (yyvsp[(3) - (3)].iVal));
        (yyval.pObj).str = concat((yyvsp[(1) - (3)].pObj).str, buf, "");
    ;}
    break;

  case 23:
#line 213 "oguz.ozbal-hw3.y"
    {
        (yyval.pObj).poly = powerPoly((yyvsp[(1) - (4)].pObj).poly, -(yyvsp[(4) - (4)].iVal)); 
        char buf[32]; sprintf(buf, "^-%d", (yyvsp[(4) - (4)].iVal));
        (yyval.pObj).str = concat((yyvsp[(1) - (4)].pObj).str, buf, "");
    ;}
    break;

  case 24:
#line 222 "oguz.ozbal-hw3.y"
    { 
        (yyval.pObj).poly = createPolyFromNum((yyvsp[(1) - (1)].iVal)); 
        char buf[32]; sprintf(buf, "%d", (yyvsp[(1) - (1)].iVal));
        (yyval.pObj).str = strdup(buf);
    ;}
    break;

  case 25:
#line 228 "oguz.ozbal-hw3.y"
    { 
        (yyval.pObj).poly = createPolyFromVar((yyvsp[(1) - (1)].idInfo).name, (yyvsp[(1) - (1)].idInfo).line); 
        (yyval.pObj).str = strdup((yyvsp[(1) - (1)].idInfo).name);
    ;}
    break;

  case 26:
#line 233 "oguz.ozbal-hw3.y"
    { 
        (yyval.pObj).poly = (yyvsp[(2) - (3)].pObj).poly; 
        (yyval.pObj).str = concat("(", (yyvsp[(2) - (3)].pObj).str, ")");
    ;}
    break;

  case 27:
#line 238 "oguz.ozbal-hw3.y"
    {
        // Parametresiz fonksiyon çağrısı: g()
        FuncNode *f = getFunction((yyvsp[(1) - (3)].idInfo).name);
        int cnt = 0;
        
        (yyval.pObj).str = NULL;
        
        if (!f) {
            char buf[100]; sprintf(buf, "UNDEFINED_FUNCTION_(%s)", (yyvsp[(1) - (3)].idInfo).name);
            addError((yyvsp[(1) - (3)].idInfo).line, buf);
            (yyval.pObj).poly = NULL;
            (yyval.pObj).str = concat((yyvsp[(1) - (3)].idInfo).name, "()", "");
        } else {
            FuncNode *fExact = getFunctionWithArity((yyvsp[(1) - (3)].idInfo).name, cnt);
            int redefined = isFunctionRedefined((yyvsp[(1) - (3)].idInfo).name);
            
            if (!fExact || redefined) {
                char buf[100]; sprintf(buf, "ARITY_CONTRADICTION_(%s)", (yyvsp[(1) - (3)].idInfo).name);
                addError((yyvsp[(1) - (3)].idInfo).line, buf);
                (yyval.pObj).poly = NULL;
                (yyval.pObj).str = concat((yyvsp[(1) - (3)].idInfo).name, "()", "");
            } else {
                // Parametresiz fonksiyon - body'yi direkt kopyala
                (yyval.pObj).poly = fExact->body ? copyPoly(fExact->body) : createPolyFromNum(0);
                (yyval.pObj).str = concat((yyvsp[(1) - (3)].idInfo).name, "()", "");
            }
        }
        if ((yyval.pObj).str == NULL) (yyval.pObj).str = strdup("error");
    ;}
    break;

  case 28:
#line 268 "oguz.ozbal-hw3.y"
    {
        FuncNode *f = getFunction((yyvsp[(1) - (4)].idInfo).name);
        
        // Argüman sayısını store'dan hesapla
        int cnt = 0;
        ArgPolyStore *countStore = argPolyStore;
        while (countStore) {
            cnt++;
            countStore = countStore->next;
        }
        if (cnt == 0) cnt = 1;
        
        (yyval.pObj).str = NULL;

        if (!f) {
            // Fonksiyon tanımlı değil
            if (cnt == 1) {
                // Tek parametre - implicit multiplication, HATA VERME
                PolyNode *identPoly = createPolyFromVar((yyvsp[(1) - (4)].idInfo).name, (yyvsp[(1) - (4)].idInfo).line);
                PolyNode *argPoly = (yyvsp[(3) - (4)].argList)->poly; 
                (yyval.pObj).poly = mulPoly(identPoly, argPoly);
                (yyval.pObj).str = concat((yyvsp[(1) - (4)].idInfo).name, "(", (yyvsp[(3) - (4)].argList)->str);
                (yyval.pObj).str = concat((yyval.pObj).str, ")", "");
            } else {
                // Çoklu parametre - UNDEFINED_FUNCTION hatası ver
                char buf[100]; sprintf(buf, "UNDEFINED_FUNCTION_(%s)", (yyvsp[(1) - (4)].idInfo).name);
                addError((yyvsp[(1) - (4)].idInfo).line, buf);
                (yyval.pObj).poly = NULL;
                (yyval.pObj).str = buildFuncCallString((yyvsp[(1) - (4)].idInfo).name, cnt);
            }
        } else {
            FuncNode *fExact = getFunctionWithArity((yyvsp[(1) - (4)].idInfo).name, cnt);
            int redefined = isFunctionRedefined((yyvsp[(1) - (4)].idInfo).name);
            
            if (redefined) {
                // Fonksiyon yeniden tanımlanmış - her zaman ARITY_CONTRADICTION
                char buf[100]; sprintf(buf, "ARITY_CONTRADICTION_(%s)", (yyvsp[(1) - (4)].idInfo).name);
                addError((yyvsp[(1) - (4)].idInfo).line, buf); 
                (yyval.pObj).poly = NULL;
                (yyval.pObj).str = buildFuncCallString((yyvsp[(1) - (4)].idInfo).name, cnt);
            } else if (!fExact) {
                // Arity uyuşmuyor
                if (cnt == 1) {
                    // Tek parametre ve arity uyuşmuyor - implicit multiplication
                    PolyNode *identPoly = createPolyFromVar((yyvsp[(1) - (4)].idInfo).name, (yyvsp[(1) - (4)].idInfo).line);
                    PolyNode *argPoly = (yyvsp[(3) - (4)].argList)->poly; 
                    (yyval.pObj).poly = mulPoly(identPoly, argPoly);
                    (yyval.pObj).str = concat((yyvsp[(1) - (4)].idInfo).name, "(", (yyvsp[(3) - (4)].argList)->str);
                    (yyval.pObj).str = concat((yyval.pObj).str, ")", "");
                } else {
                    // Çoklu parametre ve arity uyuşmuyor - ARITY_CONTRADICTION
                    char buf[100]; sprintf(buf, "ARITY_CONTRADICTION_(%s)", (yyvsp[(1) - (4)].idInfo).name);
                    addError((yyvsp[(1) - (4)].idInfo).line, buf); 
                    (yyval.pObj).poly = NULL;
                    (yyval.pObj).str = buildFuncCallString((yyvsp[(1) - (4)].idInfo).name, cnt);
                }
            } else {
                // Arity doğru - normal substitution
                PolyNode *substituted = substituteFunc(fExact, cnt);
                if (!substituted) {
                    (yyval.pObj).poly = createPolyFromNum(0);
                } else {
                    (yyval.pObj).poly = simplifyPoly(substituted);
                }
                (yyval.pObj).str = buildFuncCallString((yyvsp[(1) - (4)].idInfo).name, cnt);
            }
        }
        if ((yyval.pObj).str == NULL) (yyval.pObj).str = strdup("error");
        
        // Store'u temizle
        clearArgStore();
    ;}
    break;

  case 29:
#line 341 "oguz.ozbal-hw3.y"
    {
         int thisLine = lastLPARLine;
         if (firstMissingFuncLine == 0) {
             firstMissingFuncLine = thisLine;
         }
         addError(firstMissingFuncLine, "MISSING_FUNCTION_NAME");
         (yyval.pObj).poly = NULL;
         (yyval.pObj).str = strdup("error");
         clearArgStore();
    ;}
    break;

  case 30:
#line 352 "oguz.ozbal-hw3.y"
    {
        FuncNode *f = getFunction((yyvsp[(3) - (8)].idInfo).name);
        if(!f) {
            char buf[100]; sprintf(buf, "UNDEFINED_FUNCTION_FOR_DERIVATION_(%s)", (yyvsp[(3) - (8)].idInfo).name);
            addError((yyvsp[(3) - (8)].idInfo).line, buf);
            (yyval.pObj).poly = NULL;
        } else {
             int valid = 0; VarNode *v = f->params;
             while(v) { if(strcmp(v->name, (yyvsp[(5) - (8)].idInfo).name)==0) valid=1; v=v->next; }
             if(!valid) {
                 char buf[100]; sprintf(buf, "UNDEFINED_VARIABLE_FOR_DERIVATION_(%s)", (yyvsp[(5) - (8)].idInfo).name);
                 addError((yyvsp[(5) - (8)].idInfo).line, buf);
                 (yyval.pObj).poly = NULL;
             } else {
                 (yyval.pObj).poly = derivePoly(f->body, (yyvsp[(5) - (8)].idInfo).name[0], (yyvsp[(7) - (8)].iVal)); 
             }
        }
        char buf[50]; sprintf(buf, "D(%s,%s,%d)", (yyvsp[(3) - (8)].idInfo).name, (yyvsp[(5) - (8)].idInfo).name, (yyvsp[(7) - (8)].iVal));
        (yyval.pObj).str = strdup(buf);
    ;}
    break;

  case 31:
#line 373 "oguz.ozbal-hw3.y"
    {
        FuncNode *f = getFunction((yyvsp[(3) - (8)].idInfo).name);
        if(!f) {
            char buf[100]; sprintf(buf, "UNDEFINED_FUNCTION_FOR_INTEGRATION_(%s)", (yyvsp[(3) - (8)].idInfo).name);
            addError((yyvsp[(3) - (8)].idInfo).line, buf);
            (yyval.pObj).poly = NULL;
        } else {
             int valid = 0; VarNode *v = f->params;
             while(v) { if(strcmp(v->name, (yyvsp[(5) - (8)].idInfo).name)==0) valid=1; v=v->next; }
             if(!valid) {
                 char buf[100]; sprintf(buf, "UNDEFINED_VARIABLE_FOR_INTEGRATION_(%s)", (yyvsp[(5) - (8)].idInfo).name);
                 addError((yyvsp[(5) - (8)].idInfo).line, buf);
                 (yyval.pObj).poly = NULL;
             } else {
                 (yyval.pObj).poly = integratePoly(f->body, (yyvsp[(5) - (8)].idInfo).name[0], (yyvsp[(7) - (8)].iVal));
             }
        }
        char buf[50]; sprintf(buf, "I(%s,%s,%d)", (yyvsp[(3) - (8)].idInfo).name, (yyvsp[(5) - (8)].idInfo).name, (yyvsp[(7) - (8)].iVal));
        (yyval.pObj).str = strdup(buf);
    ;}
    break;

  case 32:
#line 397 "oguz.ozbal-hw3.y"
    {
        (yyval.argList) = malloc(sizeof(ParseObj)); 
        (yyval.argList)->str = (yyvsp[(1) - (1)].pObj).str;
        (yyval.argList)->poly = (yyvsp[(1) - (1)].pObj).poly;
        
        // İlk argümanı store'a ekle
        ArgPolyStore *store = malloc(sizeof(ArgPolyStore));
        store->arg = (yyval.argList);
        store->poly = copyPoly((yyvsp[(1) - (1)].pObj).poly);
        store->str = (yyvsp[(1) - (1)].pObj).str ? strdup((yyvsp[(1) - (1)].pObj).str) : NULL;
        store->next = argPolyStore;
        argPolyStore = store;
    ;}
    break;

  case 33:
#line 411 "oguz.ozbal-hw3.y"
    {
        ParseObj *node = malloc(sizeof(ParseObj));
        node->str = (yyvsp[(3) - (3)].pObj).str;
        node->poly = (yyvsp[(3) - (3)].pObj).poly;
        
        // Bu argümanı store'a ekle
        ArgPolyStore *store = malloc(sizeof(ArgPolyStore));
        store->arg = node;
        store->poly = copyPoly((yyvsp[(3) - (3)].pObj).poly);
        store->str = (yyvsp[(3) - (3)].pObj).str ? strdup((yyvsp[(3) - (3)].pObj).str) : NULL;
        store->next = argPolyStore;
        argPolyStore = store;
        
        node->poly = (PolyNode*)(yyvsp[(1) - (3)].argList); 
        (yyval.argList) = node;
    ;}
    break;


/* Line 1267 of yacc.c.  */
#line 1840 "oguz.ozbal-hw3.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


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
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
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

  /* Else will try to reuse look-ahead token after shifting the error
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
      if (yyn != YYPACT_NINF)
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

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


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

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
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
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


#line 429 "oguz.ozbal-hw3.y"


/* --- IMPLEMENTATION --- */

void clearArgStore() {
    ArgPolyStore *store = argPolyStore;
    while (store) {
        ArgPolyStore *next = store->next;
        // poly'yi temizle
        if (store->poly) {
            Term *t = store->poly->head;
            while (t) {
                Term *tnext = t->next;
                PolyVar *v = t->vars;
                while (v) {
                    PolyVar *vnext = v->next;
                    free(v);
                    v = vnext;
                }
                free(t);
                t = tnext;
            }
            free(store->poly);
        }
        if (store->str) free(store->str);
        free(store);
        store = next;
    }
    argPolyStore = NULL;
}

Fraction makeFrac(int n, int d) { Fraction f = {n, d}; return simplifyFrac(f); }
int gcd(int a, int b) { return b == 0 ? a : gcd(b, a % b); }
Fraction simplifyFrac(Fraction f) {
    if (f.den == 0) { f.den = 1; return f; }
    int common = gcd(abs(f.num), abs(f.den));
    if (common == 0) common = 1;
    f.num /= common; f.den /= common;
    if (f.den < 0) { f.num = -f.num; f.den = -f.den; }
    return f;
}
Fraction addFrac(Fraction a, Fraction b) {
    return simplifyFrac((Fraction){a.num*b.den + b.num*a.den, a.den*b.den});
}
Fraction mulFrac(Fraction a, Fraction b) {
    return simplifyFrac((Fraction){a.num*b.num, a.den*b.den});
}

PolyNode* createPolyFromNum(int n) {
    PolyNode *p = malloc(sizeof(PolyNode));
    Term *t = malloc(sizeof(Term));
    t->coeff = makeFrac(n, 1);
    t->vars = NULL; t->next = NULL;
    p->head = t;
    return p;
}

PolyNode* createPolyFromVar(char *name, int line) {
    if (!name || !name[0]) return createPolyFromNum(0);

    PolyNode *p = malloc(sizeof(PolyNode));
    Term *t = malloc(sizeof(Term));
    t->coeff = makeFrac(1, 1);
    
    PolyVar *v = malloc(sizeof(PolyVar));
    v->name = name[0]; 
    v->power = 1; 
    v->line = line; 
    v->next = NULL;
    
    t->vars = v; 
    t->next = NULL;
    p->head = t;
    return p;
}

PolyVar* copyVars(PolyVar *v) {
    if(!v) return NULL;
    PolyVar *n = malloc(sizeof(PolyVar));
    n->name = v->name; n->power = v->power; 
    n->line = v->line; 
    n->next = copyVars(v->next);
    return n;
}

Term* copyTerm(Term *t) {
    if(!t) return NULL;
    Term *nt = malloc(sizeof(Term));
    nt->coeff = t->coeff;
    nt->vars = copyVars(t->vars);
    nt->next = NULL;
    return nt;
}

PolyNode* copyPoly(PolyNode *p) {
    if(!p) return NULL;
    if(!p->head) return createPolyFromNum(0);
    
    PolyNode *n = malloc(sizeof(PolyNode));
    n->head = NULL;
    Term **tail = &n->head;
    
    for (Term *t = p->head; t; t = t->next) {
        Term *newTerm = copyTerm(t);
        *tail = newTerm;
        tail = &newTerm->next;
    }
    return n;
}

PolyNode* addPoly(PolyNode *p1, PolyNode *p2, int subtract) {
    if(!p1 && !p2) return createPolyFromNum(0);
    if(!p1) return copyPoly(p2);
    if(!p2) return copyPoly(p1);
    
    PolyNode *res = malloc(sizeof(PolyNode));
    res->head = NULL;
    Term **tail = &res->head;
    
    // p1'in terimlerini ekle
    for (Term *t = p1->head; t; t = t->next) {
        Term *newTerm = copyTerm(t);
        *tail = newTerm;
        tail = &newTerm->next;
    }
    
    // p2'nin terimlerini ekle (subtract ise işaretini değiştir)
    for (Term *t = p2->head; t; t = t->next) {
        Term *newTerm = copyTerm(t);
        if (subtract) {
            newTerm->coeff.num = -newTerm->coeff.num;
        }
        *tail = newTerm;
        tail = &newTerm->next;
    }
    
    return res;
}

PolyVar* mergeVars(PolyVar *v1, PolyVar *v2) {
    PolyVar *res = copyVars(v1);
    
    for (PolyVar *v2_curr = v2; v2_curr; v2_curr = v2_curr->next) {
        PolyVar *res_curr = res;
        PolyVar *prev = NULL;
        int found = 0;
        
        while (res_curr) {
            if (res_curr->name == v2_curr->name) {
                res_curr->power += v2_curr->power;
                found = 1;
                break;
            }
            prev = res_curr;
            res_curr = res_curr->next;
        }
        
        if (!found) {
            PolyVar *newVar = malloc(sizeof(PolyVar));
            newVar->name = v2_curr->name;
            newVar->power = v2_curr->power;
            newVar->line = v2_curr->line;
            newVar->next = NULL;
            
            if (prev) {
                prev->next = newVar;
            } else {
                res = newVar;
            }
        }
    }
    return res;
}

PolyNode* mulPoly(PolyNode *p1, PolyNode *p2) {
    if(!p1 || !p2) return createPolyFromNum(0);
    if(!p1->head || !p2->head) return createPolyFromNum(0);
    
    PolyNode *res = malloc(sizeof(PolyNode)); 
    res->head = NULL;
    Term **tail = &res->head;
    
    for(Term *t1 = p1->head; t1; t1 = t1->next) {
        for(Term *t2 = p2->head; t2; t2 = t2->next) {
            Term *nt = malloc(sizeof(Term));
            nt->coeff = mulFrac(t1->coeff, t2->coeff);
            nt->vars = mergeVars(t1->vars, t2->vars);
            nt->next = NULL;
            *tail = nt;
            tail = &nt->next;
        }
    }
    return res;
}

PolyNode* powerPoly(PolyNode *p, int pow) {
    if(!p || !p->head) return createPolyFromNum(0);
    if(pow == 0) return createPolyFromNum(1);
    if(pow < 0) return createPolyFromNum(0);
    
    PolyNode *res = copyPoly(p);
    for(int i = 1; i < pow; i++) {
        PolyNode *tmp = mulPoly(res, p);
        // Eski res'i temizle
        Term *t = res->head;
        while(t) {
            Term *next = t->next;
            PolyVar *v = t->vars;
            while(v) {
                PolyVar *nextVar = v->next;
                free(v);
                v = nextVar;
            }
            free(t);
            t = next;
        }
        free(res);
        res = tmp;
    }
    return res;
}

PolyNode* derivePoly(PolyNode *p, char var, int order) {
    if (!p || !p->head) return createPolyFromNum(0);
    if (order <= 0) return copyPoly(p);
    
    // Bir kez türev al
    PolyNode *result = malloc(sizeof(PolyNode));
    result->head = NULL;
    Term **tail = &result->head;
    
    for (Term *t = p->head; t; t = t->next) {
        // Bu terimde 'var' değişkenini bul
        int varPower = 0;
        for (PolyVar *v = t->vars; v; v = v->next) {
            if (v->name == var) {
                varPower = v->power;
                break;
            }
        }
        
        // Eğer değişken yoksa veya üssü 0 ise, türev 0
        if (varPower == 0) continue;
        
        // Yeni terim oluştur: coeff * power * var^(power-1) * diğer_değişkenler
        Term *newTerm = malloc(sizeof(Term));
        newTerm->coeff = mulFrac(t->coeff, makeFrac(varPower, 1));
        newTerm->vars = NULL;
        newTerm->next = NULL;
        
        // Değişkenleri kopyala (türevi alınan değişkenin üssünü 1 azalt)
        PolyVar **varTail = &newTerm->vars;
        for (PolyVar *v = t->vars; v; v = v->next) {
            if (v->name == var) {
                // Üssü 1 azalt, 0 olursa ekleme
                if (v->power > 1) {
                    PolyVar *newVar = malloc(sizeof(PolyVar));
                    newVar->name = v->name;
                    newVar->power = v->power - 1;
                    newVar->line = v->line;
                    newVar->next = NULL;
                    *varTail = newVar;
                    varTail = &newVar->next;
                }
            } else {
                // Diğer değişkenleri aynen kopyala
                PolyVar *newVar = malloc(sizeof(PolyVar));
                newVar->name = v->name;
                newVar->power = v->power;
                newVar->line = v->line;
                newVar->next = NULL;
                *varTail = newVar;
                varTail = &newVar->next;
            }
        }
        
        *tail = newTerm;
        tail = &newTerm->next;
    }
    
    if (!result->head) {
        free(result);
        result = createPolyFromNum(0);
    }
    
    // Eğer order > 1 ise, recursive olarak devam et
    if (order > 1) {
        PolyNode *nextDeriv = derivePoly(result, var, order - 1);
        // result'u temizle
        Term *t = result->head;
        while (t) {
            Term *next = t->next;
            PolyVar *v = t->vars;
            while (v) {
                PolyVar *nextVar = v->next;
                free(v);
                v = nextVar;
            }
            free(t);
            t = next;
        }
        free(result);
        return nextDeriv;
    }
    
    return result;
}

PolyNode* integratePoly(PolyNode *p, char var, int order) {
    if (!p || !p->head) return createPolyFromNum(0);
    if (order <= 0) return copyPoly(p);
    
    // Bir kez integral al
    PolyNode *result = malloc(sizeof(PolyNode));
    result->head = NULL;
    Term **tail = &result->head;
    
    for (Term *t = p->head; t; t = t->next) {
        // Bu terimde 'var' değişkeninin üssünü bul
        int varPower = 0;
        int hasVar = 0;
        for (PolyVar *v = t->vars; v; v = v->next) {
            if (v->name == var) {
                varPower = v->power;
                hasVar = 1;
                break;
            }
        }
        
        // Yeni üs = varPower + 1
        int newPower = varPower + 1;
        
        // Yeni terim oluştur: coeff / newPower * var^newPower * diğer_değişkenler
        Term *newTerm = malloc(sizeof(Term));
        newTerm->coeff = mulFrac(t->coeff, makeFrac(1, newPower));
        newTerm->vars = NULL;
        newTerm->next = NULL;
        
        // Değişkenleri kopyala
        PolyVar **varTail = &newTerm->vars;
        int varAdded = 0;
        
        for (PolyVar *v = t->vars; v; v = v->next) {
            PolyVar *newVar = malloc(sizeof(PolyVar));
            newVar->name = v->name;
            newVar->line = v->line;
            newVar->next = NULL;
            
            if (v->name == var) {
                // Üssü 1 artır
                newVar->power = v->power + 1;
                varAdded = 1;
            } else {
                newVar->power = v->power;
            }
            
            *varTail = newVar;
            varTail = &newVar->next;
        }
        
        // Eğer değişken yoksa, yeni değişken ekle
        if (!hasVar) {
            PolyVar *newVar = malloc(sizeof(PolyVar));
            newVar->name = var;
            newVar->power = 1;
            newVar->line = 0;
            newVar->next = NULL;
            *varTail = newVar;
        }
        
        *tail = newTerm;
        tail = &newTerm->next;
    }
    
    if (!result->head) {
        free(result);
        result = createPolyFromNum(0);
    }
    
    // Eğer order > 1 ise, recursive olarak devam et
    if (order > 1) {
        PolyNode *nextInteg = integratePoly(result, var, order - 1);
        // result'u temizle
        Term *t = result->head;
        while (t) {
            Term *next = t->next;
            PolyVar *v = t->vars;
            while (v) {
                PolyVar *nextVar = v->next;
                free(v);
                v = nextVar;
            }
            free(t);
            t = next;
        }
        free(result);
        return nextInteg;
    }
    
    return result;
}

PolyNode* substituteFunc(FuncNode *fn, int argCount) {
    if (!fn || !fn->body || !fn->body->head) return createPolyFromNum(0);
    
    // Argümanları diziye al (store ters sırada, düzeltmemiz lazım)
    PolyNode *argPolys[256];
    int idx = 0;
    ArgPolyStore *store = argPolyStore;
    while (store && idx < 256) {
        argPolys[idx++] = store->poly;
        store = store->next;
    }
    
    // Diziyi ters çevir (ilk argüman index 0'da olmalı)
    for (int i = 0; i < idx / 2; i++) {
        PolyNode *temp = argPolys[i];
        argPolys[i] = argPolys[idx - 1 - i];
        argPolys[idx - 1 - i] = temp;
    }
    
    // Parametre-argüman eşleştirmesi
    PolyNode *paramMap[256];
    for (int i = 0; i < 256; i++) paramMap[i] = NULL;
    
    VarNode *param = fn->params;
    int paramIdx = 0;
    while (param && paramIdx < idx) {
        if (param->name && strlen(param->name) > 0) {
            char paramName = param->name[0];
            paramMap[(unsigned char)paramName] = argPolys[paramIdx];
        }
        param = param->next;
        paramIdx++;
    }
    
    // Substitution işlemi
    PolyNode *result = malloc(sizeof(PolyNode));
    result->head = NULL;
    Term **tail = &result->head;
    
    for (Term *origTerm = fn->body->head; origTerm; origTerm = origTerm->next) {
        // Eğer origTerm'de değişken yoksa (sabit terim)
        if (!origTerm->vars) {
            Term *newTerm = malloc(sizeof(Term));
            newTerm->coeff = origTerm->coeff;
            newTerm->vars = NULL;
            newTerm->next = NULL;
            *tail = newTerm;
            tail = &newTerm->next;
            continue;
        }
        
        // Her terim için: coeff * (var1^pow1) * (var2^pow2) * ...
        // Başlangıç: sadece katsayı ile başla
        PolyNode *termResult = createPolyFromNum(origTerm->coeff.num);
        termResult->head->coeff.den = origTerm->coeff.den;
        
        for (PolyVar *v = origTerm->vars; v; v = v->next) {
            PolyNode *varPoly = NULL;
            
            if (paramMap[(unsigned char)v->name] && paramMap[(unsigned char)v->name]->head) {
                // Bu değişken bir parametre, yerine koy
                PolyNode *argPoly = paramMap[(unsigned char)v->name];
                
                // argPoly'nin KOPYASINI al ve üssünü uygula
                PolyNode *argCopy = copyPoly(argPoly);
                if (v->power == 1) {
                    varPoly = argCopy;
                } else {
                    varPoly = powerPoly(argCopy, v->power);
                    // argCopy'yi temizle (powerPoly yeni poly döndürür)
                    if (varPoly != argCopy) {
                        Term *t = argCopy->head;
                        while (t) {
                            Term *next = t->next;
                            PolyVar *pv = t->vars;
                            while (pv) {
                                PolyVar *nextVar = pv->next;
                                free(pv);
                                pv = nextVar;
                            }
                            free(t);
                            t = next;
                        }
                        free(argCopy);
                    }
                }
            } else {
                // Parametre değil, değişken olarak kalsın
                varPoly = malloc(sizeof(PolyNode));
                Term *varTerm = malloc(sizeof(Term));
                varTerm->coeff = makeFrac(1, 1);
                PolyVar *newVar = malloc(sizeof(PolyVar));
                newVar->name = v->name;
                newVar->power = v->power;
                newVar->line = v->line;
                newVar->next = NULL;
                varTerm->vars = newVar;
                varTerm->next = NULL;
                varPoly->head = varTerm;
            }
            
            if (!varPoly || !varPoly->head) {
                if (varPoly) free(varPoly);
                varPoly = createPolyFromNum(1);
            }
            
            // termResult ile varPoly'yi çarp
            PolyNode *temp = mulPoly(termResult, varPoly);
            
            // Eski termResult'u temizle
            if (termResult) {
                Term *t = termResult->head;
                while (t) {
                    Term *next = t->next;
                    PolyVar *pv = t->vars;
                    while (pv) {
                        PolyVar *nextVar = pv->next;
                        free(pv);
                        pv = nextVar;
                    }
                    free(t);
                    t = next;
                }
                free(termResult);
            }
            
            // varPoly'yi temizle
            if (varPoly) {
                Term *t = varPoly->head;
                while (t) {
                    Term *next = t->next;
                    PolyVar *pv = t->vars;
                    while (pv) {
                        PolyVar *nextVar = pv->next;
                        free(pv);
                        pv = nextVar;
                    }
                    free(t);
                    t = next;
                }
                free(varPoly);
            }
            
            termResult = temp;
        }
        
        // termResult'un terimlerini result'a ekle
        if (termResult && termResult->head) {
            for (Term *t = termResult->head; t; ) {
                Term *next = t->next;
                t->next = NULL;
                *tail = t;
                tail = &t->next;
                t = next;
            }
            free(termResult);
        }
    }
    
    if (!result->head) {
        free(result);
        return createPolyFromNum(0);
    }
    
    return result;
}

void addError(int line, const char *msg) {
    hasSemanticErrors = 1;
    ErrorNode *n = malloc(sizeof(ErrorNode));
    char b[128]; sprintf(b, "%d_%s", line, msg);
    n->msg = strdup(b);
    n->next = errsHead;
    errsHead = n;
}

void addOutput(char *lhs, PolyNode *rhs) {
    if(hasSemanticErrors) return;
    OutputNode *n = malloc(sizeof(OutputNode));
    n->lhs = lhs ? strdup(lhs) : strdup("expr");
    n->rhs = rhs;
    n->next = NULL;
    if(outTail) { outTail->next = n; outTail = n; }
    else { outHead = n; outTail = n; }
}

void printSortedErrors() {
    if(!errsHead) return;
    
    int count = 0;
    ErrorNode *curr = errsHead;
    while(curr) { count++; curr = curr->next; }
    
    char **msgs = malloc(sizeof(char*) * count);
    curr = errsHead;
    int i = 0;
    while(curr) { msgs[i++] = curr->msg; curr = curr->next; }
    
    for(int i = 0; i < count - 1; i++) {
        for(int j = 0; j < count - i - 1; j++) {
            int line1 = 0, line2 = 0;
            sscanf(msgs[j], "%d", &line1);
            sscanf(msgs[j+1], "%d", &line2);
            
            if(line1 > line2 || (line1 == line2 && strcmp(msgs[j], msgs[j+1]) > 0)) {
                char *temp = msgs[j];
                msgs[j] = msgs[j+1];
                msgs[j+1] = temp;
            }
        }
    }
    
    for(int i = 0; i < count; i++) {
        if(i > 0 && strcmp(msgs[i], msgs[i-1]) == 0) {
            if(strstr(msgs[i], "MISSING_FUNCTION_NAME") != NULL) {
                printf("%s\n", msgs[i]);
            }
        } else {
            if(strstr(msgs[i], "UNDEFINED_FUNCTION_(") != NULL) {
                char funcName[100];
                sscanf(msgs[i], "%*d_UNDEFINED_FUNCTION_(%[^)])", funcName);
                int shouldPrint = 1;
                for(int j = 0; j < i; j++) {
                    if(strstr(msgs[j], "UNDEFINED_FUNCTION_(") != NULL) {
                        char earlierFuncName[100];
                        sscanf(msgs[j], "%*d_UNDEFINED_FUNCTION_(%[^)])", earlierFuncName);
                        if(strcmp(funcName, earlierFuncName) == 0) {
                            shouldPrint = 0;
                            break;
                        }
                    }
                }
                if(shouldPrint) {
                    printf("%s\n", msgs[i]);
                }
            } else {
                printf("%s\n", msgs[i]);
            }
        }
    }
    free(msgs);
}

void printReport() {
    OutputNode *curr = outHead;
    while(curr) {
        char *cleanLhs = removeWhitespace(curr->lhs);
        
        PolyNode *simplified = curr->rhs ? simplifyPoly(curr->rhs) : createPolyFromNum(0);
        char *formatted = formatPoly(simplified);
        
        printf("%s=%s\n", cleanLhs, formatted);
        
        free(cleanLhs);
        free(formatted);
        curr = curr->next;
    }
}

void addFunction(char *name, VarNode *params, PolyNode *body) {
    FuncNode *f = malloc(sizeof(FuncNode));
    f->name = strdup(name); 
    f->params = params; 
    f->body = body ? copyPoly(body) : NULL; 
    f->paramCount = countVars(params);
    f->next = funcsHead; funcsHead = f;
}

FuncNode* getFunction(char *name) {
    FuncNode *f = funcsHead;
    while(f) { if(strcmp(f->name, name)==0) return f; f = f->next; }
    return NULL;
}

FuncNode* getFunctionWithArity(char *name, int arity) {
    FuncNode *f = funcsHead;
    while(f) { 
        if(strcmp(f->name, name)==0 && f->paramCount == arity) return f; 
        f = f->next; 
    }
    return NULL;
}

int isFunctionRedefined(char *name) {
    FuncNode *f = funcsHead;
    int count = 0;
    while(f) { 
        if(strcmp(f->name, name)==0) count++; 
        f = f->next; 
    }
    return count > 1;
}

VarNode* createVarNode(char *name) { 
    VarNode* n = malloc(sizeof(VarNode)); 
    n->name = strdup(name); 
    n->next = NULL; 
    return n; 
}

VarNode* appendVarNode(VarNode *h, VarNode *n) { 
    if(!h) return n; 
    VarNode* c = h; 
    while(c->next) c = c->next; 
    c->next = n; 
    return h; 
}

int countVars(VarNode *h) { 
    int c = 0; 
    while(h) { c++; h = h->next; } 
    return c; 
}

char* concat(const char *s1, const char *s2, const char *s3) {
    if (!s1) s1 = "";
    if (!s2) s2 = "";
    if (!s3) s3 = "";
    char *res = malloc(strlen(s1)+strlen(s2)+strlen(s3)+1);
    sprintf(res, "%s%s%s", s1, s2, s3); 
    return res;
}

char* buildFuncCallString(char *funcName, int argCount) {
    if (!funcName) return strdup("error");
    
    // Store'dan string'leri topla
    char *argStrings[256];
    int idx = 0;
    ArgPolyStore *store = argPolyStore;
    while (store && idx < 256) {
        argStrings[idx++] = store->str ? store->str : "?";
        store = store->next;
    }
    
    // Diziyi ters çevir
    for (int i = 0; i < idx / 2; i++) {
        char *temp = argStrings[i];
        argStrings[i] = argStrings[idx - 1 - i];
        argStrings[idx - 1 - i] = temp;
    }
    
    if (idx == 0) {
        return concat(funcName, "()", "");
    }
    
    // Argüman string'ini oluştur
    char *argStr = strdup(argStrings[0]);
    for (int i = 1; i < idx; i++) {
        char *temp = concat(argStr, ",", argStrings[i]);
        free(argStr);
        argStr = temp;
    }
    
    char *result = concat(funcName, "(", "");
    char *result2 = concat(result, argStr, ")");
    free(result);
    free(argStr);
    return result2;
}

PolyVar* sortVars(PolyVar *vars) {
    if (!vars) return NULL;
    if (!vars->next) return copyVars(vars);
    
    PolyVar *arr[26];
    int count = 0;
    for (PolyVar *v = vars; v && count < 26; v = v->next) {
        arr[count++] = v;
    }
    
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (arr[j]->name > arr[j+1]->name) {
                PolyVar *temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
    
    PolyVar *result = NULL;
    PolyVar **tail = &result;
    for (int i = 0; i < count; i++) {
        PolyVar *newVar = malloc(sizeof(PolyVar));
        newVar->name = arr[i]->name;
        newVar->power = arr[i]->power;
        newVar->line = arr[i]->line;
        newVar->next = NULL;
        *tail = newVar;
        tail = &newVar->next;
    }
    
    return result;
}

int varsEqual(PolyVar *v1, PolyVar *v2) {
    while (v1 && v2) {
        if (v1->name != v2->name || v1->power != v2->power) return 0;
        v1 = v1->next;
        v2 = v2->next;
    }
    return (v1 == NULL && v2 == NULL);
}

PolyNode* simplifyPoly(PolyNode *p) {
    if (!p) return createPolyFromNum(0);
    if (!p->head) return createPolyFromNum(0);
    
    PolyNode *result = malloc(sizeof(PolyNode));
    result->head = NULL;
    Term **tail = &result->head;
    
    for (Term *t = p->head; t; t = t->next) {
        // Sıfır katsayılı terimleri atla
        if (t->coeff.num == 0) continue;
        
        // Değişkenleri sırala
        PolyVar *sortedVars = sortVars(t->vars);
        
        // Aynı değişkenlere sahip mevcut terim var mı?
        Term *existing = result->head;
        Term *prev = NULL;
        int found = 0;
        
        while (existing) {
            if (varsEqual(sortedVars, existing->vars)) {
                existing->coeff = addFrac(existing->coeff, t->coeff);
                found = 1;
                
                // Katsayı sıfır olduysa terimi sil
                if (existing->coeff.num == 0) {
                    if (prev) prev->next = existing->next;
                    else result->head = existing->next;
                }
                
                // sortedVars'ı temizle
                PolyVar *v = sortedVars;
                while (v) {
                    PolyVar *nextVar = v->next;
                    free(v);
                    v = nextVar;
                }
                break;
            }
            prev = existing;
            existing = existing->next;
        }
        
        if (!found) {
            Term *newTerm = malloc(sizeof(Term));
            newTerm->coeff = t->coeff;
            newTerm->vars = sortedVars;
            newTerm->next = NULL;
            *tail = newTerm;
            tail = &newTerm->next;
        }
    }
    
    if (!result->head) {
        free(result);
        return createPolyFromNum(0);
    }
    
    return result;
}

int compareTerms(Term *t1, Term *t2) {
    int powers1[26] = {0}, powers2[26] = {0};
    
    for (PolyVar *v = t1->vars; v; v = v->next) {
        if (v->name >= 'a' && v->name <= 'z') {
            powers1[v->name - 'a'] += v->power;
        }
    }
    
    for (PolyVar *v = t2->vars; v; v = v->next) {
        if (v->name >= 'a' && v->name <= 'z') {
            powers2[v->name - 'a'] += v->power;
        }
    }
    
    for (int i = 0; i < 26; i++) {
        if (powers1[i] > powers2[i]) return -1;
        if (powers1[i] < powers2[i]) return 1;
    }
    return 0;
}

char* formatTerm(Term *t) {
    if (!t || t->coeff.num == 0) return strdup("");
    
    char buf[1000] = "";
    
    if (t->coeff.den == 1) {
        if (t->coeff.num == -1 && t->vars) {
            strcat(buf, "-");
        } else if (t->coeff.num != 1 || !t->vars) {
            char num[32];
            sprintf(num, "%d", t->coeff.num);
            strcat(buf, num);
        }
    } else {
        char frac[32];
        sprintf(frac, "%d/%d", t->coeff.num, t->coeff.den);
        strcat(buf, frac);
    }
    
    for (PolyVar *v = t->vars; v; v = v->next) {
        if (v->power == 0) continue; 
        char var[10];
        if (v->power == 1) {
            sprintf(var, "%c", v->name);
        } else {
            sprintf(var, "%c^%d", v->name, v->power);
        }
        strcat(buf, var);
    }
    
    return strdup(buf);
}

char* formatPoly(PolyNode *p) {
    if (!p || !p->head) return strdup("0");
    
    int count = 0;
    Term *t = p->head;
    while (t) { count++; t = t->next; }
    
    Term **terms = malloc(sizeof(Term*) * count);
    int i = 0;
    for (t = p->head; t; t = t->next) {
        terms[i++] = t;
    }
    
    // Terimleri sırala
    for (i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (compareTerms(terms[j], terms[j+1]) > 0) {
                Term *temp = terms[j];
                terms[j] = terms[j+1];
                terms[j+1] = temp;
            }
        }
    }
    
    char *result = strdup("");
    int first = 1;
    
    for (i = 0; i < count; i++) {
        if (terms[i]->coeff.num == 0) continue;
        
        char *termStr = formatTerm(terms[i]);
        if (strlen(termStr) == 0) {
            free(termStr);
            continue;
        }
        
        if (first) {
            free(result);
            result = termStr;
            first = 0;
        } else {
            if (terms[i]->coeff.num > 0) {
                char *temp = concat(result, "+", termStr);
                free(result);
                free(termStr);
                result = temp;
            } else {
                char *temp = concat(result, "", termStr);
                free(result);
                free(termStr);
                result = temp;
            }
        }
    }
    
    free(terms);
    if (strlen(result) == 0) {
        free(result);
        return strdup("0");
    }
    return result;
}

char* removeWhitespace(const char *str) {
    if (!str) return strdup("");
    int len = strlen(str);
    char *result = malloc(len + 1);
    int j = 0;
    for (int i = 0; i < len; i++) {
        if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n' && str[i] != '\r') {
            result[j++] = str[i];
        }
    }
    result[j] = '\0';
    return result;
}

int main() {
    yyparse();
    if(hasSemanticErrors) {
        printSortedErrors();
    } else {
        printReport();
    }
    return 0;
}

