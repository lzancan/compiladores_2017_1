/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2011 Free Software Foundation, Inc.
   
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
#define YYBISON_VERSION "2.5"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 268 of yacc.c  */
#line 1 "parser.y"

	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include "hash.h"
	#include "asm.h"
	
	ASTREE* root;





/* Line 268 of yacc.c  */
#line 85 "y.tab.c"

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


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     KW_TO = 258,
     KW_BYTE = 259,
     KW_SHORT = 260,
     KW_LONG = 261,
     KW_FLOAT = 262,
     KW_DOUBLE = 263,
     KW_WHEN = 264,
     KW_THEN = 265,
     KW_ELSE = 266,
     KW_WHILE = 267,
     KW_FOR = 268,
     KW_READ = 269,
     KW_RETURN = 270,
     KW_PRINT = 271,
     OPERATOR_LE = 272,
     OPERATOR_GE = 273,
     OPERATOR_EQ = 274,
     OPERATOR_NE = 275,
     OPERATOR_AND = 276,
     OPERATOR_OR = 277,
     TK_IDENTIFIER = 278,
     LIT_INTEGER = 279,
     LIT_REAL = 280,
     LIT_CHAR = 281,
     LIT_STRING = 282,
     TOKEN_ERROR = 283
   };
#endif
/* Tokens.  */
#define KW_TO 258
#define KW_BYTE 259
#define KW_SHORT 260
#define KW_LONG 261
#define KW_FLOAT 262
#define KW_DOUBLE 263
#define KW_WHEN 264
#define KW_THEN 265
#define KW_ELSE 266
#define KW_WHILE 267
#define KW_FOR 268
#define KW_READ 269
#define KW_RETURN 270
#define KW_PRINT 271
#define OPERATOR_LE 272
#define OPERATOR_GE 273
#define OPERATOR_EQ 274
#define OPERATOR_NE 275
#define OPERATOR_AND 276
#define OPERATOR_OR 277
#define TK_IDENTIFIER 278
#define LIT_INTEGER 279
#define LIT_REAL 280
#define LIT_CHAR 281
#define LIT_STRING 282
#define TOKEN_ERROR 283




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 293 of yacc.c  */
#line 14 "parser.y"
 
	HASH_NODE* symbol; 
	ASTREE* astree; 
      


/* Line 293 of yacc.c  */
#line 184 "y.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 343 of yacc.c  */
#line 196 "y.tab.c"

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
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  16
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   342

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  47
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  32
/* YYNRULES -- Number of rules.  */
#define YYNRULES  79
/* YYNRULES -- Number of states.  */
#define YYNSTATES  145

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   283

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    46,     2,    45,     2,     2,     2,     2,
      38,    39,    33,    31,    42,    32,     2,    34,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    41,    40,
      29,    35,    30,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    36,     2,    37,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    43,     2,    44,     2,     2,     2,     2,
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
      25,    26,    27,    28
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     5,     7,    10,    11,    13,    16,    21,
      23,    28,    30,    32,    34,    37,    38,    40,    42,    44,
      46,    48,    51,    57,    61,    62,    67,    68,    71,    75,
      79,    80,    82,    84,    86,    88,    90,    92,    93,    97,
     103,   106,   109,   112,   114,   116,   118,   121,   123,   126,
     131,   133,   135,   137,   141,   145,   149,   153,   157,   161,
     165,   169,   173,   177,   181,   185,   189,   193,   196,   199,
     200,   204,   205,   207,   209,   211,   213,   220,   229,   235
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      48,     0,    -1,    49,    -1,    50,    -1,    51,    50,    -1,
      -1,    57,    -1,    52,    40,    -1,    23,    41,    56,    53,
      -1,    54,    -1,    36,    24,    37,    55,    -1,    24,    -1,
      25,    -1,    26,    -1,    54,    55,    -1,    -1,     4,    -1,
       5,    -1,     6,    -1,     7,    -1,     8,    -1,    58,    61,
      -1,    56,    23,    38,    59,    39,    -1,    56,    23,    60,
      -1,    -1,    42,    56,    23,    60,    -1,    -1,    64,    40,
      -1,    43,    63,    44,    -1,    64,    40,    63,    -1,    -1,
      65,    -1,    74,    -1,    66,    -1,    67,    -1,    70,    -1,
      62,    -1,    -1,    23,    35,    71,    -1,    23,    45,    71,
      35,    71,    -1,    14,    23,    -1,    16,    68,    -1,    69,
      68,    -1,    69,    -1,    27,    -1,    71,    -1,    15,    71,
      -1,    23,    -1,    23,    71,    -1,    23,    38,    72,    39,
      -1,    24,    -1,    25,    -1,    26,    -1,    38,    71,    39,
      -1,    36,    71,    37,    -1,    71,    31,    71,    -1,    71,
      32,    71,    -1,    71,    33,    71,    -1,    71,    34,    71,
      -1,    71,    30,    71,    -1,    71,    29,    71,    -1,    71,
      17,    71,    -1,    71,    18,    71,    -1,    71,    19,    71,
      -1,    71,    20,    71,    -1,    71,    21,    71,    -1,    71,
      22,    71,    -1,    46,    71,    -1,    71,    73,    -1,    -1,
      42,    71,    73,    -1,    -1,    75,    -1,    76,    -1,    78,
      -1,    77,    -1,     9,    38,    71,    39,    10,    64,    -1,
       9,    38,    71,    39,    10,    64,    11,    64,    -1,    12,
      38,    71,    39,    64,    -1,    13,    38,    23,    35,    71,
       3,    71,    39,    64,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    95,    95,   100,   102,   103,   105,   106,   108,   115,
     116,   118,   119,   120,   122,   125,   127,   128,   129,   130,
     131,   133,   135,   140,   143,   145,   148,   150,   152,   154,
     155,   157,   158,   159,   160,   161,   162,   163,   165,   168,
     173,   175,   177,   180,   184,   186,   190,   192,   203,   210,
     220,   221,   222,   223,   224,   225,   226,   227,   228,   229,
     230,   231,   232,   233,   234,   235,   236,   237,   240,   242,
     244,   245,   247,   248,   249,   250,   252,   256,   259,   263
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "KW_TO", "KW_BYTE", "KW_SHORT",
  "KW_LONG", "KW_FLOAT", "KW_DOUBLE", "KW_WHEN", "KW_THEN", "KW_ELSE",
  "KW_WHILE", "KW_FOR", "KW_READ", "KW_RETURN", "KW_PRINT", "OPERATOR_LE",
  "OPERATOR_GE", "OPERATOR_EQ", "OPERATOR_NE", "OPERATOR_AND",
  "OPERATOR_OR", "TK_IDENTIFIER", "LIT_INTEGER", "LIT_REAL", "LIT_CHAR",
  "LIT_STRING", "TOKEN_ERROR", "'<'", "'>'", "'+'", "'-'", "'*'", "'/'",
  "'='", "'['", "']'", "'('", "')'", "';'", "':'", "','", "'{'", "'}'",
  "'#'", "'!'", "$accept", "P", "PROGRAMA", "DECLARACOES", "DECLARACAO",
  "VARIAVEL_GLOBAL", "VAR_GLOBAL_INIT_VEC", "VALOR",
  "VALOR_INICIALIZACAO_VETOR", "TIPO", "FUNCOES", "CABECALHO",
  "LISTA_PARAMETROS", "MAIS_PARAMETROS", "CORPO", "BLOCO_COMANDOS",
  "LISTA_COMANDOS", "COMANDO", "ATRIBUICAO", "READ", "PRINT",
  "LISTA_ELEMENTOS_PRINT", "ELEMENTO_PRINT", "RETURN", "EXPRESSAO",
  "LISTA_FUNCAO_PARAMETROS", "LISTA_FUNCAO_MAIS_PARAMETROS",
  "CONTROLE_FLUXO", "WHEN_THEN", "WHEN_THEN_ELSE", "WHILE", "FOR", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,    60,
      62,    43,    45,    42,    47,    61,    91,    93,    40,    41,
      59,    58,    44,   123,   125,    35,    33
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    47,    48,    49,    50,    50,    51,    51,    52,    53,
      53,    54,    54,    54,    55,    55,    56,    56,    56,    56,
      56,    57,    58,    59,    59,    60,    60,    61,    62,    63,
      63,    64,    64,    64,    64,    64,    64,    64,    65,    65,
      66,    67,    68,    68,    69,    69,    70,    71,    71,    71,
      71,    71,    71,    71,    71,    71,    71,    71,    71,    71,
      71,    71,    71,    71,    71,    71,    71,    71,    72,    72,
      73,    73,    74,    74,    74,    74,    75,    76,    77,    78
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     2,     0,     1,     2,     4,     1,
       4,     1,     1,     1,     2,     0,     1,     1,     1,     1,
       1,     2,     5,     3,     0,     4,     0,     2,     3,     3,
       0,     1,     1,     1,     1,     1,     1,     0,     3,     5,
       2,     2,     2,     1,     1,     1,     2,     1,     2,     4,
       1,     1,     1,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     2,     2,     0,
       3,     0,     1,     1,     1,     1,     6,     8,     5,     9
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       5,    16,    17,    18,    19,    20,     0,     0,     2,     3,
       5,     0,     0,     6,    37,     0,     1,     4,     7,     0,
       0,     0,     0,     0,     0,     0,     0,    30,    21,    36,
       0,    31,    33,    34,    35,    32,    72,    73,    75,    74,
       0,    24,     0,     0,     0,    40,    47,    50,    51,    52,
       0,     0,     0,    46,    44,    41,    43,    45,     0,     0,
       0,     0,    27,    11,    12,    13,     0,     8,     9,     0,
       0,     0,     0,     0,    69,    48,     0,     0,    67,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    42,    38,     0,    28,    30,     0,    26,    22,     0,
      37,     0,     0,     0,    54,    53,    61,    62,    63,    64,
      65,    66,    60,    59,    55,    56,    57,    58,     0,    29,
      15,     0,    23,    37,    78,     0,     0,    68,    49,    39,
      15,    10,     0,    76,     0,    71,    14,    26,    37,     0,
      70,    25,    77,    37,    79
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     7,     8,     9,    10,    11,    67,   130,   131,    12,
      13,    14,    70,   122,    28,    29,    60,    61,    31,    32,
      33,    55,    56,    34,    57,   103,   127,    35,    36,    37,
      38,    39
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -40
static const yytype_int16 yypact[] =
{
       8,   -40,   -40,   -40,   -40,   -40,   -39,     5,   -40,   -40,
       8,   -22,    16,   -40,    29,    42,   -40,   -40,   -40,   -16,
       2,    15,    17,    31,    51,    56,   -24,    -6,   -40,   -40,
      33,   -40,   -40,   -40,   -40,   -40,   -40,   -40,   -40,   -40,
      81,    42,    51,    51,    61,   -40,   146,   -40,   -40,   -40,
      51,    51,    51,   308,   -40,   -40,    56,   308,    51,    51,
      41,    48,   -40,   -40,   -40,   -40,    66,   -40,   -40,    68,
      54,   176,   199,    63,    51,   308,   268,   222,   308,    51,
      51,    51,    51,    51,    51,    51,    51,    51,    51,    51,
      51,   -40,   308,   289,   -40,    -6,    59,    57,   -40,    90,
      29,    51,   119,    62,   -40,   -40,    94,    94,    94,    94,
      37,    37,    94,    94,    -1,    -1,   -40,   -40,    51,   -40,
       0,    42,   -40,    29,   -40,   101,    51,   -40,   -40,   308,
       0,   -40,    85,   102,    51,   145,   -40,    57,    29,   245,
     -40,   -40,   -40,    29,   -40
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -40,   -40,   -40,   104,   -40,   -40,   -40,    72,    12,   -11,
     -40,   -40,   -40,     6,   -40,   -40,    49,   -14,   -40,   -40,
     -40,    89,   -40,   -40,   -23,   -40,    11,   -40,   -40,   -40,
     -40,   -40
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -38
static const yytype_int16 yytable[] =
{
      30,    53,    15,    20,    40,    16,    21,    22,    23,    24,
      25,    58,     1,     2,     3,     4,     5,    26,    18,    71,
      72,    59,    41,    75,    63,    64,    65,    76,    77,    78,
      69,     6,    89,    90,   -37,    92,    93,    27,    20,    19,
      42,    21,    22,    23,    24,    25,     1,     2,     3,     4,
       5,   102,    26,    43,    45,    44,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   116,   117,    87,    88,
      89,    90,    27,    62,    46,    47,    48,    49,   125,    46,
      47,    48,    49,    54,    73,    94,   124,    50,    95,    51,
      96,    97,    50,    98,    51,   129,   120,    52,   101,   121,
     123,   128,    52,   135,   134,    63,    64,    65,   137,   133,
     132,   139,    68,   138,    17,    83,    84,    66,    79,    80,
      81,    82,    83,    84,   142,    87,    88,    89,    90,   144,
      85,    86,    87,    88,    89,    90,    79,    80,    81,    82,
      83,    84,   136,   141,   119,    91,   140,     0,    85,    86,
      87,    88,    89,    90,     0,     0,     0,     0,   105,     0,
       0,   126,    79,    80,    81,    82,    83,    84,     0,    46,
      47,    48,    49,     0,    85,    86,    87,    88,    89,    90,
       0,     0,    50,     0,    74,     0,     0,   126,     0,     0,
       0,     0,    52,    79,    80,    81,    82,    83,    84,     0,
       0,     0,     0,     0,     0,    85,    86,    87,    88,    89,
      90,     0,     0,     0,     0,    99,    79,    80,    81,    82,
      83,    84,     0,     0,     0,     0,     0,     0,    85,    86,
      87,    88,    89,    90,     0,     0,     0,     0,   100,    79,
      80,    81,    82,    83,    84,     0,     0,     0,     0,     0,
       0,    85,    86,    87,    88,    89,    90,     0,     0,     0,
       0,   105,    79,    80,    81,    82,    83,    84,     0,     0,
       0,     0,     0,     0,    85,    86,    87,    88,    89,    90,
       0,     0,     0,     0,   143,    79,    80,    81,    82,    83,
      84,     0,     0,     0,     0,     0,     0,    85,    86,    87,
      88,    89,    90,     0,     0,   104,    79,    80,    81,    82,
      83,    84,     0,     0,     0,     0,     0,     0,    85,    86,
      87,    88,    89,    90,   118,    79,    80,    81,    82,    83,
      84,     0,     0,     0,     0,     0,     0,    85,    86,    87,
      88,    89,    90
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-40))

#define yytable_value_is_error(yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
      14,    24,    41,     9,    15,     0,    12,    13,    14,    15,
      16,    35,     4,     5,     6,     7,     8,    23,    40,    42,
      43,    45,    38,    46,    24,    25,    26,    50,    51,    52,
      41,    23,    33,    34,    40,    58,    59,    43,     9,    23,
      38,    12,    13,    14,    15,    16,     4,     5,     6,     7,
       8,    74,    23,    38,    23,    38,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    31,    32,
      33,    34,    43,    40,    23,    24,    25,    26,   101,    23,
      24,    25,    26,    27,    23,    44,   100,    36,    40,    38,
      24,    23,    36,    39,    38,   118,    37,    46,    35,    42,
      10,    39,    46,   126,     3,    24,    25,    26,    23,   123,
     121,   134,    40,    11,    10,    21,    22,    36,    17,    18,
      19,    20,    21,    22,   138,    31,    32,    33,    34,   143,
      29,    30,    31,    32,    33,    34,    17,    18,    19,    20,
      21,    22,   130,   137,    95,    56,   135,    -1,    29,    30,
      31,    32,    33,    34,    -1,    -1,    -1,    -1,    39,    -1,
      -1,    42,    17,    18,    19,    20,    21,    22,    -1,    23,
      24,    25,    26,    -1,    29,    30,    31,    32,    33,    34,
      -1,    -1,    36,    -1,    38,    -1,    -1,    42,    -1,    -1,
      -1,    -1,    46,    17,    18,    19,    20,    21,    22,    -1,
      -1,    -1,    -1,    -1,    -1,    29,    30,    31,    32,    33,
      34,    -1,    -1,    -1,    -1,    39,    17,    18,    19,    20,
      21,    22,    -1,    -1,    -1,    -1,    -1,    -1,    29,    30,
      31,    32,    33,    34,    -1,    -1,    -1,    -1,    39,    17,
      18,    19,    20,    21,    22,    -1,    -1,    -1,    -1,    -1,
      -1,    29,    30,    31,    32,    33,    34,    -1,    -1,    -1,
      -1,    39,    17,    18,    19,    20,    21,    22,    -1,    -1,
      -1,    -1,    -1,    -1,    29,    30,    31,    32,    33,    34,
      -1,    -1,    -1,    -1,    39,    17,    18,    19,    20,    21,
      22,    -1,    -1,    -1,    -1,    -1,    -1,    29,    30,    31,
      32,    33,    34,    -1,    -1,    37,    17,    18,    19,    20,
      21,    22,    -1,    -1,    -1,    -1,    -1,    -1,    29,    30,
      31,    32,    33,    34,    35,    17,    18,    19,    20,    21,
      22,    -1,    -1,    -1,    -1,    -1,    -1,    29,    30,    31,
      32,    33,    34
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     4,     5,     6,     7,     8,    23,    48,    49,    50,
      51,    52,    56,    57,    58,    41,     0,    50,    40,    23,
       9,    12,    13,    14,    15,    16,    23,    43,    61,    62,
      64,    65,    66,    67,    70,    74,    75,    76,    77,    78,
      56,    38,    38,    38,    38,    23,    23,    24,    25,    26,
      36,    38,    46,    71,    27,    68,    69,    71,    35,    45,
      63,    64,    40,    24,    25,    26,    36,    53,    54,    56,
      59,    71,    71,    23,    38,    71,    71,    71,    71,    17,
      18,    19,    20,    21,    22,    29,    30,    31,    32,    33,
      34,    68,    71,    71,    44,    40,    24,    23,    39,    39,
      39,    35,    71,    72,    37,    39,    71,    71,    71,    71,
      71,    71,    71,    71,    71,    71,    71,    71,    35,    63,
      37,    42,    60,    10,    64,    71,    42,    73,    39,    71,
      54,    55,    56,    64,     3,    71,    55,    23,    11,    71,
      73,    60,    64,    39,    64
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

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
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


/* This macro is provided for backward compatibility. */

#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
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
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
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
  YYSIZE_T yysize0 = yytnamerr (0, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  YYSIZE_T yysize1;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = 0;
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
                yysize1 = yysize + yytnamerr (0, yytname[yyx]);
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


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
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
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
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
  int yytoken;
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

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
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
        case 2:

/* Line 1806 of yacc.c  */
#line 95 "parser.y"
    {	 uncompile((yyvsp[(1) - (1)].astree));
			 tacPrintForward(tacReverse(tacGenerate((yyvsp[(1) - (1)].astree))));
			 asmGen(tacReverse(tacGenerate((yyvsp[(1) - (1)].astree))));	 
		   }
    break;

  case 3:

/* Line 1806 of yacc.c  */
#line 100 "parser.y"
    { (yyval.astree) = astreeCreate(ASTREE_PROGRAMA, NULL, (yyvsp[(1) - (1)].astree), 0, 0, 0);}
    break;

  case 4:

/* Line 1806 of yacc.c  */
#line 102 "parser.y"
    {(yyval.astree) = astreeCreate(ASTREE_DECLARACAO, NULL, (yyvsp[(1) - (2)].astree), (yyvsp[(2) - (2)].astree), 0, 0);}
    break;

  case 5:

/* Line 1806 of yacc.c  */
#line 103 "parser.y"
    { (yyval.astree) = 0; }
    break;

  case 6:

/* Line 1806 of yacc.c  */
#line 105 "parser.y"
    {(yyval.astree) = (yyvsp[(1) - (1)].astree);}
    break;

  case 7:

/* Line 1806 of yacc.c  */
#line 106 "parser.y"
    {(yyval.astree) = (yyvsp[(1) - (2)].astree);}
    break;

  case 8:

/* Line 1806 of yacc.c  */
#line 108 "parser.y"
    { if((yyvsp[(4) - (4)].astree)->type == ASTREE_VAR_GLOBAL_INIT_VEC){
									setNature_dataType(NATURE_VECTOR,(yyvsp[(1) - (4)].symbol),(yyvsp[(3) - (4)].astree));
								      } else 
									setNature_dataType(NATURE_ESCALAR,(yyvsp[(1) - (4)].symbol),(yyvsp[(3) - (4)].astree));
								      (yyval.astree) = astreeCreate(ASTREE_VAR_GLOBAL, (yyvsp[(1) - (4)].symbol), (yyvsp[(3) - (4)].astree), (yyvsp[(4) - (4)].astree), 0, 0);
								    }
    break;

  case 10:

/* Line 1806 of yacc.c  */
#line 116 "parser.y"
    { (yyval.astree) = astreeCreate(ASTREE_VAR_GLOBAL_INIT_VEC, (yyvsp[(2) - (4)].symbol), (yyvsp[(4) - (4)].astree), 0, 0, 0); testVectorInit((yyvsp[(4) - (4)].astree),atoi((yyvsp[(2) - (4)].symbol)->value));}
    break;

  case 11:

/* Line 1806 of yacc.c  */
#line 118 "parser.y"
    { (yyval.astree) = astreeCreate(ASTREE_LITERAL, (yyvsp[(1) - (1)].symbol), 0, 0, 0, 0); (yyval.astree)->valueType = VALUETYPE_INTEGER;}
    break;

  case 12:

/* Line 1806 of yacc.c  */
#line 119 "parser.y"
    { (yyval.astree) = astreeCreate(ASTREE_LITERAL, (yyvsp[(1) - (1)].symbol), 0, 0, 0, 0); (yyval.astree)->valueType = VALUETYPE_REAL;}
    break;

  case 13:

/* Line 1806 of yacc.c  */
#line 120 "parser.y"
    { (yyval.astree) = astreeCreate(ASTREE_LITERAL, (yyvsp[(1) - (1)].symbol), 0, 0, 0, 0); (yyval.astree)->valueType = VALUETYPE_CHAR;}
    break;

  case 14:

/* Line 1806 of yacc.c  */
#line 122 "parser.y"
    { (yyval.astree) = astreeCreate(ASTREE_VAR_GLOBAL_VEC_VALORES, NULL, (yyvsp[(1) - (2)].astree), (yyvsp[(2) - (2)].astree), 0, 0);
								     (yyval.astree)->valueType = (yyvsp[(1) - (2)].astree)->valueType;
								   }
    break;

  case 15:

/* Line 1806 of yacc.c  */
#line 125 "parser.y"
    {(yyval.astree) = 0;}
    break;

  case 16:

/* Line 1806 of yacc.c  */
#line 127 "parser.y"
    { (yyval.astree) = astreeCreate(ASTREE_BYTE_TYPE, NULL, 0, 0, 0, 0);}
    break;

  case 17:

/* Line 1806 of yacc.c  */
#line 128 "parser.y"
    { (yyval.astree) = astreeCreate(ASTREE_SHORT_TYPE, NULL, 0, 0, 0, 0); }
    break;

  case 18:

/* Line 1806 of yacc.c  */
#line 129 "parser.y"
    { (yyval.astree) = astreeCreate(ASTREE_LONG_TYPE, NULL, 0, 0, 0, 0);}
    break;

  case 19:

/* Line 1806 of yacc.c  */
#line 130 "parser.y"
    { (yyval.astree) = astreeCreate(ASTREE_FLOAT_TYPE, NULL, 0, 0, 0, 0); }
    break;

  case 20:

/* Line 1806 of yacc.c  */
#line 131 "parser.y"
    { (yyval.astree) = astreeCreate(ASTREE_DOUBLE_TYPE, NULL, 0, 0, 0, 0); }
    break;

  case 21:

/* Line 1806 of yacc.c  */
#line 133 "parser.y"
    { (yyval.astree) = astreeCreate(ASTREE_FUNCAO, NULL, (yyvsp[(1) - (2)].astree), (yyvsp[(2) - (2)].astree), 0, 0);}
    break;

  case 22:

/* Line 1806 of yacc.c  */
#line 135 "parser.y"
    { setNature_dataType(NATURE_FUNCTION,(yyvsp[(2) - (5)].symbol),(yyvsp[(1) - (5)].astree)); 
								 (yyval.astree) = astreeCreate(ASTREE_FUNC_CABECALHO, (yyvsp[(2) - (5)].symbol), (yyvsp[(1) - (5)].astree), (yyvsp[(4) - (5)].astree), 0, 0);
								 (yyvsp[(2) - (5)].symbol)->astreeNode = (yyvsp[(4) - (5)].astree);
							       }
    break;

  case 23:

/* Line 1806 of yacc.c  */
#line 140 "parser.y"
    {  setNature_dataType(NATURE_ESCALAR,(yyvsp[(2) - (3)].symbol),(yyvsp[(1) - (3)].astree)); 
								(yyval.astree) = astreeCreate(ASTREE_LISTA_PARAMETROS, (yyvsp[(2) - (3)].symbol), (yyvsp[(1) - (3)].astree), (yyvsp[(3) - (3)].astree), 0, 0);
							     }
    break;

  case 24:

/* Line 1806 of yacc.c  */
#line 143 "parser.y"
    {(yyval.astree) = 0;}
    break;

  case 25:

/* Line 1806 of yacc.c  */
#line 145 "parser.y"
    { setNature_dataType(NATURE_ESCALAR,(yyvsp[(3) - (4)].symbol),(yyvsp[(2) - (4)].astree)); 
								   (yyval.astree) = astreeCreate(ASTREE_MAIS_PARAMETROS, (yyvsp[(3) - (4)].symbol), (yyvsp[(2) - (4)].astree), (yyvsp[(4) - (4)].astree), 0, 0);
								 }
    break;

  case 26:

/* Line 1806 of yacc.c  */
#line 148 "parser.y"
    {(yyval.astree) = 0;}
    break;

  case 28:

/* Line 1806 of yacc.c  */
#line 152 "parser.y"
    {(yyval.astree) = astreeCreate(ASTREE_BLOCO_COMANDOS, NULL, (yyvsp[(2) - (3)].astree), 0, 0, 0);}
    break;

  case 29:

/* Line 1806 of yacc.c  */
#line 154 "parser.y"
    {(yyval.astree) = astreeCreate(ASTREE_LISTA_COMANDOS, NULL, (yyvsp[(1) - (3)].astree), (yyvsp[(3) - (3)].astree), 0, 0);}
    break;

  case 30:

/* Line 1806 of yacc.c  */
#line 155 "parser.y"
    {(yyval.astree) = 0;}
    break;

  case 37:

/* Line 1806 of yacc.c  */
#line 163 "parser.y"
    {(yyval.astree) = 0;}
    break;

  case 38:

/* Line 1806 of yacc.c  */
#line 165 "parser.y"
    { (yyval.astree) = astreeCreate(ASTREE_ATRIBUICAO, (yyvsp[(1) - (3)].symbol), (yyvsp[(3) - (3)].astree), 0, 0, 0);
						 testAtribuicao((yyvsp[(1) - (3)].symbol),(yyvsp[(3) - (3)].astree));
						}
    break;

  case 39:

/* Line 1806 of yacc.c  */
#line 168 "parser.y"
    {(yyval.astree) = astreeCreate(ASTREE_ATRIBUICAO_VETOR, (yyvsp[(1) - (5)].symbol), (yyvsp[(3) - (5)].astree), (yyvsp[(5) - (5)].astree), 0, 0);
							    testIndiceVetor((yyvsp[(3) - (5)].astree));
							    testAtribuicao((yyvsp[(1) - (5)].symbol),(yyvsp[(5) - (5)].astree));
							   }
    break;

  case 40:

/* Line 1806 of yacc.c  */
#line 173 "parser.y"
    {(yyval.astree) = astreeCreate(ASTREE_READ, (yyvsp[(2) - (2)].symbol), 0, 0, 0, 0);}
    break;

  case 41:

/* Line 1806 of yacc.c  */
#line 175 "parser.y"
    { (yyval.astree) = astreeCreate(ASTREE_PRINT, NULL, (yyvsp[(2) - (2)].astree), 0, 0, 0);}
    break;

  case 42:

/* Line 1806 of yacc.c  */
#line 177 "parser.y"
    { (yyval.astree) = astreeCreate(ASTREE_PRINT_LISTA, NULL, (yyvsp[(1) - (2)].astree), (yyvsp[(2) - (2)].astree), 0, 0);
								      (yyval.astree)->valueType = (yyvsp[(1) - (2)].astree)->valueType;
								    }
    break;

  case 43:

/* Line 1806 of yacc.c  */
#line 180 "parser.y"
    { (yyval.astree) = astreeCreate(ASTREE_PRINT_ELEMENT, NULL, (yyvsp[(1) - (1)].astree), 0, 0, 0);

								    }
    break;

  case 44:

/* Line 1806 of yacc.c  */
#line 184 "parser.y"
    { (yyval.astree) = astreeCreate(ASTREE_LITERAL, (yyvsp[(1) - (1)].symbol), 0, 0, 0, 0);
				     (yyval.astree)->valueType = VALUETYPE_STRING;}
    break;

  case 45:

/* Line 1806 of yacc.c  */
#line 186 "parser.y"
    { (yyval.astree)=(yyvsp[(1) - (1)].astree);
				      (yyval.astree)->valueType = VALUETYPE_STRING;
                                    }
    break;

  case 46:

/* Line 1806 of yacc.c  */
#line 190 "parser.y"
    { (yyval.astree) = astreeCreate(ASTREE_RETURN, NULL, (yyvsp[(2) - (2)].astree), 0, 0, 0);}
    break;

  case 47:

/* Line 1806 of yacc.c  */
#line 192 "parser.y"
    { (yyval.astree) = astreeCreate(ASTREE_IDENTIFIER, (yyvsp[(1) - (1)].symbol), 0, 0, 0, 0); 
				   if((yyvsp[(1) - (1)].symbol)-> dataType == DATATYPE_BYTE || (yyvsp[(1) - (1)].symbol)-> dataType == DATATYPE_SHORT || (yyvsp[(1) - (1)].symbol)-> dataType == DATATYPE_LONG){
					(yyval.astree)->valueType = VALUETYPE_INTEGER;
				   }
				  if((yyvsp[(1) - (1)].symbol)-> dataType == DATATYPE_FLOAT || (yyvsp[(1) - (1)].symbol)-> dataType == DATATYPE_DOUBLE){
					(yyval.astree)->valueType = VALUETYPE_REAL;
				   }
					
				   
				 }
    break;

  case 48:

/* Line 1806 of yacc.c  */
#line 203 "parser.y"
    { (yyval.astree) = astreeCreate(ASTREE_EXPRESSAO_VETOR, (yyvsp[(1) - (2)].symbol), (yyvsp[(2) - (2)].astree), 0, 0, 0); 
					     if((yyvsp[(1) - (2)].symbol)->nature == NATURE_FUNCTION){
						(yyval.astree) = astreeCreate(ASTREE_EXPRESSAO_FUNCAO, (yyvsp[(1) - (2)].symbol), (yyvsp[(2) - (2)].astree), 0, 0, 0);
					        getFunctCallAstreeNode((yyvsp[(1) - (2)].symbol),(yyvsp[(2) - (2)].astree));
					     }
					  
					   }
    break;

  case 49:

/* Line 1806 of yacc.c  */
#line 210 "parser.y"
    { (yyval.astree) = astreeCreate(ASTREE_EXPRESSAO_FUNCAO, (yyvsp[(1) - (4)].symbol), (yyvsp[(3) - (4)].astree), 0, 0, 0);
								   getFunctCallAstreeNode((yyvsp[(1) - (4)].symbol),(yyvsp[(3) - (4)].astree));
								   if((yyvsp[(1) - (4)].symbol)->dataType == DATATYPE_FLOAT || (yyvsp[(1) - (4)].symbol)->dataType == DATATYPE_DOUBLE){
									(yyval.astree)->valueType = VALUETYPE_REAL;
								   }
								   if((yyvsp[(1) - (4)].symbol)->dataType == DATATYPE_LONG || (yyvsp[(1) - (4)].symbol)->dataType == DATATYPE_SHORT || (yyvsp[(1) - (4)].symbol)->dataType == DATATYPE_BYTE){
									(yyval.astree)->valueType = VALUETYPE_INTEGER;
								    }
								 }
    break;

  case 50:

/* Line 1806 of yacc.c  */
#line 220 "parser.y"
    { (yyval.astree) = astreeCreate(ASTREE_LITERAL, (yyvsp[(1) - (1)].symbol), 0, 0, 0, 0);(yyval.astree)->valueType = VALUETYPE_INTEGER;}
    break;

  case 51:

/* Line 1806 of yacc.c  */
#line 221 "parser.y"
    { (yyval.astree) = astreeCreate(ASTREE_LITERAL, (yyvsp[(1) - (1)].symbol), 0, 0, 0, 0);(yyval.astree)->valueType = VALUETYPE_REAL;}
    break;

  case 52:

/* Line 1806 of yacc.c  */
#line 222 "parser.y"
    { (yyval.astree) = astreeCreate(ASTREE_LITERAL, (yyvsp[(1) - (1)].symbol), 0, 0, 0, 0);(yyval.astree)->valueType = VALUETYPE_INTEGER;}
    break;

  case 53:

/* Line 1806 of yacc.c  */
#line 223 "parser.y"
    { (yyval.astree) = astreeCreate(ASTREE_PARENTESES, NULL, (yyvsp[(2) - (3)].astree), 0, 0, 0);setValueType((yyval.astree));}
    break;

  case 54:

/* Line 1806 of yacc.c  */
#line 224 "parser.y"
    { (yyval.astree) = astreeCreate(ASTREE_COLCHETES, NULL, (yyvsp[(2) - (3)].astree), 0, 0, 0);setValueType((yyval.astree));}
    break;

  case 55:

/* Line 1806 of yacc.c  */
#line 225 "parser.y"
    { (yyval.astree) = astreeCreate(ASTREE_ADD, NULL, (yyvsp[(1) - (3)].astree), (yyvsp[(3) - (3)].astree), 0, 0);setValueType((yyval.astree));}
    break;

  case 56:

/* Line 1806 of yacc.c  */
#line 226 "parser.y"
    { (yyval.astree) = astreeCreate(ASTREE_SUB, NULL, (yyvsp[(1) - (3)].astree), (yyvsp[(3) - (3)].astree), 0, 0);setValueType((yyval.astree));}
    break;

  case 57:

/* Line 1806 of yacc.c  */
#line 227 "parser.y"
    { (yyval.astree) = astreeCreate(ASTREE_MUL, NULL, (yyvsp[(1) - (3)].astree), (yyvsp[(3) - (3)].astree), 0, 0);setValueType((yyval.astree));}
    break;

  case 58:

/* Line 1806 of yacc.c  */
#line 228 "parser.y"
    { (yyval.astree) = astreeCreate(ASTREE_DIV, NULL, (yyvsp[(1) - (3)].astree), (yyvsp[(3) - (3)].astree), 0, 0);setValueType((yyval.astree));}
    break;

  case 59:

/* Line 1806 of yacc.c  */
#line 229 "parser.y"
    { (yyval.astree) = astreeCreate(ASTREE_GREATER_THAN, NULL, (yyvsp[(1) - (3)].astree), (yyvsp[(3) - (3)].astree), 0, 0);setValueType((yyval.astree));}
    break;

  case 60:

/* Line 1806 of yacc.c  */
#line 230 "parser.y"
    { (yyval.astree) = astreeCreate(ASTREE_LESS_THAN, NULL, (yyvsp[(1) - (3)].astree), (yyvsp[(3) - (3)].astree), 0, 0);setValueType((yyval.astree));}
    break;

  case 61:

/* Line 1806 of yacc.c  */
#line 231 "parser.y"
    { (yyval.astree) = astreeCreate(ASTREE_LE, NULL, (yyvsp[(1) - (3)].astree), (yyvsp[(3) - (3)].astree), 0, 0);setValueType((yyval.astree));}
    break;

  case 62:

/* Line 1806 of yacc.c  */
#line 232 "parser.y"
    { (yyval.astree) = astreeCreate(ASTREE_GE, NULL, (yyvsp[(1) - (3)].astree), (yyvsp[(3) - (3)].astree), 0, 0);setValueType((yyval.astree));}
    break;

  case 63:

/* Line 1806 of yacc.c  */
#line 233 "parser.y"
    { (yyval.astree) = astreeCreate(ASTREE_EQ, NULL, (yyvsp[(1) - (3)].astree), (yyvsp[(3) - (3)].astree), 0, 0);setValueType((yyval.astree));}
    break;

  case 64:

/* Line 1806 of yacc.c  */
#line 234 "parser.y"
    { (yyval.astree) = astreeCreate(ASTREE_NE, NULL, (yyvsp[(1) - (3)].astree), (yyvsp[(3) - (3)].astree), 0, 0);setValueType((yyval.astree));}
    break;

  case 65:

/* Line 1806 of yacc.c  */
#line 235 "parser.y"
    { (yyval.astree) = astreeCreate(ASTREE_AND, NULL, (yyvsp[(1) - (3)].astree), (yyvsp[(3) - (3)].astree), 0, 0);setValueType((yyval.astree));}
    break;

  case 66:

/* Line 1806 of yacc.c  */
#line 236 "parser.y"
    { (yyval.astree) = astreeCreate(ASTREE_OR, NULL, (yyvsp[(1) - (3)].astree), (yyvsp[(3) - (3)].astree), 0, 0);setValueType((yyval.astree));}
    break;

  case 67:

/* Line 1806 of yacc.c  */
#line 237 "parser.y"
    { (yyval.astree) = astreeCreate(ASTREE_NEGADO, NULL, (yyvsp[(2) - (2)].astree), 0, 0, 0);setValueType((yyval.astree));}
    break;

  case 68:

/* Line 1806 of yacc.c  */
#line 240 "parser.y"
    { (yyval.astree) = astreeCreate(ASTREE_LISTA_FUNC_PARAMETROS, NULL, (yyvsp[(1) - (2)].astree), (yyvsp[(2) - (2)].astree), 0, 0);}
    break;

  case 69:

/* Line 1806 of yacc.c  */
#line 242 "parser.y"
    {(yyval.astree) = 0;}
    break;

  case 70:

/* Line 1806 of yacc.c  */
#line 244 "parser.y"
    { (yyval.astree) = astreeCreate(ASTREE_LISTA_FUNC_MAIS_PARAMETROS, NULL, (yyvsp[(2) - (3)].astree), (yyvsp[(3) - (3)].astree), 0, 0);}
    break;

  case 71:

/* Line 1806 of yacc.c  */
#line 245 "parser.y"
    {(yyval.astree) = 0;}
    break;

  case 76:

/* Line 1806 of yacc.c  */
#line 252 "parser.y"
    { mustBeBoolType((yyvsp[(3) - (6)].astree));
							      (yyval.astree) = astreeCreate(ASTREE_WHEN_THEN, NULL, (yyvsp[(3) - (6)].astree), (yyvsp[(6) - (6)].astree), 0, 0);
							    }
    break;

  case 77:

/* Line 1806 of yacc.c  */
#line 256 "parser.y"
    { mustBeBoolType((yyvsp[(3) - (8)].astree)); 
										   (yyval.astree) = astreeCreate(ASTREE_WHEN_THEN_ELSE, NULL, (yyvsp[(3) - (8)].astree), (yyvsp[(6) - (8)].astree), (yyvsp[(8) - (8)].astree), 0);}
    break;

  case 78:

/* Line 1806 of yacc.c  */
#line 259 "parser.y"
    { mustBeBoolType((yyvsp[(3) - (5)].astree)); 
						    (yyval.astree) = astreeCreate(ASTREE_WHILE, NULL, (yyvsp[(3) - (5)].astree), (yyvsp[(5) - (5)].astree), 0, 0);
						  }
    break;

  case 79:

/* Line 1806 of yacc.c  */
#line 263 "parser.y"
    { (yyval.astree) = astreeCreate(ASTREE_FOR, (yyvsp[(3) - (9)].symbol), (yyvsp[(5) - (9)].astree), (yyvsp[(7) - (9)].astree), (yyvsp[(9) - (9)].astree), 0);
										  testFor((yyvsp[(3) - (9)].symbol), (yyvsp[(5) - (9)].astree), (yyvsp[(7) - (9)].astree));	
										}
    break;



/* Line 1806 of yacc.c  */
#line 2114 "y.tab.c"
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


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

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

#if !defined(yyoverflow) || YYERROR_VERBOSE
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



/* Line 2067 of yacc.c  */
#line 269 "parser.y"


int yyerror(char *value){
  fprintf(stderr, "Erro: %s ,na linha: %d\n",value,getLineNumber());
  exit(3);
}






