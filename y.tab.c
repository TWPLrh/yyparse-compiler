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
#line 3 "compiler_hw2.y" /* yacc.c:339  */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_RESET   "\x1b[0m"
extern int yylineno;
extern int yylex();
extern FILE *yyin;

char mID[20];
char lockedID[20];
char mType[8];
int I_data;
float F_data;
char mStr[87];
int printErrflag = 0;
int initflag = 0;
int isflt = 0;
int declaredtwice = 0;
int ScopeDepth = 0;
int MaxScopeDepth = 0;
int l = 0;
int r = 0;

typedef struct symbol_table
{
	int ScopeDepth;
	int scopeindex;

	char mID[20];
	char mType[8];
	int I_data;
	float F_data;
	struct symbol_table *next;

}symbol_table;

typedef struct scope	// include symbol_table
{
	struct scope *child;
	struct scope *mother;

	symbol_table *inScope_head;
	symbol_table *inScope_list;

	int scopeindex;
	int IFIF;
}scope;

int scopeindex = 0;		// 每個scope有自己的標籤
scope *scopelist[256];	// 在 dump 時使用, print所有的variable

/* Symbol table function - you can add new function if need. */
symbol_table *lookup_symbol(char const *); // 搜尋 symbol_table, return NULL 或一個 symbol_table
void create_symbol();			// 初始化 - print "Create symbol table", 之後都交給 insert_symbol
void insert_symbol();			// 對每個Scope的symbol_table做賦值
void dump_symbol();				// 印出所有的變數資訊
void IAlwaysInit();				// 避免 Core dump 在 main() 直接做初始化
void scopefunc(char);			// 處理 '{' 和 '}'
float Func_Assign(char, float);	// 處理 Assign Op
float IncDecFunc(char);			// 處理 ++ 和 --

// 必要的函式 
void yyerror(char const *s) { fprintf(stderr, ANSI_COLOR_RED	"<Error> %s (line %d)\n"	ANSI_COLOR_RESET, s, yylineno); }

symbol_table *gbTmp;	// 用於 symboltable 的暫存
scope *Scope, *MasterScope; //Scope 會一直變, MasterScope 作為所有 Scope 的祖先


#line 137 "y.tab.c" /* yacc.c:339  */

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
    PRINT = 258,
    PRINTLN = 259,
    IF = 260,
    ELSE = 261,
    FOR = 262,
    ELIF = 263,
    VAR = 264,
    NEWLINE = 265,
    INT = 266,
    FLOAT = 267,
    VOID = 268,
    INCREMENT = 269,
    DECREMENT = 270,
    Add_Assign = 271,
    Sub_Assign = 272,
    Mul_Assign = 273,
    Div_Assign = 274,
    Mod_Assign = 275,
    GRE = 276,
    LSE = 277,
    EQU = 278,
    NEQ = 279,
    AND = 280,
    OR = 281,
    Other = 282,
    I_CONST = 283,
    F_CONST = 284,
    STRING = 285,
    ID = 286
  };
#endif
/* Tokens.  */
#define PRINT 258
#define PRINTLN 259
#define IF 260
#define ELSE 261
#define FOR 262
#define ELIF 263
#define VAR 264
#define NEWLINE 265
#define INT 266
#define FLOAT 267
#define VOID 268
#define INCREMENT 269
#define DECREMENT 270
#define Add_Assign 271
#define Sub_Assign 272
#define Mul_Assign 273
#define Div_Assign 274
#define Mod_Assign 275
#define GRE 276
#define LSE 277
#define EQU 278
#define NEQ 279
#define AND 280
#define OR 281
#define Other 282
#define I_CONST 283
#define F_CONST 284
#define STRING 285
#define ID 286

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 75 "compiler_hw2.y" /* yacc.c:355  */

	int i_val;
	double f_val;
	char* string;

#line 245 "y.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 262 "y.tab.c" /* yacc.c:358  */

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
#define YYFINAL  49
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   298

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  44
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  18
/* YYNRULES -- Number of rules.  */
#define YYNRULES  76
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  132

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   286

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,    41,     2,     2,
      36,    37,    34,    32,     2,    33,     2,    35,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      43,    38,    42,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    39,     2,    40,     2,     2,     2,     2,
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
      25,    26,    27,    28,    29,    30,    31
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   120,   120,   121,   125,   126,   127,   128,   129,   130,
     131,   134,   138,   139,   140,   141,   142,   145,   146,   150,
     151,   155,   156,   157,   158,   159,   160,   161,   162,   166,
     167,   168,   169,   173,   174,   175,   179,   180,   181,   182,
     183,   187,   188,   189,   190,   191,   192,   193,   208,   223,
     238,   253,   254,   255,   256,   257,   258,   259,   260,   261,
     262,   263,   264,   265,   266,   267,   268,   269,   270,   274,
     282,   310,   313,   316,   319,   320,   321
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "PRINT", "PRINTLN", "IF", "ELSE", "FOR",
  "ELIF", "VAR", "NEWLINE", "INT", "FLOAT", "VOID", "INCREMENT",
  "DECREMENT", "Add_Assign", "Sub_Assign", "Mul_Assign", "Div_Assign",
  "Mod_Assign", "GRE", "LSE", "EQU", "NEQ", "AND", "OR", "Other",
  "I_CONST", "F_CONST", "STRING", "ID", "'+'", "'-'", "'*'", "'/'", "'('",
  "')'", "'='", "'{'", "'}'", "'%'", "'>'", "'<'", "$accept", "program",
  "stmt", "ForStmt", "IfStmt", "dcl", "comp", "expr", "print_func", "type",
  "IncDecStmt", "CALC", "lockedID", "STORE_ID", "STORE_STR", "STORE_INT",
  "STORE_FLT", "trap", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,    43,    45,    42,    47,    40,    41,    61,   123,
     125,    37,    62,    60
};
# endif

#define YYPACT_NINF -35

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-35)))

#define YYTABLE_NINF -70

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     132,   -34,   -22,   228,   132,   -20,   234,   -26,   -35,    13,
      13,   -35,   -35,   -35,   255,    56,   -35,   -35,    42,   132,
     -35,   -35,   -35,   -35,   -35,   -35,    -7,   152,   260,   194,
      23,    33,    19,    65,    65,   253,   132,   -35,   253,   253,
     132,   -35,    39,   -35,    -7,   -35,    -7,   -11,    36,   -35,
     -35,   -35,   -35,    56,    56,    56,    56,    56,    56,    56,
      56,    56,    56,    56,   152,    56,    56,    56,    56,    56,
      56,    56,    69,    56,    19,   -35,    62,    67,    79,    83,
      84,   -11,   -35,    85,    86,   -35,   -35,   -35,   -35,    71,
     -35,   152,   152,   152,   152,   178,   178,   210,   210,   152,
      36,    33,   152,   152,   152,   152,   152,   152,   152,   152,
     152,    23,    33,   -35,   -35,   -35,   152,    36,    23,    33,
     -35,   -35,   -35,   -35,   132,   132,   132,    56,   -35,   -35,
     -35,   152
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     0,     0,     0,     0,     0,     0,    74,     0,
       0,    75,    72,    73,    70,     0,    19,    20,     0,     3,
       8,     9,     4,     5,     6,     7,    28,    21,     0,    40,
      61,    62,    10,     0,     0,     0,     0,    16,     0,     0,
       0,    69,     0,    70,    36,    40,    37,     0,    60,     1,
       2,    38,    39,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    46,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    76,    71,     0,     0,     0,     0,
       0,     0,    12,     0,     0,    14,    33,    34,    35,    18,
      59,    66,    67,    65,    68,    41,    42,    43,    44,    45,
      48,    57,    63,    64,    23,    24,    25,    26,    27,    22,
      47,    49,    52,    50,    51,    54,    56,    53,    55,    58,
      29,    31,    30,    32,     0,     0,     0,     0,    13,    11,
      15,    17
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -35,    98,     5,   -35,   -35,   -35,   -35,    80,   -35,   -35,
      93,     0,   121,    72,   100,    17,   -24,   -31
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,    18,    19,    20,    21,    22,    23,    24,    25,    89,
      26,    64,    28,    48,    77,    30,    31,    32
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      27,    74,    33,    27,    27,    41,    27,    51,    52,    37,
      53,    54,    55,    56,    34,    47,    38,    12,    13,    27,
      43,    57,    58,    59,    60,    15,    90,     9,    10,     8,
      61,    62,    63,    27,    27,    81,    27,   101,    27,    81,
      27,    82,    49,    74,    43,    85,    11,   112,   115,   119,
      86,    87,    88,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   102,   103,    72,   104,   105,   106,   107,   108,
     109,   110,    29,   116,    73,    29,    29,    71,    29,     9,
      10,    45,    45,    36,    12,    13,    40,    43,   111,   114,
     118,    29,    15,    12,    13,    75,    14,    12,    13,   120,
      43,    15,    44,    46,   121,    29,    29,    29,    29,   127,
      29,    29,    29,    76,    78,    80,   122,    50,    83,    84,
     123,   124,   125,   126,    27,    27,    27,   131,    42,   128,
     129,   130,     0,   100,    79,     1,     2,     3,     4,     5,
       6,     7,     8,     0,   113,   117,     9,    10,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    11,
      12,    13,     0,    14,     0,     0,     0,     0,    15,     0,
       0,    16,    17,    53,    54,    55,    56,     0,     0,     0,
      12,    13,     0,    43,    57,    58,    59,    60,    15,     0,
       0,     0,     0,    61,    62,    63,    29,    29,    29,    53,
      54,    55,    56,     0,     0,     0,    12,    13,     0,    43,
       0,     0,    59,    60,    15,   -60,   -60,   -60,   -60,    61,
      62,    63,     0,     0,     0,     0,   -60,   -60,   -60,   -60,
       0,    53,    54,    55,    56,    71,   -60,   -60,    12,    13,
       0,    43,     9,    10,     0,     0,    15,     0,     9,    10,
       0,    61,    62,    63,     0,     0,    12,    13,     0,    14,
       0,     0,    12,    13,    35,    14,     0,     9,    10,     0,
      39,   -69,   -69,   -69,   -69,   -69,    65,    66,    67,    68,
      69,    12,    13,     0,    14,     0,     0,     0,     0,    15,
       0,     0,     0,   -69,     0,     0,     0,     0,    70
};

static const yytype_int8 yycheck[] =
{
       0,    32,    36,     3,     4,    31,     6,    14,    15,     4,
      21,    22,    23,    24,    36,    15,    36,    28,    29,    19,
      31,    32,    33,    34,    35,    36,    37,    14,    15,    10,
      41,    42,    43,    33,    34,    35,    36,    61,    38,    39,
      40,    36,     0,    74,    31,    40,    27,    71,    72,    73,
      11,    12,    13,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    41,    65,    66,    67,    68,    69,
      70,    71,     0,    73,    41,     3,     4,    41,     6,    14,
      15,     9,    10,     3,    28,    29,     6,    31,    71,    72,
      73,    19,    36,    28,    29,    30,    31,    28,    29,    37,
      31,    36,     9,    10,    37,    33,    34,    35,    36,    38,
      38,    39,    40,    33,    34,    35,    37,    19,    38,    39,
      37,    37,    37,    37,   124,   125,   126,   127,     7,   124,
     125,   126,    -1,    61,    34,     3,     4,     5,     6,     7,
       8,     9,    10,    -1,    72,    73,    14,    15,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    27,
      28,    29,    -1,    31,    -1,    -1,    -1,    -1,    36,    -1,
      -1,    39,    40,    21,    22,    23,    24,    -1,    -1,    -1,
      28,    29,    -1,    31,    32,    33,    34,    35,    36,    -1,
      -1,    -1,    -1,    41,    42,    43,   124,   125,   126,    21,
      22,    23,    24,    -1,    -1,    -1,    28,    29,    -1,    31,
      -1,    -1,    34,    35,    36,    21,    22,    23,    24,    41,
      42,    43,    -1,    -1,    -1,    -1,    32,    33,    34,    35,
      -1,    21,    22,    23,    24,    41,    42,    43,    28,    29,
      -1,    31,    14,    15,    -1,    -1,    36,    -1,    14,    15,
      -1,    41,    42,    43,    -1,    -1,    28,    29,    -1,    31,
      -1,    -1,    28,    29,    36,    31,    -1,    14,    15,    -1,
      36,    16,    17,    18,    19,    20,    16,    17,    18,    19,
      20,    28,    29,    -1,    31,    -1,    -1,    -1,    -1,    36,
      -1,    -1,    -1,    38,    -1,    -1,    -1,    -1,    38
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     5,     6,     7,     8,     9,    10,    14,
      15,    27,    28,    29,    31,    36,    39,    40,    45,    46,
      47,    48,    49,    50,    51,    52,    54,    55,    56,    57,
      59,    60,    61,    36,    36,    36,    51,    46,    36,    36,
      51,    31,    56,    31,    54,    57,    54,    55,    57,     0,
      45,    14,    15,    21,    22,    23,    24,    32,    33,    34,
      35,    41,    42,    43,    55,    16,    17,    18,    19,    20,
      38,    41,    41,    41,    61,    30,    51,    58,    51,    58,
      51,    55,    46,    51,    51,    46,    11,    12,    13,    53,
      37,    55,    55,    55,    55,    55,    55,    55,    55,    55,
      57,    60,    55,    55,    55,    55,    55,    55,    55,    55,
      55,    59,    60,    57,    59,    60,    55,    57,    59,    60,
      37,    37,    37,    37,    37,    37,    37,    38,    46,    46,
      46,    55
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    44,    45,    45,    46,    46,    46,    46,    46,    46,
      46,    47,    48,    48,    48,    48,    48,    49,    49,    50,
      50,    51,    51,    51,    51,    51,    51,    51,    51,    52,
      52,    52,    52,    53,    53,    53,    54,    54,    54,    54,
      54,    55,    55,    55,    55,    55,    55,    55,    55,    55,
      55,    55,    55,    55,    55,    55,    55,    55,    55,    55,
      55,    55,    55,    55,    55,    55,    55,    55,    55,    56,
      57,    58,    59,    60,    61,    61,    61
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     0,     1,     1,     1,     1,     1,     1,
       1,     5,     3,     5,     3,     5,     2,     5,     3,     1,
       1,     1,     3,     3,     3,     3,     3,     3,     1,     4,
       4,     4,     4,     1,     1,     1,     2,     2,     2,     2,
       1,     3,     3,     3,     3,     3,     2,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       1,     1,     1,     3,     3,     3,     3,     3,     3,     1,
       1,     1,     1,     1,     1,     1,     2
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
        case 11:
#line 134 "compiler_hw2.y" /* yacc.c:1646  */
    { printf("For Stmt");}
#line 1461 "y.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 138 "compiler_hw2.y" /* yacc.c:1646  */
    { printf("If Stmt\n"); Scope -> mother -> IFIF ++; }
#line 1467 "y.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 139 "compiler_hw2.y" /* yacc.c:1646  */
    { printf("If Stmt\n"); Scope -> mother -> IFIF ++; }
#line 1473 "y.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 140 "compiler_hw2.y" /* yacc.c:1646  */
    { puts("Else If Stmt"); if(Scope -> mother -> IFIF <= 0){ yyerror("<ELSE IF> used without <IF>");} }
#line 1479 "y.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 141 "compiler_hw2.y" /* yacc.c:1646  */
    { puts("Else If Stmt"); if(Scope -> mother -> IFIF <= 0){ yyerror("<ELSE IF> used without <IF>");} }
#line 1485 "y.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 142 "compiler_hw2.y" /* yacc.c:1646  */
    { puts("Else Stmt"); Scope -> mother -> IFIF--; if(Scope -> mother -> IFIF < 0){ yyerror("<ELSE> used without <IF> or <ELSE> used twice ");} }
#line 1491 "y.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 145 "compiler_hw2.y" /* yacc.c:1646  */
    { I_data = (int)(yyvsp[0].f_val); F_data = (yyvsp[0].f_val); create_symbol(); }
#line 1497 "y.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 146 "compiler_hw2.y" /* yacc.c:1646  */
    { I_data = 0; F_data = 0; create_symbol(); }
#line 1503 "y.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 150 "compiler_hw2.y" /* yacc.c:1646  */
    { scopefunc('{'); }
#line 1509 "y.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 151 "compiler_hw2.y" /* yacc.c:1646  */
    { scopefunc('}'); }
#line 1515 "y.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 156 "compiler_hw2.y" /* yacc.c:1646  */
    {puts("ASSIGN"); (yyval.f_val) = Func_Assign('=', (yyvsp[0].f_val));}
#line 1521 "y.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 157 "compiler_hw2.y" /* yacc.c:1646  */
    {puts("Add Assign"); (yyval.f_val) = Func_Assign('+', (yyvsp[0].f_val));}
#line 1527 "y.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 158 "compiler_hw2.y" /* yacc.c:1646  */
    {puts("Sub Assign"); (yyval.f_val) = Func_Assign('-', (yyvsp[0].f_val));}
#line 1533 "y.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 159 "compiler_hw2.y" /* yacc.c:1646  */
    {puts("Mul Assign"); (yyval.f_val) = Func_Assign('*', (yyvsp[0].f_val));}
#line 1539 "y.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 160 "compiler_hw2.y" /* yacc.c:1646  */
    {puts("Div Assign"); (yyval.f_val) = Func_Assign('/', (yyvsp[0].f_val));}
#line 1545 "y.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 161 "compiler_hw2.y" /* yacc.c:1646  */
    {puts("Mod Assign"); (yyval.f_val) = Func_Assign('%', (yyvsp[0].f_val));}
#line 1551 "y.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 166 "compiler_hw2.y" /* yacc.c:1646  */
    { if(printErrflag == 1) {  printErrflag = 0; } else printf("Print : %g\n", (yyvsp[-1].f_val)); }
#line 1557 "y.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 167 "compiler_hw2.y" /* yacc.c:1646  */
    { if(printErrflag == 1) {  printErrflag = 0; } else printf("Println : %g\n", (yyvsp[-1].f_val)); }
#line 1563 "y.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 168 "compiler_hw2.y" /* yacc.c:1646  */
    { printf("Print : %s\n", mStr); }
#line 1569 "y.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 169 "compiler_hw2.y" /* yacc.c:1646  */
    { printf("Println %s\n", mStr); }
#line 1575 "y.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 173 "compiler_hw2.y" /* yacc.c:1646  */
    { strcpy(mType, "int"); }
#line 1581 "y.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 174 "compiler_hw2.y" /* yacc.c:1646  */
    { strcpy(mType, "float32"); }
#line 1587 "y.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 175 "compiler_hw2.y" /* yacc.c:1646  */
    { strcpy(mType, "void"); }
#line 1593 "y.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 179 "compiler_hw2.y" /* yacc.c:1646  */
    {puts("preInc"); (yyval.f_val) = IncDecFunc('+');}
#line 1599 "y.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 180 "compiler_hw2.y" /* yacc.c:1646  */
    {puts("preDec"); (yyval.f_val) = IncDecFunc('-');}
#line 1605 "y.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 181 "compiler_hw2.y" /* yacc.c:1646  */
    {puts("postInc");(yyval.f_val) = IncDecFunc('+') - 1;}
#line 1611 "y.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 182 "compiler_hw2.y" /* yacc.c:1646  */
    {puts("postDec");(yyval.f_val) = IncDecFunc('-') + 1;}
#line 1617 "y.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 183 "compiler_hw2.y" /* yacc.c:1646  */
    { (yyval.f_val) = (yyvsp[0].f_val); }
#line 1623 "y.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 187 "compiler_hw2.y" /* yacc.c:1646  */
    { puts("Add");  (yyval.f_val) = (yyvsp[-2].f_val) + (yyvsp[0].f_val);}
#line 1629 "y.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 188 "compiler_hw2.y" /* yacc.c:1646  */
    { puts("Sub");  (yyval.f_val) = (yyvsp[-2].f_val) - (yyvsp[0].f_val);}
#line 1635 "y.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 189 "compiler_hw2.y" /* yacc.c:1646  */
    { puts("Mul");  (yyval.f_val) = (yyvsp[-2].f_val) * (yyvsp[0].f_val);}
#line 1641 "y.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 190 "compiler_hw2.y" /* yacc.c:1646  */
    { if((yyvsp[0].f_val) == 0) { printErrflag = 1; printf(ANSI_COLOR_RED   "<ERROR> The divisor can’t be 0 (line %d)\n"    ANSI_COLOR_RESET, yylineno);} else { puts("Div"); (yyval.f_val) = (yyvsp[-2].f_val) / (yyvsp[0].f_val);} }
#line 1647 "y.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 191 "compiler_hw2.y" /* yacc.c:1646  */
    { (yyval.f_val) = (int)(yyvsp[-2].f_val) % (int)(yyvsp[0].f_val);}
#line 1653 "y.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 192 "compiler_hw2.y" /* yacc.c:1646  */
    { printf(ANSI_COLOR_RED   "<ERROR> Syntax Error (line %d)\n"    ANSI_COLOR_RESET, yylineno); return 0; }
#line 1659 "y.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 194 "compiler_hw2.y" /* yacc.c:1646  */
    { 
		if ( isflt == 1 )
		{
			isflt = 0;
			printf(ANSI_COLOR_RED   "<ERROR> float type can't MOD (line %d)\n"    ANSI_COLOR_RESET, yylineno); 
			(yyval.f_val) = 0;
		}

		else
		{
			puts("Mod");
			(yyval.f_val) = (int)(yyvsp[-2].f_val) % (int)(yyvsp[0].f_val);
		}
	}
#line 1678 "y.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 209 "compiler_hw2.y" /* yacc.c:1646  */
    { 
        if ( isflt == 1 ) 
        {   
            isflt = 0;
            printf(ANSI_COLOR_RED   "<ERROR> float type can't MOD (line %d)\n"    ANSI_COLOR_RESET, yylineno); 
            (yyval.f_val) = 0;
        }   

        else
        {   
			puts("Mod");
            (yyval.f_val) = (int)(yyvsp[-2].f_val) % (int)(yyvsp[0].f_val); 
        }	
	}
#line 1697 "y.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 224 "compiler_hw2.y" /* yacc.c:1646  */
    {
        if ( isflt == 1 ) 
        {   
            isflt = 0;
            printf(ANSI_COLOR_RED   "<ERROR> float type can't MOD (line %d)\n"    ANSI_COLOR_RESET, yylineno); 
            (yyval.f_val) = 0;
        }   

        else
        {   
			puts("Mod");
            (yyval.f_val) = (int)(yyvsp[-2].f_val) % I_data;
        }
	}
#line 1716 "y.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 239 "compiler_hw2.y" /* yacc.c:1646  */
    {
        if ( isflt == 1 ) 
        {   
            isflt = 0;
            printf(ANSI_COLOR_RED   "<ERROR> float type can't MOD (line %d)\n"    ANSI_COLOR_RESET, yylineno+1); 
            (yyval.f_val) = 0;
        }   

        else
        {   
			puts("Mod");
            (yyval.f_val) = I_data % (int)(yyvsp[0].f_val); 
        }
	}
#line 1735 "y.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 253 "compiler_hw2.y" /* yacc.c:1646  */
    { puts("Mod"); (yyval.f_val) = (int)(yyvsp[-2].f_val) % (int)(yyvsp[0].f_val); }
#line 1741 "y.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 254 "compiler_hw2.y" /* yacc.c:1646  */
    { printf(ANSI_COLOR_RED   "<ERROR> float type can't MOD (line %d)\n"    ANSI_COLOR_RESET, yylineno); (yyval.f_val) = 0; }
#line 1747 "y.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 255 "compiler_hw2.y" /* yacc.c:1646  */
    { printf(ANSI_COLOR_RED   "<ERROR> float type can't MOD (line %d)\n"    ANSI_COLOR_RESET, yylineno); (yyval.f_val) = 0; }
#line 1753 "y.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 256 "compiler_hw2.y" /* yacc.c:1646  */
    { printf(ANSI_COLOR_RED   "<ERROR> float type can't MOD (line %d)\n"    ANSI_COLOR_RESET, yylineno+1); (yyval.f_val) = 0;}
#line 1759 "y.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 257 "compiler_hw2.y" /* yacc.c:1646  */
    { printf(ANSI_COLOR_RED   "<ERROR> float type can't MOD (line %d)\n"    ANSI_COLOR_RESET, yylineno); (yyval.f_val) = 0;}
#line 1765 "y.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 258 "compiler_hw2.y" /* yacc.c:1646  */
    { printf(ANSI_COLOR_RED   "<ERROR> float type can't MOD (line %d)\n"    ANSI_COLOR_RESET, yylineno); (yyval.f_val) = 0;}
#line 1771 "y.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 259 "compiler_hw2.y" /* yacc.c:1646  */
    { printf(ANSI_COLOR_RED   "<ERROR> float type can't MOD (line %d)\n"    ANSI_COLOR_RESET, yylineno); (yyval.f_val) = 0;}
#line 1777 "y.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 260 "compiler_hw2.y" /* yacc.c:1646  */
    { printf(ANSI_COLOR_RED   "<ERROR> float type can't MOD (line %d)\n"    ANSI_COLOR_RESET, yylineno); (yyval.f_val) = 0;}
#line 1783 "y.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 261 "compiler_hw2.y" /* yacc.c:1646  */
    { (yyval.f_val) = (yyvsp[-1].f_val); }
#line 1789 "y.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 262 "compiler_hw2.y" /* yacc.c:1646  */
    { (yyval.f_val) = (yyvsp[0].f_val); }
#line 1795 "y.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 263 "compiler_hw2.y" /* yacc.c:1646  */
    { (yyval.f_val) = (yyvsp[0].f_val);}
#line 1801 "y.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 264 "compiler_hw2.y" /* yacc.c:1646  */
    { (yyval.f_val) = (yyvsp[0].f_val);}
#line 1807 "y.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 265 "compiler_hw2.y" /* yacc.c:1646  */
    { (yyval.f_val) = (yyvsp[-2].f_val) > (yyvsp[0].f_val); if((yyval.f_val) == 1) puts("True"); else puts("False");}
#line 1813 "y.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 266 "compiler_hw2.y" /* yacc.c:1646  */
    { (yyval.f_val) = (yyvsp[-2].f_val) < (yyvsp[0].f_val); if((yyval.f_val) == 1) puts("True"); else puts("False");}
#line 1819 "y.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 267 "compiler_hw2.y" /* yacc.c:1646  */
    { (yyval.f_val) = (yyvsp[-2].f_val) == (yyvsp[0].f_val); if((yyval.f_val) == 1) puts("True"); else puts("False");}
#line 1825 "y.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 268 "compiler_hw2.y" /* yacc.c:1646  */
    { (yyval.f_val) = (yyvsp[-2].f_val) >= (yyvsp[0].f_val); if((yyval.f_val) == 1) puts("True"); else puts("False");}
#line 1831 "y.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 269 "compiler_hw2.y" /* yacc.c:1646  */
    { (yyval.f_val) = (yyvsp[-2].f_val) <= (yyvsp[0].f_val); if((yyval.f_val) == 1) puts("True"); else puts("False");}
#line 1837 "y.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 270 "compiler_hw2.y" /* yacc.c:1646  */
    { (yyval.f_val) = (yyvsp[-2].f_val) != (yyvsp[0].f_val); if((yyval.f_val) == 1) puts("True"); else puts("False");}
#line 1843 "y.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 275 "compiler_hw2.y" /* yacc.c:1646  */
    { 
		char *p = strtok((yyvsp[0].string), "+-*/()=%><$!@#^& \t"); 
		strcpy(lockedID, p);
	}
#line 1852 "y.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 283 "compiler_hw2.y" /* yacc.c:1646  */
    {
		char *p = strtok((yyvsp[0].string), "+-*/()=%><$!@#^& \t");
		strcpy(mID, p); 

		gbTmp = lookup_symbol(mID);
		
		if(!gbTmp)
		{
			printf(ANSI_COLOR_RED   "<ERROR> can't find variable %s (line %d)\n"    ANSI_COLOR_RESET, mID, yylineno);
		}
		else
		{
			printf("variable %s is depth %d\n", mID, gbTmp->ScopeDepth);
			if(gbTmp->mType[0] == 'i')
			{
				(yyval.f_val) = (float)gbTmp->I_data; I_data = (int)(yyval.f_val), F_data = (yyval.f_val);
			}
			else if(gbTmp->mType[0] == 'f')
			{
				isflt = 1;
				(yyval.f_val) = gbTmp->F_data;; I_data = (int)(yyval.f_val), F_data = (yyval.f_val);
			}
		}
	}
#line 1881 "y.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 310 "compiler_hw2.y" /* yacc.c:1646  */
    { strcpy(mStr, (yyvsp[0].string)); }
#line 1887 "y.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 313 "compiler_hw2.y" /* yacc.c:1646  */
    { (yyval.f_val) = (float)(yyvsp[0].i_val); I_data = (yyvsp[0].i_val); F_data = (float)(yyvsp[0].i_val);}
#line 1893 "y.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 316 "compiler_hw2.y" /* yacc.c:1646  */
    { (yyval.f_val) = (yyvsp[0].f_val); F_data = (yyvsp[0].f_val); I_data = (int)(yyvsp[0].f_val);}
#line 1899 "y.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 319 "compiler_hw2.y" /* yacc.c:1646  */
    { /* puts("NEWLINE"); */}
#line 1905 "y.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 320 "compiler_hw2.y" /* yacc.c:1646  */
    {  /*puts("Other");*/  }
#line 1911 "y.tab.c" /* yacc.c:1646  */
    break;


#line 1915 "y.tab.c" /* yacc.c:1646  */
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
#line 324 "compiler_hw2.y" /* yacc.c:1906  */


/* C code section */
int main(int argc, char** argv)
{
	yyin = fopen(argv[1], "r");

	yylineno = 0;
	IAlwaysInit();	

	yyparse();
	
	printf("\nTotal line : %d\n", yylineno);

	printf("\nThe symbol table:\n");
	dump_symbol();
	
	return 0;
}

void IAlwaysInit()
{
	Scope = malloc(sizeof(scope));
	Scope -> inScope_list = malloc(sizeof(symbol_table));
	Scope -> inScope_list -> scopeindex = scopeindex;
	Scope -> inScope_head = Scope->inScope_list;
	Scope -> scopeindex = scopeindex;
	MasterScope = Scope;
	MasterScope->mother = malloc(sizeof(scope));

	scopelist[0] = Scope;
}

void scopefunc(char m)
{
	/*
		每個Scope有自己的Symbol Table
		應該要直接使用scope裡面的inScope_table, inScope_head 才對.
		如果在自己的Symbol Table找不到變數 -> 則尋找Mother.
	*/
	scope *mother;

	if(m == '{') // 如果遇到左括號
	{
		Scope -> child = malloc(sizeof(scope)); // 分配空間

		mother = Scope; 					// 設給 mother 當前的 Scope

		Scope = Scope -> child; 			// 當前 Scope 設為 child
		Scope -> mother = mother; 			// child 的 mother 等於前面設定好的 mother

		ScopeDepth ++; 						// 深度 + 1

		Scope -> inScope_list = malloc(sizeof(symbol_table));
		Scope -> inScope_head = Scope -> inScope_list;

		scopeindex ++; // 每個scope都有自己的 index
		scopelist[scopeindex] = Scope; 
		Scope -> scopeindex = scopeindex;

		l = 1;
	}

	else if(m == '}') // 如果遇到右括號
	{
		Scope = Scope -> mother; // Scope 設為 mother
		ScopeDepth --; // 深度 - 1
		
		if( l == 1 && r == 0 )
		{
			Scope -> child -> child = malloc(sizeof(scope));
			r = 1;
		}
	}

	if (ScopeDepth == 0)
	{
		r = 0;
	}

	if (MaxScopeDepth < ScopeDepth)
	{
		MaxScopeDepth = ScopeDepth; // 紀錄最大深度
	}
}

void create_symbol() 
{	
	if(initflag == 0){
		puts("Create symbol table");
		initflag = 1;
	}
	insert_symbol();
}

void insert_symbol() 
{
	declaredtwice = 0;

	if(lookup_symbol(lockedID) && declaredtwice == 0)
	{
		printf(ANSI_COLOR_RED   "<ERROR> re-declaration for variable %s (line %d)\n"    ANSI_COLOR_RESET, lockedID, yylineno);
		return;
	}

	printf("Insert a symbol: %s\n", lockedID);

	Scope -> inScope_list -> ScopeDepth = ScopeDepth;
	Scope -> inScope_list -> scopeindex = scopeindex;
	strcpy(Scope -> inScope_list -> mID, lockedID);
	strcpy(Scope -> inScope_list -> mType, mType);

	if(mType[0] == 'i')
	{
		Scope -> inScope_list ->I_data = I_data;
	}
	else if(mType[0] == 'f')
	{
		Scope -> inScope_list ->F_data = F_data;
	}

	printf("declare %s in block of depth %d\n", lockedID, Scope-> inScope_list -> ScopeDepth);

	Scope -> inScope_list -> next = malloc(sizeof(symbol_table));
	Scope -> inScope_list = Scope-> inScope_list -> next;
}

symbol_table *lookup_symbol(char const *Look_ID) // 只搜尋自己的Scope 找不到再找 mother
{
	scope *tmp = Scope;

	while(tmp -> mother != NULL)
	{
		symbol_table *ttmp  = tmp -> inScope_head;
		
		while(ttmp -> next != NULL)
		{
			if(strcmp(ttmp->mID, Look_ID) == 0)
			{
				return ttmp;
			}
			ttmp = ttmp -> next;
		}

		declaredtwice++;
		tmp = tmp -> mother;
	}

	return NULL;
}

void dump_symbol()
{
	puts("ID\tType\tData\tDepth");

	scope *tmp = MasterScope;
	symbol_table *previous;

	int i = 0;

	for ( i = 0; i <= scopeindex; i++)
	{
		symbol_table *ttmp = scopelist[i] -> inScope_head;

		while(ttmp -> next != NULL)
		{
            if(ttmp -> mType[0] == 'i')
            {
                printf("%s\t%s\t%d\t%d\n", ttmp -> mID, ttmp -> mType, ttmp->I_data, ttmp->ScopeDepth); 
            }
            else if(ttmp -> mType[0] == 'f')
            {
                printf("%s\t%s\t%g\t%d\n", ttmp -> mID, ttmp -> mType, ttmp->F_data, ttmp->ScopeDepth);
            }
			previous = ttmp;
            ttmp = ttmp -> next;

			free(previous);
		}

		free(scopelist[i]);
	}
}

float Func_Assign(char m, float flt)
{
	gbTmp = lookup_symbol(lockedID);

	if(!gbTmp)
	{   
		printf(ANSI_COLOR_RED   "<ERROR> can't find variable %s (line %d)\n"    ANSI_COLOR_RESET, lockedID, yylineno);
	}

	else
	{
		if(gbTmp->mType[0] == 'i')
		{
			switch(m)
			{
				case '=' : gbTmp->I_data = (int)flt; break;
				case '+' : gbTmp->I_data += (int)flt; break;
				case '-' : gbTmp->I_data -= (int)flt; break;
				case '*' : gbTmp->I_data *= (int)flt; break;
				case '/' : gbTmp->I_data /= (int)flt; break;
				case '%' : gbTmp->I_data %= (int)flt; break;
			}
			return (float)gbTmp->I_data;
		}
		else if(gbTmp->mType[0] == 'f')
		{
			switch(m)
			{
				case '=' : gbTmp->F_data = flt; break;
				case '+' : gbTmp->F_data += flt; break;
				case '-' : gbTmp->F_data -= flt; break;
				case '*' : gbTmp->F_data *= flt; break;
				case '/' : gbTmp->F_data /= flt; break;
				case '%' : printf(ANSI_COLOR_RED   "<ERROR> float type can't MOD (line %d)\n"    ANSI_COLOR_RESET, yylineno); break;
			}
			return gbTmp->F_data;
		}
	}
}

float IncDecFunc(char m)
{
	gbTmp = lookup_symbol(mID);
	
	if(gbTmp)
	{   
		if(gbTmp->mType[0] == 'i')
		{
			switch(m)
			{
				case '+': gbTmp -> I_data++; break; 
				case '-': gbTmp -> I_data--; break;
			}
			return (float)gbTmp->I_data;
		}
		else if(gbTmp->mType[0] == 'f')
		{
			switch(m)
			{
				case '+': gbTmp -> F_data++; break;
				case '-': gbTmp -> F_data--; break;
			}
			return gbTmp->F_data;
		}
	}
}
