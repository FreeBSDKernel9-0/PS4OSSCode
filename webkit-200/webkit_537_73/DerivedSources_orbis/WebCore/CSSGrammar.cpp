/* A Bison parser, made by GNU Bison 2.7.12-4996.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.
   
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
#define YYBISON_VERSION "2.7.12-4996"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 1

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1


/* Substitute the variable and function names.  */
#define yyparse         cssyyparse
#define yylex           cssyylex
#define yyerror         cssyyerror
#define yylval          cssyylval
#define yychar          cssyychar
#define yydebug         cssyydebug
#define yynerrs         cssyynerrs

/* Copy the first part of user declarations.  */
/* Line 371 of yacc.c  */
#line 1 "./CSSGrammar.y"


/*
 *  Copyright (C) 2002-2003 Lars Knoll (knoll@kde.org)
 *  Copyright (C) 2004, 2005, 2006, 2007, 2008, 2009, 2010 Apple Inc. All rights reserved.
 *  Copyright (C) 2006 Alexey Proskuryakov (ap@nypop.com)
 *  Copyright (C) 2008 Eric Seidel <eric@webkit.org>
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */

#include "config.h"

#include "CSSParser.h"
#include "CSSParserMode.h"
#include "CSSPrimitiveValue.h"
#include "CSSPropertyNames.h"
#include "CSSSelector.h"
#include "CSSSelectorList.h"
#include "Document.h"
#include "HTMLNames.h"
#include "MediaList.h"
#include "MediaQueryExp.h"
#include "StyleRule.h"
#include "StyleSheetContents.h"
#include "WebKitCSSKeyframeRule.h"
#include "WebKitCSSKeyframesRule.h"
#include <wtf/FastMalloc.h>
#include <stdlib.h>
#include <string.h>

using namespace WebCore;
using namespace HTMLNames;

#define YYMALLOC fastMalloc
#define YYFREE fastFree

#define YYENABLE_NLS 0
#define YYLTYPE_IS_TRIVIAL 1
#define YYMAXDEPTH 10000
#define YYDEBUG 0

#if YYDEBUG > 0
#include <wtf/text/CString.h>
#define YYPRINT(File,Type,Value) if (isCSSTokenAString(Type)) YYFPRINTF(File, "%s", String((Value).string).utf8().data())
#endif


/* Line 371 of yacc.c  */
#line 137 "./CSSGrammar.cpp"

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
   by #include "CSSGrammar.hpp".  */
#ifndef YY_CSSYY_CSSGRAMMAR_HPP_INCLUDED
# define YY_CSSYY_CSSGRAMMAR_HPP_INCLUDED
/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int cssyydebug;
#endif

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     TOKEN_EOF = 0,
     LOWEST_PREC = 258,
     UNIMPORTANT_TOK = 259,
     WHITESPACE = 260,
     SGML_CD = 261,
     INCLUDES = 262,
     DASHMATCH = 263,
     BEGINSWITH = 264,
     ENDSWITH = 265,
     CONTAINS = 266,
     STRING = 267,
     IDENT = 268,
     NTH = 269,
     HEX = 270,
     IDSEL = 271,
     IMPORT_SYM = 272,
     PAGE_SYM = 273,
     MEDIA_SYM = 274,
     FONT_FACE_SYM = 275,
     CHARSET_SYM = 276,
     NAMESPACE_SYM = 277,
     VARFUNCTION = 278,
     WEBKIT_RULE_SYM = 279,
     WEBKIT_DECLS_SYM = 280,
     WEBKIT_KEYFRAME_RULE_SYM = 281,
     WEBKIT_KEYFRAMES_SYM = 282,
     WEBKIT_VALUE_SYM = 283,
     WEBKIT_MEDIAQUERY_SYM = 284,
     WEBKIT_SELECTOR_SYM = 285,
     WEBKIT_REGION_RULE_SYM = 286,
     WEBKIT_VIEWPORT_RULE_SYM = 287,
     TOPLEFTCORNER_SYM = 288,
     TOPLEFT_SYM = 289,
     TOPCENTER_SYM = 290,
     TOPRIGHT_SYM = 291,
     TOPRIGHTCORNER_SYM = 292,
     BOTTOMLEFTCORNER_SYM = 293,
     BOTTOMLEFT_SYM = 294,
     BOTTOMCENTER_SYM = 295,
     BOTTOMRIGHT_SYM = 296,
     BOTTOMRIGHTCORNER_SYM = 297,
     LEFTTOP_SYM = 298,
     LEFTMIDDLE_SYM = 299,
     LEFTBOTTOM_SYM = 300,
     RIGHTTOP_SYM = 301,
     RIGHTMIDDLE_SYM = 302,
     RIGHTBOTTOM_SYM = 303,
     ATKEYWORD = 304,
     IMPORTANT_SYM = 305,
     MEDIA_ONLY = 306,
     MEDIA_NOT = 307,
     MEDIA_AND = 308,
     REMS = 309,
     CHS = 310,
     QEMS = 311,
     EMS = 312,
     EXS = 313,
     PXS = 314,
     CMS = 315,
     MMS = 316,
     INS = 317,
     PTS = 318,
     PCS = 319,
     DEGS = 320,
     RADS = 321,
     GRADS = 322,
     TURNS = 323,
     MSECS = 324,
     SECS = 325,
     HERTZ = 326,
     KHERTZ = 327,
     DIMEN = 328,
     INVALIDDIMEN = 329,
     PERCENTAGE = 330,
     FLOATTOKEN = 331,
     INTEGER = 332,
     VW = 333,
     VH = 334,
     VMIN = 335,
     VMAX = 336,
     DPPX = 337,
     DPI = 338,
     DPCM = 339,
     URI = 340,
     FUNCTION = 341,
     ANYFUNCTION = 342,
     CUEFUNCTION = 343,
     NOTFUNCTION = 344,
     CALCFUNCTION = 345,
     MINFUNCTION = 346,
     MAXFUNCTION = 347,
     VAR_DEFINITION = 348,
     UNICODERANGE = 349
   };
#endif


#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{
/* Line 387 of yacc.c  */
#line 65 "./CSSGrammar.y"

    bool boolean;
    char character;
    int integer;
    double number;
    CSSParserString string;
    StyleRuleBase* rule;
    Vector<RefPtr<StyleRuleBase> >* ruleList;
    CSSParserSelector* selector;
    Vector<OwnPtr<CSSParserSelector> >* selectorList;
    CSSSelector::MarginBoxType marginBox;
    CSSSelector::Relation relation;
    MediaQuerySet* mediaList;
    MediaQuery* mediaQuery;
    MediaQuery::Restrictor mediaQueryRestrictor;
    MediaQueryExp* mediaQueryExp;
    CSSParserValue value;
    CSSParserValueList* valueList;
    Vector<OwnPtr<MediaQueryExp> >* mediaQueryExpList;
    StyleKeyframe* keyframe;
    Vector<RefPtr<StyleKeyframe> >* keyframeRuleList;
    float val;
    CSSPropertyID id;
    CSSParser::Location location;


/* Line 387 of yacc.c  */
#line 302 "./CSSGrammar.cpp"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int cssyyparse (void *YYPARSE_PARAM);
#else
int cssyyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int cssyyparse (CSSParser* parser);
#else
int cssyyparse ();
#endif
#endif /* ! YYPARSE_PARAM */

#endif /* !YY_CSSYY_CSSGRAMMAR_HPP_INCLUDED  */

/* Copy the second part of user declarations.  */
/* Line 390 of yacc.c  */
#line 90 "./CSSGrammar.y"

static inline int cssyyerror(void*, const char*)
{
    return 1;
}

/* Line 390 of yacc.c  */
#line 336 "./CSSGrammar.cpp"

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

#ifndef __attribute__
/* This feature is available in gcc versions 2.5 and later.  */
# if (! defined __GNUC__ || __GNUC__ < 2 \
      || (__GNUC__ == 2 && __GNUC_MINOR__ < 5))
#  define __attribute__(Spec) /* empty */
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
#define YYLAST   1873

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  115
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  115
/* YYNRULES -- Number of rules.  */
#define YYNRULES  324
/* YYNRULES -- Number of states.  */
#define YYNSTATES  591

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   349

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,   113,     2,   114,     2,     2,
     104,   102,    20,   106,   105,   109,    18,   112,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    17,   103,
       2,   111,   108,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    19,     2,   110,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   100,    21,   101,   107,     2,     2,     2,
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
      15,    16,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     8,    11,    14,    17,    20,    23,    26,
      33,    40,    46,    52,    58,    64,    65,    68,    69,    72,
      75,    76,    78,    80,    82,    84,    86,    92,    96,   100,
     106,   110,   111,   115,   117,   119,   121,   123,   125,   127,
     129,   131,   133,   135,   137,   139,   140,   144,   145,   149,
     151,   153,   155,   157,   159,   161,   163,   165,   167,   169,
     171,   173,   174,   182,   190,   198,   203,   208,   215,   222,
     226,   230,   231,   234,   236,   238,   241,   242,   247,   257,
     259,   265,   266,   270,   271,   273,   275,   277,   282,   283,
     285,   287,   292,   295,   296,   297,   299,   310,   319,   324,
     327,   328,   339,   341,   343,   344,   348,   355,   357,   363,
     366,   368,   370,   371,   382,   387,   392,   394,   397,   399,
     400,   402,   407,   408,   416,   418,   420,   422,   424,   426,
     428,   430,   432,   434,   436,   438,   440,   442,   444,   446,
     448,   449,   458,   463,   468,   470,   471,   482,   485,   488,
     491,   493,   494,   496,   498,   500,   501,   502,   503,   513,
     514,   516,   523,   526,   529,   531,   533,   536,   540,   543,
     545,   548,   551,   553,   556,   558,   561,   565,   568,   570,
     576,   579,   581,   583,   585,   588,   591,   593,   595,   597,
     599,   601,   604,   607,   612,   621,   627,   637,   639,   641,
     643,   645,   647,   649,   651,   653,   656,   659,   663,   671,
     678,   685,   693,   700,   707,   708,   710,   713,   715,   717,
     720,   724,   728,   733,   738,   742,   749,   755,   758,   765,
     769,   774,   778,   781,   784,   785,   787,   791,   794,   798,
     801,   804,   805,   808,   812,   815,   818,   821,   825,   828,
     831,   834,   837,   843,   846,   849,   852,   855,   857,   859,
     861,   863,   865,   867,   869,   871,   873,   875,   877,   879,
     881,   883,   885,   887,   889,   891,   893,   895,   897,   899,
     901,   903,   905,   907,   909,   911,   913,   918,   922,   927,
     929,   934,   937,   941,   945,   949,   953,   954,   956,   962,
     964,   968,   972,   974,   977,   980,   986,   992,   997,   999,
    1001,  1006,  1011,  1013,  1016,  1020,  1024,  1027,  1033,  1037,
    1039,  1043,  1044,  1045,  1048
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     116,     0,    -1,   123,   125,   124,   130,    -1,   117,   123,
      -1,   119,   123,    -1,   120,   123,    -1,   121,   123,    -1,
     122,   123,    -1,   118,   123,    -1,    29,   100,   123,   131,
     123,   101,    -1,    31,   100,   123,   161,   123,   101,    -1,
      30,   100,   179,   201,   101,    -1,    33,   100,   123,   208,
     101,    -1,    34,     5,   123,   149,   101,    -1,    35,   100,
     123,   185,   101,    -1,    -1,   123,     5,    -1,    -1,   124,
       6,    -1,   124,     5,    -1,    -1,   128,    -1,   101,    -1,
       0,    -1,   102,    -1,     0,    -1,    26,   123,    12,   123,
     103,    -1,    26,     1,   226,    -1,    26,     1,   103,    -1,
      26,   123,    12,   123,   103,    -1,    26,   123,   103,    -1,
      -1,   130,   132,   124,    -1,   183,    -1,   155,    -1,   165,
      -1,   172,    -1,   158,    -1,   140,    -1,   139,    -1,   175,
      -1,   131,    -1,   129,    -1,   225,    -1,   224,    -1,    -1,
     133,   136,   124,    -1,    -1,   134,   135,   124,    -1,   183,
      -1,   165,    -1,   172,    -1,   155,    -1,   158,    -1,   135,
      -1,   225,    -1,   224,    -1,   140,    -1,   139,    -1,   175,
      -1,   123,    -1,    -1,   138,    22,   137,   142,   123,   150,
     103,    -1,   138,    22,   137,   142,   123,   150,     0,    -1,
     138,    22,   137,   142,   123,   150,   226,    -1,   138,    22,
       1,   103,    -1,   138,    22,     1,   226,    -1,    27,   123,
     141,   142,   123,   103,    -1,    27,   123,   141,   142,   123,
     226,    -1,    27,     1,   226,    -1,    27,     1,   103,    -1,
      -1,    13,   123,    -1,    12,    -1,    90,    -1,    13,   123,
      -1,    -1,    17,   123,   208,   123,    -1,   148,   123,   104,
     123,   143,   123,   144,   102,   123,    -1,   145,    -1,   146,
     123,    58,   123,   145,    -1,    -1,    58,   123,   146,    -1,
      -1,    56,    -1,    57,    -1,   146,    -1,   148,   123,   156,
     147,    -1,    -1,   151,    -1,   149,    -1,   151,   105,   123,
     149,    -1,   151,     1,    -1,    -1,    -1,   123,    -1,   153,
      24,   123,   151,   181,   100,   152,   123,   133,   223,    -1,
     153,    24,   154,   100,   152,   123,   133,   223,    -1,   153,
      24,   154,   103,    -1,    13,   123,    -1,    -1,   157,    32,
     123,   159,   154,   100,   152,   123,   160,   126,    -1,    13,
      -1,    12,    -1,    -1,   160,   161,   123,    -1,   162,   123,
     100,   123,   201,   126,    -1,   163,    -1,   162,   123,   105,
     123,   163,    -1,   177,    80,    -1,    13,    -1,     1,    -1,
      -1,   164,    23,   123,   166,   154,   100,   152,   179,   167,
     126,    -1,   164,    23,     1,   226,    -1,   164,    23,     1,
     103,    -1,    13,    -1,    13,   199,    -1,   199,    -1,    -1,
     201,    -1,   167,   168,   123,   201,    -1,    -1,   170,   169,
     123,   100,   123,   201,   126,    -1,    38,    -1,    39,    -1,
      40,    -1,    41,    -1,    42,    -1,    43,    -1,    44,    -1,
      45,    -1,    46,    -1,    47,    -1,    48,    -1,    49,    -1,
      50,    -1,    51,    -1,    52,    -1,    53,    -1,    -1,   171,
      25,   154,   100,   152,   179,   201,   126,    -1,   171,    25,
       1,   226,    -1,   171,    25,     1,   103,    -1,   185,    -1,
      -1,   174,    36,     5,   173,   181,   100,   152,   123,   134,
     223,    -1,   106,   123,    -1,   107,   123,    -1,   108,   123,
      -1,   178,    -1,    -1,   109,    -1,   106,    -1,   123,    -1,
      -1,    -1,    -1,   180,   185,   182,   181,   100,   152,   179,
     201,   126,    -1,    -1,   187,    -1,   185,   182,   105,   123,
     184,   187,    -1,   185,     1,    -1,   187,     5,    -1,   189,
      -1,   186,    -1,   186,   189,    -1,   187,   176,   189,    -1,
     187,     1,    -1,    21,    -1,    20,    21,    -1,    13,    21,
      -1,   191,    -1,   191,   192,    -1,   192,    -1,   188,   191,
      -1,   188,   191,   192,    -1,   188,   192,    -1,   189,    -1,
     190,   123,   105,   123,   189,    -1,   190,     1,    -1,    13,
      -1,    20,    -1,   193,    -1,   192,   193,    -1,   192,     1,
      -1,    16,    -1,    15,    -1,   194,    -1,   196,    -1,   200,
      -1,    18,    13,    -1,    13,   123,    -1,    19,   123,   195,
     110,    -1,    19,   123,   195,   197,   123,   198,   123,   110,
      -1,    19,   123,   188,   195,   110,    -1,    19,   123,   188,
     195,   197,   123,   198,   123,   110,    -1,   111,    -1,     7,
      -1,     8,    -1,     9,    -1,    10,    -1,    11,    -1,    13,
      -1,    12,    -1,    17,    13,    -1,    17,    13,    -1,    17,
      17,    13,    -1,    17,    17,    93,   123,   190,   123,   102,
      -1,    17,    92,   123,   190,   123,   102,    -1,    17,    91,
     123,    14,   123,   102,    -1,    17,    91,   123,   177,    82,
     123,   102,    -1,    17,    91,   123,    13,   123,   102,    -1,
      17,    94,   123,   189,   123,   102,    -1,    -1,   204,    -1,
     202,   204,    -1,   202,    -1,   203,    -1,   202,   203,    -1,
     204,   103,   123,    -1,   203,   103,   123,    -1,   202,   204,
     103,   123,    -1,   202,   203,   103,   123,    -1,     1,   228,
     229,    -1,    98,   123,    17,   123,   208,   207,    -1,   206,
      17,   123,   208,   207,    -1,   206,   205,    -1,   206,    17,
     123,   208,   207,   205,    -1,    55,   123,   205,    -1,   206,
      17,   123,   205,    -1,     1,   228,   229,    -1,    13,   123,
      -1,    55,   123,    -1,    -1,   211,    -1,   208,   210,   211,
      -1,   208,   209,    -1,     1,   228,   229,    -1,   112,   123,
      -1,   105,   123,    -1,    -1,   212,   123,    -1,   178,   212,
     123,    -1,    12,   123,    -1,    13,   123,    -1,    78,   123,
      -1,   178,    78,   123,    -1,    90,   123,    -1,    99,   123,
      -1,    15,   123,    -1,   113,   123,    -1,    28,   123,    13,
     127,   123,    -1,   213,   123,    -1,   220,   123,    -1,   222,
     123,    -1,   114,   123,    -1,    82,    -1,    81,    -1,    80,
      -1,    64,    -1,    65,    -1,    66,    -1,    67,    -1,    68,
      -1,    69,    -1,    70,    -1,    71,    -1,    72,    -1,    73,
      -1,    74,    -1,    75,    -1,    76,    -1,    77,    -1,    62,
      -1,    61,    -1,    63,    -1,    59,    -1,    60,    -1,    83,
      -1,    84,    -1,    85,    -1,    86,    -1,    87,    -1,    88,
      -1,    89,    -1,    91,   123,   208,   127,    -1,    91,   123,
     127,    -1,    91,   123,   209,   127,    -1,   212,    -1,    28,
     123,    13,   127,    -1,   178,   212,    -1,     5,   106,     5,
      -1,     5,   109,     5,    -1,   216,    20,   123,    -1,   216,
     112,   123,    -1,    -1,     5,    -1,   104,   123,   218,   216,
     127,    -1,   214,    -1,   218,   215,   214,    -1,   218,   215,
     217,    -1,   217,    -1,   218,     1,    -1,   218,   216,    -1,
     219,   105,   123,   218,   216,    -1,    95,   123,   218,   216,
     127,    -1,    95,   123,   209,   127,    -1,    96,    -1,    97,
      -1,   221,   123,   219,   127,    -1,   221,   123,   209,   127,
      -1,   126,    -1,     1,   126,    -1,    54,     1,   226,    -1,
      54,     1,   103,    -1,     1,   226,    -1,   100,     1,   227,
       1,   126,    -1,   100,     1,   126,    -1,   226,    -1,   227,
       1,   226,    -1,    -1,    -1,   229,   226,    -1,   229,     1,
      -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   276,   276,   277,   278,   279,   280,   281,   282,   285,
     290,   295,   299,   310,   315,   323,   324,   326,   327,   328,
     330,   331,   335,   336,   339,   340,   343,   350,   352,   356,
     359,   363,   364,   370,   371,   372,   373,   374,   375,   376,
     377,   380,   383,   384,   385,   388,   389,   399,   400,   410,
     411,   412,   413,   414,   417,   418,   419,   420,   421,   422,
     425,   431,   436,   439,   442,   446,   450,   456,   460,   463,
     466,   471,   472,   475,   476,   479,   484,   487,   492,   502,
     506,   512,   515,   520,   523,   526,   531,   535,   541,   544,
     547,   552,   559,   564,   569,   574,   579,   582,   585,   591,
     596,   601,   606,   607,   610,   611,   618,   623,   627,   634,
     635,   647,   652,   657,   667,   671,   677,   681,   688,   693,
     699,   700,   703,   703,   710,   713,   716,   719,   722,   725,
     728,   731,   734,   737,   740,   743,   746,   749,   752,   755,
     760,   765,   769,   773,   779,   789,   794,   804,   805,   806,
     809,   810,   813,   814,   817,   822,   828,   833,   838,   843,
     847,   855,   863,   868,   873,   876,   880,   888,   895,   900,
     901,   902,   905,   908,   913,   918,   921,   926,   933,   940,
     947,   952,   958,   964,   967,   973,   978,   985,   996,   997,
     998,  1001,  1010,  1018,  1023,  1029,  1034,  1042,  1045,  1048,
    1051,  1054,  1057,  1062,  1063,  1066,  1076,  1085,  1094,  1106,
    1119,  1128,  1137,  1154,  1169,  1170,  1173,  1178,  1181,  1184,
    1189,  1193,  1197,  1203,  1209,  1214,  1218,  1234,  1238,  1243,
    1247,  1253,  1258,  1263,  1264,  1267,  1271,  1284,  1289,  1292,
    1295,  1298,  1303,  1304,  1305,  1306,  1311,  1312,  1313,  1314,
    1315,  1316,  1317,  1319,  1322,  1325,  1328,  1333,  1334,  1335,
    1336,  1337,  1338,  1339,  1340,  1341,  1342,  1343,  1344,  1345,
    1346,  1347,  1348,  1349,  1350,  1351,  1352,  1353,  1360,  1361,
    1362,  1363,  1364,  1365,  1366,  1367,  1370,  1378,  1387,  1397,
    1398,  1400,  1403,  1406,  1409,  1412,  1416,  1417,  1420,  1435,
    1439,  1451,  1463,  1464,  1469,  1472,  1486,  1494,  1499,  1502,
    1507,  1515,  1520,  1523,  1528,  1531,  1536,  1541,  1544,  1549,
    1550,  1552,  1556,  1557,  1558
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "TOKEN_EOF", "error", "$undefined", "LOWEST_PREC", "UNIMPORTANT_TOK",
  "WHITESPACE", "SGML_CD", "INCLUDES", "DASHMATCH", "BEGINSWITH",
  "ENDSWITH", "CONTAINS", "STRING", "IDENT", "NTH", "HEX", "IDSEL", "':'",
  "'.'", "'['", "'*'", "'|'", "IMPORT_SYM", "PAGE_SYM", "MEDIA_SYM",
  "FONT_FACE_SYM", "CHARSET_SYM", "NAMESPACE_SYM", "VARFUNCTION",
  "WEBKIT_RULE_SYM", "WEBKIT_DECLS_SYM", "WEBKIT_KEYFRAME_RULE_SYM",
  "WEBKIT_KEYFRAMES_SYM", "WEBKIT_VALUE_SYM", "WEBKIT_MEDIAQUERY_SYM",
  "WEBKIT_SELECTOR_SYM", "WEBKIT_REGION_RULE_SYM",
  "WEBKIT_VIEWPORT_RULE_SYM", "TOPLEFTCORNER_SYM", "TOPLEFT_SYM",
  "TOPCENTER_SYM", "TOPRIGHT_SYM", "TOPRIGHTCORNER_SYM",
  "BOTTOMLEFTCORNER_SYM", "BOTTOMLEFT_SYM", "BOTTOMCENTER_SYM",
  "BOTTOMRIGHT_SYM", "BOTTOMRIGHTCORNER_SYM", "LEFTTOP_SYM",
  "LEFTMIDDLE_SYM", "LEFTBOTTOM_SYM", "RIGHTTOP_SYM", "RIGHTMIDDLE_SYM",
  "RIGHTBOTTOM_SYM", "ATKEYWORD", "IMPORTANT_SYM", "MEDIA_ONLY",
  "MEDIA_NOT", "MEDIA_AND", "REMS", "CHS", "QEMS", "EMS", "EXS", "PXS",
  "CMS", "MMS", "INS", "PTS", "PCS", "DEGS", "RADS", "GRADS", "TURNS",
  "MSECS", "SECS", "HERTZ", "KHERTZ", "DIMEN", "INVALIDDIMEN",
  "PERCENTAGE", "FLOATTOKEN", "INTEGER", "VW", "VH", "VMIN", "VMAX",
  "DPPX", "DPI", "DPCM", "URI", "FUNCTION", "ANYFUNCTION", "CUEFUNCTION",
  "NOTFUNCTION", "CALCFUNCTION", "MINFUNCTION", "MAXFUNCTION",
  "VAR_DEFINITION", "UNICODERANGE", "'{'", "'}'", "')'", "';'", "'('",
  "','", "'+'", "'~'", "'>'", "'-'", "']'", "'='", "'/'", "'#'", "'%'",
  "$accept", "stylesheet", "webkit_rule", "webkit_keyframe_rule",
  "webkit_decls", "webkit_value", "webkit_mediaquery", "webkit_selector",
  "maybe_space", "maybe_sgml", "maybe_charset", "closing_brace",
  "closing_parenthesis", "charset", "ignored_charset", "rule_list",
  "valid_rule", "rule", "block_rule_list", "region_block_rule_list",
  "block_valid_rule", "block_rule", "at_import_header_end_maybe_space",
  "before_import_rule", "import", "namespace", "maybe_ns_prefix",
  "string_or_uri", "media_feature", "maybe_media_value", "media_query_exp",
  "media_query_exp_list", "maybe_and_media_query_exp_list",
  "maybe_media_restrictor", "media_query", "maybe_media_list",
  "media_list", "at_rule_body_start", "before_media_rule",
  "at_rule_header_end_maybe_space", "media", "medium",
  "before_keyframes_rule", "keyframes", "keyframe_name", "keyframes_rule",
  "keyframe_rule", "key_list", "key", "before_page_rule", "page",
  "page_selector", "declarations_and_margins", "margin_box", "$@1",
  "margin_sym", "before_font_face_rule", "font_face", "region_selector",
  "before_region_rule", "region", "combinator", "maybe_unary_operator",
  "unary_operator", "maybe_space_before_declaration",
  "before_selector_list", "at_rule_header_end", "at_selector_end",
  "ruleset", "before_selector_group_item", "selector_list",
  "selector_with_trailing_whitespace", "selector", "namespace_selector",
  "simple_selector", "simple_selector_list", "element_name",
  "specifier_list", "specifier", "class", "attr_name", "attrib", "match",
  "ident_or_string", "pseudo_page", "pseudo", "declaration_list",
  "decl_list", "decl_list_recovery", "declaration", "declaration_recovery",
  "property", "prio", "expr", "expr_recovery", "operator", "term",
  "unary_term", "function", "calc_func_term", "calc_func_operator",
  "calc_maybe_space", "calc_func_paren_expr", "calc_func_expr",
  "calc_func_expr_list", "calc_function", "min_or_max",
  "min_or_max_function", "save_block", "invalid_at", "invalid_rule",
  "invalid_block", "invalid_block_list", "error_location",
  "error_recovery", YY_NULL
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,    58,    46,    91,
      42,   124,   272,   273,   274,   275,   276,   277,   278,   279,
     280,   281,   282,   283,   284,   285,   286,   287,   288,   289,
     290,   291,   292,   293,   294,   295,   296,   297,   298,   299,
     300,   301,   302,   303,   304,   305,   306,   307,   308,   309,
     310,   311,   312,   313,   314,   315,   316,   317,   318,   319,
     320,   321,   322,   323,   324,   325,   326,   327,   328,   329,
     330,   331,   332,   333,   334,   335,   336,   337,   338,   339,
     340,   341,   342,   343,   344,   345,   346,   347,   348,   349,
     123,   125,    41,    59,    40,    44,    43,   126,    62,    45,
      93,    61,    47,    35,    37
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   115,   116,   116,   116,   116,   116,   116,   116,   117,
     118,   119,   120,   121,   122,   123,   123,   124,   124,   124,
     125,   125,   126,   126,   127,   127,   128,   128,   128,   129,
     129,   130,   130,   131,   131,   131,   131,   131,   131,   131,
     131,   132,   132,   132,   132,   133,   133,   134,   134,   135,
     135,   135,   135,   135,   136,   136,   136,   136,   136,   136,
     137,   138,   139,   139,   139,   139,   139,   140,   140,   140,
     140,   141,   141,   142,   142,   143,   144,   144,   145,   146,
     146,   147,   147,   148,   148,   148,   149,   149,   150,   150,
     151,   151,   151,   152,   153,   154,   155,   155,   155,   156,
     157,   158,   159,   159,   160,   160,   161,   162,   162,   163,
     163,   163,   164,   165,   165,   165,   166,   166,   166,   166,
     167,   167,   169,   168,   170,   170,   170,   170,   170,   170,
     170,   170,   170,   170,   170,   170,   170,   170,   170,   170,
     171,   172,   172,   172,   173,   174,   175,   176,   176,   176,
     177,   177,   178,   178,   179,   180,   181,   182,   183,   184,
     185,   185,   185,   186,   187,   187,   187,   187,   187,   188,
     188,   188,   189,   189,   189,   189,   189,   189,   190,   190,
     190,   191,   191,   192,   192,   192,   193,   193,   193,   193,
     193,   194,   195,   196,   196,   196,   196,   197,   197,   197,
     197,   197,   197,   198,   198,   199,   200,   200,   200,   200,
     200,   200,   200,   200,   201,   201,   201,   201,   201,   201,
     202,   202,   202,   202,   203,   204,   204,   204,   204,   204,
     204,   205,   206,   207,   207,   208,   208,   208,   209,   210,
     210,   210,   211,   211,   211,   211,   211,   211,   211,   211,
     211,   211,   211,   211,   211,   211,   211,   212,   212,   212,
     212,   212,   212,   212,   212,   212,   212,   212,   212,   212,
     212,   212,   212,   212,   212,   212,   212,   212,   212,   212,
     212,   212,   212,   212,   212,   212,   213,   213,   213,   214,
     214,   214,   215,   215,   215,   215,   216,   216,   217,   218,
     218,   218,   218,   218,   219,   219,   220,   220,   221,   221,
     222,   222,   223,   223,   224,   224,   225,   226,   226,   227,
     227,   228,   229,   229,   229
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     4,     2,     2,     2,     2,     2,     2,     6,
       6,     5,     5,     5,     5,     0,     2,     0,     2,     2,
       0,     1,     1,     1,     1,     1,     5,     3,     3,     5,
       3,     0,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     3,     0,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     7,     7,     7,     4,     4,     6,     6,     3,
       3,     0,     2,     1,     1,     2,     0,     4,     9,     1,
       5,     0,     3,     0,     1,     1,     1,     4,     0,     1,
       1,     4,     2,     0,     0,     1,    10,     8,     4,     2,
       0,    10,     1,     1,     0,     3,     6,     1,     5,     2,
       1,     1,     0,    10,     4,     4,     1,     2,     1,     0,
       1,     4,     0,     7,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     8,     4,     4,     1,     0,    10,     2,     2,     2,
       1,     0,     1,     1,     1,     0,     0,     0,     9,     0,
       1,     6,     2,     2,     1,     1,     2,     3,     2,     1,
       2,     2,     1,     2,     1,     2,     3,     2,     1,     5,
       2,     1,     1,     1,     2,     2,     1,     1,     1,     1,
       1,     2,     2,     4,     8,     5,     9,     1,     1,     1,
       1,     1,     1,     1,     1,     2,     2,     3,     7,     6,
       6,     7,     6,     6,     0,     1,     2,     1,     1,     2,
       3,     3,     4,     4,     3,     6,     5,     2,     6,     3,
       4,     3,     2,     2,     0,     1,     3,     2,     3,     2,
       2,     0,     2,     3,     2,     2,     2,     3,     2,     2,
       2,     2,     5,     2,     2,     2,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     4,     3,     4,     1,
       4,     2,     3,     3,     3,     3,     0,     1,     5,     1,
       3,     3,     1,     2,     2,     5,     5,     4,     1,     1,
       4,     4,     1,     2,     3,     3,     2,     5,     3,     1,
       3,     0,     0,     2,     2
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
      15,     0,     0,     0,     0,     0,     0,     0,    15,    15,
      15,    15,    15,    15,    20,    15,    15,    15,    15,    15,
      15,     1,     3,     8,     4,     5,     6,     7,    16,     0,
      17,    21,   155,   154,     0,     0,     0,    83,     0,     0,
       0,    31,     0,    15,     0,    39,    38,     0,    34,     0,
      37,     0,    35,     0,    36,     0,    40,     0,    33,   321,
      15,    15,    15,     0,     0,   218,   215,     0,   111,   110,
     153,   152,    15,    15,   107,     0,   150,    15,    15,    15,
      15,   277,   278,   275,   274,   276,   260,   261,   262,   263,
     264,   265,   266,   267,   268,   269,   270,   271,   272,   273,
      15,   259,   258,   257,   279,   280,   281,   282,   283,   284,
     285,    15,    15,    15,   308,   309,    15,    15,    15,     0,
       0,   235,    15,    15,    15,    15,    15,    84,    85,    79,
      86,    15,     0,   181,   187,   186,     0,     0,    15,   182,
     169,     0,   165,     0,     0,   164,   172,     0,   183,   188,
     189,   190,     0,    28,    27,    15,    19,    18,     0,     0,
      71,     0,     0,    15,    15,     0,     0,     0,     0,   322,
     232,     0,     0,    11,   219,   216,    15,    15,   321,    15,
     227,     0,     0,   109,   244,   245,   250,     0,   246,   248,
       0,     0,   249,   251,   256,    15,    15,   321,    12,    15,
      15,   237,     0,   242,   253,   254,     0,   255,     0,     0,
      13,   171,   206,     0,    15,    15,    15,   191,     0,   170,
     162,    14,     0,   166,   168,   163,    15,    15,    15,     0,
     181,   182,   175,     0,     0,   185,   184,     0,     0,     0,
      15,     0,    42,    41,    17,    44,    43,    70,    69,    15,
       0,     9,     0,    60,     0,    83,     0,     0,     0,   119,
       0,    95,     0,     0,   156,     0,   229,    15,    15,    15,
     221,   220,   322,     0,    10,    15,    15,     0,    25,    24,
     287,     0,     0,    15,    15,     0,     0,   289,   299,   302,
       0,   247,   243,   322,   240,   239,   236,     0,     0,     0,
      15,    15,    15,    81,   207,    15,   151,     0,     0,    15,
       0,     0,     0,    15,   147,   148,   149,   167,     0,    23,
      22,   318,   319,     0,    26,   316,     0,     0,    32,    72,
      73,    74,    15,    65,    66,    15,    90,     0,    93,    98,
     103,   102,    15,   115,   114,   116,     0,    15,   118,   143,
     142,    93,   156,     0,     0,   324,   323,     0,   223,   222,
       0,   230,     0,     0,     0,    15,   286,   288,     0,     0,
     291,   307,   303,   297,     0,     0,   238,   311,   304,    15,
     310,    83,    99,     0,    15,    87,     0,    15,    15,     0,
     178,     0,    15,   192,    15,     0,   198,   199,   200,   201,
     202,   193,   197,    15,   159,     0,    15,    30,   315,   314,
       0,    88,    92,    15,     0,    15,     0,   117,   205,     0,
      15,     0,    93,     0,    15,     0,     0,   108,   252,     0,
       0,     0,     0,   300,   301,    15,    15,   306,     0,    80,
      15,    15,    15,    83,     0,     0,     0,    15,   180,     0,
       0,   195,    15,     0,     0,   317,   320,     0,    67,    68,
       0,     0,    83,    93,    45,    93,    93,     0,    93,    15,
     225,   233,   228,   106,   290,     0,   292,   293,   294,   295,
       0,     0,    75,    76,    82,     0,   212,   210,     0,   209,
      15,   213,     0,   204,   203,    15,     0,    29,    63,    62,
      64,    91,    15,     0,    15,    15,     0,    15,     0,   298,
     305,    15,     0,   208,   211,     0,    15,     0,    45,     0,
     312,    54,    17,    58,    57,    52,    53,    50,    51,    59,
      49,    97,    56,    55,   104,     0,   141,    47,     0,     0,
      15,   179,     0,   194,     0,   313,    46,     0,     0,   120,
       0,   158,     0,    78,   196,    96,   101,    15,   124,   125,
     126,   127,   128,   129,   130,   131,   132,   133,   134,   135,
     136,   137,   138,   139,   113,    15,   122,     0,    17,   146,
      77,   105,     0,    15,    48,   121,     0,    15,     0,     0,
     123
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     7,     8,     9,    10,    11,    12,    13,    33,    41,
      30,   520,   280,    31,   242,   158,    43,   244,   503,   550,
     521,   522,   254,    44,    45,    46,   250,   332,   442,   512,
     129,   130,   385,   131,   336,   460,   337,   415,    47,   256,
     525,   303,    49,   526,   342,   547,    72,    73,    74,    51,
     527,   347,   548,   575,   583,   576,    53,   528,   352,    55,
      56,   229,    75,   119,    34,    57,   354,   222,   530,   454,
     141,   142,   143,   144,   145,   391,   146,   147,   148,   149,
     312,   150,   403,   495,   348,   151,    63,    64,    65,    66,
     180,    67,   425,   120,   201,   202,   121,   122,   123,   288,
     374,   375,   289,   290,   299,   124,   125,   126,   531,   532,
     533,   356,   323,   169,   265
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -452
static const yytype_int16 yypact[] =
{
     508,   -52,   -43,   -19,   -12,   110,    29,   251,  -452,  -452,
    -452,  -452,  -452,  -452,    48,  -452,  -452,  -452,  -452,  -452,
    -452,  -452,   266,   266,   266,   266,   266,   266,  -452,   475,
    -452,  -452,   549,   266,   261,    81,  1157,   273,   692,   444,
     441,   563,   476,  -452,   234,  -452,  -452,   256,  -452,   288,
    -452,   285,  -452,   320,  -452,   333,  -452,   868,  -452,  -452,
    -452,  -452,  -452,   284,  1544,   295,   309,   363,  -452,  -452,
    -452,  -452,  -452,  -452,  -452,   334,  -452,  -452,  -452,  -452,
    -452,  -452,  -452,  -452,  -452,  -452,  -452,  -452,  -452,  -452,
    -452,  -452,  -452,  -452,  -452,  -452,  -452,  -452,  -452,  -452,
    -452,  -452,  -452,  -452,  -452,  -452,  -452,  -452,  -452,  -452,
    -452,  -452,  -452,  -452,  -452,  -452,  -452,  -452,  -452,  1753,
     966,  -452,  -452,  -452,  -452,  -452,  -452,  -452,  -452,  -452,
      50,  -452,   332,   400,  -452,  -452,   488,   424,  -452,   429,
    -452,    97,   868,    27,   798,  -452,   897,   356,  -452,  -452,
    -452,  -452,   454,  -452,  -452,  -452,  -452,  -452,  1757,   456,
     417,   248,   422,  -452,  -452,   338,   289,   474,   118,  -452,
     266,   298,    41,  -452,   366,   383,  -452,  -452,  -452,  -452,
    -452,   328,   206,  -452,   266,   266,   266,   426,   266,   266,
     760,  1250,   266,   266,   266,  -452,  -452,  -452,  -452,  -452,
    -452,  -452,  1424,   266,   266,   266,  1250,   266,   276,   259,
    -452,  -452,  -452,   231,  -452,  -452,  -452,  -452,   540,  -452,
    -452,  -452,   386,  -452,  -452,  -452,  -452,  -452,  -452,   868,
    -452,  -452,   897,   392,   676,  -452,  -452,   186,    33,   396,
    -452,   507,  -452,  -452,  -452,  -452,  -452,  -452,  -452,  -452,
      14,  -452,   464,   266,    14,   345,   504,   455,   565,    78,
     571,   266,   406,   868,   386,  1249,  -452,  -452,  -452,  -452,
     266,   266,  -452,  1069,  -452,  -452,  -452,    35,  -452,  -452,
    -452,   657,    35,  -452,  -452,  1784,    35,  -452,  -452,  -452,
     101,   266,   266,  -452,   266,   266,  -452,    35,    39,    47,
    -452,  -452,  -452,   457,  -452,  -452,   216,   692,   692,   400,
     429,   535,   227,  -452,   266,   266,   266,  -452,   685,  -452,
    -452,  -452,  -452,   554,  -452,  -452,   220,   573,   563,   266,
    -452,  -452,  -452,  -452,  -452,  -452,  -452,   119,  -452,  -452,
    -452,  -452,  -452,  -452,  -452,   541,   557,  -452,  -452,  -452,
    -452,  -452,  -452,   158,   477,  -452,  -452,  1157,   266,   266,
    1379,  -452,   550,   377,    81,  -452,  -452,  -452,   446,  1301,
    -452,  -452,  -452,   440,  1662,    76,    91,  -452,   246,  -452,
    -452,   273,   266,   469,  -452,  -452,   692,  -452,  -452,   524,
    -452,    70,  -452,   266,  -452,   409,  -452,  -452,  -452,  -452,
    -452,  -452,  -452,  -452,   266,   186,  -452,  -452,  -452,  -452,
     283,   339,  -452,  -452,   486,  -452,   529,  -452,  -452,   542,
    -452,   543,  -452,   550,  -452,   757,    66,  -452,   266,    35,
     101,   603,   639,  -452,  -452,  -452,  -452,  -452,  1301,  -452,
    -452,  -452,  -452,   273,    70,    46,   212,  -452,  -452,   202,
     252,  -452,  -452,   505,   868,  -452,  -452,   237,  -452,  -452,
      89,   145,   273,  -452,   266,  -452,  -452,   906,  -452,  -452,
    -452,   266,  -452,  -452,  -452,    76,  -452,  -452,   266,   266,
      39,   215,   266,   274,    50,   323,  -452,  -452,   265,  -452,
    -452,  -452,   505,  -452,  -452,  -452,   365,  -452,  -452,  -452,
    -452,  -452,  -452,  1664,  -452,  -452,    66,  -452,   906,  -452,
     246,  -452,   546,  -452,  -452,   692,  -452,    32,   266,   186,
    -452,  -452,  -452,  -452,  -452,  -452,  -452,  -452,  -452,  -452,
    -452,  -452,  -452,  -452,   266,  1608,  -452,   266,    66,  1157,
    -452,  -452,    64,  -452,  1664,  -452,   563,   209,   483,  -452,
     879,  -452,   863,   266,  -452,  -452,  -452,  -452,  -452,  -452,
    -452,  -452,  -452,  -452,  -452,  -452,  -452,  -452,  -452,  -452,
    -452,  -452,  -452,  -452,  -452,  -452,  -452,    66,  -452,  -452,
     266,   266,  1526,  -452,   563,  -452,   260,  -452,   377,    66,
    -452
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -452,  -452,  -452,  -452,  -452,  -452,  -452,  -452,     0,  -230,
    -452,  -221,  -232,  -452,  -452,  -452,   492,  -452,   134,  -452,
     104,  -452,  -452,  -452,  -451,  -447,  -452,   407,  -452,  -452,
     279,   223,  -452,  -340,   -36,  -452,   264,  -283,  -452,  -141,
     -11,  -452,  -452,    -8,  -452,  -452,   120,  -452,   314,  -452,
      -2,  -452,  -452,  -452,  -452,  -452,  -452,    -1,  -452,  -452,
    -439,  -452,   373,   -33,   -20,  -452,  -267,   512,     2,  -452,
     -51,  -452,   228,   465,  -139,   301,   544,   149,  -124,  -452,
     378,  -452,   303,   192,   351,  -452,  -327,  -452,   635,   642,
    -166,  -452,   291,  -186,   106,  -452,   513,   -92,  -452,   362,
    -452,  -276,   375,  -199,  -452,  -452,  -452,  -452,   -41,   592,
     593,    -6,  -452,    63,  -209
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -297
static const yytype_int16 yytable[] =
{
      14,   132,    76,   223,   281,   266,   168,   298,    22,    23,
      24,    25,    26,    27,   328,    32,   321,    35,    36,    37,
      38,    48,   378,   236,    50,   262,   330,   196,   224,    40,
      52,    54,   225,   154,    58,   278,   426,    28,    28,  -296,
     372,   440,   160,   161,   373,   365,    28,   278,    15,   366,
     367,    28,   523,    28,   371,   -15,   524,    16,   267,  -296,
     170,   171,   172,   360,   529,   377,   319,   380,   420,    28,
     414,   448,   181,   182,    29,   -15,   278,   184,   185,   186,
     187,    17,    68,    28,   376,   421,    28,   362,    18,   498,
     317,   345,  -297,   523,    69,   346,   435,   524,   220,   287,
     188,  -296,   372,   440,   331,   529,   373,   361,   -15,   236,
     236,   189,   190,   191,   287,    19,   192,   193,   194,   220,
     412,  -296,   203,   204,   205,   206,   207,  -160,  -160,    20,
     208,   209,  -160,   226,   227,   228,   324,   279,   218,   469,
     506,  -296,   543,   437,  -296,   -89,   412,    48,   486,   279,
      50,  -296,   379,   248,   475,   238,    52,    54,   285,   220,
      58,  -151,   253,   255,   257,   259,   261,   320,   390,   392,
     430,   423,   -15,   285,   554,   -15,   270,   271,   279,   273,
     502,   538,   504,   505,   455,   507,   319,    70,   436,   152,
      71,   152,   499,   370,   236,   291,   292,   474,   221,   294,
     295,   416,  -157,  -296,   510,   473,   419,    28,   549,   319,
      68,    28,   353,  -296,   306,   307,   308,    28,  -157,  -156,
      28,    28,    69,  -157,   413,    28,   314,   315,   316,   387,
     388,   322,   406,   325,   396,   397,   398,   399,   400,   480,
     326,   272,    28,   509,   304,   -89,   334,   390,   -89,   329,
     413,    21,   344,    28,   350,   585,   162,    28,  -144,   472,
     293,   589,    59,  -157,    28,    28,   435,   357,   358,   359,
      28,    28,   301,    76,    60,   363,   364,   287,    28,    28,
     163,    28,   287,   368,   369,   536,   152,   320,    28,  -151,
     260,   511,   546,   233,   -15,   234,   282,   286,   545,   178,
     381,   382,   383,    28,   489,   386,   275,   490,   165,   393,
     320,   276,   297,   404,   487,    70,    61,   551,    71,   302,
     164,   409,    70,   407,   305,    71,   556,   574,    28,   127,
     128,    76,   410,    28,   300,   411,   285,   401,   402,   258,
     497,   285,   261,   -15,    28,   166,   287,   261,   584,   251,
      28,   -15,   -83,   552,   491,   -15,   545,   235,   436,    62,
     587,  -174,  -214,   302,   178,   428,   224,   514,   590,   167,
     225,   134,   135,   136,   137,   138,   541,  -214,    59,   438,
     179,   318,    28,   152,   443,   173,   458,   445,   446,   -15,
      60,   449,   450,   235,   393,   127,   128,  -177,   176,   456,
     467,   127,   128,   453,   459,   285,   457,   134,   135,   136,
     137,   138,   177,   462,   183,   464,   396,   397,   398,   399,
     400,   211,    28,   252,   471,   513,   501,   -15,   490,   274,
     249,    28,    61,   210,   -15,   478,   479,   217,   -15,   277,
     481,   482,   483,   -83,   485,   -95,    28,   488,   -95,   508,
     219,    28,   492,   155,   500,   237,  -174,  -174,  -174,   429,
      28,  -174,  -174,  -174,  -174,  -161,  -161,   340,   341,   268,
    -161,   226,   227,   228,    28,    62,    39,   159,  -214,   263,
     -15,   -15,   441,   319,   208,   535,   269,   -15,   -15,   -15,
     515,   313,  -177,  -177,  -177,   517,   152,  -177,  -177,  -177,
    -177,   212,   518,   555,   534,   213,   351,   537,   327,   579,
      28,   539,   -15,   325,    76,   384,   542,   493,   494,   451,
     402,   558,   559,   560,   561,   562,   563,   564,   565,   566,
     567,   568,   569,   570,   571,   572,   573,     1,     2,     3,
     553,     4,     5,     6,   152,    28,   431,   153,   394,   432,
    -234,   197,   580,   309,    28,   405,   152,   581,   346,   247,
     310,   140,  -241,  -241,   152,  -241,   -15,   333,   156,   157,
     418,   -61,  -112,   -94,  -140,   582,    42,   422,  -241,   214,
     215,  -100,   216,   586,   320,  -145,   463,   588,  -234,  -234,
    -234,  -234,  -234,  -234,  -234,  -234,  -234,  -234,  -234,  -234,
    -234,  -234,  -234,  -234,   338,   424,   447,   339,   476,  -241,
    -241,  -241,  -241,  -241,  -241,  -241,  -241,  -241,  -241,  -241,
    -241,  -241,  -241,  -241,  -241,  -241,  -241,  -241,  -241,   465,
    -241,  -241,  -241,  -241,  -241,  -241,  -241,  -241,  -241,  -241,
    -241,  -241,   466,   468,   477,  -241,  -241,  -241,   540,  -241,
     243,  -234,   544,  -234,   578,   199,  -241,   278,   197,  -241,
     439,   335,   200,  -241,  -241,   152,   484,   557,   343,  -241,
    -241,   152,  -241,   152,   349,   461,   408,   235,   427,   389,
     264,  -173,   496,   311,   516,  -241,   235,   444,   232,   395,
    -176,   134,   135,   136,   137,   138,   417,    28,   452,   174,
     134,   135,   136,   137,   138,   133,   175,   134,   135,   136,
     137,   138,   139,   140,   470,   296,  -241,  -241,  -241,  -241,
    -241,  -241,  -241,  -241,  -241,  -241,  -241,  -241,  -241,  -241,
    -241,  -241,  -241,  -241,  -241,  -241,   433,  -241,  -241,  -241,
    -241,  -241,  -241,  -241,  -241,  -241,  -241,  -241,  -241,   434,
     245,   246,  -241,  -241,  -241,     0,  -241,  -226,   178,   279,
     278,   197,   199,  -241,     0,    28,  -241,     0,     0,   200,
    -241,  -241,    77,    78,     0,    79,  -173,  -173,  -173,     0,
       0,  -173,  -173,  -173,  -173,  -176,  -176,  -176,    80,     0,
    -176,  -176,  -176,  -176,     0,  -226,  -226,  -226,  -226,  -226,
    -226,  -226,  -226,  -226,  -226,  -226,  -226,  -226,  -226,  -226,
    -226,   230,     0,   134,   135,   136,   137,   138,   231,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    99,   100,     0,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,     0,     0,     0,   113,   114,   115,  -226,   116,
    -226,     0,   279,     0,   197,     0,    70,     0,   -15,    71,
       0,     0,     0,   117,   118,  -241,  -241,     0,  -241,   319,
     577,   133,     0,   134,   135,   136,   137,   138,   139,   140,
       0,  -241,  -155,     0,  -155,  -155,  -155,  -155,  -155,  -155,
    -155,     0,  -112,   -94,  -140,     0,  -214,    59,     0,     0,
       0,  -100,   134,   135,   136,   137,   138,     0,     0,    60,
       0,     0,  -241,  -241,  -241,  -241,  -241,  -241,  -241,  -241,
    -241,  -241,  -241,  -241,  -241,  -241,  -241,  -241,  -241,  -241,
    -241,  -241,     0,  -241,  -241,  -241,  -241,  -241,  -241,  -241,
    -241,  -241,  -241,  -241,  -241,     0,     0,     0,  -241,  -241,
    -241,    61,  -241,     0,     0,   -15,     0,   197,   199,  -241,
       0,     0,  -241,     0,     0,   200,  -241,  -241,  -241,  -241,
     320,  -241,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  -241,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    62,     0,     0,  -214,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  -241,  -241,  -241,  -241,  -241,
    -241,  -241,  -241,  -241,  -241,  -241,  -241,  -241,  -241,  -241,
    -241,  -241,  -241,  -241,  -241,     0,  -241,  -241,  -241,  -241,
    -241,  -241,  -241,  -241,  -241,  -241,  -241,  -241,     0,     0,
       0,  -241,  -241,  -241,     0,  -241,     0,   198,     0,     0,
     178,   199,  -241,     0,    28,  -241,     0,     0,   200,  -241,
    -241,    77,    78,     0,    79,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    80,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   100,     0,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,     0,    28,     0,   113,   114,   115,     0,   116,    77,
      78,     0,    79,     0,     0,    70,     0,     0,    71,     0,
       0,     0,   117,   118,     0,    80,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,     0,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,  -224,
     355,   197,   113,   114,   115,    28,   116,     0,     0,     0,
       0,     0,     0,    70,     0,     0,    71,     0,     0,     0,
     117,   118,     0,     0,     0,     0,     0,     0,   283,     0,
       0,     0,     0,     0,     0,     0,     0,  -224,  -224,  -224,
    -224,  -224,  -224,  -224,  -224,  -224,  -224,  -224,  -224,  -224,
    -224,  -224,  -224,     0,     0,     0,    28,     0,     0,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    99,     0,   283,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   152,
    -224,     0,  -224,     0,   284,     0,    70,     0,     0,    71,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    99,  -231,
     355,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   284,     0,    70,     0,     0,
      71,     0,     0,     0,     0,     0,     0,  -231,  -231,  -231,
    -231,  -231,  -231,  -231,  -231,  -231,  -231,  -231,  -231,  -231,
    -231,  -231,  -231,     0,     0,     0,    77,    78,     0,    79,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    80,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   152,
    -231,     0,  -231,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   100,     0,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,     0,     0,     0,   113,
     114,   115,     0,   116,     0,     0,  -214,    59,     0,     0,
      70,    28,     0,    71,     0,     0,     0,   117,   118,    60,
       0,     0,     0,     0,  -217,    59,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    60,     0,     0,
       0,     0,     0,     0,  -214,  -214,  -214,  -214,  -214,  -214,
    -214,  -214,  -214,  -214,  -214,  -214,  -214,  -214,  -214,  -214,
       0,    61,  -217,  -217,  -217,  -217,  -217,  -217,  -217,  -217,
    -217,  -217,  -217,  -217,  -217,  -217,  -217,  -217,     0,    61,
       0,     0,     0,     0,     0,     0,     0,     0,  -214,    59,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    60,     0,     0,    62,     0,     0,  -214,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    62,     0,     0,  -217,  -214,  -214,  -214,  -214,
    -214,  -214,  -214,  -214,  -214,  -214,  -214,  -214,  -214,  -214,
    -214,  -214,     0,    61,   319,   519,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  -155,     0,  -155,
    -155,  -155,  -155,  -155,  -155,  -155,   -61,  -112,   -94,  -140,
     283,    42,     0,     0,     0,     0,  -100,     0,     0,     0,
    -145,     0,     0,     0,     0,     0,    62,     0,     0,  -214,
       0,     0,     0,     0,     0,     0,     0,     0,   241,     0,
       0,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
       0,     0,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,     0,     0,     0,     0,     0,    -2,   239,     0,
       0,     0,     0,     0,     0,   320,   284,     0,    70,     0,
    -155,    71,  -155,  -155,  -155,  -155,  -155,  -155,  -155,   -61,
    -112,   -94,  -140,   240,    42,     0,     0,     0,     0,  -100,
       0,     0,     0,  -145,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   241,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   195,     0,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,     0,     0,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110
};

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-452)))

#define yytable_value_is_error(Yytable_value) \
  (!!((Yytable_value) == (-297)))

static const yytype_int16 yycheck[] =
{
       0,    37,    35,   142,   190,   171,    57,   206,     8,     9,
      10,    11,    12,    13,   244,    15,   237,    17,    18,    19,
      20,    32,   298,   147,    32,   166,    12,   119,     1,    29,
      32,    32,     5,    39,    32,     0,   363,     5,     5,     0,
       1,   381,    42,    43,     5,   277,     5,     0,   100,   281,
     282,     5,   503,     5,   286,     5,   503,   100,    17,    20,
      60,    61,    62,   272,   503,   297,     0,   299,   351,     5,
     337,     1,    72,    73,    26,     5,     0,    77,    78,    79,
      80,   100,     1,     5,   293,   352,     5,   273,   100,     0,
     229,    13,     1,   544,    13,    17,    20,   544,     1,   191,
     100,     0,     1,   443,    90,   544,     5,   273,    58,   233,
     234,   111,   112,   113,   206,     5,   116,   117,   118,     1,
       1,    20,   122,   123,   124,   125,   126,   100,   101,   100,
     130,   131,   105,   106,   107,   108,   103,   102,   138,   422,
     467,   102,   110,   375,   105,     0,     1,   158,   102,   102,
     158,   112,   105,   159,   430,   155,   158,   158,   191,     1,
     158,    80,   162,   163,   164,   165,   166,   101,   307,   308,
     369,   357,   102,   206,   110,   105,   176,   177,   102,   179,
     463,   508,   465,   466,   405,   468,     0,   106,   112,   100,
     109,   100,   103,   285,   318,   195,   196,   429,   101,   199,
     200,   342,   105,   102,   480,   426,   347,     5,   535,     0,
       1,     5,   263,   112,   214,   215,   216,     5,   100,   100,
       5,     5,    13,   105,   105,     5,   226,   227,   228,    13,
      14,   237,    12,   239,     7,     8,     9,    10,    11,   438,
     240,   178,     5,   475,    13,   100,   252,   386,   103,   249,
     105,     0,   258,     5,   260,   582,    22,     5,   100,   425,
     197,   588,     1,   105,     5,     5,    20,   267,   268,   269,
       5,     5,    13,   306,    13,   275,   276,   369,     5,     5,
      24,     5,   374,   283,   284,   506,   100,   101,     5,    80,
       1,    17,   522,   144,     5,   146,   190,   191,   519,     1,
     300,   301,   302,     5,   102,   305,   100,   105,    23,   309,
     101,   105,   206,   313,   102,   106,    55,   538,   109,   104,
      32,   327,   106,   103,    93,   109,   547,   548,     5,    56,
      57,   364,   332,     5,    58,   335,   369,   110,   111,     1,
     103,   374,   342,     5,     5,    25,   438,   347,   578,   101,
       5,    13,    13,   539,   102,    17,   577,     1,   112,    98,
     100,     5,   101,   104,     1,   365,     1,   102,   589,    36,
       5,    15,    16,    17,    18,    19,   515,     0,     1,   379,
      17,   232,     5,   100,   384,   101,   103,   387,   388,   100,
      13,   391,   392,     1,   394,    56,    57,     5,   103,   405,
     420,    56,    57,   403,   410,   438,   406,    15,    16,    17,
      18,    19,   103,   413,    80,   415,     7,     8,     9,    10,
      11,    21,     5,     1,   424,   102,   462,     5,   105,   101,
      13,     5,    55,   101,    12,   435,   436,    13,   100,    13,
     440,   441,   442,   104,   444,   100,     5,   447,   103,   469,
      21,     5,   452,    12,   460,     1,   100,   101,   102,    13,
       5,   105,   106,   107,   108,   100,   101,    12,    13,   103,
     105,   106,   107,   108,     5,    98,     1,     1,   101,     5,
       5,     5,    13,     0,   484,   505,   103,    12,    12,    13,
     490,   105,   100,   101,   102,   495,   100,   105,   106,   107,
     108,    13,   502,   544,   504,    17,   100,   507,     1,   550,
       5,   511,    90,   519,   547,    58,   516,    12,    13,   110,
     111,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    29,    30,    31,
     540,    33,    34,    35,   100,     5,   106,   103,    13,   109,
       0,     1,   552,    13,     5,     1,   100,   557,    17,   103,
      20,    21,    12,    13,   100,    15,    90,   103,     5,     6,
      13,    22,    23,    24,    25,   575,    27,   100,    28,    91,
      92,    32,    94,   583,   101,    36,   100,   587,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,   100,    55,    82,   103,     5,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,   100,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,   100,   100,     5,    95,    96,    97,   102,    99,
     158,   101,   518,   103,   550,   105,   106,     0,     1,   109,
     381,   254,   112,   113,   114,   100,   443,   547,   103,    12,
      13,   100,    15,   100,   103,   411,   103,     1,   364,   306,
     168,     5,   454,   218,   492,    28,     1,   386,   144,   311,
       5,    15,    16,    17,    18,    19,   345,     5,   395,    64,
      15,    16,    17,    18,    19,    13,    64,    15,    16,    17,
      18,    19,    20,    21,   423,   202,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,   374,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,   374,
     158,   158,    95,    96,    97,    -1,    99,     0,     1,   102,
       0,     1,   105,   106,    -1,     5,   109,    -1,    -1,   112,
     113,   114,    12,    13,    -1,    15,   100,   101,   102,    -1,
      -1,   105,   106,   107,   108,   100,   101,   102,    28,    -1,
     105,   106,   107,   108,    -1,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    13,    -1,    15,    16,    17,    18,    19,    20,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    -1,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    -1,    -1,    -1,    95,    96,    97,   101,    99,
     103,    -1,   102,    -1,     1,    -1,   106,    -1,     5,   109,
      -1,    -1,    -1,   113,   114,    12,    13,    -1,    15,     0,
       1,    13,    -1,    15,    16,    17,    18,    19,    20,    21,
      -1,    28,    13,    -1,    15,    16,    17,    18,    19,    20,
      21,    -1,    23,    24,    25,    -1,     0,     1,    -1,    -1,
      -1,    32,    15,    16,    17,    18,    19,    -1,    -1,    13,
      -1,    -1,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    -1,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    -1,    -1,    -1,    95,    96,
      97,    55,    99,    -1,    -1,   102,    -1,     1,   105,   106,
      -1,    -1,   109,    -1,    -1,   112,   113,   114,    12,    13,
     101,    15,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    28,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    98,    -1,    -1,   101,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    -1,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    -1,    -1,
      -1,    95,    96,    97,    -1,    99,    -1,   101,    -1,    -1,
       1,   105,   106,    -1,     5,   109,    -1,    -1,   112,   113,
     114,    12,    13,    -1,    15,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    28,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    -1,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    -1,     5,    -1,    95,    96,    97,    -1,    99,    12,
      13,    -1,    15,    -1,    -1,   106,    -1,    -1,   109,    -1,
      -1,    -1,   113,   114,    -1,    28,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    -1,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,     0,
       1,     1,    95,    96,    97,     5,    99,    -1,    -1,    -1,
      -1,    -1,    -1,   106,    -1,    -1,   109,    -1,    -1,    -1,
     113,   114,    -1,    -1,    -1,    -1,    -1,    -1,    28,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    -1,    -1,    -1,     5,    -1,    -1,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    -1,    28,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   100,
     101,    -1,   103,    -1,   104,    -1,   106,    -1,    -1,   109,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,     0,
       1,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   104,    -1,   106,    -1,    -1,
     109,    -1,    -1,    -1,    -1,    -1,    -1,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    -1,    -1,    -1,    12,    13,    -1,    15,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    28,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   100,
     101,    -1,   103,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    -1,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    -1,    -1,    -1,    95,
      96,    97,    -1,    99,    -1,    -1,     0,     1,    -1,    -1,
     106,     5,    -1,   109,    -1,    -1,    -1,   113,   114,    13,
      -1,    -1,    -1,    -1,     0,     1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    13,    -1,    -1,
      -1,    -1,    -1,    -1,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      -1,    55,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    -1,    55,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     0,     1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    13,    -1,    -1,    98,    -1,    -1,   101,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    98,    -1,    -1,   101,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    -1,    55,     0,     1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    13,    -1,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      28,    27,    -1,    -1,    -1,    -1,    32,    -1,    -1,    -1,
      36,    -1,    -1,    -1,    -1,    -1,    98,    -1,    -1,   101,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    54,    -1,
      -1,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      -1,    -1,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    -1,    -1,    -1,    -1,    -1,     0,     1,    -1,
      -1,    -1,    -1,    -1,    -1,   101,   104,    -1,   106,    -1,
      13,   109,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    -1,    -1,    -1,    -1,    32,
      -1,    -1,    -1,    36,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    54,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    -1,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    -1,    -1,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    29,    30,    31,    33,    34,    35,   116,   117,   118,
     119,   120,   121,   122,   123,   100,   100,   100,   100,     5,
     100,     0,   123,   123,   123,   123,   123,   123,     5,    26,
     125,   128,   123,   123,   179,   123,   123,   123,   123,     1,
     123,   124,    27,   131,   138,   139,   140,   153,   155,   157,
     158,   164,   165,   171,   172,   174,   175,   180,   183,     1,
      13,    55,    98,   201,   202,   203,   204,   206,     1,    13,
     106,   109,   161,   162,   163,   177,   178,    12,    13,    15,
      28,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    95,    96,    97,    99,   113,   114,   178,
     208,   211,   212,   213,   220,   221,   222,    56,    57,   145,
     146,   148,   149,    13,    15,    16,    17,    18,    19,    20,
      21,   185,   186,   187,   188,   189,   191,   192,   193,   194,
     196,   200,   100,   103,   226,    12,     5,     6,   130,     1,
     123,   123,    22,    24,    32,    23,    25,    36,   185,   228,
     123,   123,   123,   101,   203,   204,   103,   103,     1,    17,
     205,   123,   123,    80,   123,   123,   123,   123,   123,   123,
     123,   123,   123,   123,   123,    78,   212,     1,   101,   105,
     112,   209,   210,   123,   123,   123,   123,   123,   123,   123,
     101,    21,    13,    17,    91,    92,    94,    13,   123,    21,
       1,   101,   182,   189,     1,     5,   106,   107,   108,   176,
      13,    20,   191,   192,   192,     1,   193,     1,   123,     1,
      26,    54,   129,   131,   132,   224,   225,   103,   226,    13,
     141,   101,     1,   123,   137,   123,   154,   123,     1,   123,
       1,   123,   154,     5,   182,   229,   205,    17,   103,   103,
     123,   123,   228,   123,   101,   100,   105,    13,     0,   102,
     127,   208,   209,    28,   104,   178,   209,   212,   214,   217,
     218,   123,   123,   228,   123,   123,   211,   209,   218,   219,
      58,    13,   104,   156,    13,    93,   123,   123,   123,    13,
      20,   188,   195,   105,   123,   123,   123,   189,   192,     0,
     101,   126,   226,   227,   103,   226,   123,     1,   124,   123,
      12,    90,   142,   103,   226,   142,   149,   151,   100,   103,
      12,    13,   159,   103,   226,    13,    17,   166,   199,   103,
     226,   100,   173,   185,   181,     1,   226,   123,   123,   123,
     229,   205,   208,   123,   123,   127,   127,   127,   123,   123,
     212,   127,     1,     5,   215,   216,   229,   127,   216,   105,
     127,   123,   123,   123,    58,   147,   123,    13,    14,   177,
     189,   190,   189,   123,    13,   195,     7,     8,     9,    10,
      11,   110,   111,   197,   123,     1,    12,   103,   103,   226,
     123,   123,     1,   105,   181,   152,   154,   199,    13,   154,
     152,   181,   100,   208,    55,   207,   201,   163,   123,    13,
     218,   106,   109,   214,   217,    20,   112,   127,   123,   145,
     148,    13,   143,   123,   190,   123,   123,    82,     1,   123,
     123,   110,   197,   123,   184,   126,   226,   123,   103,   226,
     150,   151,   123,   100,   123,   100,   100,   179,   100,   152,
     207,   123,   205,   126,   127,   216,     5,     5,   123,   123,
     218,   123,   123,   123,   146,   123,   102,   102,   123,   102,
     105,   102,   123,    12,    13,   198,   187,   103,     0,   103,
     226,   149,   152,   133,   152,   152,   201,   152,   179,   127,
     216,    17,   144,   102,   102,   123,   198,   123,   123,     1,
     126,   135,   136,   139,   140,   155,   158,   165,   172,   175,
     183,   223,   224,   225,   123,   179,   126,   123,   201,   123,
     102,   189,   123,   110,   133,   126,   124,   160,   167,   201,
     134,   126,   208,   123,   110,   223,   126,   161,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,   126,   168,   170,     1,   135,   223,
     123,   123,   123,   169,   124,   201,   123,   100,   123,   201,
     126
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
      yyerror (parser, YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))

/* Error token number */
#define YYTERROR	1
#define YYERRCODE	256


/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */
#ifdef YYLEX_PARAM
# define YYLEX yylex (&yylval, YYLEX_PARAM)
#else
# define YYLEX yylex (&yylval, parser)
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
		  Type, Value, parser); \
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
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, CSSParser* parser)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep, parser)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    CSSParser* parser;
#endif
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
  YYUSE (parser);
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, CSSParser* parser)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep, parser)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    CSSParser* parser;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep, parser);
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
yy_reduce_print (YYSTYPE *yyvsp, int yyrule, CSSParser* parser)
#else
static void
yy_reduce_print (yyvsp, yyrule, parser)
    YYSTYPE *yyvsp;
    int yyrule;
    CSSParser* parser;
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
		       		       , parser);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule, parser); \
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
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULL, yytname[yyx]);
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

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, CSSParser* parser)
#else
static void
yydestruct (yymsg, yytype, yyvaluep, parser)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
    CSSParser* parser;
#endif
{
  YYUSE (yyvaluep);
  YYUSE (parser);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YYUSE (yytype);
}




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
yyparse (CSSParser* parser)
#else
int
yyparse (parser)
    CSSParser* parser;
#endif
#endif
{
/* The lookahead symbol.  */
int yychar;


#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
static YYSTYPE yyval_default;
# define YY_INITIAL_VALUE(Value) = Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval YY_INITIAL_VALUE(yyval_default);

    /* Number of syntax errors so far.  */
    int yynerrs;

    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

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
        case 9:
/* Line 1787 of yacc.c  */
#line 285 "./CSSGrammar.y"
    {
        parser->m_rule = (yyvsp[(4) - (6)].rule);
    }
    break;

  case 10:
/* Line 1787 of yacc.c  */
#line 290 "./CSSGrammar.y"
    {
        parser->m_keyframe = (yyvsp[(4) - (6)].keyframe);
    }
    break;

  case 11:
/* Line 1787 of yacc.c  */
#line 295 "./CSSGrammar.y"
    {
    }
    break;

  case 12:
/* Line 1787 of yacc.c  */
#line 299 "./CSSGrammar.y"
    {
        if ((yyvsp[(4) - (5)].valueList)) {
            parser->m_valueList = parser->sinkFloatingValueList((yyvsp[(4) - (5)].valueList));
            int oldParsedProperties = parser->m_parsedProperties.size();
            if (!parser->parseValue(parser->m_id, parser->m_important))
                parser->rollbackLastProperties(parser->m_parsedProperties.size() - oldParsedProperties);
            parser->m_valueList = nullptr;
        }
    }
    break;

  case 13:
/* Line 1787 of yacc.c  */
#line 310 "./CSSGrammar.y"
    {
         parser->m_mediaQuery = parser->sinkFloatingMediaQuery((yyvsp[(4) - (5)].mediaQuery));
     }
    break;

  case 14:
/* Line 1787 of yacc.c  */
#line 315 "./CSSGrammar.y"
    {
        if ((yyvsp[(4) - (5)].selectorList)) {
            if (parser->m_selectorListForParseSelector)
                parser->m_selectorListForParseSelector->adoptSelectorVector(*(yyvsp[(4) - (5)].selectorList));
        }
    }
    break;

  case 21:
/* Line 1787 of yacc.c  */
#line 331 "./CSSGrammar.y"
    {
  }
    break;

  case 26:
/* Line 1787 of yacc.c  */
#line 343 "./CSSGrammar.y"
    {
     if (parser->m_styleSheet)
         parser->m_styleSheet->parserSetEncodingFromCharsetRule((yyvsp[(3) - (5)].string));
     if (parser->isExtractingSourceData() && parser->m_currentRuleDataStack->isEmpty() && parser->m_ruleSourceDataResult)
         parser->addNewRuleToSourceTree(CSSRuleSourceData::createUnknown());
     (yyval.rule) = 0;
  }
    break;

  case 27:
/* Line 1787 of yacc.c  */
#line 350 "./CSSGrammar.y"
    {
  }
    break;

  case 28:
/* Line 1787 of yacc.c  */
#line 352 "./CSSGrammar.y"
    {
  }
    break;

  case 29:
/* Line 1787 of yacc.c  */
#line 356 "./CSSGrammar.y"
    {
        (yyval.rule) = 0;
    }
    break;

  case 30:
/* Line 1787 of yacc.c  */
#line 359 "./CSSGrammar.y"
    {
        (yyval.rule) = 0;
    }
    break;

  case 32:
/* Line 1787 of yacc.c  */
#line 364 "./CSSGrammar.y"
    {
     if ((yyvsp[(2) - (3)].rule) && parser->m_styleSheet)
         parser->m_styleSheet->parserAppendRule((yyvsp[(2) - (3)].rule));
 }
    break;

  case 41:
/* Line 1787 of yacc.c  */
#line 380 "./CSSGrammar.y"
    {
        parser->m_hadSyntacticallyValidCSSRule = true;
    }
    break;

  case 45:
/* Line 1787 of yacc.c  */
#line 388 "./CSSGrammar.y"
    { (yyval.ruleList) = 0; }
    break;

  case 46:
/* Line 1787 of yacc.c  */
#line 389 "./CSSGrammar.y"
    {
      (yyval.ruleList) = (yyvsp[(1) - (3)].ruleList);
      if ((yyvsp[(2) - (3)].rule)) {
          if (!(yyval.ruleList))
              (yyval.ruleList) = parser->createRuleList();
          (yyval.ruleList)->append((yyvsp[(2) - (3)].rule));
      }
  }
    break;

  case 47:
/* Line 1787 of yacc.c  */
#line 399 "./CSSGrammar.y"
    { (yyval.ruleList) = 0; }
    break;

  case 48:
/* Line 1787 of yacc.c  */
#line 400 "./CSSGrammar.y"
    {
      (yyval.ruleList) = (yyvsp[(1) - (3)].ruleList);
      if ((yyvsp[(2) - (3)].rule)) {
          if (!(yyval.ruleList))
              (yyval.ruleList) = parser->createRuleList();
          (yyval.ruleList)->append((yyvsp[(2) - (3)].rule));
      }
  }
    break;

  case 60:
/* Line 1787 of yacc.c  */
#line 425 "./CSSGrammar.y"
    {
        parser->markRuleHeaderEnd();
        parser->markRuleBodyStart();
    }
    break;

  case 61:
/* Line 1787 of yacc.c  */
#line 431 "./CSSGrammar.y"
    {
        parser->markRuleHeaderStart(CSSRuleSourceData::IMPORT_RULE);
    }
    break;

  case 62:
/* Line 1787 of yacc.c  */
#line 436 "./CSSGrammar.y"
    {
        (yyval.rule) = parser->createImportRule((yyvsp[(4) - (7)].string), (yyvsp[(6) - (7)].mediaList));
    }
    break;

  case 63:
/* Line 1787 of yacc.c  */
#line 439 "./CSSGrammar.y"
    {
        (yyval.rule) = parser->createImportRule((yyvsp[(4) - (7)].string), (yyvsp[(6) - (7)].mediaList));
    }
    break;

  case 64:
/* Line 1787 of yacc.c  */
#line 442 "./CSSGrammar.y"
    {
        (yyval.rule) = 0;
        parser->popRuleData();
    }
    break;

  case 65:
/* Line 1787 of yacc.c  */
#line 446 "./CSSGrammar.y"
    {
        (yyval.rule) = 0;
        parser->popRuleData();
    }
    break;

  case 66:
/* Line 1787 of yacc.c  */
#line 450 "./CSSGrammar.y"
    {
        (yyval.rule) = 0;
        parser->popRuleData();
    }
    break;

  case 67:
/* Line 1787 of yacc.c  */
#line 456 "./CSSGrammar.y"
    {
    parser->addNamespace((yyvsp[(3) - (6)].string), (yyvsp[(4) - (6)].string));
    (yyval.rule) = 0;
}
    break;

  case 68:
/* Line 1787 of yacc.c  */
#line 460 "./CSSGrammar.y"
    {
    (yyval.rule) = 0;
}
    break;

  case 69:
/* Line 1787 of yacc.c  */
#line 463 "./CSSGrammar.y"
    {
    (yyval.rule) = 0;
}
    break;

  case 70:
/* Line 1787 of yacc.c  */
#line 466 "./CSSGrammar.y"
    {
    (yyval.rule) = 0;
}
    break;

  case 71:
/* Line 1787 of yacc.c  */
#line 471 "./CSSGrammar.y"
    { (yyval.string).clear(); }
    break;

  case 72:
/* Line 1787 of yacc.c  */
#line 472 "./CSSGrammar.y"
    { (yyval.string) = (yyvsp[(1) - (2)].string); }
    break;

  case 75:
/* Line 1787 of yacc.c  */
#line 479 "./CSSGrammar.y"
    {
        (yyval.string) = (yyvsp[(1) - (2)].string);
    }
    break;

  case 76:
/* Line 1787 of yacc.c  */
#line 484 "./CSSGrammar.y"
    {
        (yyval.valueList) = 0;
    }
    break;

  case 77:
/* Line 1787 of yacc.c  */
#line 487 "./CSSGrammar.y"
    {
        (yyval.valueList) = (yyvsp[(3) - (4)].valueList);
    }
    break;

  case 78:
/* Line 1787 of yacc.c  */
#line 492 "./CSSGrammar.y"
    {
        if ((yyvsp[(1) - (9)].mediaQueryRestrictor) != MediaQuery::None)
            (yyval.mediaQueryExp) = parser->createFloatingMediaQueryExp("", 0);
        else {
            (yyvsp[(5) - (9)].string).lower();
            (yyval.mediaQueryExp) = parser->createFloatingMediaQueryExp((yyvsp[(5) - (9)].string), (yyvsp[(7) - (9)].valueList));
        }
    }
    break;

  case 79:
/* Line 1787 of yacc.c  */
#line 502 "./CSSGrammar.y"
    {
        (yyval.mediaQueryExpList) = parser->createFloatingMediaQueryExpList();
        (yyval.mediaQueryExpList)->append(parser->sinkFloatingMediaQueryExp((yyvsp[(1) - (1)].mediaQueryExp)));
    }
    break;

  case 80:
/* Line 1787 of yacc.c  */
#line 506 "./CSSGrammar.y"
    {
        (yyval.mediaQueryExpList) = (yyvsp[(1) - (5)].mediaQueryExpList);
        (yyval.mediaQueryExpList)->append(parser->sinkFloatingMediaQueryExp((yyvsp[(5) - (5)].mediaQueryExp)));
    }
    break;

  case 81:
/* Line 1787 of yacc.c  */
#line 512 "./CSSGrammar.y"
    {
        (yyval.mediaQueryExpList) = parser->createFloatingMediaQueryExpList();
    }
    break;

  case 82:
/* Line 1787 of yacc.c  */
#line 515 "./CSSGrammar.y"
    {
        (yyval.mediaQueryExpList) = (yyvsp[(3) - (3)].mediaQueryExpList);
    }
    break;

  case 83:
/* Line 1787 of yacc.c  */
#line 520 "./CSSGrammar.y"
    {
        (yyval.mediaQueryRestrictor) = MediaQuery::None;
    }
    break;

  case 84:
/* Line 1787 of yacc.c  */
#line 523 "./CSSGrammar.y"
    {
        (yyval.mediaQueryRestrictor) = MediaQuery::Only;
    }
    break;

  case 85:
/* Line 1787 of yacc.c  */
#line 526 "./CSSGrammar.y"
    {
        (yyval.mediaQueryRestrictor) = MediaQuery::Not;
    }
    break;

  case 86:
/* Line 1787 of yacc.c  */
#line 531 "./CSSGrammar.y"
    {
        (yyval.mediaQuery) = parser->createFloatingMediaQuery(parser->sinkFloatingMediaQueryExpList((yyvsp[(1) - (1)].mediaQueryExpList)));
    }
    break;

  case 87:
/* Line 1787 of yacc.c  */
#line 535 "./CSSGrammar.y"
    {
        (yyvsp[(3) - (4)].string).lower();
        (yyval.mediaQuery) = parser->createFloatingMediaQuery((yyvsp[(1) - (4)].mediaQueryRestrictor), (yyvsp[(3) - (4)].string), parser->sinkFloatingMediaQueryExpList((yyvsp[(4) - (4)].mediaQueryExpList)));
    }
    break;

  case 88:
/* Line 1787 of yacc.c  */
#line 541 "./CSSGrammar.y"
    {
        (yyval.mediaList) = parser->createMediaQuerySet();
     }
    break;

  case 90:
/* Line 1787 of yacc.c  */
#line 547 "./CSSGrammar.y"
    {
        (yyval.mediaList) = parser->createMediaQuerySet();
        (yyval.mediaList)->addMediaQuery(parser->sinkFloatingMediaQuery((yyvsp[(1) - (1)].mediaQuery)));
        parser->updateLastMediaLine((yyval.mediaList));
    }
    break;

  case 91:
/* Line 1787 of yacc.c  */
#line 552 "./CSSGrammar.y"
    {
        (yyval.mediaList) = (yyvsp[(1) - (4)].mediaList);
        if ((yyval.mediaList)) {
            (yyval.mediaList)->addMediaQuery(parser->sinkFloatingMediaQuery((yyvsp[(4) - (4)].mediaQuery)));
            parser->updateLastMediaLine((yyval.mediaList));
        }
    }
    break;

  case 92:
/* Line 1787 of yacc.c  */
#line 559 "./CSSGrammar.y"
    {
        (yyval.mediaList) = 0;
    }
    break;

  case 93:
/* Line 1787 of yacc.c  */
#line 564 "./CSSGrammar.y"
    {
        parser->markRuleBodyStart();
    }
    break;

  case 94:
/* Line 1787 of yacc.c  */
#line 569 "./CSSGrammar.y"
    {
        parser->markRuleHeaderStart(CSSRuleSourceData::MEDIA_RULE);
    }
    break;

  case 95:
/* Line 1787 of yacc.c  */
#line 574 "./CSSGrammar.y"
    {
        parser->markRuleHeaderEnd();
    }
    break;

  case 96:
/* Line 1787 of yacc.c  */
#line 579 "./CSSGrammar.y"
    {
        (yyval.rule) = parser->createMediaRule((yyvsp[(4) - (10)].mediaList), (yyvsp[(9) - (10)].ruleList));
    }
    break;

  case 97:
/* Line 1787 of yacc.c  */
#line 582 "./CSSGrammar.y"
    {
        (yyval.rule) = parser->createMediaRule(0, (yyvsp[(7) - (8)].ruleList));
    }
    break;

  case 98:
/* Line 1787 of yacc.c  */
#line 585 "./CSSGrammar.y"
    {
        (yyval.rule) = 0;
        parser->popRuleData();
    }
    break;

  case 99:
/* Line 1787 of yacc.c  */
#line 591 "./CSSGrammar.y"
    {
      (yyval.string) = (yyvsp[(1) - (2)].string);
  }
    break;

  case 100:
/* Line 1787 of yacc.c  */
#line 596 "./CSSGrammar.y"
    {
        parser->markRuleHeaderStart(CSSRuleSourceData::KEYFRAMES_RULE);
    }
    break;

  case 101:
/* Line 1787 of yacc.c  */
#line 601 "./CSSGrammar.y"
    {
        (yyval.rule) = parser->createKeyframesRule((yyvsp[(4) - (10)].string), parser->sinkFloatingKeyframeVector((yyvsp[(9) - (10)].keyframeRuleList)));
    }
    break;

  case 104:
/* Line 1787 of yacc.c  */
#line 610 "./CSSGrammar.y"
    { (yyval.keyframeRuleList) = parser->createFloatingKeyframeVector(); }
    break;

  case 105:
/* Line 1787 of yacc.c  */
#line 611 "./CSSGrammar.y"
    {
        (yyval.keyframeRuleList) = (yyvsp[(1) - (3)].keyframeRuleList);
        if ((yyvsp[(2) - (3)].keyframe))
            (yyval.keyframeRuleList)->append((yyvsp[(2) - (3)].keyframe));
    }
    break;

  case 106:
/* Line 1787 of yacc.c  */
#line 618 "./CSSGrammar.y"
    {
        (yyval.keyframe) = parser->createKeyframe((yyvsp[(1) - (6)].valueList));
    }
    break;

  case 107:
/* Line 1787 of yacc.c  */
#line 623 "./CSSGrammar.y"
    {
        (yyval.valueList) = parser->createFloatingValueList();
        (yyval.valueList)->addValue(parser->sinkFloatingValue((yyvsp[(1) - (1)].value)));
    }
    break;

  case 108:
/* Line 1787 of yacc.c  */
#line 627 "./CSSGrammar.y"
    {
        (yyval.valueList) = (yyvsp[(1) - (5)].valueList);
        if ((yyval.valueList))
            (yyval.valueList)->addValue(parser->sinkFloatingValue((yyvsp[(5) - (5)].value)));
    }
    break;

  case 109:
/* Line 1787 of yacc.c  */
#line 634 "./CSSGrammar.y"
    { (yyval.value).id = 0; (yyval.value).isInt = false; (yyval.value).fValue = (yyvsp[(1) - (2)].integer) * (yyvsp[(2) - (2)].number); (yyval.value).unit = CSSPrimitiveValue::CSS_NUMBER; }
    break;

  case 110:
/* Line 1787 of yacc.c  */
#line 635 "./CSSGrammar.y"
    {
        (yyval.value).id = 0; (yyval.value).isInt = false; (yyval.value).unit = CSSPrimitiveValue::CSS_NUMBER;
        CSSParserString& str = (yyvsp[(1) - (1)].string);
        if (str.equalIgnoringCase("from"))
            (yyval.value).fValue = 0;
        else if (str.equalIgnoringCase("to"))
            (yyval.value).fValue = 100;
        else {
            (yyval.value).unit = 0;
            YYERROR;
        }
    }
    break;

  case 111:
/* Line 1787 of yacc.c  */
#line 647 "./CSSGrammar.y"
    {
        (yyval.value).unit = 0;
    }
    break;

  case 112:
/* Line 1787 of yacc.c  */
#line 652 "./CSSGrammar.y"
    {
        parser->markRuleHeaderStart(CSSRuleSourceData::PAGE_RULE);
    }
    break;

  case 113:
/* Line 1787 of yacc.c  */
#line 658 "./CSSGrammar.y"
    {
        if ((yyvsp[(4) - (10)].selector))
            (yyval.rule) = parser->createPageRule(parser->sinkFloatingSelector((yyvsp[(4) - (10)].selector)));
        else {
            parser->clearProperties();
            (yyval.rule) = 0;
            parser->popRuleData();
        }
    }
    break;

  case 114:
/* Line 1787 of yacc.c  */
#line 667 "./CSSGrammar.y"
    {
      parser->popRuleData();
      (yyval.rule) = 0;
    }
    break;

  case 115:
/* Line 1787 of yacc.c  */
#line 671 "./CSSGrammar.y"
    {
      parser->popRuleData();
      (yyval.rule) = 0;
    }
    break;

  case 116:
/* Line 1787 of yacc.c  */
#line 677 "./CSSGrammar.y"
    {
        (yyval.selector) = parser->createFloatingSelectorWithTagName(QualifiedName(nullAtom, (yyvsp[(1) - (1)].string), parser->m_defaultNamespace));
        (yyval.selector)->setForPage();
    }
    break;

  case 117:
/* Line 1787 of yacc.c  */
#line 681 "./CSSGrammar.y"
    {
        (yyval.selector) = (yyvsp[(2) - (2)].selector);
        if ((yyval.selector)) {
            (yyval.selector)->prependTagSelector(QualifiedName(nullAtom, (yyvsp[(1) - (2)].string), parser->m_defaultNamespace));
            (yyval.selector)->setForPage();
        }
    }
    break;

  case 118:
/* Line 1787 of yacc.c  */
#line 688 "./CSSGrammar.y"
    {
        (yyval.selector) = (yyvsp[(1) - (1)].selector);
        if ((yyval.selector))
            (yyval.selector)->setForPage();
    }
    break;

  case 119:
/* Line 1787 of yacc.c  */
#line 693 "./CSSGrammar.y"
    {
        (yyval.selector) = parser->createFloatingSelector();
        (yyval.selector)->setForPage();
    }
    break;

  case 122:
/* Line 1787 of yacc.c  */
#line 703 "./CSSGrammar.y"
    {
        parser->startDeclarationsForMarginBox();
    }
    break;

  case 123:
/* Line 1787 of yacc.c  */
#line 705 "./CSSGrammar.y"
    {
        (yyval.rule) = parser->createMarginAtRule((yyvsp[(1) - (7)].marginBox));
    }
    break;

  case 124:
/* Line 1787 of yacc.c  */
#line 710 "./CSSGrammar.y"
    {
        (yyval.marginBox) = CSSSelector::TopLeftCornerMarginBox;
    }
    break;

  case 125:
/* Line 1787 of yacc.c  */
#line 713 "./CSSGrammar.y"
    {
        (yyval.marginBox) = CSSSelector::TopLeftMarginBox;
    }
    break;

  case 126:
/* Line 1787 of yacc.c  */
#line 716 "./CSSGrammar.y"
    {
        (yyval.marginBox) = CSSSelector::TopCenterMarginBox;
    }
    break;

  case 127:
/* Line 1787 of yacc.c  */
#line 719 "./CSSGrammar.y"
    {
        (yyval.marginBox) = CSSSelector::TopRightMarginBox;
    }
    break;

  case 128:
/* Line 1787 of yacc.c  */
#line 722 "./CSSGrammar.y"
    {
        (yyval.marginBox) = CSSSelector::TopRightCornerMarginBox;
    }
    break;

  case 129:
/* Line 1787 of yacc.c  */
#line 725 "./CSSGrammar.y"
    {
        (yyval.marginBox) = CSSSelector::BottomLeftCornerMarginBox;
    }
    break;

  case 130:
/* Line 1787 of yacc.c  */
#line 728 "./CSSGrammar.y"
    {
        (yyval.marginBox) = CSSSelector::BottomLeftMarginBox;
    }
    break;

  case 131:
/* Line 1787 of yacc.c  */
#line 731 "./CSSGrammar.y"
    {
        (yyval.marginBox) = CSSSelector::BottomCenterMarginBox;
    }
    break;

  case 132:
/* Line 1787 of yacc.c  */
#line 734 "./CSSGrammar.y"
    {
        (yyval.marginBox) = CSSSelector::BottomRightMarginBox;
    }
    break;

  case 133:
/* Line 1787 of yacc.c  */
#line 737 "./CSSGrammar.y"
    {
        (yyval.marginBox) = CSSSelector::BottomRightCornerMarginBox;
    }
    break;

  case 134:
/* Line 1787 of yacc.c  */
#line 740 "./CSSGrammar.y"
    {
        (yyval.marginBox) = CSSSelector::LeftTopMarginBox;
    }
    break;

  case 135:
/* Line 1787 of yacc.c  */
#line 743 "./CSSGrammar.y"
    {
        (yyval.marginBox) = CSSSelector::LeftMiddleMarginBox;
    }
    break;

  case 136:
/* Line 1787 of yacc.c  */
#line 746 "./CSSGrammar.y"
    {
        (yyval.marginBox) = CSSSelector::LeftBottomMarginBox;
    }
    break;

  case 137:
/* Line 1787 of yacc.c  */
#line 749 "./CSSGrammar.y"
    {
        (yyval.marginBox) = CSSSelector::RightTopMarginBox;
    }
    break;

  case 138:
/* Line 1787 of yacc.c  */
#line 752 "./CSSGrammar.y"
    {
        (yyval.marginBox) = CSSSelector::RightMiddleMarginBox;
    }
    break;

  case 139:
/* Line 1787 of yacc.c  */
#line 755 "./CSSGrammar.y"
    {
        (yyval.marginBox) = CSSSelector::RightBottomMarginBox;
    }
    break;

  case 140:
/* Line 1787 of yacc.c  */
#line 760 "./CSSGrammar.y"
    {
        parser->markRuleHeaderStart(CSSRuleSourceData::FONT_FACE_RULE);
    }
    break;

  case 141:
/* Line 1787 of yacc.c  */
#line 766 "./CSSGrammar.y"
    {
        (yyval.rule) = parser->createFontFaceRule();
    }
    break;

  case 142:
/* Line 1787 of yacc.c  */
#line 769 "./CSSGrammar.y"
    {
      (yyval.rule) = 0;
      parser->popRuleData();
    }
    break;

  case 143:
/* Line 1787 of yacc.c  */
#line 773 "./CSSGrammar.y"
    {
      (yyval.rule) = 0;
      parser->popRuleData();
    }
    break;

  case 144:
/* Line 1787 of yacc.c  */
#line 779 "./CSSGrammar.y"
    {
        if ((yyvsp[(1) - (1)].selectorList)) {
            parser->setReusableRegionSelectorVector((yyvsp[(1) - (1)].selectorList));
            (yyval.selectorList) = parser->reusableRegionSelectorVector();
        }
        else
            (yyval.selectorList) = 0;
    }
    break;

  case 145:
/* Line 1787 of yacc.c  */
#line 789 "./CSSGrammar.y"
    {
        parser->markRuleHeaderStart(CSSRuleSourceData::REGION_RULE);
    }
    break;

  case 146:
/* Line 1787 of yacc.c  */
#line 794 "./CSSGrammar.y"
    {
        if ((yyvsp[(4) - (10)].selectorList))
            (yyval.rule) = parser->createRegionRule((yyvsp[(4) - (10)].selectorList), (yyvsp[(9) - (10)].ruleList));
        else {
            (yyval.rule) = 0;
            parser->popRuleData();
        }
    }
    break;

  case 147:
/* Line 1787 of yacc.c  */
#line 804 "./CSSGrammar.y"
    { (yyval.relation) = CSSSelector::DirectAdjacent; }
    break;

  case 148:
/* Line 1787 of yacc.c  */
#line 805 "./CSSGrammar.y"
    { (yyval.relation) = CSSSelector::IndirectAdjacent; }
    break;

  case 149:
/* Line 1787 of yacc.c  */
#line 806 "./CSSGrammar.y"
    { (yyval.relation) = CSSSelector::Child; }
    break;

  case 150:
/* Line 1787 of yacc.c  */
#line 809 "./CSSGrammar.y"
    { (yyval.integer) = (yyvsp[(1) - (1)].integer); }
    break;

  case 151:
/* Line 1787 of yacc.c  */
#line 810 "./CSSGrammar.y"
    { (yyval.integer) = 1; }
    break;

  case 152:
/* Line 1787 of yacc.c  */
#line 813 "./CSSGrammar.y"
    { (yyval.integer) = -1; }
    break;

  case 153:
/* Line 1787 of yacc.c  */
#line 814 "./CSSGrammar.y"
    { (yyval.integer) = 1; }
    break;

  case 154:
/* Line 1787 of yacc.c  */
#line 817 "./CSSGrammar.y"
    {
        parser->markPropertyStart();
    }
    break;

  case 155:
/* Line 1787 of yacc.c  */
#line 822 "./CSSGrammar.y"
    {
        parser->markRuleHeaderStart(CSSRuleSourceData::STYLE_RULE);
        parser->markSelectorStart();
    }
    break;

  case 156:
/* Line 1787 of yacc.c  */
#line 828 "./CSSGrammar.y"
    {
        parser->markRuleHeaderEnd();
    }
    break;

  case 157:
/* Line 1787 of yacc.c  */
#line 833 "./CSSGrammar.y"
    {
        parser->markSelectorEnd();
    }
    break;

  case 158:
/* Line 1787 of yacc.c  */
#line 838 "./CSSGrammar.y"
    {
        (yyval.rule) = parser->createStyleRule((yyvsp[(2) - (9)].selectorList));
    }
    break;

  case 159:
/* Line 1787 of yacc.c  */
#line 843 "./CSSGrammar.y"
    {
        parser->markSelectorStart();
    }
    break;

  case 160:
/* Line 1787 of yacc.c  */
#line 847 "./CSSGrammar.y"
    {
        if ((yyvsp[(1) - (1)].selector)) {
            (yyval.selectorList) = parser->reusableSelectorVector();
            (yyval.selectorList)->shrink(0);
            (yyval.selectorList)->append(parser->sinkFloatingSelector((yyvsp[(1) - (1)].selector)));
            parser->updateLastSelectorLineAndPosition();
        }
    }
    break;

  case 161:
/* Line 1787 of yacc.c  */
#line 855 "./CSSGrammar.y"
    {
        if ((yyvsp[(1) - (6)].selectorList) && (yyvsp[(6) - (6)].selector)) {
            (yyval.selectorList) = (yyvsp[(1) - (6)].selectorList);
            (yyval.selectorList)->append(parser->sinkFloatingSelector((yyvsp[(6) - (6)].selector)));
            parser->updateLastSelectorLineAndPosition();
        } else
            (yyval.selectorList) = 0;
    }
    break;

  case 162:
/* Line 1787 of yacc.c  */
#line 863 "./CSSGrammar.y"
    {
        (yyval.selectorList) = 0;
    }
    break;

  case 163:
/* Line 1787 of yacc.c  */
#line 868 "./CSSGrammar.y"
    {
        (yyval.selector) = (yyvsp[(1) - (2)].selector);
    }
    break;

  case 164:
/* Line 1787 of yacc.c  */
#line 873 "./CSSGrammar.y"
    {
        (yyval.selector) = (yyvsp[(1) - (1)].selector);
    }
    break;

  case 165:
/* Line 1787 of yacc.c  */
#line 877 "./CSSGrammar.y"
    {
        (yyval.selector) = (yyvsp[(1) - (1)].selector);
    }
    break;

  case 166:
/* Line 1787 of yacc.c  */
#line 881 "./CSSGrammar.y"
    {
        (yyval.selector) = (yyvsp[(2) - (2)].selector);
        if (!(yyvsp[(1) - (2)].selector))
            (yyval.selector) = 0;
        else if ((yyval.selector))
            (yyval.selector)->appendTagHistory(CSSSelector::Descendant, parser->sinkFloatingSelector((yyvsp[(1) - (2)].selector)));
    }
    break;

  case 167:
/* Line 1787 of yacc.c  */
#line 888 "./CSSGrammar.y"
    {
        (yyval.selector) = (yyvsp[(3) - (3)].selector);
        if (!(yyvsp[(1) - (3)].selector))
            (yyval.selector) = 0;
        else if ((yyval.selector))
            (yyval.selector)->appendTagHistory((yyvsp[(2) - (3)].relation), parser->sinkFloatingSelector((yyvsp[(1) - (3)].selector)));
    }
    break;

  case 168:
/* Line 1787 of yacc.c  */
#line 895 "./CSSGrammar.y"
    {
        (yyval.selector) = 0;
    }
    break;

  case 169:
/* Line 1787 of yacc.c  */
#line 900 "./CSSGrammar.y"
    { (yyval.string).clear(); }
    break;

  case 170:
/* Line 1787 of yacc.c  */
#line 901 "./CSSGrammar.y"
    { static LChar star = '*'; (yyval.string).init(&star, 1); }
    break;

  case 171:
/* Line 1787 of yacc.c  */
#line 902 "./CSSGrammar.y"
    { (yyval.string) = (yyvsp[(1) - (2)].string); }
    break;

  case 172:
/* Line 1787 of yacc.c  */
#line 905 "./CSSGrammar.y"
    {
        (yyval.selector) = parser->createFloatingSelectorWithTagName(QualifiedName(nullAtom, (yyvsp[(1) - (1)].string), parser->m_defaultNamespace));
    }
    break;

  case 173:
/* Line 1787 of yacc.c  */
#line 908 "./CSSGrammar.y"
    {
        (yyval.selector) = (yyvsp[(2) - (2)].selector);
        if ((yyval.selector))
            (yyval.selector) = parser->rewriteSpecifiersWithElementName(nullAtom, (yyvsp[(1) - (2)].string), (yyval.selector));
    }
    break;

  case 174:
/* Line 1787 of yacc.c  */
#line 913 "./CSSGrammar.y"
    {
        (yyval.selector) = (yyvsp[(1) - (1)].selector);
        if ((yyval.selector))
            (yyval.selector) = parser->rewriteSpecifiersWithNamespaceIfNeeded((yyval.selector));
    }
    break;

  case 175:
/* Line 1787 of yacc.c  */
#line 918 "./CSSGrammar.y"
    {
        (yyval.selector) = parser->createFloatingSelectorWithTagName(parser->determineNameInNamespace((yyvsp[(1) - (2)].string), (yyvsp[(2) - (2)].string)));
    }
    break;

  case 176:
/* Line 1787 of yacc.c  */
#line 921 "./CSSGrammar.y"
    {
        (yyval.selector) = (yyvsp[(3) - (3)].selector);
        if ((yyval.selector))
            (yyval.selector) = parser->rewriteSpecifiersWithElementName((yyvsp[(1) - (3)].string), (yyvsp[(2) - (3)].string), (yyval.selector));
    }
    break;

  case 177:
/* Line 1787 of yacc.c  */
#line 926 "./CSSGrammar.y"
    {
        (yyval.selector) = (yyvsp[(2) - (2)].selector);
        if ((yyval.selector))
            (yyval.selector) = parser->rewriteSpecifiersWithElementName((yyvsp[(1) - (2)].string), starAtom, (yyval.selector));
    }
    break;

  case 178:
/* Line 1787 of yacc.c  */
#line 933 "./CSSGrammar.y"
    {
        if ((yyvsp[(1) - (1)].selector)) {
            (yyval.selectorList) = parser->createFloatingSelectorVector();
            (yyval.selectorList)->append(parser->sinkFloatingSelector((yyvsp[(1) - (1)].selector)));
        } else
            (yyval.selectorList) = 0;
    }
    break;

  case 179:
/* Line 1787 of yacc.c  */
#line 940 "./CSSGrammar.y"
    {
        if ((yyvsp[(1) - (5)].selectorList) && (yyvsp[(5) - (5)].selector)) {
            (yyval.selectorList) = (yyvsp[(1) - (5)].selectorList);
            (yyval.selectorList)->append(parser->sinkFloatingSelector((yyvsp[(5) - (5)].selector)));
        } else
            (yyval.selectorList) = 0;
    }
    break;

  case 180:
/* Line 1787 of yacc.c  */
#line 947 "./CSSGrammar.y"
    {
        (yyval.selectorList) = 0;
    }
    break;

  case 181:
/* Line 1787 of yacc.c  */
#line 952 "./CSSGrammar.y"
    {
        CSSParserString& str = (yyvsp[(1) - (1)].string);
        if (parser->m_context.isHTMLDocument)
            str.lower();
        (yyval.string) = str;
    }
    break;

  case 182:
/* Line 1787 of yacc.c  */
#line 958 "./CSSGrammar.y"
    {
        static LChar star = '*';
        (yyval.string).init(&star, 1);
    }
    break;

  case 183:
/* Line 1787 of yacc.c  */
#line 964 "./CSSGrammar.y"
    {
        (yyval.selector) = (yyvsp[(1) - (1)].selector);
    }
    break;

  case 184:
/* Line 1787 of yacc.c  */
#line 967 "./CSSGrammar.y"
    {
        if (!(yyvsp[(2) - (2)].selector))
            (yyval.selector) = 0;
        else if ((yyvsp[(1) - (2)].selector))
            (yyval.selector) = parser->rewriteSpecifiers((yyvsp[(1) - (2)].selector), (yyvsp[(2) - (2)].selector));
    }
    break;

  case 185:
/* Line 1787 of yacc.c  */
#line 973 "./CSSGrammar.y"
    {
        (yyval.selector) = 0;
    }
    break;

  case 186:
/* Line 1787 of yacc.c  */
#line 978 "./CSSGrammar.y"
    {
        (yyval.selector) = parser->createFloatingSelector();
        (yyval.selector)->setMatch(CSSSelector::Id);
        if (parser->m_context.mode == CSSQuirksMode)
            (yyvsp[(1) - (1)].string).lower();
        (yyval.selector)->setValue((yyvsp[(1) - (1)].string));
    }
    break;

  case 187:
/* Line 1787 of yacc.c  */
#line 985 "./CSSGrammar.y"
    {
        if ((yyvsp[(1) - (1)].string)[0] >= '0' && (yyvsp[(1) - (1)].string)[0] <= '9') {
            (yyval.selector) = 0;
        } else {
            (yyval.selector) = parser->createFloatingSelector();
            (yyval.selector)->setMatch(CSSSelector::Id);
            if (parser->m_context.mode == CSSQuirksMode)
                (yyvsp[(1) - (1)].string).lower();
            (yyval.selector)->setValue((yyvsp[(1) - (1)].string));
        }
    }
    break;

  case 191:
/* Line 1787 of yacc.c  */
#line 1001 "./CSSGrammar.y"
    {
        (yyval.selector) = parser->createFloatingSelector();
        (yyval.selector)->setMatch(CSSSelector::Class);
        if (parser->m_context.mode == CSSQuirksMode)
            (yyvsp[(2) - (2)].string).lower();
        (yyval.selector)->setValue((yyvsp[(2) - (2)].string));
    }
    break;

  case 192:
/* Line 1787 of yacc.c  */
#line 1010 "./CSSGrammar.y"
    {
        CSSParserString& str = (yyvsp[(1) - (2)].string);
        if (parser->m_context.isHTMLDocument)
            str.lower();
        (yyval.string) = str;
    }
    break;

  case 193:
/* Line 1787 of yacc.c  */
#line 1018 "./CSSGrammar.y"
    {
        (yyval.selector) = parser->createFloatingSelector();
        (yyval.selector)->setAttribute(QualifiedName(nullAtom, (yyvsp[(3) - (4)].string), nullAtom));
        (yyval.selector)->setMatch(CSSSelector::Set);
    }
    break;

  case 194:
/* Line 1787 of yacc.c  */
#line 1023 "./CSSGrammar.y"
    {
        (yyval.selector) = parser->createFloatingSelector();
        (yyval.selector)->setAttribute(QualifiedName(nullAtom, (yyvsp[(3) - (8)].string), nullAtom));
        (yyval.selector)->setMatch((CSSSelector::Match)(yyvsp[(4) - (8)].integer));
        (yyval.selector)->setValue((yyvsp[(6) - (8)].string));
    }
    break;

  case 195:
/* Line 1787 of yacc.c  */
#line 1029 "./CSSGrammar.y"
    {
        (yyval.selector) = parser->createFloatingSelector();
        (yyval.selector)->setAttribute(parser->determineNameInNamespace((yyvsp[(3) - (5)].string), (yyvsp[(4) - (5)].string)));
        (yyval.selector)->setMatch(CSSSelector::Set);
    }
    break;

  case 196:
/* Line 1787 of yacc.c  */
#line 1034 "./CSSGrammar.y"
    {
        (yyval.selector) = parser->createFloatingSelector();
        (yyval.selector)->setAttribute(parser->determineNameInNamespace((yyvsp[(3) - (9)].string), (yyvsp[(4) - (9)].string)));
        (yyval.selector)->setMatch((CSSSelector::Match)(yyvsp[(5) - (9)].integer));
        (yyval.selector)->setValue((yyvsp[(7) - (9)].string));
    }
    break;

  case 197:
/* Line 1787 of yacc.c  */
#line 1042 "./CSSGrammar.y"
    {
        (yyval.integer) = CSSSelector::Exact;
    }
    break;

  case 198:
/* Line 1787 of yacc.c  */
#line 1045 "./CSSGrammar.y"
    {
        (yyval.integer) = CSSSelector::List;
    }
    break;

  case 199:
/* Line 1787 of yacc.c  */
#line 1048 "./CSSGrammar.y"
    {
        (yyval.integer) = CSSSelector::Hyphen;
    }
    break;

  case 200:
/* Line 1787 of yacc.c  */
#line 1051 "./CSSGrammar.y"
    {
        (yyval.integer) = CSSSelector::Begin;
    }
    break;

  case 201:
/* Line 1787 of yacc.c  */
#line 1054 "./CSSGrammar.y"
    {
        (yyval.integer) = CSSSelector::End;
    }
    break;

  case 202:
/* Line 1787 of yacc.c  */
#line 1057 "./CSSGrammar.y"
    {
        (yyval.integer) = CSSSelector::Contain;
    }
    break;

  case 205:
/* Line 1787 of yacc.c  */
#line 1066 "./CSSGrammar.y"
    {
        (yyval.selector) = parser->createFloatingSelector();
        (yyval.selector)->setMatch(CSSSelector::PagePseudoClass);
        (yyvsp[(2) - (2)].string).lower();
        (yyval.selector)->setValue((yyvsp[(2) - (2)].string));
        CSSSelector::PseudoType type = (yyval.selector)->pseudoType();
        if (type == CSSSelector::PseudoUnknown)
            (yyval.selector) = 0;
    }
    break;

  case 206:
/* Line 1787 of yacc.c  */
#line 1076 "./CSSGrammar.y"
    {
        (yyval.selector) = parser->createFloatingSelector();
        (yyval.selector)->setMatch(CSSSelector::PseudoClass);
        (yyvsp[(2) - (2)].string).lower();
        (yyval.selector)->setValue((yyvsp[(2) - (2)].string));
        CSSSelector::PseudoType type = (yyval.selector)->pseudoType();
        if (type == CSSSelector::PseudoUnknown)
            (yyval.selector) = 0;
    }
    break;

  case 207:
/* Line 1787 of yacc.c  */
#line 1085 "./CSSGrammar.y"
    {
        (yyval.selector) = parser->createFloatingSelector();
        (yyval.selector)->setMatch(CSSSelector::PseudoElement);
        (yyvsp[(3) - (3)].string).lower();
        (yyval.selector)->setValue((yyvsp[(3) - (3)].string));
        CSSSelector::PseudoType type = (yyval.selector)->pseudoType();
        if (type == CSSSelector::PseudoUnknown)
            (yyval.selector) = 0;
    }
    break;

  case 208:
/* Line 1787 of yacc.c  */
#line 1094 "./CSSGrammar.y"
    {
        if ((yyvsp[(5) - (7)].selectorList)) {
            (yyval.selector) = parser->createFloatingSelector();
            (yyval.selector)->setMatch(CSSSelector::PseudoClass);
            (yyval.selector)->adoptSelectorVector(*parser->sinkFloatingSelectorVector((yyvsp[(5) - (7)].selectorList)));
            (yyval.selector)->setValue((yyvsp[(3) - (7)].string));
            CSSSelector::PseudoType type = (yyval.selector)->pseudoType();
            if (type != CSSSelector::PseudoCue)
                (yyval.selector) = 0;
        } else
            (yyval.selector) = 0;
    }
    break;

  case 209:
/* Line 1787 of yacc.c  */
#line 1106 "./CSSGrammar.y"
    {
        if ((yyvsp[(4) - (6)].selectorList)) {
            (yyval.selector) = parser->createFloatingSelector();
            (yyval.selector)->setMatch(CSSSelector::PseudoClass);
            (yyval.selector)->adoptSelectorVector(*parser->sinkFloatingSelectorVector((yyvsp[(4) - (6)].selectorList)));
            (yyvsp[(2) - (6)].string).lower();
            (yyval.selector)->setValue((yyvsp[(2) - (6)].string));
            CSSSelector::PseudoType type = (yyval.selector)->pseudoType();
            if (type != CSSSelector::PseudoAny)
                (yyval.selector) = 0;
        } else
            (yyval.selector) = 0;
    }
    break;

  case 210:
/* Line 1787 of yacc.c  */
#line 1119 "./CSSGrammar.y"
    {
        (yyval.selector) = parser->createFloatingSelector();
        (yyval.selector)->setMatch(CSSSelector::PseudoClass);
        (yyval.selector)->setArgument((yyvsp[(4) - (6)].string));
        (yyval.selector)->setValue((yyvsp[(2) - (6)].string));
        CSSSelector::PseudoType type = (yyval.selector)->pseudoType();
        if (type == CSSSelector::PseudoUnknown)
            (yyval.selector) = 0;
    }
    break;

  case 211:
/* Line 1787 of yacc.c  */
#line 1128 "./CSSGrammar.y"
    {
        (yyval.selector) = parser->createFloatingSelector();
        (yyval.selector)->setMatch(CSSSelector::PseudoClass);
        (yyval.selector)->setArgument(String::number((yyvsp[(4) - (7)].integer) * (yyvsp[(5) - (7)].number)));
        (yyval.selector)->setValue((yyvsp[(2) - (7)].string));
        CSSSelector::PseudoType type = (yyval.selector)->pseudoType();
        if (type == CSSSelector::PseudoUnknown)
            (yyval.selector) = 0;
    }
    break;

  case 212:
/* Line 1787 of yacc.c  */
#line 1137 "./CSSGrammar.y"
    {
        (yyval.selector) = parser->createFloatingSelector();
        (yyval.selector)->setMatch(CSSSelector::PseudoClass);
        (yyval.selector)->setArgument((yyvsp[(4) - (6)].string));
        (yyvsp[(2) - (6)].string).lower();
        (yyval.selector)->setValue((yyvsp[(2) - (6)].string));
        CSSSelector::PseudoType type = (yyval.selector)->pseudoType();
        if (type == CSSSelector::PseudoUnknown)
            (yyval.selector) = 0;
        else if (type == CSSSelector::PseudoNthChild ||
                 type == CSSSelector::PseudoNthOfType ||
                 type == CSSSelector::PseudoNthLastChild ||
                 type == CSSSelector::PseudoNthLastOfType) {
            if (!isValidNthToken((yyvsp[(4) - (6)].string)))
                (yyval.selector) = 0;
        }
    }
    break;

  case 213:
/* Line 1787 of yacc.c  */
#line 1154 "./CSSGrammar.y"
    {
        if (!(yyvsp[(4) - (6)].selector) || !(yyvsp[(4) - (6)].selector)->isSimple())
            (yyval.selector) = 0;
        else {
            (yyval.selector) = parser->createFloatingSelector();
            (yyval.selector)->setMatch(CSSSelector::PseudoClass);
            Vector<OwnPtr<CSSParserSelector> > selectorVector;
            selectorVector.append(parser->sinkFloatingSelector((yyvsp[(4) - (6)].selector)));
            (yyval.selector)->adoptSelectorVector(selectorVector);
            (yyvsp[(2) - (6)].string).lower();
            (yyval.selector)->setValue((yyvsp[(2) - (6)].string));
        }
    }
    break;

  case 214:
/* Line 1787 of yacc.c  */
#line 1169 "./CSSGrammar.y"
    { (yyval.boolean) = false; }
    break;

  case 215:
/* Line 1787 of yacc.c  */
#line 1170 "./CSSGrammar.y"
    {
        (yyval.boolean) = (yyvsp[(1) - (1)].boolean);
    }
    break;

  case 216:
/* Line 1787 of yacc.c  */
#line 1173 "./CSSGrammar.y"
    {
        (yyval.boolean) = (yyvsp[(1) - (2)].boolean);
        if ( (yyvsp[(2) - (2)].boolean) )
            (yyval.boolean) = (yyvsp[(2) - (2)].boolean);
    }
    break;

  case 217:
/* Line 1787 of yacc.c  */
#line 1178 "./CSSGrammar.y"
    {
        (yyval.boolean) = (yyvsp[(1) - (1)].boolean);
    }
    break;

  case 218:
/* Line 1787 of yacc.c  */
#line 1181 "./CSSGrammar.y"
    {
        (yyval.boolean) = false;
    }
    break;

  case 219:
/* Line 1787 of yacc.c  */
#line 1184 "./CSSGrammar.y"
    {
        (yyval.boolean) = (yyvsp[(1) - (2)].boolean);
    }
    break;

  case 220:
/* Line 1787 of yacc.c  */
#line 1189 "./CSSGrammar.y"
    {
        parser->markPropertyStart();
        (yyval.boolean) = (yyvsp[(1) - (3)].boolean);
    }
    break;

  case 221:
/* Line 1787 of yacc.c  */
#line 1193 "./CSSGrammar.y"
    {
        parser->markPropertyStart();
        (yyval.boolean) = false;
    }
    break;

  case 222:
/* Line 1787 of yacc.c  */
#line 1197 "./CSSGrammar.y"
    {
        parser->markPropertyStart();
        (yyval.boolean) = (yyvsp[(1) - (4)].boolean);
        if ((yyvsp[(2) - (4)].boolean))
            (yyval.boolean) = (yyvsp[(2) - (4)].boolean);
    }
    break;

  case 223:
/* Line 1787 of yacc.c  */
#line 1203 "./CSSGrammar.y"
    {
        parser->markPropertyStart();
        (yyval.boolean) = (yyvsp[(1) - (4)].boolean);
    }
    break;

  case 224:
/* Line 1787 of yacc.c  */
#line 1209 "./CSSGrammar.y"
    {
        parser->syntaxError((yyvsp[(2) - (3)].location), CSSParser::PropertyDeclarationError);
    }
    break;

  case 225:
/* Line 1787 of yacc.c  */
#line 1214 "./CSSGrammar.y"
    {
        (yyval.boolean) = false;
    }
    break;

  case 226:
/* Line 1787 of yacc.c  */
#line 1218 "./CSSGrammar.y"
    {
        (yyval.boolean) = false;
        bool isPropertyParsed = false;
        if ((yyvsp[(1) - (5)].id) && (yyvsp[(4) - (5)].valueList)) {
            parser->m_valueList = parser->sinkFloatingValueList((yyvsp[(4) - (5)].valueList));
            int oldParsedProperties = parser->m_parsedProperties.size();
            (yyval.boolean) = parser->parseValue(static_cast<CSSPropertyID>((yyvsp[(1) - (5)].id)), (yyvsp[(5) - (5)].boolean));
            if (!(yyval.boolean))
                parser->rollbackLastProperties(parser->m_parsedProperties.size() - oldParsedProperties);
            else
                isPropertyParsed = true;
            parser->m_valueList = nullptr;
        }
        parser->markPropertyEnd((yyvsp[(5) - (5)].boolean), isPropertyParsed);
    }
    break;

  case 227:
/* Line 1787 of yacc.c  */
#line 1234 "./CSSGrammar.y"
    {
        (yyval.boolean) = false;
    }
    break;

  case 228:
/* Line 1787 of yacc.c  */
#line 1238 "./CSSGrammar.y"
    {
        parser->markPropertyEnd(false, false);
        (yyval.boolean) = false;
    }
    break;

  case 229:
/* Line 1787 of yacc.c  */
#line 1243 "./CSSGrammar.y"
    {
        (yyval.boolean) = false;
    }
    break;

  case 230:
/* Line 1787 of yacc.c  */
#line 1247 "./CSSGrammar.y"
    {
        parser->markPropertyEnd(false, false);
        (yyval.boolean) = false;
    }
    break;

  case 231:
/* Line 1787 of yacc.c  */
#line 1253 "./CSSGrammar.y"
    {
        parser->syntaxError((yyvsp[(2) - (3)].location));
    }
    break;

  case 232:
/* Line 1787 of yacc.c  */
#line 1258 "./CSSGrammar.y"
    {
        (yyval.id) = cssPropertyID((yyvsp[(1) - (2)].string));
    }
    break;

  case 233:
/* Line 1787 of yacc.c  */
#line 1263 "./CSSGrammar.y"
    { (yyval.boolean) = true; }
    break;

  case 234:
/* Line 1787 of yacc.c  */
#line 1264 "./CSSGrammar.y"
    { (yyval.boolean) = false; }
    break;

  case 235:
/* Line 1787 of yacc.c  */
#line 1267 "./CSSGrammar.y"
    {
        (yyval.valueList) = parser->createFloatingValueList();
        (yyval.valueList)->addValue(parser->sinkFloatingValue((yyvsp[(1) - (1)].value)));
    }
    break;

  case 236:
/* Line 1787 of yacc.c  */
#line 1271 "./CSSGrammar.y"
    {
        (yyval.valueList) = (yyvsp[(1) - (3)].valueList);
        if ((yyval.valueList)) {
            if ((yyvsp[(2) - (3)].character)) {
                CSSParserValue v;
                v.id = 0;
                v.unit = CSSParserValue::Operator;
                v.iValue = (yyvsp[(2) - (3)].character);
                (yyval.valueList)->addValue(v);
            }
            (yyval.valueList)->addValue(parser->sinkFloatingValue((yyvsp[(3) - (3)].value)));
        }
    }
    break;

  case 237:
/* Line 1787 of yacc.c  */
#line 1284 "./CSSGrammar.y"
    {
        (yyval.valueList) = 0;
    }
    break;

  case 239:
/* Line 1787 of yacc.c  */
#line 1292 "./CSSGrammar.y"
    {
        (yyval.character) = '/';
    }
    break;

  case 240:
/* Line 1787 of yacc.c  */
#line 1295 "./CSSGrammar.y"
    {
        (yyval.character) = ',';
    }
    break;

  case 241:
/* Line 1787 of yacc.c  */
#line 1298 "./CSSGrammar.y"
    {
        (yyval.character) = 0;
  }
    break;

  case 242:
/* Line 1787 of yacc.c  */
#line 1303 "./CSSGrammar.y"
    { (yyval.value) = (yyvsp[(1) - (2)].value); }
    break;

  case 243:
/* Line 1787 of yacc.c  */
#line 1304 "./CSSGrammar.y"
    { (yyval.value) = (yyvsp[(2) - (3)].value); (yyval.value).fValue *= (yyvsp[(1) - (3)].integer); }
    break;

  case 244:
/* Line 1787 of yacc.c  */
#line 1305 "./CSSGrammar.y"
    { (yyval.value).id = 0; (yyval.value).string = (yyvsp[(1) - (2)].string); (yyval.value).unit = CSSPrimitiveValue::CSS_STRING; }
    break;

  case 245:
/* Line 1787 of yacc.c  */
#line 1306 "./CSSGrammar.y"
    {
      (yyval.value).id = cssValueKeywordID((yyvsp[(1) - (2)].string));
      (yyval.value).unit = CSSPrimitiveValue::CSS_IDENT;
      (yyval.value).string = (yyvsp[(1) - (2)].string);
  }
    break;

  case 246:
/* Line 1787 of yacc.c  */
#line 1311 "./CSSGrammar.y"
    { (yyval.value).id = 0; (yyval.value).string = (yyvsp[(1) - (2)].string); (yyval.value).unit = CSSPrimitiveValue::CSS_DIMENSION; }
    break;

  case 247:
/* Line 1787 of yacc.c  */
#line 1312 "./CSSGrammar.y"
    { (yyval.value).id = 0; (yyval.value).string = (yyvsp[(2) - (3)].string); (yyval.value).unit = CSSPrimitiveValue::CSS_DIMENSION; }
    break;

  case 248:
/* Line 1787 of yacc.c  */
#line 1313 "./CSSGrammar.y"
    { (yyval.value).id = 0; (yyval.value).string = (yyvsp[(1) - (2)].string); (yyval.value).unit = CSSPrimitiveValue::CSS_URI; }
    break;

  case 249:
/* Line 1787 of yacc.c  */
#line 1314 "./CSSGrammar.y"
    { (yyval.value).id = 0; (yyval.value).string = (yyvsp[(1) - (2)].string); (yyval.value).unit = CSSPrimitiveValue::CSS_UNICODE_RANGE; }
    break;

  case 250:
/* Line 1787 of yacc.c  */
#line 1315 "./CSSGrammar.y"
    { (yyval.value).id = 0; (yyval.value).string = (yyvsp[(1) - (2)].string); (yyval.value).unit = CSSPrimitiveValue::CSS_PARSER_HEXCOLOR; }
    break;

  case 251:
/* Line 1787 of yacc.c  */
#line 1316 "./CSSGrammar.y"
    { (yyval.value).id = 0; (yyval.value).string = CSSParserString(); (yyval.value).unit = CSSPrimitiveValue::CSS_PARSER_HEXCOLOR; }
    break;

  case 252:
/* Line 1787 of yacc.c  */
#line 1317 "./CSSGrammar.y"
    {
  }
    break;

  case 253:
/* Line 1787 of yacc.c  */
#line 1319 "./CSSGrammar.y"
    {
      (yyval.value) = (yyvsp[(1) - (2)].value);
  }
    break;

  case 254:
/* Line 1787 of yacc.c  */
#line 1322 "./CSSGrammar.y"
    {
      (yyval.value) = (yyvsp[(1) - (2)].value);
  }
    break;

  case 255:
/* Line 1787 of yacc.c  */
#line 1325 "./CSSGrammar.y"
    {
      (yyval.value) = (yyvsp[(1) - (2)].value);
  }
    break;

  case 256:
/* Line 1787 of yacc.c  */
#line 1328 "./CSSGrammar.y"
    {
      (yyval.value).id = 0; (yyval.value).unit = 0;
  }
    break;

  case 257:
/* Line 1787 of yacc.c  */
#line 1333 "./CSSGrammar.y"
    { (yyval.value).id = 0; (yyval.value).isInt = true; (yyval.value).fValue = (yyvsp[(1) - (1)].number); (yyval.value).unit = CSSPrimitiveValue::CSS_NUMBER; }
    break;

  case 258:
/* Line 1787 of yacc.c  */
#line 1334 "./CSSGrammar.y"
    { (yyval.value).id = 0; (yyval.value).isInt = false; (yyval.value).fValue = (yyvsp[(1) - (1)].number); (yyval.value).unit = CSSPrimitiveValue::CSS_NUMBER; }
    break;

  case 259:
/* Line 1787 of yacc.c  */
#line 1335 "./CSSGrammar.y"
    { (yyval.value).id = 0; (yyval.value).fValue = (yyvsp[(1) - (1)].number); (yyval.value).unit = CSSPrimitiveValue::CSS_PERCENTAGE; }
    break;

  case 260:
/* Line 1787 of yacc.c  */
#line 1336 "./CSSGrammar.y"
    { (yyval.value).id = 0; (yyval.value).fValue = (yyvsp[(1) - (1)].number); (yyval.value).unit = CSSPrimitiveValue::CSS_PX; }
    break;

  case 261:
/* Line 1787 of yacc.c  */
#line 1337 "./CSSGrammar.y"
    { (yyval.value).id = 0; (yyval.value).fValue = (yyvsp[(1) - (1)].number); (yyval.value).unit = CSSPrimitiveValue::CSS_CM; }
    break;

  case 262:
/* Line 1787 of yacc.c  */
#line 1338 "./CSSGrammar.y"
    { (yyval.value).id = 0; (yyval.value).fValue = (yyvsp[(1) - (1)].number); (yyval.value).unit = CSSPrimitiveValue::CSS_MM; }
    break;

  case 263:
/* Line 1787 of yacc.c  */
#line 1339 "./CSSGrammar.y"
    { (yyval.value).id = 0; (yyval.value).fValue = (yyvsp[(1) - (1)].number); (yyval.value).unit = CSSPrimitiveValue::CSS_IN; }
    break;

  case 264:
/* Line 1787 of yacc.c  */
#line 1340 "./CSSGrammar.y"
    { (yyval.value).id = 0; (yyval.value).fValue = (yyvsp[(1) - (1)].number); (yyval.value).unit = CSSPrimitiveValue::CSS_PT; }
    break;

  case 265:
/* Line 1787 of yacc.c  */
#line 1341 "./CSSGrammar.y"
    { (yyval.value).id = 0; (yyval.value).fValue = (yyvsp[(1) - (1)].number); (yyval.value).unit = CSSPrimitiveValue::CSS_PC; }
    break;

  case 266:
/* Line 1787 of yacc.c  */
#line 1342 "./CSSGrammar.y"
    { (yyval.value).id = 0; (yyval.value).fValue = (yyvsp[(1) - (1)].number); (yyval.value).unit = CSSPrimitiveValue::CSS_DEG; }
    break;

  case 267:
/* Line 1787 of yacc.c  */
#line 1343 "./CSSGrammar.y"
    { (yyval.value).id = 0; (yyval.value).fValue = (yyvsp[(1) - (1)].number); (yyval.value).unit = CSSPrimitiveValue::CSS_RAD; }
    break;

  case 268:
/* Line 1787 of yacc.c  */
#line 1344 "./CSSGrammar.y"
    { (yyval.value).id = 0; (yyval.value).fValue = (yyvsp[(1) - (1)].number); (yyval.value).unit = CSSPrimitiveValue::CSS_GRAD; }
    break;

  case 269:
/* Line 1787 of yacc.c  */
#line 1345 "./CSSGrammar.y"
    { (yyval.value).id = 0; (yyval.value).fValue = (yyvsp[(1) - (1)].number); (yyval.value).unit = CSSPrimitiveValue::CSS_TURN; }
    break;

  case 270:
/* Line 1787 of yacc.c  */
#line 1346 "./CSSGrammar.y"
    { (yyval.value).id = 0; (yyval.value).fValue = (yyvsp[(1) - (1)].number); (yyval.value).unit = CSSPrimitiveValue::CSS_MS; }
    break;

  case 271:
/* Line 1787 of yacc.c  */
#line 1347 "./CSSGrammar.y"
    { (yyval.value).id = 0; (yyval.value).fValue = (yyvsp[(1) - (1)].number); (yyval.value).unit = CSSPrimitiveValue::CSS_S; }
    break;

  case 272:
/* Line 1787 of yacc.c  */
#line 1348 "./CSSGrammar.y"
    { (yyval.value).id = 0; (yyval.value).fValue = (yyvsp[(1) - (1)].number); (yyval.value).unit = CSSPrimitiveValue::CSS_HZ; }
    break;

  case 273:
/* Line 1787 of yacc.c  */
#line 1349 "./CSSGrammar.y"
    { (yyval.value).id = 0; (yyval.value).fValue = (yyvsp[(1) - (1)].number); (yyval.value).unit = CSSPrimitiveValue::CSS_KHZ; }
    break;

  case 274:
/* Line 1787 of yacc.c  */
#line 1350 "./CSSGrammar.y"
    { (yyval.value).id = 0; (yyval.value).fValue = (yyvsp[(1) - (1)].number); (yyval.value).unit = CSSPrimitiveValue::CSS_EMS; }
    break;

  case 275:
/* Line 1787 of yacc.c  */
#line 1351 "./CSSGrammar.y"
    { (yyval.value).id = 0; (yyval.value).fValue = (yyvsp[(1) - (1)].number); (yyval.value).unit = CSSParserValue::Q_EMS; }
    break;

  case 276:
/* Line 1787 of yacc.c  */
#line 1352 "./CSSGrammar.y"
    { (yyval.value).id = 0; (yyval.value).fValue = (yyvsp[(1) - (1)].number); (yyval.value).unit = CSSPrimitiveValue::CSS_EXS; }
    break;

  case 277:
/* Line 1787 of yacc.c  */
#line 1353 "./CSSGrammar.y"
    {
      (yyval.value).id = 0;
      (yyval.value).fValue = (yyvsp[(1) - (1)].number);
      (yyval.value).unit = CSSPrimitiveValue::CSS_REMS;
      if (parser->m_styleSheet)
          parser->m_styleSheet->parserSetUsesRemUnits(true);
  }
    break;

  case 278:
/* Line 1787 of yacc.c  */
#line 1360 "./CSSGrammar.y"
    { (yyval.value).id = 0; (yyval.value).fValue = (yyvsp[(1) - (1)].number); (yyval.value).unit = CSSPrimitiveValue::CSS_CHS; }
    break;

  case 279:
/* Line 1787 of yacc.c  */
#line 1361 "./CSSGrammar.y"
    { (yyval.value).id = 0; (yyval.value).fValue = (yyvsp[(1) - (1)].number); (yyval.value).unit = CSSPrimitiveValue::CSS_VW; }
    break;

  case 280:
/* Line 1787 of yacc.c  */
#line 1362 "./CSSGrammar.y"
    { (yyval.value).id = 0; (yyval.value).fValue = (yyvsp[(1) - (1)].number); (yyval.value).unit = CSSPrimitiveValue::CSS_VH; }
    break;

  case 281:
/* Line 1787 of yacc.c  */
#line 1363 "./CSSGrammar.y"
    { (yyval.value).id = 0; (yyval.value).fValue = (yyvsp[(1) - (1)].number); (yyval.value).unit = CSSPrimitiveValue::CSS_VMIN; }
    break;

  case 282:
/* Line 1787 of yacc.c  */
#line 1364 "./CSSGrammar.y"
    { (yyval.value).id = 0; (yyval.value).fValue = (yyvsp[(1) - (1)].number); (yyval.value).unit = CSSPrimitiveValue::CSS_VMAX; }
    break;

  case 283:
/* Line 1787 of yacc.c  */
#line 1365 "./CSSGrammar.y"
    { (yyval.value).id = 0; (yyval.value).fValue = (yyvsp[(1) - (1)].number); (yyval.value).unit = CSSPrimitiveValue::CSS_DPPX; }
    break;

  case 284:
/* Line 1787 of yacc.c  */
#line 1366 "./CSSGrammar.y"
    { (yyval.value).id = 0; (yyval.value).fValue = (yyvsp[(1) - (1)].number); (yyval.value).unit = CSSPrimitiveValue::CSS_DPI; }
    break;

  case 285:
/* Line 1787 of yacc.c  */
#line 1367 "./CSSGrammar.y"
    { (yyval.value).id = 0; (yyval.value).fValue = (yyvsp[(1) - (1)].number); (yyval.value).unit = CSSPrimitiveValue::CSS_DPCM; }
    break;

  case 286:
/* Line 1787 of yacc.c  */
#line 1370 "./CSSGrammar.y"
    {
        CSSParserFunction* f = parser->createFloatingFunction();
        f->name = (yyvsp[(1) - (4)].string);
        f->args = parser->sinkFloatingValueList((yyvsp[(3) - (4)].valueList));
        (yyval.value).id = 0;
        (yyval.value).unit = CSSParserValue::Function;
        (yyval.value).function = f;
    }
    break;

  case 287:
/* Line 1787 of yacc.c  */
#line 1378 "./CSSGrammar.y"
    {
        CSSParserFunction* f = parser->createFloatingFunction();
        f->name = (yyvsp[(1) - (3)].string);
        CSSParserValueList* valueList = parser->createFloatingValueList();
        f->args = parser->sinkFloatingValueList(valueList);
        (yyval.value).id = 0;
        (yyval.value).unit = CSSParserValue::Function;
        (yyval.value).function = f;
    }
    break;

  case 288:
/* Line 1787 of yacc.c  */
#line 1387 "./CSSGrammar.y"
    {
        CSSParserFunction* f = parser->createFloatingFunction();
        f->name = (yyvsp[(1) - (4)].string);
        f->args = nullptr;
        (yyval.value).id = 0;
        (yyval.value).unit = CSSParserValue::Function;
        (yyval.value).function = f;
  }
    break;

  case 289:
/* Line 1787 of yacc.c  */
#line 1397 "./CSSGrammar.y"
    { (yyval.value) = (yyvsp[(1) - (1)].value); }
    break;

  case 290:
/* Line 1787 of yacc.c  */
#line 1398 "./CSSGrammar.y"
    {
  }
    break;

  case 291:
/* Line 1787 of yacc.c  */
#line 1400 "./CSSGrammar.y"
    { (yyval.value) = (yyvsp[(2) - (2)].value); (yyval.value).fValue *= (yyvsp[(1) - (2)].integer); }
    break;

  case 292:
/* Line 1787 of yacc.c  */
#line 1403 "./CSSGrammar.y"
    {
        (yyval.character) = '+';
    }
    break;

  case 293:
/* Line 1787 of yacc.c  */
#line 1406 "./CSSGrammar.y"
    {
        (yyval.character) = '-';
    }
    break;

  case 294:
/* Line 1787 of yacc.c  */
#line 1409 "./CSSGrammar.y"
    {
        (yyval.character) = '*';
    }
    break;

  case 295:
/* Line 1787 of yacc.c  */
#line 1412 "./CSSGrammar.y"
    {
        (yyval.character) = '/';
    }
    break;

  case 298:
/* Line 1787 of yacc.c  */
#line 1420 "./CSSGrammar.y"
    {
        if ((yyvsp[(3) - (5)].valueList)) {
            (yyval.valueList) = (yyvsp[(3) - (5)].valueList);
            CSSParserValue v;
            v.id = 0;
            v.unit = CSSParserValue::Operator;
            v.iValue = '(';
            (yyval.valueList)->insertValueAt(0, v);
            v.iValue = ')';
            (yyval.valueList)->addValue(v);
        } else
            (yyval.valueList) = 0;
    }
    break;

  case 299:
/* Line 1787 of yacc.c  */
#line 1435 "./CSSGrammar.y"
    {
        (yyval.valueList) = parser->createFloatingValueList();
        (yyval.valueList)->addValue(parser->sinkFloatingValue((yyvsp[(1) - (1)].value)));
    }
    break;

  case 300:
/* Line 1787 of yacc.c  */
#line 1439 "./CSSGrammar.y"
    {
        if ((yyvsp[(1) - (3)].valueList) && (yyvsp[(2) - (3)].character)) {
            (yyval.valueList) = (yyvsp[(1) - (3)].valueList);
            CSSParserValue v;
            v.id = 0;
            v.unit = CSSParserValue::Operator;
            v.iValue = (yyvsp[(2) - (3)].character);
            (yyval.valueList)->addValue(v);
            (yyval.valueList)->addValue(parser->sinkFloatingValue((yyvsp[(3) - (3)].value)));
        } else
            (yyval.valueList) = 0;
    }
    break;

  case 301:
/* Line 1787 of yacc.c  */
#line 1451 "./CSSGrammar.y"
    {
        if ((yyvsp[(1) - (3)].valueList) && (yyvsp[(2) - (3)].character) && (yyvsp[(3) - (3)].valueList)) {
            (yyval.valueList) = (yyvsp[(1) - (3)].valueList);
            CSSParserValue v;
            v.id = 0;
            v.unit = CSSParserValue::Operator;
            v.iValue = (yyvsp[(2) - (3)].character);
            (yyval.valueList)->addValue(v);
            (yyval.valueList)->extend(*((yyvsp[(3) - (3)].valueList)));
        } else
            (yyval.valueList) = 0;
    }
    break;

  case 303:
/* Line 1787 of yacc.c  */
#line 1464 "./CSSGrammar.y"
    {
        (yyval.valueList) = 0;
    }
    break;

  case 304:
/* Line 1787 of yacc.c  */
#line 1469 "./CSSGrammar.y"
    {
        (yyval.valueList) = (yyvsp[(1) - (2)].valueList);
    }
    break;

  case 305:
/* Line 1787 of yacc.c  */
#line 1472 "./CSSGrammar.y"
    {
        if ((yyvsp[(1) - (5)].valueList) && (yyvsp[(4) - (5)].valueList)) {
            (yyval.valueList) = (yyvsp[(1) - (5)].valueList);
            CSSParserValue v;
            v.id = 0;
            v.unit = CSSParserValue::Operator;
            v.iValue = ',';
            (yyval.valueList)->addValue(v);
            (yyval.valueList)->extend(*((yyvsp[(4) - (5)].valueList)));
        } else
            (yyval.valueList) = 0;
    }
    break;

  case 306:
/* Line 1787 of yacc.c  */
#line 1486 "./CSSGrammar.y"
    {
        CSSParserFunction* f = parser->createFloatingFunction();
        f->name = (yyvsp[(1) - (5)].string);
        f->args = parser->sinkFloatingValueList((yyvsp[(3) - (5)].valueList));
        (yyval.value).id = 0;
        (yyval.value).unit = CSSParserValue::Function;
        (yyval.value).function = f;
    }
    break;

  case 307:
/* Line 1787 of yacc.c  */
#line 1494 "./CSSGrammar.y"
    {
        YYERROR;
    }
    break;

  case 308:
/* Line 1787 of yacc.c  */
#line 1499 "./CSSGrammar.y"
    {
        (yyval.string) = (yyvsp[(1) - (1)].string);
    }
    break;

  case 309:
/* Line 1787 of yacc.c  */
#line 1502 "./CSSGrammar.y"
    {
        (yyval.string) = (yyvsp[(1) - (1)].string);
    }
    break;

  case 310:
/* Line 1787 of yacc.c  */
#line 1507 "./CSSGrammar.y"
    {
        CSSParserFunction* f = parser->createFloatingFunction();
        f->name = (yyvsp[(1) - (4)].string);
        f->args = parser->sinkFloatingValueList((yyvsp[(3) - (4)].valueList));
        (yyval.value).id = 0;
        (yyval.value).unit = CSSParserValue::Function;
        (yyval.value).function = f;
    }
    break;

  case 311:
/* Line 1787 of yacc.c  */
#line 1515 "./CSSGrammar.y"
    {
        YYERROR;
    }
    break;

  case 312:
/* Line 1787 of yacc.c  */
#line 1520 "./CSSGrammar.y"
    {
        (yyval.rule) = 0;
    }
    break;

  case 313:
/* Line 1787 of yacc.c  */
#line 1523 "./CSSGrammar.y"
    {
        (yyval.rule) = 0;
    }
    break;

  case 314:
/* Line 1787 of yacc.c  */
#line 1528 "./CSSGrammar.y"
    {
        (yyval.rule) = 0;
    }
    break;

  case 315:
/* Line 1787 of yacc.c  */
#line 1531 "./CSSGrammar.y"
    {
        (yyval.rule) = 0;
    }
    break;

  case 316:
/* Line 1787 of yacc.c  */
#line 1536 "./CSSGrammar.y"
    {
        (yyval.rule) = 0;
    }
    break;

  case 317:
/* Line 1787 of yacc.c  */
#line 1541 "./CSSGrammar.y"
    {
        parser->invalidBlockHit();
    }
    break;

  case 318:
/* Line 1787 of yacc.c  */
#line 1544 "./CSSGrammar.y"
    {
        parser->invalidBlockHit();
    }
    break;

  case 321:
/* Line 1787 of yacc.c  */
#line 1552 "./CSSGrammar.y"
    {
        (yyval.location) = parser->currentLocation();
    }
    break;


/* Line 1787 of yacc.c  */
#line 4715 "./CSSGrammar.cpp"
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
      yyerror (parser, YY_("syntax error"));
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
        yyerror (parser, yymsgp);
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
		      yytoken, &yylval, parser);
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
		  yystos[yystate], yyvsp, parser);
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
  yyerror (parser, YY_("memory exhausted"));
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
                  yytoken, &yylval, parser);
    }
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp, parser);
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


/* Line 2050 of yacc.c  */
#line 1560 "./CSSGrammar.y"

