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
#line 1 "parser.yy" /* yacc.c:339  */

#include "scanner.h"//se importa el header del analisis sintactico
#include <string>
#include <list>
#include <iostream>
#include <algorithm>
#include "exec.h"
#include "fdisk.h"
#include "mkdisk.h"
#include "mount.h"
#include "rep.h"
#include "rmdisk.h"
#include "unmount.h"
#include "command.h"
#include "mkfs.h"
#include "login.h"
#include "logout.h"
#include "rmgrp.h"
#include "mkgrp.h"
#include "mkusr.h"
#include "rmusr.h"
#include "chmod.h"
#include "mkfile.h"
#include "mkdir.h"

extern int yylineno; //linea actual donde se encuentra el parser (analisis lexico) lo maneja BISON
extern int columna; //columna actual donde se encuentra el parser (analisis lexico) lo maneja BISON
extern char *yytext; //lexema actual donde esta el parser (analisis lexico) lo maneja BISON
extern std::list<Command*> listCommand;
int yyerror(const char* mens)
{
    std::cout << "No se reconoce " <<yytext<<" Linea: "<< yylineno<< " Columna: " << columna << std::endl;
    return 0;
}

#line 102 "parser.cpp" /* yacc.c:339  */

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
# define YYERROR_VERBOSE 1
#endif

/* In a future release of Bison, this section will be replaced
   by #include "parser.h".  */
#ifndef YY_YY_PARSER_H_INCLUDED
# define YY_YY_PARSER_H_INCLUDED
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
    numero = 258,
    cadena = 259,
    pmkdisk = 260,
    psize = 261,
    pfit = 262,
    punit = 263,
    ppath = 264,
    prmdisk = 265,
    pfdisk = 266,
    ptype = 267,
    pdetele = 268,
    pname = 269,
    padd = 270,
    pmount = 271,
    punmount = 272,
    pid = 273,
    prep = 274,
    pexec = 275,
    id = 276,
    igual = 277,
    guion = 278,
    pb = 279,
    pk = 280,
    pm = 281,
    pbf = 282,
    pff = 283,
    pwf = 284,
    pp = 285,
    pe = 286,
    pl = 287,
    pfast = 288,
    pfull = 289,
    pmbr = 290,
    pdisk = 291,
    pmkfs = 292,
    pfs = 293,
    p2fs = 294,
    p3fs = 295,
    plogin = 296,
    pusr = 297,
    ppwd = 298,
    plogout = 299,
    prmgrp = 300,
    pmkgrp = 301,
    pmkusr = 302,
    pgrp = 303,
    prmusr = 304,
    pchmod = 305,
    pr = 306,
    pugo = 307,
    pmkfile = 308,
    pcont = 309,
    pmkdir = 310,
    ampersand = 311,
    mayorQ = 312,
    porcentaje = 313,
    pallocation = 314,
    pc = 315,
    pix = 316
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 40 "parser.yy" /* yacc.c:355  */

int NUM;
char TEXT [256];
class Exec* exec;
class Fdisk* fdisk;
class Mkdisk* mkdisk;
class Mount* mount;
class Rep* rep;
class Rmdisk* rmdisk;
class Unmount* unmount;
class Mkfs* mkfs;
class Login* login;
class Rmgrp* rmgrp;
class Mkgrp* mkgrp;
class Mkusr* mkusr;
class Rmusr* rmusr;
class Chmod* chmod;
class Mkfile* mkfile;
class Mkdir* mkdir;

#line 225 "parser.cpp" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;
int yyparse (void);

#endif /* !YY_YY_PARSER_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 256 "parser.cpp" /* yacc.c:358  */

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
#define YYFINAL  54
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   431

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  62
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  29
/* YYNRULES -- Number of rules.  */
#define YYNRULES  138
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  422

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   316

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
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
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   154,   154,   156,   157,   159,   160,   161,   162,   163,
     164,   165,   166,   167,   168,   169,   170,   171,   172,   173,
     174,   175,   176,   178,   179,   180,   181,   182,   183,   184,
     185,   187,   188,   189,   191,   192,   193,   195,   196,   198,
     200,   201,   202,   203,   204,   205,   206,   207,   208,   209,
     210,   211,   212,   213,   214,   215,   216,   217,   219,   220,
     222,   223,   224,   226,   227,   229,   230,   231,   233,   234,
     235,   236,   238,   240,   241,   242,   243,   244,   245,   247,
     248,   250,   251,   252,   254,   256,   257,   258,   259,   260,
     261,   262,   263,   265,   266,   267,   268,   269,   270,   272,
     273,   274,   275,   277,   278,   279,   280,   282,   283,   284,
     285,   286,   287,   288,   289,   291,   292,   293,   294,   296,
     297,   298,   299,   300,   301,   303,   304,   305,   306,   307,
     308,   309,   310,   312,   313,   314,   315,   316,   317
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "numero", "cadena", "pmkdisk", "psize",
  "pfit", "punit", "ppath", "prmdisk", "pfdisk", "ptype", "pdetele",
  "pname", "padd", "pmount", "punmount", "pid", "prep", "pexec", "id",
  "igual", "guion", "pb", "pk", "pm", "pbf", "pff", "pwf", "pp", "pe",
  "pl", "pfast", "pfull", "pmbr", "pdisk", "pmkfs", "pfs", "p2fs", "p3fs",
  "plogin", "pusr", "ppwd", "plogout", "prmgrp", "pmkgrp", "pmkusr",
  "pgrp", "prmusr", "pchmod", "pr", "pugo", "pmkfile", "pcont", "pmkdir",
  "ampersand", "mayorQ", "porcentaje", "pallocation", "pc", "pix",
  "$accept", "INICIO", "LCOMANDOS", "COMANDO", "PROPIEDADESMK", "AJUSTE",
  "UNIDAD", "PATH", "PROPIEDADESRM", "PROPIEDADESFD", "DELETE",
  "ALLOCATION", "E", "TYPE", "PROPIEDADESMOUNT", "PROPIEDADESUNMOUNT",
  "PROPIEDADESREP", "NAME", "VALUE", "PROPIEDADESEXEC", "PROPIEDADESMKFS",
  "PROPIEDADESLOGIN", "PROPIEDADESRMGRP", "PROPIEDADESMKGRP",
  "PROPIEDADESMKUSR", "PROPIEDADESRMUSR", "PROPIEDADESCHMOD",
  "PROPIEDADESMKFILE", "PROPIEDADESMKDIR", YY_NULLPTR
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
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316
};
# endif

#define YYPACT_NINF -267

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-267)))

#define YYTABLE_NINF -3

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     144,  -267,   -44,   -31,   -12,     1,    56,    57,    59,    31,
      40,  -267,    88,    90,    95,    97,   127,   136,   106,   113,
      26,  -267,   162,   116,   158,  -267,     7,   118,    14,   121,
     157,  -267,   101,   164,   171,  -267,   180,   151,   -13,   165,
     155,   166,   168,   172,    80,   173,   -10,   174,     8,   197,
      84,   204,   109,   176,  -267,  -267,   210,   211,   212,   213,
     195,   214,   215,   216,   217,   218,   219,   220,   221,   222,
     223,    41,   224,   225,    55,   228,   229,   230,   231,   134,
     232,   227,   233,   234,   193,   235,   236,   237,    43,   238,
     239,   182,   240,   241,   198,   242,   243,   244,   245,    94,
     246,   247,    -8,   249,  -267,   250,    32,   251,   252,  -267,
     253,    86,   254,   255,  -267,   111,   226,   248,   256,   257,
     258,   259,   261,   262,   260,   263,   264,   265,   266,   267,
     268,   269,   270,   271,   272,   273,   274,   275,   276,   277,
     278,   279,   280,   281,   282,   283,   284,  -267,    47,    67,
     287,   288,   289,   290,    47,   285,   286,   291,   292,   293,
     295,   294,   296,   297,   306,   307,   308,   298,   299,   309,
     310,   300,   301,   311,   312,   302,   303,   304,   305,   313,
     314,   317,   318,   315,   316,   321,   322,    47,   343,   325,
    -267,   327,   347,    47,    47,   330,   341,  -267,   342,   319,
     320,   344,   345,  -267,   362,   189,    47,   348,   323,   324,
     326,   328,    47,   363,   190,   189,    47,   194,    91,    47,
      15,    70,   329,   331,   332,   333,   334,   335,   336,   337,
     338,    47,    47,   339,   340,  -267,  -267,  -267,  -267,  -267,
    -267,  -267,    47,    67,   349,  -267,   132,    15,   350,   346,
     351,   352,   353,    47,     3,   354,   355,   356,    47,   357,
     358,   359,    47,   361,   360,   364,   366,     3,     3,     3,
     365,   367,   368,   369,   377,    47,   370,   371,  -267,  -267,
      47,   372,  -267,  -267,  -267,   376,    47,    47,    47,   378,
     373,   374,  -267,  -267,  -267,  -267,  -267,  -267,  -267,   381,
     189,    47,   379,  -267,  -267,  -267,  -267,  -267,  -267,  -267,
    -267,  -267,  -267,  -267,  -267,  -267,  -267,  -267,  -267,  -267,
     398,  -267,  -267,  -267,  -267,  -267,   399,   190,   189,    47,
     194,    91,    47,    15,    70,  -267,  -267,    47,    47,  -267,
    -267,  -267,  -267,  -267,  -267,  -267,   132,    15,   383,  -267,
    -267,  -267,  -267,  -267,  -267,   384,    47,     3,  -267,  -267,
      47,   385,  -267,  -267,    47,   386,  -267,  -267,  -267,  -267,
     389,     3,     3,     3,  -267,  -267,   393,    47,  -267,  -267,
    -267,  -267,  -267,  -267,  -267,    47,   397,  -267,  -267,  -267,
    -267,  -267,  -267,  -267,  -267,  -267,  -267,  -267,  -267,  -267,
    -267,  -267,  -267,  -267,  -267,  -267,  -267,  -267,  -267,  -267,
    -267,  -267,  -267,  -267,  -267,  -267,  -267,  -267,  -267,  -267,
    -267,  -267
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    22,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    14,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     4,     0,     5,     0,     6,     0,     7,     0,     8,
       0,     9,     0,    10,     0,    11,     0,    12,     0,    13,
       0,    16,     0,    15,     0,    17,     0,    18,     0,    19,
       0,    20,     0,    21,     1,     3,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   124,     0,     0,     0,     0,   130,
       0,     0,     0,     0,   137,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    72,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     121,     0,     0,     0,     0,     0,     0,   126,     0,     0,
       0,     0,     0,   135,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    37,    38,    77,    79,    80,
      76,    78,     0,     0,     0,    84,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   122,   123,
       0,     0,   131,   129,   132,     0,     0,     0,     0,     0,
       0,     0,    28,    34,    35,    36,    29,    30,    27,     0,
       0,     0,     0,    39,    49,    31,    32,    33,    56,    50,
      51,    65,    66,    67,    52,    58,    59,    53,    54,    63,
       0,    55,    61,    60,    62,    57,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    70,    71,     0,     0,    74,
      73,    75,    92,    90,    91,    89,     0,     0,     0,    98,
      96,    83,    82,    81,    97,     0,     0,     0,   101,   102,
       0,     0,   105,   106,     0,     0,   114,   111,   112,   113,
       0,     0,     0,     0,   118,   117,     0,     0,   119,   120,
     127,   125,   128,   136,   138,     0,     0,    23,    24,    25,
      26,    64,    40,    47,    41,    42,    43,    44,    45,    46,
      48,    68,    69,    88,    86,    87,    85,    95,    93,    94,
      99,   100,   103,   104,   108,   107,   109,   110,   116,   115,
     133,   134
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -267,  -267,  -267,   400,  -267,   -72,  -211,  -154,  -267,  -267,
    -237,   -58,  -236,   -51,  -267,  -267,  -267,    37,  -266,  -267,
    -267,  -267,  -267,  -267,  -267,  -267,  -267,  -267,  -267
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    19,    20,    21,    23,   308,   296,   237,    25,    27,
     317,   325,   321,   314,    29,    31,    33,   240,   354,    35,
      37,    39,    41,    43,    45,    47,    49,    51,    53
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     245,   367,   368,   369,   309,    85,   351,   352,   100,   343,
     185,   344,    22,    62,    63,    64,    65,   103,   319,    66,
      67,    68,    69,    72,   353,    24,    -2,     1,    73,    86,
      87,     2,   101,   278,   186,   342,     3,     4,   320,   283,
     284,   189,     5,     6,    26,     7,     8,   134,   135,   136,
     137,   235,   297,   138,   139,   140,   141,    28,   303,   104,
     105,   164,   310,     9,   145,   318,    70,    10,   236,   146,
      11,    12,    13,    14,    30,    15,    16,   335,   336,    17,
      32,    18,    34,   190,   191,   165,   166,    36,   339,   388,
     107,   409,   195,   108,   397,   196,    38,   399,    95,   350,
     142,   322,   238,   239,   358,   415,   416,   417,   362,   404,
      76,   405,   179,    54,   109,    77,   197,   394,   112,    78,
     201,   375,    96,    97,   315,   316,   378,   113,    98,   202,
     323,   324,   381,   382,   383,   403,   180,   181,   110,   114,
     198,   203,   182,   151,    40,     1,    42,   389,   152,     2,
      48,    44,   153,    46,     3,     4,   293,   294,   295,    50,
       5,     6,    52,     7,     8,   315,   316,    61,    56,    89,
      57,    58,    60,    90,    71,   395,    59,    74,   398,    75,
      80,     9,    92,   401,   402,    10,    93,    79,    11,    12,
      13,    14,    81,    15,    16,    82,   169,    17,    83,    18,
     170,   120,   408,   121,   122,   158,   410,    84,   159,   123,
     412,   160,   173,   293,   294,   295,   174,   305,   306,   307,
     106,    88,    91,   419,   311,   312,   313,   111,    94,    99,
     102,   420,   115,   116,   117,   118,   119,   124,   125,   126,
     127,   128,   129,   130,   131,   132,   133,   143,   144,   147,
     155,   148,   149,   150,   154,   393,   156,   157,   161,   162,
     163,   167,   168,   171,   172,   175,   176,   177,   178,   183,
     184,   187,   188,   192,   193,   194,   400,   199,   200,   396,
     340,   208,   209,   204,   210,   211,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   222,   223,   224,   225,   226,
     227,   228,   229,   230,     0,   205,   233,   234,   241,     0,
     242,   243,   244,   206,   207,   249,   250,   212,   251,     0,
     213,   214,   215,   216,   217,   218,   219,   220,   221,   255,
     256,   257,   260,   261,   264,   265,   270,   271,   231,   232,
     272,   273,   246,   247,   276,   277,   279,   280,   248,   281,
     282,   252,   285,   253,   254,   258,   259,   262,   263,   266,
     267,   268,   269,   286,   287,   292,   304,   290,   291,   298,
     341,   345,   274,   275,   349,   379,   288,   289,   359,   380,
     299,   300,   363,   301,   387,   302,   326,   366,   327,   328,
     329,   330,   331,   332,   333,   334,   337,   338,   374,   384,
     390,   391,   392,   346,   406,   407,   411,   413,   347,   348,
     414,   355,   356,   357,   418,   360,   361,   364,   421,     0,
      55,   365,   370,     0,   371,   372,   373,   376,   377,     0,
     385,   386
};

static const yytype_int16 yycheck[] =
{
     154,   267,   268,   269,   215,    18,     3,     4,    18,   246,
      18,   247,    56,     6,     7,     8,     9,     9,     3,    12,
      13,    14,    15,     9,    21,    56,     0,     1,    14,    42,
      43,     5,    42,   187,    42,   246,    10,    11,    23,   193,
     194,     9,    16,    17,    56,    19,    20,     6,     7,     8,
       9,     4,   206,    12,    13,    14,    15,    56,   212,    51,
      52,    18,   216,    37,     9,   219,    59,    41,    21,    14,
      44,    45,    46,    47,    18,    49,    50,   231,   232,    53,
      23,    55,    23,    51,    52,    42,    43,    56,   242,   300,
       6,   357,     6,     9,   331,     9,    56,   333,    18,   253,
      59,    31,    35,    36,   258,   371,   372,   373,   262,   346,
       9,   347,    18,     0,    30,    14,    30,   328,     9,    18,
       9,   275,    42,    43,    33,    34,   280,    18,    48,    18,
      60,    61,   286,   287,   288,   346,    42,    43,    54,    30,
      54,    30,    48,     9,    56,     1,    56,   301,    14,     5,
      23,    56,    18,    56,    10,    11,    24,    25,    26,    23,
      16,    17,    56,    19,    20,    33,    34,     9,     6,    14,
       8,     9,    56,    18,    56,   329,    14,    56,   332,    22,
       9,    37,    14,   337,   338,    41,    18,    23,    44,    45,
      46,    47,    12,    49,    50,    15,    14,    53,    18,    55,
      18,     6,   356,     8,     9,    12,   360,    56,    15,    14,
     364,    18,    14,    24,    25,    26,    18,    27,    28,    29,
      23,    56,    56,   377,    30,    31,    32,    23,    56,    56,
      56,   385,    56,    23,    23,    23,    23,    23,    23,    23,
      23,    23,    23,    23,    23,    23,    23,    23,    23,    21,
      23,    22,    22,    22,    22,   327,    23,    23,    23,    23,
      23,    23,    23,    23,    23,    23,    23,    23,    23,    23,
      23,    22,    22,    22,    22,    22,   334,    23,    23,   330,
     243,    23,    23,    57,    23,    23,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    23,    23,    23,    23,    23,
      23,    23,    23,    23,    -1,    57,    23,    23,    21,    -1,
      22,    22,    22,    57,    57,    23,    23,    57,    23,    -1,
      57,    57,    57,    57,    57,    57,    57,    57,    57,    23,
      23,    23,    23,    23,    23,    23,    23,    23,    57,    57,
      23,    23,    57,    57,    23,    23,     3,    22,    57,    22,
       3,    57,    22,    57,    57,    57,    57,    57,    57,    57,
      57,    57,    57,    22,    22,     3,     3,    23,    23,    21,
      21,    21,    57,    57,    21,     3,    57,    57,    21,     3,
      57,    57,    21,    57,     3,    57,    57,    21,    57,    57,
      57,    57,    57,    57,    57,    57,    57,    57,    21,    21,
      21,     3,     3,    57,    21,    21,    21,    21,    57,    57,
      21,    57,    57,    57,    21,    57,    57,    57,    21,    -1,
      20,    57,    57,    -1,    57,    57,    57,    57,    57,    -1,
      57,    57
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,     5,    10,    11,    16,    17,    19,    20,    37,
      41,    44,    45,    46,    47,    49,    50,    53,    55,    63,
      64,    65,    56,    66,    56,    70,    56,    71,    56,    76,
      18,    77,    23,    78,    23,    81,    56,    82,    56,    83,
      56,    84,    56,    85,    56,    86,    56,    87,    23,    88,
      23,    89,    56,    90,     0,    65,     6,     8,     9,    14,
      56,     9,     6,     7,     8,     9,    12,    13,    14,    15,
      59,    56,     9,    14,    56,    22,     9,    14,    18,    23,
       9,    12,    15,    18,    56,    18,    42,    43,    56,    14,
      18,    56,    14,    18,    56,    18,    42,    43,    48,    56,
      18,    42,    56,     9,    51,    52,    23,     6,     9,    30,
      54,    23,     9,    18,    30,    56,    23,    23,    23,    23,
       6,     8,     9,    14,    23,    23,    23,    23,    23,    23,
      23,    23,    23,    23,     6,     7,     8,     9,    12,    13,
      14,    15,    59,    23,    23,     9,    14,    21,    22,    22,
      22,     9,    14,    18,    22,    23,    23,    23,    12,    15,
      18,    23,    23,    23,    18,    42,    43,    23,    23,    14,
      18,    23,    23,    14,    18,    23,    23,    23,    23,    18,
      42,    43,    48,    23,    23,    18,    42,    22,    22,     9,
      51,    52,    22,    22,    22,     6,     9,    30,    54,    23,
      23,     9,    18,    30,    57,    57,    57,    57,    23,    23,
      23,    23,    57,    57,    57,    57,    57,    57,    57,    57,
      57,    57,    23,    23,    23,    23,    23,    23,    23,    23,
      23,    57,    57,    23,    23,     4,    21,    69,    35,    36,
      79,    21,    22,    22,    22,    69,    57,    57,    57,    23,
      23,    23,    57,    57,    57,    23,    23,    23,    57,    57,
      23,    23,    57,    57,    23,    23,    57,    57,    57,    57,
      23,    23,    23,    23,    57,    57,    23,    23,    69,     3,
      22,    22,     3,    69,    69,    22,    22,    22,    57,    57,
      23,    23,     3,    24,    25,    26,    68,    69,    21,    57,
      57,    57,    57,    69,     3,    27,    28,    29,    67,    68,
      69,    30,    31,    32,    75,    33,    34,    72,    69,     3,
      23,    74,    31,    60,    61,    73,    57,    57,    57,    57,
      57,    57,    57,    57,    57,    69,    69,    57,    57,    69,
      79,    21,    68,    72,    74,    21,    57,    57,    57,    21,
      69,     3,     4,    21,    80,    57,    57,    57,    69,    21,
      57,    57,    69,    21,    57,    57,    21,    80,    80,    80,
      57,    57,    57,    57,    21,    69,    57,    57,    69,     3,
       3,    69,    69,    69,    21,    57,    57,     3,    68,    69,
      21,     3,     3,    67,    68,    69,    75,    72,    69,    74,
      73,    69,    69,    68,    72,    74,    21,    21,    69,    80,
      69,    21,    69,    21,    21,    80,    80,    80,    21,    69,
      69,    21
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    62,    63,    64,    64,    65,    65,    65,    65,    65,
      65,    65,    65,    65,    65,    65,    65,    65,    65,    65,
      65,    65,    65,    66,    66,    66,    66,    66,    66,    66,
      66,    67,    67,    67,    68,    68,    68,    69,    69,    70,
      71,    71,    71,    71,    71,    71,    71,    71,    71,    71,
      71,    71,    71,    71,    71,    71,    71,    71,    72,    72,
      73,    73,    73,    74,    74,    75,    75,    75,    76,    76,
      76,    76,    77,    78,    78,    78,    78,    78,    78,    79,
      79,    80,    80,    80,    81,    82,    82,    82,    82,    82,
      82,    82,    82,    83,    83,    83,    83,    83,    83,    84,
      84,    84,    84,    85,    85,    85,    85,    86,    86,    86,
      86,    86,    86,    86,    86,    87,    87,    87,    87,    88,
      88,    88,    88,    88,    88,    89,    89,    89,    89,    89,
      89,    89,    89,    90,    90,    90,    90,    90,    90
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     1,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     1,     2,     2,     2,     2,     2,
       2,     2,     1,     6,     6,     6,     6,     5,     5,     5,
       5,     1,     1,     1,     1,     1,     1,     1,     1,     5,
       6,     6,     6,     6,     6,     6,     6,     6,     6,     5,
       5,     5,     5,     5,     5,     5,     5,     5,     1,     1,
       1,     1,     1,     1,     2,     1,     1,     1,     6,     6,
       5,     5,     3,     5,     5,     5,     4,     4,     4,     1,
       1,     1,     1,     1,     4,     6,     6,     6,     6,     5,
       5,     5,     5,     6,     6,     6,     5,     5,     5,     6,
       6,     5,     5,     6,     6,     5,     5,     6,     6,     6,
       6,     5,     5,     5,     5,     6,     6,     5,     5,     5,
       5,     3,     4,     4,     2,     5,     3,     5,     5,     4,
       2,     4,     4,     6,     6,     3,     5,     2,     5
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


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
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
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


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


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static unsigned
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  unsigned res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
 }

#  define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  YYUSE (yylocationp);
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
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp);
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
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
                       , &(yylsp[(yyi + 1) - (yynrhs)])                       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
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
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
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
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
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
       'yyls': related to locations.

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

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yylsp = yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  yylsp[0] = yylloc;
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
     '$$ = $1'.

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
        case 5:
#line 159 "parser.yy" /* yacc.c:1646  */
    { listCommand.push_back((yyvsp[0].mkdisk)); }
#line 1696 "parser.cpp" /* yacc.c:1646  */
    break;

  case 6:
#line 160 "parser.yy" /* yacc.c:1646  */
    { listCommand.push_back((yyvsp[0].rmdisk)); }
#line 1702 "parser.cpp" /* yacc.c:1646  */
    break;

  case 7:
#line 161 "parser.yy" /* yacc.c:1646  */
    { listCommand.push_back((yyvsp[0].fdisk)); }
#line 1708 "parser.cpp" /* yacc.c:1646  */
    break;

  case 8:
#line 162 "parser.yy" /* yacc.c:1646  */
    { listCommand.push_back((yyvsp[0].mount)); }
#line 1714 "parser.cpp" /* yacc.c:1646  */
    break;

  case 9:
#line 163 "parser.yy" /* yacc.c:1646  */
    { listCommand.push_back((yyvsp[0].unmount)); }
#line 1720 "parser.cpp" /* yacc.c:1646  */
    break;

  case 10:
#line 164 "parser.yy" /* yacc.c:1646  */
    { listCommand.push_back((yyvsp[0].rep)); }
#line 1726 "parser.cpp" /* yacc.c:1646  */
    break;

  case 11:
#line 165 "parser.yy" /* yacc.c:1646  */
    { listCommand.push_back((yyvsp[0].exec)); }
#line 1732 "parser.cpp" /* yacc.c:1646  */
    break;

  case 12:
#line 166 "parser.yy" /* yacc.c:1646  */
    { listCommand.push_back((yyvsp[0].mkfs)); }
#line 1738 "parser.cpp" /* yacc.c:1646  */
    break;

  case 13:
#line 167 "parser.yy" /* yacc.c:1646  */
    { listCommand.push_back((yyvsp[0].login)); }
#line 1744 "parser.cpp" /* yacc.c:1646  */
    break;

  case 14:
#line 168 "parser.yy" /* yacc.c:1646  */
    { listCommand.push_back(new Logout()); }
#line 1750 "parser.cpp" /* yacc.c:1646  */
    break;

  case 15:
#line 169 "parser.yy" /* yacc.c:1646  */
    { listCommand.push_back((yyvsp[0].mkgrp)); }
#line 1756 "parser.cpp" /* yacc.c:1646  */
    break;

  case 16:
#line 170 "parser.yy" /* yacc.c:1646  */
    { listCommand.push_back((yyvsp[0].rmgrp)); }
#line 1762 "parser.cpp" /* yacc.c:1646  */
    break;

  case 17:
#line 171 "parser.yy" /* yacc.c:1646  */
    { listCommand.push_back((yyvsp[0].mkusr)); }
#line 1768 "parser.cpp" /* yacc.c:1646  */
    break;

  case 18:
#line 172 "parser.yy" /* yacc.c:1646  */
    { listCommand.push_back((yyvsp[0].rmusr)); }
#line 1774 "parser.cpp" /* yacc.c:1646  */
    break;

  case 19:
#line 173 "parser.yy" /* yacc.c:1646  */
    { listCommand.push_back((yyvsp[0].chmod)); }
#line 1780 "parser.cpp" /* yacc.c:1646  */
    break;

  case 20:
#line 174 "parser.yy" /* yacc.c:1646  */
    { listCommand.push_back((yyvsp[0].mkfile)); }
#line 1786 "parser.cpp" /* yacc.c:1646  */
    break;

  case 21:
#line 175 "parser.yy" /* yacc.c:1646  */
    { listCommand.push_back((yyvsp[0].mkdir)); }
#line 1792 "parser.cpp" /* yacc.c:1646  */
    break;

  case 23:
#line 178 "parser.yy" /* yacc.c:1646  */
    { (yyval.mkdisk) = (yyvsp[-5].mkdisk); (yyval.mkdisk)->size = std::stoi((yyvsp[0].TEXT)); }
#line 1798 "parser.cpp" /* yacc.c:1646  */
    break;

  case 24:
#line 179 "parser.yy" /* yacc.c:1646  */
    { (yyval.mkdisk) = (yyvsp[-5].mkdisk); (yyval.mkdisk)->unit = (yyvsp[0].TEXT); }
#line 1804 "parser.cpp" /* yacc.c:1646  */
    break;

  case 25:
#line 180 "parser.yy" /* yacc.c:1646  */
    { (yyval.mkdisk) = (yyvsp[-5].mkdisk); (yyval.mkdisk)->path = (yyvsp[0].TEXT); }
#line 1810 "parser.cpp" /* yacc.c:1646  */
    break;

  case 26:
#line 181 "parser.yy" /* yacc.c:1646  */
    { (yyval.mkdisk) = (yyvsp[-5].mkdisk); (yyval.mkdisk)->name = (yyvsp[0].TEXT); }
#line 1816 "parser.cpp" /* yacc.c:1646  */
    break;

  case 27:
#line 182 "parser.yy" /* yacc.c:1646  */
    { (yyval.mkdisk) = new Mkdisk(); (yyval.mkdisk)->name = (yyvsp[0].TEXT); }
#line 1822 "parser.cpp" /* yacc.c:1646  */
    break;

  case 28:
#line 183 "parser.yy" /* yacc.c:1646  */
    { (yyval.mkdisk) =  new Mkdisk(); (yyval.mkdisk)->size = std::stoi((yyvsp[0].TEXT)); }
#line 1828 "parser.cpp" /* yacc.c:1646  */
    break;

  case 29:
#line 184 "parser.yy" /* yacc.c:1646  */
    { (yyval.mkdisk) = new Mkdisk(); (yyval.mkdisk)->unit = (yyvsp[0].TEXT); }
#line 1834 "parser.cpp" /* yacc.c:1646  */
    break;

  case 30:
#line 185 "parser.yy" /* yacc.c:1646  */
    { (yyval.mkdisk) = new Mkdisk(); (yyval.mkdisk)->path = (yyvsp[0].TEXT); }
#line 1840 "parser.cpp" /* yacc.c:1646  */
    break;

  case 31:
#line 187 "parser.yy" /* yacc.c:1646  */
    { strcpy((yyval.TEXT), "bf"); }
#line 1846 "parser.cpp" /* yacc.c:1646  */
    break;

  case 32:
#line 188 "parser.yy" /* yacc.c:1646  */
    { strcpy((yyval.TEXT), "ff"); }
#line 1852 "parser.cpp" /* yacc.c:1646  */
    break;

  case 33:
#line 189 "parser.yy" /* yacc.c:1646  */
    { strcpy((yyval.TEXT), "wf"); }
#line 1858 "parser.cpp" /* yacc.c:1646  */
    break;

  case 34:
#line 191 "parser.yy" /* yacc.c:1646  */
    { strcpy((yyval.TEXT), "b"); }
#line 1864 "parser.cpp" /* yacc.c:1646  */
    break;

  case 35:
#line 192 "parser.yy" /* yacc.c:1646  */
    { strcpy((yyval.TEXT), "k"); }
#line 1870 "parser.cpp" /* yacc.c:1646  */
    break;

  case 36:
#line 193 "parser.yy" /* yacc.c:1646  */
    { strcpy((yyval.TEXT), "m"); }
#line 1876 "parser.cpp" /* yacc.c:1646  */
    break;

  case 37:
#line 195 "parser.yy" /* yacc.c:1646  */
    { std::string text = (yyvsp[0].TEXT); text.replace(0,1,""); text.replace(text.length()-1, 1, ""); strcpy((yyval.TEXT), text.c_str()); }
#line 1882 "parser.cpp" /* yacc.c:1646  */
    break;

  case 38:
#line 196 "parser.yy" /* yacc.c:1646  */
    { strcpy((yyval.TEXT), (yyvsp[0].TEXT)); }
#line 1888 "parser.cpp" /* yacc.c:1646  */
    break;

  case 39:
#line 198 "parser.yy" /* yacc.c:1646  */
    { (yyval.rmdisk) = new Rmdisk(); (yyval.rmdisk)->path = (yyvsp[0].TEXT); }
#line 1894 "parser.cpp" /* yacc.c:1646  */
    break;

  case 40:
#line 200 "parser.yy" /* yacc.c:1646  */
    { (yyval.fdisk) = (yyvsp[-5].fdisk); (yyval.fdisk)->size = std::stoi((yyvsp[0].TEXT)); }
#line 1900 "parser.cpp" /* yacc.c:1646  */
    break;

  case 41:
#line 201 "parser.yy" /* yacc.c:1646  */
    { (yyval.fdisk) = (yyvsp[-5].fdisk); (yyval.fdisk)->unit = (yyvsp[0].TEXT); }
#line 1906 "parser.cpp" /* yacc.c:1646  */
    break;

  case 42:
#line 202 "parser.yy" /* yacc.c:1646  */
    { (yyval.fdisk) = (yyvsp[-5].fdisk); (yyval.fdisk)->path = (yyvsp[0].TEXT); }
#line 1912 "parser.cpp" /* yacc.c:1646  */
    break;

  case 43:
#line 203 "parser.yy" /* yacc.c:1646  */
    { (yyval.fdisk) = (yyvsp[-5].fdisk); (yyval.fdisk)->type = (yyvsp[0].TEXT); }
#line 1918 "parser.cpp" /* yacc.c:1646  */
    break;

  case 44:
#line 204 "parser.yy" /* yacc.c:1646  */
    { (yyval.fdisk) = (yyvsp[-5].fdisk); (yyval.fdisk)->toDelete = (yyvsp[0].TEXT); }
#line 1924 "parser.cpp" /* yacc.c:1646  */
    break;

  case 45:
#line 205 "parser.yy" /* yacc.c:1646  */
    { (yyval.fdisk) = (yyvsp[-5].fdisk); (yyval.fdisk)->name = (yyvsp[0].TEXT); }
#line 1930 "parser.cpp" /* yacc.c:1646  */
    break;

  case 46:
#line 206 "parser.yy" /* yacc.c:1646  */
    { (yyval.fdisk) = (yyvsp[-5].fdisk); (yyval.fdisk)->add = (yyvsp[0].NUM); (yyval.fdisk)->isAdd = true; }
#line 1936 "parser.cpp" /* yacc.c:1646  */
    break;

  case 47:
#line 207 "parser.yy" /* yacc.c:1646  */
    { (yyval.fdisk) = (yyvsp[-5].fdisk); (yyval.fdisk)->fit = (yyvsp[0].TEXT); }
#line 1942 "parser.cpp" /* yacc.c:1646  */
    break;

  case 48:
#line 208 "parser.yy" /* yacc.c:1646  */
    { (yyval.fdisk) = (yyvsp[-5].fdisk); (yyval.fdisk)->allocation = (yyvsp[0].TEXT); }
#line 1948 "parser.cpp" /* yacc.c:1646  */
    break;

  case 49:
#line 209 "parser.yy" /* yacc.c:1646  */
    { (yyval.fdisk) = new Fdisk(); (yyval.fdisk)->size = std::stoi((yyvsp[0].TEXT)); }
#line 1954 "parser.cpp" /* yacc.c:1646  */
    break;

  case 50:
#line 210 "parser.yy" /* yacc.c:1646  */
    { (yyval.fdisk) = new Fdisk(); (yyval.fdisk)->unit = (yyvsp[0].TEXT); }
#line 1960 "parser.cpp" /* yacc.c:1646  */
    break;

  case 51:
#line 211 "parser.yy" /* yacc.c:1646  */
    { (yyval.fdisk) = new Fdisk(); (yyval.fdisk)->path = (yyvsp[0].TEXT); }
#line 1966 "parser.cpp" /* yacc.c:1646  */
    break;

  case 52:
#line 212 "parser.yy" /* yacc.c:1646  */
    { (yyval.fdisk) = new Fdisk(); (yyval.fdisk)->type = (yyvsp[0].TEXT); }
#line 1972 "parser.cpp" /* yacc.c:1646  */
    break;

  case 53:
#line 213 "parser.yy" /* yacc.c:1646  */
    { (yyval.fdisk) = new Fdisk(); (yyval.fdisk)->toDelete = (yyvsp[0].TEXT); }
#line 1978 "parser.cpp" /* yacc.c:1646  */
    break;

  case 54:
#line 214 "parser.yy" /* yacc.c:1646  */
    { (yyval.fdisk) = new Fdisk(); (yyval.fdisk)->name = (yyvsp[0].TEXT); }
#line 1984 "parser.cpp" /* yacc.c:1646  */
    break;

  case 55:
#line 215 "parser.yy" /* yacc.c:1646  */
    { (yyval.fdisk) = new Fdisk(); (yyval.fdisk)->add = (yyvsp[0].NUM); (yyval.fdisk)->isAdd = true; }
#line 1990 "parser.cpp" /* yacc.c:1646  */
    break;

  case 56:
#line 216 "parser.yy" /* yacc.c:1646  */
    { (yyval.fdisk) = new Fdisk(); (yyval.fdisk)->fit = (yyvsp[0].TEXT); }
#line 1996 "parser.cpp" /* yacc.c:1646  */
    break;

  case 57:
#line 217 "parser.yy" /* yacc.c:1646  */
    { (yyval.fdisk) = new Fdisk(); (yyval.fdisk)->fit = (yyvsp[0].TEXT); }
#line 2002 "parser.cpp" /* yacc.c:1646  */
    break;

  case 58:
#line 219 "parser.yy" /* yacc.c:1646  */
    { strcpy((yyval.TEXT), "fast"); }
#line 2008 "parser.cpp" /* yacc.c:1646  */
    break;

  case 59:
#line 220 "parser.yy" /* yacc.c:1646  */
    { strcpy((yyval.TEXT), "full"); }
#line 2014 "parser.cpp" /* yacc.c:1646  */
    break;

  case 60:
#line 222 "parser.yy" /* yacc.c:1646  */
    { strcpy((yyval.TEXT), "c"); }
#line 2020 "parser.cpp" /* yacc.c:1646  */
    break;

  case 61:
#line 223 "parser.yy" /* yacc.c:1646  */
    { strcpy((yyval.TEXT), "e"); }
#line 2026 "parser.cpp" /* yacc.c:1646  */
    break;

  case 62:
#line 224 "parser.yy" /* yacc.c:1646  */
    { strcpy((yyval.TEXT), "ix"); }
#line 2032 "parser.cpp" /* yacc.c:1646  */
    break;

  case 63:
#line 226 "parser.yy" /* yacc.c:1646  */
    { (yyval.NUM) = std::stoi((yyvsp[0].TEXT)); }
#line 2038 "parser.cpp" /* yacc.c:1646  */
    break;

  case 64:
#line 227 "parser.yy" /* yacc.c:1646  */
    { (yyval.NUM) = (-1) * std::stoi((yyvsp[0].TEXT)); }
#line 2044 "parser.cpp" /* yacc.c:1646  */
    break;

  case 65:
#line 229 "parser.yy" /* yacc.c:1646  */
    { strcpy((yyval.TEXT), "p"); }
#line 2050 "parser.cpp" /* yacc.c:1646  */
    break;

  case 66:
#line 230 "parser.yy" /* yacc.c:1646  */
    { strcpy((yyval.TEXT), "e"); }
#line 2056 "parser.cpp" /* yacc.c:1646  */
    break;

  case 67:
#line 231 "parser.yy" /* yacc.c:1646  */
    { strcpy((yyval.TEXT), "l"); }
#line 2062 "parser.cpp" /* yacc.c:1646  */
    break;

  case 68:
#line 233 "parser.yy" /* yacc.c:1646  */
    { (yyval.mount) = (yyvsp[-5].mount); (yyval.mount)->path = (yyvsp[0].TEXT); }
#line 2068 "parser.cpp" /* yacc.c:1646  */
    break;

  case 69:
#line 234 "parser.yy" /* yacc.c:1646  */
    { (yyval.mount) = (yyvsp[-5].mount); (yyval.mount)->name = (yyvsp[0].TEXT); }
#line 2074 "parser.cpp" /* yacc.c:1646  */
    break;

  case 70:
#line 235 "parser.yy" /* yacc.c:1646  */
    { (yyval.mount) = new Mount(); (yyval.mount)->path = (yyvsp[0].TEXT); }
#line 2080 "parser.cpp" /* yacc.c:1646  */
    break;

  case 71:
#line 236 "parser.yy" /* yacc.c:1646  */
    { (yyval.mount) = new Mount(); (yyval.mount)->name = (yyvsp[0].TEXT); }
#line 2086 "parser.cpp" /* yacc.c:1646  */
    break;

  case 72:
#line 238 "parser.yy" /* yacc.c:1646  */
    { (yyval.unmount) = new Unmount(); (yyval.unmount)->id = (yyvsp[0].TEXT); }
#line 2092 "parser.cpp" /* yacc.c:1646  */
    break;

  case 73:
#line 240 "parser.yy" /* yacc.c:1646  */
    { (yyval.rep) = (yyvsp[-4].rep); (yyval.rep)->name = (yyvsp[0].TEXT); }
#line 2098 "parser.cpp" /* yacc.c:1646  */
    break;

  case 74:
#line 241 "parser.yy" /* yacc.c:1646  */
    { (yyval.rep) = (yyvsp[-4].rep); (yyval.rep)->path = (yyvsp[0].TEXT); }
#line 2104 "parser.cpp" /* yacc.c:1646  */
    break;

  case 75:
#line 242 "parser.yy" /* yacc.c:1646  */
    { (yyval.rep) = (yyvsp[-4].rep); (yyval.rep)->id = (yyvsp[0].TEXT); }
#line 2110 "parser.cpp" /* yacc.c:1646  */
    break;

  case 76:
#line 243 "parser.yy" /* yacc.c:1646  */
    { (yyval.rep) = new Rep(); (yyval.rep)->name = (yyvsp[0].TEXT); }
#line 2116 "parser.cpp" /* yacc.c:1646  */
    break;

  case 77:
#line 244 "parser.yy" /* yacc.c:1646  */
    { (yyval.rep) = new Rep(); (yyval.rep)->path = (yyvsp[0].TEXT); }
#line 2122 "parser.cpp" /* yacc.c:1646  */
    break;

  case 78:
#line 245 "parser.yy" /* yacc.c:1646  */
    { (yyval.rep) = new Rep(); (yyval.rep)->id = (yyvsp[0].TEXT); }
#line 2128 "parser.cpp" /* yacc.c:1646  */
    break;

  case 79:
#line 247 "parser.yy" /* yacc.c:1646  */
    { strcpy((yyval.TEXT), "mbr"); }
#line 2134 "parser.cpp" /* yacc.c:1646  */
    break;

  case 80:
#line 248 "parser.yy" /* yacc.c:1646  */
    { strcpy((yyval.TEXT), "disk"); }
#line 2140 "parser.cpp" /* yacc.c:1646  */
    break;

  case 81:
#line 250 "parser.yy" /* yacc.c:1646  */
    { strcpy((yyval.TEXT), (yyvsp[0].TEXT)); }
#line 2146 "parser.cpp" /* yacc.c:1646  */
    break;

  case 82:
#line 251 "parser.yy" /* yacc.c:1646  */
    { std::string text = (yyvsp[0].TEXT); text.replace(0,1,""); text.replace(text.length()-1, 1, ""); strcpy((yyval.TEXT), text.c_str()); }
#line 2152 "parser.cpp" /* yacc.c:1646  */
    break;

  case 83:
#line 252 "parser.yy" /* yacc.c:1646  */
    { strcpy((yyval.TEXT), (yyvsp[0].TEXT)); }
#line 2158 "parser.cpp" /* yacc.c:1646  */
    break;

  case 84:
#line 254 "parser.yy" /* yacc.c:1646  */
    { (yyval.exec) = new Exec(); (yyval.exec)->path = (yyvsp[0].TEXT); }
#line 2164 "parser.cpp" /* yacc.c:1646  */
    break;

  case 85:
#line 256 "parser.yy" /* yacc.c:1646  */
    { (yyval.mkfs) = (yyvsp[-5].mkfs); (yyval.mkfs)->id = (yyvsp[0].TEXT); }
#line 2170 "parser.cpp" /* yacc.c:1646  */
    break;

  case 86:
#line 257 "parser.yy" /* yacc.c:1646  */
    { (yyval.mkfs) = (yyvsp[-5].mkfs); (yyval.mkfs)->type = (yyvsp[0].TEXT); }
#line 2176 "parser.cpp" /* yacc.c:1646  */
    break;

  case 87:
#line 258 "parser.yy" /* yacc.c:1646  */
    { (yyval.mkfs) = (yyvsp[-5].mkfs); (yyval.mkfs)->add = (yyvsp[0].NUM); (yyval.mkfs)->isAdd = true; }
#line 2182 "parser.cpp" /* yacc.c:1646  */
    break;

  case 88:
#line 259 "parser.yy" /* yacc.c:1646  */
    { (yyval.mkfs) = (yyvsp[-5].mkfs); (yyval.mkfs)->unit = (yyvsp[0].TEXT); }
#line 2188 "parser.cpp" /* yacc.c:1646  */
    break;

  case 89:
#line 260 "parser.yy" /* yacc.c:1646  */
    { (yyval.mkfs) = new Mkfs(); (yyval.mkfs)->id = (yyvsp[0].TEXT); }
#line 2194 "parser.cpp" /* yacc.c:1646  */
    break;

  case 90:
#line 261 "parser.yy" /* yacc.c:1646  */
    { (yyval.mkfs) = new Mkfs(); (yyval.mkfs)->type = (yyvsp[0].TEXT); }
#line 2200 "parser.cpp" /* yacc.c:1646  */
    break;

  case 91:
#line 262 "parser.yy" /* yacc.c:1646  */
    { (yyval.mkfs) = new Mkfs(); (yyval.mkfs)->add = (yyvsp[0].NUM); (yyval.mkfs)->isAdd = true; }
#line 2206 "parser.cpp" /* yacc.c:1646  */
    break;

  case 92:
#line 263 "parser.yy" /* yacc.c:1646  */
    { (yyval.mkfs) = new Mkfs(); (yyval.mkfs)->unit = (yyvsp[0].TEXT); }
#line 2212 "parser.cpp" /* yacc.c:1646  */
    break;

  case 93:
#line 265 "parser.yy" /* yacc.c:1646  */
    { (yyval.login) = (yyvsp[-5].login); (yyval.login)->usr = (yyvsp[0].TEXT); }
#line 2218 "parser.cpp" /* yacc.c:1646  */
    break;

  case 94:
#line 266 "parser.yy" /* yacc.c:1646  */
    { (yyval.login) = (yyvsp[-5].login); (yyval.login)->pwd = (yyvsp[0].TEXT); }
#line 2224 "parser.cpp" /* yacc.c:1646  */
    break;

  case 95:
#line 267 "parser.yy" /* yacc.c:1646  */
    { (yyval.login) = (yyvsp[-5].login); (yyval.login)->id = (yyvsp[0].TEXT); }
#line 2230 "parser.cpp" /* yacc.c:1646  */
    break;

  case 96:
#line 268 "parser.yy" /* yacc.c:1646  */
    { (yyval.login) = new Login(); (yyval.login)->usr = (yyvsp[0].TEXT); }
#line 2236 "parser.cpp" /* yacc.c:1646  */
    break;

  case 97:
#line 269 "parser.yy" /* yacc.c:1646  */
    { (yyval.login) = new Login(); (yyval.login)->pwd = (yyvsp[0].TEXT); }
#line 2242 "parser.cpp" /* yacc.c:1646  */
    break;

  case 98:
#line 270 "parser.yy" /* yacc.c:1646  */
    { (yyval.login) = new Login(); (yyval.login)->id = (yyvsp[0].TEXT); }
#line 2248 "parser.cpp" /* yacc.c:1646  */
    break;

  case 99:
#line 272 "parser.yy" /* yacc.c:1646  */
    { (yyval.rmgrp) = (yyvsp[-5].rmgrp); (yyval.rmgrp)->name = (yyvsp[0].TEXT); }
#line 2254 "parser.cpp" /* yacc.c:1646  */
    break;

  case 100:
#line 273 "parser.yy" /* yacc.c:1646  */
    { (yyval.rmgrp) = (yyvsp[-5].rmgrp); (yyval.rmgrp)->id = (yyvsp[0].TEXT); }
#line 2260 "parser.cpp" /* yacc.c:1646  */
    break;

  case 101:
#line 274 "parser.yy" /* yacc.c:1646  */
    { (yyval.rmgrp) = new Rmgrp(); (yyval.rmgrp)->name = (yyvsp[0].TEXT); }
#line 2266 "parser.cpp" /* yacc.c:1646  */
    break;

  case 102:
#line 275 "parser.yy" /* yacc.c:1646  */
    { (yyval.rmgrp) = new Rmgrp(); (yyval.rmgrp)->id = (yyvsp[0].TEXT); }
#line 2272 "parser.cpp" /* yacc.c:1646  */
    break;

  case 103:
#line 277 "parser.yy" /* yacc.c:1646  */
    { (yyval.mkgrp) = (yyvsp[-5].mkgrp); (yyval.mkgrp)->name = (yyvsp[0].TEXT); }
#line 2278 "parser.cpp" /* yacc.c:1646  */
    break;

  case 104:
#line 278 "parser.yy" /* yacc.c:1646  */
    { (yyval.mkgrp) = (yyvsp[-5].mkgrp); (yyval.mkgrp)->id = (yyvsp[0].TEXT); }
#line 2284 "parser.cpp" /* yacc.c:1646  */
    break;

  case 105:
#line 279 "parser.yy" /* yacc.c:1646  */
    { (yyval.mkgrp) = new Mkgrp(); (yyval.mkgrp)->name = (yyvsp[0].TEXT); }
#line 2290 "parser.cpp" /* yacc.c:1646  */
    break;

  case 106:
#line 280 "parser.yy" /* yacc.c:1646  */
    { (yyval.mkgrp) = new Mkgrp(); (yyval.mkgrp)->id = (yyvsp[0].TEXT); }
#line 2296 "parser.cpp" /* yacc.c:1646  */
    break;

  case 107:
#line 282 "parser.yy" /* yacc.c:1646  */
    { (yyval.mkusr) = (yyvsp[-5].mkusr); (yyval.mkusr)->usr = (yyvsp[0].TEXT); }
#line 2302 "parser.cpp" /* yacc.c:1646  */
    break;

  case 108:
#line 283 "parser.yy" /* yacc.c:1646  */
    { (yyval.mkusr) = (yyvsp[-5].mkusr); (yyval.mkusr)->id = (yyvsp[0].TEXT); }
#line 2308 "parser.cpp" /* yacc.c:1646  */
    break;

  case 109:
#line 284 "parser.yy" /* yacc.c:1646  */
    { (yyval.mkusr) = (yyvsp[-5].mkusr); (yyval.mkusr)->pwd = (yyvsp[0].TEXT); }
#line 2314 "parser.cpp" /* yacc.c:1646  */
    break;

  case 110:
#line 285 "parser.yy" /* yacc.c:1646  */
    { (yyval.mkusr) = (yyvsp[-5].mkusr); (yyval.mkusr)->grp = (yyvsp[0].TEXT); }
#line 2320 "parser.cpp" /* yacc.c:1646  */
    break;

  case 111:
#line 286 "parser.yy" /* yacc.c:1646  */
    { (yyval.mkusr) = new Mkusr(); (yyval.mkusr)->usr = (yyvsp[0].TEXT); }
#line 2326 "parser.cpp" /* yacc.c:1646  */
    break;

  case 112:
#line 287 "parser.yy" /* yacc.c:1646  */
    { (yyval.mkusr) = new Mkusr(); (yyval.mkusr)->pwd = (yyvsp[0].TEXT); }
#line 2332 "parser.cpp" /* yacc.c:1646  */
    break;

  case 113:
#line 288 "parser.yy" /* yacc.c:1646  */
    { (yyval.mkusr) = new Mkusr(); (yyval.mkusr)->grp = (yyvsp[0].TEXT); }
#line 2338 "parser.cpp" /* yacc.c:1646  */
    break;

  case 114:
#line 289 "parser.yy" /* yacc.c:1646  */
    { (yyval.mkusr) = new Mkusr(); (yyvsp[-4].TEXT); (yyval.mkusr)->id = (yyvsp[0].TEXT); }
#line 2344 "parser.cpp" /* yacc.c:1646  */
    break;

  case 115:
#line 291 "parser.yy" /* yacc.c:1646  */
    { (yyval.rmusr) = (yyvsp[-5].rmusr); (yyval.rmusr)->usr = (yyvsp[0].TEXT); }
#line 2350 "parser.cpp" /* yacc.c:1646  */
    break;

  case 116:
#line 292 "parser.yy" /* yacc.c:1646  */
    { (yyval.rmusr) = (yyvsp[-5].rmusr); (yyval.rmusr)->id = (yyvsp[0].TEXT); }
#line 2356 "parser.cpp" /* yacc.c:1646  */
    break;

  case 117:
#line 293 "parser.yy" /* yacc.c:1646  */
    { (yyval.rmusr) = new Rmusr(); (yyval.rmusr)->usr = (yyvsp[0].TEXT); }
#line 2362 "parser.cpp" /* yacc.c:1646  */
    break;

  case 118:
#line 294 "parser.yy" /* yacc.c:1646  */
    { (yyval.rmusr) = new Rmusr(); (yyval.rmusr)->id = (yyvsp[0].TEXT); }
#line 2368 "parser.cpp" /* yacc.c:1646  */
    break;

  case 119:
#line 296 "parser.yy" /* yacc.c:1646  */
    { (yyval.chmod) = (yyvsp[-4].chmod); (yyval.chmod)->path = (yyvsp[0].TEXT); }
#line 2374 "parser.cpp" /* yacc.c:1646  */
    break;

  case 120:
#line 297 "parser.yy" /* yacc.c:1646  */
    { (yyval.chmod) = (yyvsp[-4].chmod); (yyval.chmod)->ugo = std::stoi((yyvsp[0].TEXT)); }
#line 2380 "parser.cpp" /* yacc.c:1646  */
    break;

  case 121:
#line 298 "parser.yy" /* yacc.c:1646  */
    { (yyval.chmod) = (yyvsp[-2].chmod); (yyval.chmod)->isRecursive = true; }
#line 2386 "parser.cpp" /* yacc.c:1646  */
    break;

  case 122:
#line 299 "parser.yy" /* yacc.c:1646  */
    { (yyval.chmod) = new Chmod(); (yyval.chmod)->path = (yyvsp[0].TEXT); }
#line 2392 "parser.cpp" /* yacc.c:1646  */
    break;

  case 123:
#line 300 "parser.yy" /* yacc.c:1646  */
    { (yyval.chmod) = new Chmod(); (yyval.chmod)->ugo = std::stoi((yyvsp[0].TEXT)); }
#line 2398 "parser.cpp" /* yacc.c:1646  */
    break;

  case 124:
#line 301 "parser.yy" /* yacc.c:1646  */
    { (yyval.chmod) = new Chmod(); (yyval.chmod)->isRecursive = true; }
#line 2404 "parser.cpp" /* yacc.c:1646  */
    break;

  case 125:
#line 303 "parser.yy" /* yacc.c:1646  */
    { (yyval.mkfile) = (yyvsp[-4].mkfile); (yyval.mkfile)->path = (yyvsp[0].TEXT); }
#line 2410 "parser.cpp" /* yacc.c:1646  */
    break;

  case 126:
#line 304 "parser.yy" /* yacc.c:1646  */
    { (yyval.mkfile) = (yyvsp[-2].mkfile); (yyval.mkfile)->isP = true; }
#line 2416 "parser.cpp" /* yacc.c:1646  */
    break;

  case 127:
#line 305 "parser.yy" /* yacc.c:1646  */
    { (yyval.mkfile) = (yyvsp[-4].mkfile); (yyval.mkfile)->size = std::stoi((yyvsp[0].TEXT)); }
#line 2422 "parser.cpp" /* yacc.c:1646  */
    break;

  case 128:
#line 306 "parser.yy" /* yacc.c:1646  */
    { (yyval.mkfile) = (yyvsp[-4].mkfile); (yyval.mkfile)->cont = (yyvsp[0].TEXT); }
#line 2428 "parser.cpp" /* yacc.c:1646  */
    break;

  case 129:
#line 307 "parser.yy" /* yacc.c:1646  */
    { (yyval.mkfile) = new Mkfile(); (yyval.mkfile)->path = (yyvsp[0].TEXT); }
#line 2434 "parser.cpp" /* yacc.c:1646  */
    break;

  case 130:
#line 308 "parser.yy" /* yacc.c:1646  */
    { (yyval.mkfile) = new Mkfile(); (yyval.mkfile)->isP = true; }
#line 2440 "parser.cpp" /* yacc.c:1646  */
    break;

  case 131:
#line 309 "parser.yy" /* yacc.c:1646  */
    { (yyval.mkfile) = new Mkfile(); (yyval.mkfile)->size = std::stoi((yyvsp[0].TEXT)); }
#line 2446 "parser.cpp" /* yacc.c:1646  */
    break;

  case 132:
#line 310 "parser.yy" /* yacc.c:1646  */
    { (yyval.mkfile) = new Mkfile(); (yyval.mkfile)->cont = (yyvsp[0].TEXT); }
#line 2452 "parser.cpp" /* yacc.c:1646  */
    break;

  case 133:
#line 312 "parser.yy" /* yacc.c:1646  */
    { (yyval.mkdir) = (yyvsp[-5].mkdir); (yyval.mkdir)->path = (yyvsp[0].TEXT); }
#line 2458 "parser.cpp" /* yacc.c:1646  */
    break;

  case 134:
#line 313 "parser.yy" /* yacc.c:1646  */
    { (yyval.mkdir) = (yyvsp[-5].mkdir); (yyval.mkdir)->id = (yyvsp[0].TEXT); }
#line 2464 "parser.cpp" /* yacc.c:1646  */
    break;

  case 135:
#line 314 "parser.yy" /* yacc.c:1646  */
    { (yyval.mkdir) = (yyvsp[-2].mkdir); (yyval.mkdir)->isP = true; }
#line 2470 "parser.cpp" /* yacc.c:1646  */
    break;

  case 136:
#line 315 "parser.yy" /* yacc.c:1646  */
    { (yyval.mkdir) = new Mkdir(); (yyval.mkdir)->path = (yyvsp[0].TEXT); }
#line 2476 "parser.cpp" /* yacc.c:1646  */
    break;

  case 137:
#line 316 "parser.yy" /* yacc.c:1646  */
    { (yyval.mkdir) = new Mkdir(); (yyval.mkdir)->isP = true; }
#line 2482 "parser.cpp" /* yacc.c:1646  */
    break;

  case 138:
#line 317 "parser.yy" /* yacc.c:1646  */
    { (yyval.mkdir) = new Mkdir(); (yyval.mkdir)->id = (yyvsp[0].TEXT); }
#line 2488 "parser.cpp" /* yacc.c:1646  */
    break;


#line 2492 "parser.cpp" /* yacc.c:1646  */
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
  /* Do not reclaim the symbols of the rule whose action triggered
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
  return yyresult;
}
#line 320 "parser.yy" /* yacc.c:1906  */

