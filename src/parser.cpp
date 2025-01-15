/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "parser.y"

    #include <string>
    #include <vector>
    #include <assert.h>
    #include <optional>
    #include <variant>
    #include "node.h"
    #include <map>

    std::vector<NDecl*>* programBlock;
    
    extern int yylex();
    extern void yyerror(char const *msg);

    void setLastExpr(NBexprIf* expr, NExpr else_expr)
    {
        if (!expr->elseExpr.has_value())
            expr->elseExpr = else_expr;
        else
        {
            NBexprIf* nif = std::get<NBexprIf*>(expr->elseExpr.value());
            setLastExpr(nif, else_expr);
        }
    }

    std::string parseStr(std::string s){
        s = s.substr(1, s.length() - 2);
        static const std::map<std::string, std::string> specialReplace = {
            {"\\\\", "\\"},
            {"\\\"", "\""},
            {"\\n", "\n"},
            {"\\t", "\t"}
        };
        for (auto &&[first, second] : specialReplace)
            while (s.find(first) != std::string::npos)
                s.replace(s.find(first), first.length(), second);
        return s;
    }

    #define WRAP_TYPE(x) (new NType(x))
    #define WRAP_EXPR(x) (new NExpr(x))
    #define WRAP_STMT(x) (new NStmt(x))
    #define WRAP_ATOM(x) (new NAtom(x))

#line 116 "src/parser.cpp"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "parser.hpp"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_TIDENTIFIER = 3,                /* TIDENTIFIER  */
  YYSYMBOL_TSTRING = 4,                    /* TSTRING  */
  YYSYMBOL_TINTEGER = 5,                   /* TINTEGER  */
  YYSYMBOL_TIF = 6,                        /* TIF  */
  YYSYMBOL_TELSE = 7,                      /* TELSE  */
  YYSYMBOL_TELIF = 8,                      /* TELIF  */
  YYSYMBOL_TFN = 9,                        /* TFN  */
  YYSYMBOL_TFUN = 10,                      /* TFUN  */
  YYSYMBOL_TRETURN = 11,                   /* TRETURN  */
  YYSYMBOL_TTHEN = 12,                     /* TTHEN  */
  YYSYMBOL_TVAL = 13,                      /* TVAL  */
  YYSYMBOL_TVAR = 14,                      /* TVAR  */
  YYSYMBOL_TTRUE = 15,                     /* TTRUE  */
  YYSYMBOL_TFALSE = 16,                    /* TFALSE  */
  YYSYMBOL_TADD = 17,                      /* TADD  */
  YYSYMBOL_TSUB = 18,                      /* TSUB  */
  YYSYMBOL_TMUL = 19,                      /* TMUL  */
  YYSYMBOL_TDIV = 20,                      /* TDIV  */
  YYSYMBOL_TMOD = 21,                      /* TMOD  */
  YYSYMBOL_TINC = 22,                      /* TINC  */
  YYSYMBOL_TCLT = 23,                      /* TCLT  */
  YYSYMBOL_TCLE = 24,                      /* TCLE  */
  YYSYMBOL_TCGT = 25,                      /* TCGT  */
  YYSYMBOL_TCGE = 26,                      /* TCGE  */
  YYSYMBOL_TCEQ = 27,                      /* TCEQ  */
  YYSYMBOL_TCNE = 28,                      /* TCNE  */
  YYSYMBOL_TAND = 29,                      /* TAND  */
  YYSYMBOL_TOR = 30,                       /* TOR  */
  YYSYMBOL_TRPAREN = 31,                   /* TRPAREN  */
  YYSYMBOL_TRBRACE = 32,                   /* TRBRACE  */
  YYSYMBOL_TCOMMA = 33,                    /* TCOMMA  */
  YYSYMBOL_TRARROW = 34,                   /* TRARROW  */
  YYSYMBOL_TLBRACE = 35,                   /* TLBRACE  */
  YYSYMBOL_TLBRACK = 36,                   /* TLBRACK  */
  YYSYMBOL_TRBRACK = 37,                   /* TRBRACK  */
  YYSYMBOL_TEQUAL = 38,                    /* TEQUAL  */
  YYSYMBOL_TDOT = 39,                      /* TDOT  */
  YYSYMBOL_TCOLONEQ = 40,                  /* TCOLONEQ  */
  YYSYMBOL_TCOLON = 41,                    /* TCOLON  */
  YYSYMBOL_TLPAREN = 42,                   /* TLPAREN  */
  YYSYMBOL_TSEMICOLON = 43,                /* TSEMICOLON  */
  YYSYMBOL_TTILDE = 44,                    /* TTILDE  */
  YYSYMBOL_TEXCL = 45,                     /* TEXCL  */
  YYSYMBOL_PATOM = 46,                     /* PATOM  */
  YYSYMBOL_YYACCEPT = 47,                  /* $accept  */
  YYSYMBOL_file = 48,                      /* file  */
  YYSYMBOL_semicolon_plus = 49,            /* semicolon_plus  */
  YYSYMBOL_non_empty_decl_list_semicolon = 50, /* non_empty_decl_list_semicolon  */
  YYSYMBOL_decl = 51,                      /* decl  */
  YYSYMBOL_funbody = 52,                   /* funbody  */
  YYSYMBOL_non_empty_param_list_comma = 53, /* non_empty_param_list_comma  */
  YYSYMBOL_param_list_comma = 54,          /* param_list_comma  */
  YYSYMBOL_non_empty_ident_list_comma = 55, /* non_empty_ident_list_comma  */
  YYSYMBOL_ident_list_comma = 56,          /* ident_list_comma  */
  YYSYMBOL_param = 57,                     /* param  */
  YYSYMBOL_annot = 58,                     /* annot  */
  YYSYMBOL_result = 59,                    /* result  */
  YYSYMBOL_type = 60,                      /* type  */
  YYSYMBOL_type_list_comma_2_or_more = 61, /* type_list_comma_2_or_more  */
  YYSYMBOL_atype = 62,                     /* atype  */
  YYSYMBOL_atom = 63,                      /* atom  */
  YYSYMBOL_atom_basic = 64,                /* atom_basic  */
  YYSYMBOL_atom_call = 65,                 /* atom_call  */
  YYSYMBOL_atom_sugar = 66,                /* atom_sugar  */
  YYSYMBOL_expr = 67,                      /* expr  */
  YYSYMBOL_non_empty_expr_list_comma = 68, /* non_empty_expr_list_comma  */
  YYSYMBOL_expr_list_comma = 69,           /* expr_list_comma  */
  YYSYMBOL_bexpr = 70,                     /* bexpr  */
  YYSYMBOL_bexpr_op = 71,                  /* bexpr_op  */
  YYSYMBOL_elif_list = 72,                 /* elif_list  */
  YYSYMBOL_block = 73,                     /* block  */
  YYSYMBOL_bexpr_maybe = 74,               /* bexpr_maybe  */
  YYSYMBOL_block_content_last = 75,        /* block_content_last  */
  YYSYMBOL_block_content = 76,             /* block_content  */
  YYSYMBOL_stmt = 77                       /* stmt  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

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


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
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

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

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
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
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
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  8
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   271

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  47
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  31
/* YYNRULES -- Number of rules.  */
#define YYNRULES  90
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  161

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   301


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
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
      45,    46
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   120,   120,   121,   122,   125,   126,   135,   136,   139,
     142,   143,   145,   146,   149,   150,   153,   154,   157,   158,
     161,   164,   167,   168,   178,   179,   180,   183,   184,   187,
     188,   189,   190,   193,   194,   197,   198,   199,   200,   201,
     202,   203,   204,   205,   208,   209,   210,   211,   215,   216,
     223,   224,   227,   228,   231,   232,   235,   236,   237,   238,
     239,   240,   241,   244,   245,   246,   247,   248,   249,   250,
     251,   252,   253,   254,   255,   256,   257,   258,   259,   260,
     263,   264,   267,   270,   271,   274,   275,   278,   301,   302,
     303
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "TIDENTIFIER",
  "TSTRING", "TINTEGER", "TIF", "TELSE", "TELIF", "TFN", "TFUN", "TRETURN",
  "TTHEN", "TVAL", "TVAR", "TTRUE", "TFALSE", "TADD", "TSUB", "TMUL",
  "TDIV", "TMOD", "TINC", "TCLT", "TCLE", "TCGT", "TCGE", "TCEQ", "TCNE",
  "TAND", "TOR", "TRPAREN", "TRBRACE", "TCOMMA", "TRARROW", "TLBRACE",
  "TLBRACK", "TRBRACK", "TEQUAL", "TDOT", "TCOLONEQ", "TCOLON", "TLPAREN",
  "TSEMICOLON", "TTILDE", "TEXCL", "PATOM", "$accept", "file",
  "semicolon_plus", "non_empty_decl_list_semicolon", "decl", "funbody",
  "non_empty_param_list_comma", "param_list_comma",
  "non_empty_ident_list_comma", "ident_list_comma", "param", "annot",
  "result", "type", "type_list_comma_2_or_more", "atype", "atom",
  "atom_basic", "atom_call", "atom_sugar", "expr",
  "non_empty_expr_list_comma", "expr_list_comma", "bexpr", "bexpr_op",
  "elif_list", "block", "bexpr_maybe", "block_content_last",
  "block_content", "stmt", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-49)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-89)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
       4,    12,     4,    10,    21,   -24,   -17,   -49,   -49,   -24,
     -49,    -6,    47,   -49,    -6,   -49,    11,    23,    27,   -49,
       1,    47,    18,    38,    -1,   -49,    37,   -49,    33,   -49,
     -49,   164,   -17,   150,   -49,   -49,    61,   150,     3,   107,
     164,   164,   150,    -7,     7,     9,   -49,   -49,   -49,   215,
     -49,     1,   -49,    15,    24,     3,   164,    57,   -49,   -49,
      83,    85,   -49,    55,    67,   -49,    58,   -49,    69,    63,
     101,   -49,   -49,   -49,    76,   -49,   -49,   -49,   105,   150,
     -17,   -49,   -17,   -49,   186,   186,   186,   186,   186,   186,
     186,   186,   186,   186,   186,   186,   186,   186,    84,   -49,
       1,    80,     1,   -49,   -49,   150,   150,    77,    79,   -49,
      61,   150,   -49,   -49,    91,    92,   -49,   -49,    94,   -49,
     -49,   -49,    19,    19,   -49,   -49,   -49,    19,    74,    74,
      74,    74,    74,    74,   193,   243,   -49,   -49,     3,   -49,
     -49,   -49,   150,   150,   -49,   -49,   123,     1,   -49,   -49,
      71,   -49,   -49,   -49,   -49,   150,   164,   -49,   115,   150,
     -49
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       2,     0,     2,     0,     4,     0,     0,     3,     1,     0,
       5,     7,    14,     9,     8,     6,     0,    15,     0,    12,
       0,     0,     0,    29,     0,    20,    24,    13,    40,    38,
      37,     0,     0,     0,    35,    36,    83,    54,     0,     0,
       0,     0,     0,    63,    33,    34,    43,    10,    51,    56,
      50,     0,    32,     0,     0,     0,     0,     0,    59,    60,
       0,     0,    84,    86,     0,    85,     0,    52,    55,     0,
      18,    21,    22,    39,     0,    64,    65,    11,     0,    54,
       0,    47,     0,    49,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    31,
       0,     0,     0,    25,    62,     0,     0,     0,     0,    82,
      83,     0,    42,    16,    19,     0,    41,    45,     0,    46,
      48,    40,    72,    73,    74,    75,    76,    77,    69,    68,
      71,    70,    66,    67,    78,    79,    30,    27,     0,    28,
      61,    80,     0,     0,    87,    53,     0,     0,    44,    26,
      57,    89,    90,    17,    23,     0,     0,    58,     0,     0,
      81
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -49,   127,   121,   -49,   130,   -31,   -49,   -49,   -49,   -49,
     110,   -49,   -48,   -15,   -49,   -49,   -49,   -49,   -49,   -49,
     -22,   -49,    56,   -28,   162,   -49,    36,   -49,    26,   -49,
     -49
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     3,    11,     4,     5,    13,    17,    18,   114,   115,
      19,    42,    71,    72,    54,    26,    43,    44,    45,    46,
      67,    68,    69,    48,    49,   150,    50,    63,    64,    65,
      66
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      47,    58,    23,    57,    23,    25,    23,   103,    62,    53,
       8,    59,    75,    76,     1,     6,    80,    74,    82,    10,
      77,    28,    29,    30,    31,    12,    70,    32,   104,    33,
      52,     1,    78,    34,    35,    79,    98,    15,    86,    87,
      88,    24,    36,    24,    36,    24,    99,     2,   100,   119,
      16,   120,    20,    36,    37,   101,    21,   102,    22,    38,
      39,    51,    40,    41,    28,    29,    30,    31,   105,   106,
      32,    55,    33,    56,    60,    61,    34,    35,   155,   156,
      81,    83,    62,   140,   141,   137,   107,   139,   108,   145,
     149,    84,    85,    86,    87,    88,    89,    37,   -88,   109,
     112,   110,   111,    39,   113,    40,    41,   116,   117,   136,
      28,    29,    30,    31,   138,   142,    32,   147,    33,   143,
     151,   152,    34,    35,   146,   148,   153,   159,   158,     7,
      14,    27,   154,   157,     9,   118,   144,   160,    73,     0,
       0,     0,    36,    37,     0,     0,     0,     0,     0,    39,
       0,    40,    41,    28,    29,    30,    31,     0,     0,    32,
       0,    33,     0,     0,     0,    34,    35,    28,    29,    30,
      31,     0,     0,    32,     0,    33,     0,     0,     0,    34,
      35,     0,     0,     0,     0,    36,    37,     0,     0,   121,
      29,    30,    39,     0,    40,    41,     0,     0,     0,     0,
      37,    34,    35,     0,     0,     0,    39,     0,    40,    41,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    37,    97,     0,     0,     0,     0,    39,     0,
      40,    41,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    97,   122,   123,   124,   125,
     126,   127,   128,   129,   130,   131,   132,   133,   134,   135,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95
};

static const yytype_int16 yycheck[] =
{
      22,    32,     3,    31,     3,    20,     3,    55,    36,    24,
       0,    33,    40,    41,    10,     3,     9,    39,     9,    43,
      42,     3,     4,     5,     6,    42,    23,     9,    56,    11,
      31,    10,    39,    15,    16,    42,    51,    43,    19,    20,
      21,    42,    35,    42,    35,    42,    31,    43,    33,    80,
       3,    82,    41,    35,    36,    31,    33,    33,    31,    41,
      42,    23,    44,    45,     3,     4,     5,     6,    11,    12,
       9,    34,    11,    40,    13,    14,    15,    16,     7,     8,
      44,    45,   110,   105,   106,   100,     3,   102,     3,   111,
     138,    17,    18,    19,    20,    21,    22,    36,    43,    32,
      37,    43,    33,    42,     3,    44,    45,    31,     3,    25,
       3,     4,     5,     6,    34,    38,     9,    25,    11,    40,
     142,   143,    15,    16,    33,    31,     3,    12,   156,     2,
       9,    21,   147,   155,     4,    79,   110,   159,    31,    -1,
      -1,    -1,    35,    36,    -1,    -1,    -1,    -1,    -1,    42,
      -1,    44,    45,     3,     4,     5,     6,    -1,    -1,     9,
      -1,    11,    -1,    -1,    -1,    15,    16,     3,     4,     5,
       6,    -1,    -1,     9,    -1,    11,    -1,    -1,    -1,    15,
      16,    -1,    -1,    -1,    -1,    35,    36,    -1,    -1,     3,
       4,     5,    42,    -1,    44,    45,    -1,    -1,    -1,    -1,
      36,    15,    16,    -1,    -1,    -1,    42,    -1,    44,    45,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    36,    30,    -1,    -1,    -1,    -1,    42,    -1,
      44,    45,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    10,    43,    48,    50,    51,     3,    48,     0,    51,
      43,    49,    42,    52,    49,    43,     3,    53,    54,    57,
      41,    33,    31,     3,    42,    60,    62,    57,     3,     4,
       5,     6,     9,    11,    15,    16,    35,    36,    41,    42,
      44,    45,    58,    63,    64,    65,    66,    67,    70,    71,
      73,    23,    31,    60,    61,    34,    40,    70,    52,    67,
      13,    14,    70,    74,    75,    76,    77,    67,    68,    69,
      23,    59,    60,    31,    67,    70,    70,    67,    39,    42,
       9,    73,     9,    73,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    60,    31,
      33,    31,    33,    59,    70,    11,    12,     3,     3,    32,
      43,    33,    37,     3,    55,    56,    31,     3,    69,    52,
      52,     3,    71,    71,    71,    71,    71,    71,    71,    71,
      71,    71,    71,    71,    71,    71,    25,    60,    34,    60,
      67,    67,    38,    40,    75,    67,    33,    25,    31,    59,
      72,    67,    67,     3,    60,     7,     8,    67,    70,    12,
      67
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    47,    48,    48,    48,    49,    49,    50,    50,    51,
      52,    52,    53,    53,    54,    54,    55,    55,    56,    56,
      57,    58,    59,    59,    60,    60,    60,    61,    61,    62,
      62,    62,    62,    63,    63,    64,    64,    64,    64,    64,
      64,    64,    64,    64,    65,    65,    65,    65,    66,    66,
      67,    67,    68,    68,    69,    69,    70,    70,    70,    70,
      70,    70,    70,    71,    71,    71,    71,    71,    71,    71,
      71,    71,    71,    71,    71,    71,    71,    71,    71,    71,
      72,    72,    73,    74,    74,    75,    75,    76,    77,    77,
      77
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     1,     1,     2,     2,     3,     3,
       4,     5,     1,     3,     0,     1,     1,     3,     0,     1,
       3,     2,     1,     4,     1,     3,     5,     3,     3,     1,
       4,     3,     2,     1,     1,     1,     1,     1,     1,     2,
       1,     3,     3,     1,     4,     3,     3,     2,     3,     2,
       1,     1,     1,     3,     0,     1,     1,     5,     7,     2,
       2,     4,     3,     1,     2,     2,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       0,     5,     3,     0,     1,     1,     1,     3,     1,     4,
       4
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
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

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF

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


/* YYLOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

# ifndef YYLOCATION_PRINT

#  if defined YY_LOCATION_PRINT

   /* Temporary convenience wrapper in case some people defined the
      undocumented and private YY_LOCATION_PRINT macros.  */
#   define YYLOCATION_PRINT(File, Loc)  YY_LOCATION_PRINT(File, *(Loc))

#  elif defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
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

#   define YYLOCATION_PRINT  yy_location_print_

    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT(File, Loc)  YYLOCATION_PRINT(File, &(Loc))

#  else

#   define YYLOCATION_PRINT(File, Loc) ((void) 0)
    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT  YYLOCATION_PRINT

#  endif
# endif /* !defined YYLOCATION_PRINT */


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (yylocationp);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  YYLOCATION_PRINT (yyo, yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yykind, yyvaluep, yylocationp);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)],
                       &(yylsp[(yyi + 1) - (yynrhs)]));
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
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YY_USE (yyvaluep);
  YY_USE (yylocationp);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
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
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

    /* The location stack: array, bottom, top.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls = yylsa;
    YYLTYPE *yylsp = yyls;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[3];



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  yylsp[0] = yylloc;
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


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

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      yyerror_range[1] = yylloc;
      goto yyerrlab1;
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
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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
| yyreduce -- do a reduction.  |
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

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* file: %empty  */
#line 120 "parser.y"
                   {programBlock = new std::vector<NDecl*>{}; }
#line 1435 "src/parser.cpp"
    break;

  case 3: /* file: TSEMICOLON file  */
#line 121 "parser.y"
                       { (yyval.decl_list) = (yyvsp[0].decl_list); }
#line 1441 "src/parser.cpp"
    break;

  case 4: /* file: non_empty_decl_list_semicolon  */
#line 122 "parser.y"
                                     { programBlock = (yyvsp[0].decl_list); }
#line 1447 "src/parser.cpp"
    break;

  case 7: /* non_empty_decl_list_semicolon: decl semicolon_plus  */
#line 135 "parser.y"
                                                    { (yyval.decl_list) = new std::vector<NDecl*>{(yyvsp[-1].decl)}; }
#line 1453 "src/parser.cpp"
    break;

  case 8: /* non_empty_decl_list_semicolon: non_empty_decl_list_semicolon decl semicolon_plus  */
#line 136 "parser.y"
                                                                                  { (yyvsp[-2].decl_list)->push_back((yyvsp[-1].decl)); (yyval.decl_list) = (yyvsp[-2].decl_list); }
#line 1459 "src/parser.cpp"
    break;

  case 9: /* decl: TFUN TIDENTIFIER funbody  */
#line 139 "parser.y"
                                { (yyval.decl) = new NDecl((yyloc), (yyvsp[-1].str), (yyvsp[0].funbody)); }
#line 1465 "src/parser.cpp"
    break;

  case 10: /* funbody: TLPAREN param_list_comma TRPAREN expr  */
#line 142 "parser.y"
                                                { (yyval.funbody)  = new NFunBody((yyloc), (yyvsp[-2].param_list), *(yyvsp[0].expr)); }
#line 1471 "src/parser.cpp"
    break;

  case 11: /* funbody: TLPAREN param_list_comma TRPAREN annot expr  */
#line 143 "parser.y"
                                                      { (yyval.funbody)  = new NFunBody((yyloc), (yyvsp[-3].param_list), *(yyvsp[0].expr), (yyvsp[-1].rtype)); }
#line 1477 "src/parser.cpp"
    break;

  case 12: /* non_empty_param_list_comma: param  */
#line 145 "parser.y"
                                   { (yyval.param_list) = new std::vector<NParam*>{(yyvsp[0].param)}; }
#line 1483 "src/parser.cpp"
    break;

  case 13: /* non_empty_param_list_comma: non_empty_param_list_comma TCOMMA param  */
#line 146 "parser.y"
                                                                     { (yyvsp[-2].param_list)->push_back((yyvsp[0].param)); (yyval.param_list) = (yyvsp[-2].param_list); }
#line 1489 "src/parser.cpp"
    break;

  case 14: /* param_list_comma: %empty  */
#line 149 "parser.y"
                               { (yyval.param_list) = new std::vector<NParam*>{}; }
#line 1495 "src/parser.cpp"
    break;

  case 16: /* non_empty_ident_list_comma: TIDENTIFIER  */
#line 153 "parser.y"
                                         { (yyval.ident_list) = new std::vector<std::string*>{(yyvsp[0].str)}; }
#line 1501 "src/parser.cpp"
    break;

  case 17: /* non_empty_ident_list_comma: non_empty_ident_list_comma TCOMMA TIDENTIFIER  */
#line 154 "parser.y"
                                                                           { (yyvsp[-2].ident_list)->push_back((yyvsp[0].str)); (yyval.ident_list) = (yyvsp[-2].ident_list); }
#line 1507 "src/parser.cpp"
    break;

  case 18: /* ident_list_comma: %empty  */
#line 157 "parser.y"
                               { (yyval.ident_list) = new std::vector<std::string*>{}; }
#line 1513 "src/parser.cpp"
    break;

  case 20: /* param: TIDENTIFIER TCOLON type  */
#line 161 "parser.y"
                                { (yyval.param) = new NParam((yyloc), (yyvsp[-2].str), *(yyvsp[0].type)); }
#line 1519 "src/parser.cpp"
    break;

  case 21: /* annot: TCOLON result  */
#line 164 "parser.y"
                      { (yyval.rtype) = (yyvsp[0].rtype); }
#line 1525 "src/parser.cpp"
    break;

  case 22: /* result: type  */
#line 167 "parser.y"
              { (yyval.rtype) = new NReturnType((yyloc), *(yyvsp[0].type)); }
#line 1531 "src/parser.cpp"
    break;

  case 23: /* result: TCLT ident_list_comma TCGT type  */
#line 168 "parser.y"
                                         { (yyval.rtype) = new NReturnType((yyloc), *(yyvsp[0].type), (yyvsp[-2].ident_list)); }
#line 1537 "src/parser.cpp"
    break;

  case 25: /* type: atype TRARROW result  */
#line 179 "parser.y"
                            { (yyval.type) = WRAP_TYPE(new NFunType((yyloc), new std::vector<NType>{*(yyvsp[-2].type)}, (yyvsp[0].rtype))); }
#line 1543 "src/parser.cpp"
    break;

  case 26: /* type: TLPAREN type_list_comma_2_or_more TRPAREN TRARROW result  */
#line 180 "parser.y"
                                                                { (yyval.type) = WRAP_TYPE(new NFunType((yyloc), (yyvsp[-3].type_list), (yyvsp[0].rtype))); }
#line 1549 "src/parser.cpp"
    break;

  case 27: /* type_list_comma_2_or_more: type TCOMMA type  */
#line 183 "parser.y"
                                             { (yyval.type_list) = new std::vector<NType>{*(yyvsp[-2].type), *(yyvsp[0].type)}; }
#line 1555 "src/parser.cpp"
    break;

  case 28: /* type_list_comma_2_or_more: type_list_comma_2_or_more TCOMMA type  */
#line 184 "parser.y"
                                                                  { (yyvsp[-2].type_list)->push_back(*(yyvsp[0].type)); (yyval.type_list) = (yyvsp[-2].type_list); }
#line 1561 "src/parser.cpp"
    break;

  case 29: /* atype: TIDENTIFIER  */
#line 187 "parser.y"
                    { (yyval.type) = WRAP_TYPE(new NBasicType((yyloc), (yyvsp[0].str))); }
#line 1567 "src/parser.cpp"
    break;

  case 30: /* atype: TIDENTIFIER TCLT type TCGT  */
#line 188 "parser.y"
                                   { (yyval.type) = WRAP_TYPE(new NTemplateType((yyloc), (yyvsp[-3].str), *(yyvsp[-1].type))); }
#line 1573 "src/parser.cpp"
    break;

  case 31: /* atype: TLPAREN type TRPAREN  */
#line 189 "parser.y"
                             { (yyval.type) = (yyvsp[-1].type); }
#line 1579 "src/parser.cpp"
    break;

  case 32: /* atype: TLPAREN TRPAREN  */
#line 190 "parser.y"
                        { (yyval.type) = WRAP_TYPE(new NBasicType((yyloc), new std::string("unit"))); }
#line 1585 "src/parser.cpp"
    break;

  case 34: /* atom: atom_call  */
#line 194 "parser.y"
                 { (yyval.atom) = WRAP_ATOM((yyvsp[0].atom_call)); }
#line 1591 "src/parser.cpp"
    break;

  case 35: /* atom_basic: TTRUE  */
#line 197 "parser.y"
                   { (yyval.atom) = WRAP_ATOM(new NAtomTrue((yyloc))); }
#line 1597 "src/parser.cpp"
    break;

  case 36: /* atom_basic: TFALSE  */
#line 198 "parser.y"
              { (yyval.atom) = WRAP_ATOM(new NAtomFalse((yyloc))); }
#line 1603 "src/parser.cpp"
    break;

  case 37: /* atom_basic: TINTEGER  */
#line 199 "parser.y"
                { (yyval.atom) = WRAP_ATOM(new NAtomInt((yyloc), std::stol(*(yyvsp[0].str)))); }
#line 1609 "src/parser.cpp"
    break;

  case 38: /* atom_basic: TSTRING  */
#line 200 "parser.y"
               { (yyval.atom) = WRAP_ATOM(new NAtomStr((yyloc), new std::string(parseStr(*(yyvsp[0].str))))); delete (yyvsp[0].str); }
#line 1615 "src/parser.cpp"
    break;

  case 39: /* atom_basic: TLPAREN TRPAREN  */
#line 201 "parser.y"
                       { (yyval.atom) = WRAP_ATOM(new NAtomNil((yyloc))); }
#line 1621 "src/parser.cpp"
    break;

  case 40: /* atom_basic: TIDENTIFIER  */
#line 202 "parser.y"
                   { (yyval.atom) = WRAP_ATOM(new NAtomIdent((yyloc), (yyvsp[0].str))); }
#line 1627 "src/parser.cpp"
    break;

  case 41: /* atom_basic: TLPAREN expr TRPAREN  */
#line 203 "parser.y"
                            { (yyval.atom) = WRAP_ATOM(new NAtomExpr((yyloc), *(yyvsp[-1].expr))); }
#line 1633 "src/parser.cpp"
    break;

  case 42: /* atom_basic: TLBRACK expr_list_comma TRBRACK  */
#line 204 "parser.y"
                                       { (yyval.atom) = WRAP_ATOM(new NAtomList((yyloc), (yyvsp[-1].expr_list))); }
#line 1639 "src/parser.cpp"
    break;

  case 44: /* atom_call: atom TLPAREN expr_list_comma TRPAREN  */
#line 208 "parser.y"
                                                 { (yyval.atom_call) = new NAtomCall((yyloc), *(yyvsp[-3].atom), (yyvsp[-1].expr_list)); }
#line 1645 "src/parser.cpp"
    break;

  case 45: /* atom_call: atom TDOT TIDENTIFIER  */
#line 209 "parser.y"
                                  { (yyval.atom_call) = new NAtomCall((yyloc), new NAtomIdent((yyloc), (yyvsp[0].str)), new std::vector<NExpr>{new NBAtom((yyloc), *(yyvsp[-2].atom))}); }
#line 1651 "src/parser.cpp"
    break;

  case 46: /* atom_call: atom_basic TFN funbody  */
#line 210 "parser.y"
                                   { (yyval.atom_call) = new NAtomCall((yyloc), *(yyvsp[-2].atom), new std::vector<NExpr>{new NBexprLambda((yyloc), (yyvsp[0].funbody))}); }
#line 1657 "src/parser.cpp"
    break;

  case 47: /* atom_call: atom_basic block  */
#line 211 "parser.y"
                             { (yyval.atom_call) = new NAtomCall((yyloc), *(yyvsp[-1].atom), 
                new std::vector<NExpr>{new NBexprLambda((yyloc), new NFunBody((yyloc), new std::vector<NParam*>{}, (yyvsp[0].block)))}); }
#line 1664 "src/parser.cpp"
    break;

  case 48: /* atom_sugar: atom_call TFN funbody  */
#line 215 "parser.y"
                                   { (yyvsp[-2].atom_call)->args->push_back(new NBexprLambda((yyloc), (yyvsp[0].funbody))); (yyval.atom) = WRAP_ATOM((yyvsp[-2].atom_call)); }
#line 1670 "src/parser.cpp"
    break;

  case 49: /* atom_sugar: atom_call block  */
#line 216 "parser.y"
                             { (yyvsp[-1].atom_call)->args->push_back(new NBexprLambda((yyloc), 
                new NFunBody((yyloc), new std::vector<NParam*>{}, (yyvsp[0].block)))); (yyval.atom) = WRAP_ATOM((yyvsp[-1].atom_call)); }
#line 1677 "src/parser.cpp"
    break;

  case 50: /* expr: block  */
#line 223 "parser.y"
             { (yyval.expr) = WRAP_EXPR((yyvsp[0].block)); }
#line 1683 "src/parser.cpp"
    break;

  case 51: /* expr: bexpr  */
#line 224 "parser.y"
             { (yyval.expr) = (yyvsp[0].bexpr); }
#line 1689 "src/parser.cpp"
    break;

  case 52: /* non_empty_expr_list_comma: expr  */
#line 227 "parser.y"
                                 { (yyval.expr_list) = new std::vector<NExpr>{*(yyvsp[0].expr)}; }
#line 1695 "src/parser.cpp"
    break;

  case 53: /* non_empty_expr_list_comma: non_empty_expr_list_comma TCOMMA expr  */
#line 228 "parser.y"
                                                                  { (yyvsp[-2].expr_list)->push_back(*(yyvsp[0].expr)); (yyval.expr_list) = (yyvsp[-2].expr_list); }
#line 1701 "src/parser.cpp"
    break;

  case 54: /* expr_list_comma: %empty  */
#line 231 "parser.y"
                              { (yyval.expr_list) = new std::vector<NExpr>{}; }
#line 1707 "src/parser.cpp"
    break;

  case 57: /* bexpr: TIF bexpr TTHEN expr elif_list  */
#line 236 "parser.y"
                                       { (yyvsp[0].bexpr_if)->condition = *(yyvsp[-3].bexpr); (yyvsp[0].bexpr_if)->thenExpr = *(yyvsp[-1].expr); (yyval.bexpr) = WRAP_EXPR((yyvsp[0].bexpr_if)); }
#line 1713 "src/parser.cpp"
    break;

  case 58: /* bexpr: TIF bexpr TTHEN expr elif_list TELSE expr  */
#line 237 "parser.y"
                                                  { (yyvsp[-2].bexpr_if)->condition = *(yyvsp[-5].bexpr); (yyvsp[-2].bexpr_if)->thenExpr = *(yyvsp[-3].expr); setLastExpr((yyvsp[-2].bexpr_if), *(yyvsp[0].expr)); (yyval.bexpr) = WRAP_EXPR((yyvsp[-2].bexpr_if)); }
#line 1719 "src/parser.cpp"
    break;

  case 59: /* bexpr: TFN funbody  */
#line 238 "parser.y"
                    { (yyval.bexpr) = WRAP_EXPR(new NBexprLambda((yyloc), (yyvsp[0].funbody))); }
#line 1725 "src/parser.cpp"
    break;

  case 60: /* bexpr: TRETURN expr  */
#line 239 "parser.y"
                     { (yyval.bexpr) = WRAP_EXPR(new NBexprReturn((yyloc), *(yyvsp[0].expr))); }
#line 1731 "src/parser.cpp"
    break;

  case 61: /* bexpr: TIF bexpr TRETURN expr  */
#line 240 "parser.y"
                               { (yyval.bexpr) = WRAP_EXPR(new NBexprIf((yyloc), *(yyvsp[-2].bexpr), new NBexprReturn((yyloc), *(yyvsp[0].expr)))); }
#line 1737 "src/parser.cpp"
    break;

  case 62: /* bexpr: TIDENTIFIER TCOLONEQ bexpr  */
#line 241 "parser.y"
                                   { (yyval.bexpr) = WRAP_EXPR(new NBexprAssign((yyloc), (yyvsp[-2].str), *(yyvsp[0].bexpr))); }
#line 1743 "src/parser.cpp"
    break;

  case 63: /* bexpr_op: atom  */
#line 244 "parser.y"
                { (yyval.bexpr) = WRAP_EXPR(new NBAtom((yyloc), *(yyvsp[0].atom))); }
#line 1749 "src/parser.cpp"
    break;

  case 64: /* bexpr_op: TTILDE bexpr  */
#line 245 "parser.y"
                     { (yyval.bexpr) = WRAP_EXPR(new NBexprInfix((yyloc), (yyvsp[-1].token), *(yyvsp[0].bexpr))); }
#line 1755 "src/parser.cpp"
    break;

  case 65: /* bexpr_op: TEXCL bexpr  */
#line 246 "parser.y"
                    { (yyval.bexpr) = WRAP_EXPR(new NBexprInfix((yyloc), (yyvsp[-1].token), *(yyvsp[0].bexpr))); }
#line 1761 "src/parser.cpp"
    break;

  case 66: /* bexpr_op: bexpr_op TCEQ bexpr_op  */
#line 247 "parser.y"
                               { (yyval.bexpr) = WRAP_EXPR(new NBexprBinOP((yyloc), *(yyvsp[-2].bexpr), (yyvsp[-1].token), *(yyvsp[0].bexpr))); }
#line 1767 "src/parser.cpp"
    break;

  case 67: /* bexpr_op: bexpr_op TCNE bexpr_op  */
#line 248 "parser.y"
                               { (yyval.bexpr) = WRAP_EXPR(new NBexprBinOP((yyloc), *(yyvsp[-2].bexpr), (yyvsp[-1].token), *(yyvsp[0].bexpr))); }
#line 1773 "src/parser.cpp"
    break;

  case 68: /* bexpr_op: bexpr_op TCLE bexpr_op  */
#line 249 "parser.y"
                               { (yyval.bexpr) = WRAP_EXPR(new NBexprBinOP((yyloc), *(yyvsp[-2].bexpr), (yyvsp[-1].token), *(yyvsp[0].bexpr))); }
#line 1779 "src/parser.cpp"
    break;

  case 69: /* bexpr_op: bexpr_op TCLT bexpr_op  */
#line 250 "parser.y"
                               { (yyval.bexpr) = WRAP_EXPR(new NBexprBinOP((yyloc), *(yyvsp[-2].bexpr), (yyvsp[-1].token), *(yyvsp[0].bexpr))); }
#line 1785 "src/parser.cpp"
    break;

  case 70: /* bexpr_op: bexpr_op TCGE bexpr_op  */
#line 251 "parser.y"
                               { (yyval.bexpr) = WRAP_EXPR(new NBexprBinOP((yyloc), *(yyvsp[-2].bexpr), (yyvsp[-1].token), *(yyvsp[0].bexpr))); }
#line 1791 "src/parser.cpp"
    break;

  case 71: /* bexpr_op: bexpr_op TCGT bexpr_op  */
#line 252 "parser.y"
                               { (yyval.bexpr) = WRAP_EXPR(new NBexprBinOP((yyloc), *(yyvsp[-2].bexpr), (yyvsp[-1].token), *(yyvsp[0].bexpr))); }
#line 1797 "src/parser.cpp"
    break;

  case 72: /* bexpr_op: bexpr_op TADD bexpr_op  */
#line 253 "parser.y"
                               { (yyval.bexpr) = WRAP_EXPR(new NBexprBinOP((yyloc), *(yyvsp[-2].bexpr), (yyvsp[-1].token), *(yyvsp[0].bexpr))); }
#line 1803 "src/parser.cpp"
    break;

  case 73: /* bexpr_op: bexpr_op TSUB bexpr_op  */
#line 254 "parser.y"
                               { (yyval.bexpr) = WRAP_EXPR(new NBexprBinOP((yyloc), *(yyvsp[-2].bexpr), (yyvsp[-1].token), *(yyvsp[0].bexpr))); }
#line 1809 "src/parser.cpp"
    break;

  case 74: /* bexpr_op: bexpr_op TMUL bexpr_op  */
#line 255 "parser.y"
                               { (yyval.bexpr) = WRAP_EXPR(new NBexprBinOP((yyloc), *(yyvsp[-2].bexpr), (yyvsp[-1].token), *(yyvsp[0].bexpr))); }
#line 1815 "src/parser.cpp"
    break;

  case 75: /* bexpr_op: bexpr_op TDIV bexpr_op  */
#line 256 "parser.y"
                               { (yyval.bexpr) = WRAP_EXPR(new NBexprBinOP((yyloc), *(yyvsp[-2].bexpr), (yyvsp[-1].token), *(yyvsp[0].bexpr))); }
#line 1821 "src/parser.cpp"
    break;

  case 76: /* bexpr_op: bexpr_op TMOD bexpr_op  */
#line 257 "parser.y"
                               { (yyval.bexpr) = WRAP_EXPR(new NBexprBinOP((yyloc), *(yyvsp[-2].bexpr), (yyvsp[-1].token), *(yyvsp[0].bexpr))); }
#line 1827 "src/parser.cpp"
    break;

  case 77: /* bexpr_op: bexpr_op TINC bexpr_op  */
#line 258 "parser.y"
                               { (yyval.bexpr) = WRAP_EXPR(new NBexprBinOP((yyloc), *(yyvsp[-2].bexpr), (yyvsp[-1].token), *(yyvsp[0].bexpr))); }
#line 1833 "src/parser.cpp"
    break;

  case 78: /* bexpr_op: bexpr_op TAND bexpr_op  */
#line 259 "parser.y"
                               { (yyval.bexpr) = WRAP_EXPR(new NBexprBinOP((yyloc), *(yyvsp[-2].bexpr), (yyvsp[-1].token), *(yyvsp[0].bexpr))); }
#line 1839 "src/parser.cpp"
    break;

  case 79: /* bexpr_op: bexpr_op TOR bexpr_op  */
#line 260 "parser.y"
                               { (yyval.bexpr) = WRAP_EXPR(new NBexprBinOP((yyloc), *(yyvsp[-2].bexpr), (yyvsp[-1].token), *(yyvsp[0].bexpr))); }
#line 1845 "src/parser.cpp"
    break;

  case 80: /* elif_list: %empty  */
#line 263 "parser.y"
                        { (yyval.bexpr_if) = new NBexprIf((yyloc), std::nullopt, std::nullopt, std::nullopt); }
#line 1851 "src/parser.cpp"
    break;

  case 81: /* elif_list: elif_list TELIF bexpr TTHEN expr  */
#line 264 "parser.y"
                                             {(yyvsp[-4].bexpr_if)->elseExpr = static_cast<NExpr>(new NBexprIf((yyloc), *(yyvsp[-2].bexpr), *(yyvsp[0].expr), (yyvsp[-4].bexpr_if)->elseExpr)); (yyval.bexpr_if) = (yyvsp[-4].bexpr_if); }
#line 1857 "src/parser.cpp"
    break;

  case 82: /* block: TLBRACE block_content_last TRBRACE  */
#line 267 "parser.y"
                                           { (yyval.block) = ((yyvsp[-1].block_maybe)->has_value()) ? (yyvsp[-1].block_maybe)->value() : new NBlock((yyloc)); }
#line 1863 "src/parser.cpp"
    break;

  case 83: /* bexpr_maybe: %empty  */
#line 270 "parser.y"
                          { (yyval.bexpr_maybe) = new std::optional<NExpr>(std::nullopt); }
#line 1869 "src/parser.cpp"
    break;

  case 84: /* bexpr_maybe: bexpr  */
#line 271 "parser.y"
                    { (yyval.bexpr_maybe) = new std::optional<NExpr>(*(yyvsp[0].bexpr)); }
#line 1875 "src/parser.cpp"
    break;

  case 85: /* block_content_last: block_content  */
#line 274 "parser.y"
                                   { (yyval.block_maybe) = (yyvsp[0].block_maybe); }
#line 1881 "src/parser.cpp"
    break;

  case 86: /* block_content_last: bexpr_maybe  */
#line 275 "parser.y"
                                 { (yyval.block_maybe) = ((yyvsp[0].bexpr_maybe)->has_value()) ? new std::optional<NBlock*>(new NBlock((yyloc), new std::vector<NStmt>{}, (yyvsp[0].bexpr_maybe)->value())) : new std::optional<NBlock*>(std::nullopt); }
#line 1887 "src/parser.cpp"
    break;

  case 87: /* block_content: stmt TSEMICOLON block_content_last  */
#line 279 "parser.y"
    { 
        if ((yyvsp[-2].stmt_maybe)->has_value()) 
        { 
            if ((yyvsp[0].block_maybe)->has_value()) 
            {
                ((yyvsp[0].block_maybe)->value()->stmts)->insert(((yyvsp[0].block_maybe)->value()->stmts)->begin(), (yyvsp[-2].stmt_maybe)->value());
                (yyval.block_maybe) = (yyvsp[0].block_maybe);
            }
            else 
            {
                if (!(yyvsp[-2].stmt_maybe)->has_value() || !std::holds_alternative<NStmtBexpr*>((yyvsp[-2].stmt_maybe)->value())) // note that this specific error should not really happen... its for debugging purposes
                    yyerror("Internal parsing error : malformed block, last statement of block is not an expression");
                NStmtBexpr* nretExpr = std::get<NStmtBexpr*>((yyvsp[-2].stmt_maybe)->value());
                
                (yyval.block_maybe) = new std::optional<NBlock*>(new NBlock((yyloc), new std::vector<NStmt>{}, nretExpr->expr));
            } 
        } 
        else { (yyval.block_maybe) = (yyvsp[0].block_maybe); } 
    }
#line 1911 "src/parser.cpp"
    break;

  case 88: /* stmt: bexpr_maybe  */
#line 301 "parser.y"
                   { (yyval.stmt_maybe) = ((yyvsp[0].bexpr_maybe)->has_value()) ? new std::optional<NStmt>(NStmt(new NStmtBexpr((yyloc), (yyvsp[0].bexpr_maybe)->value()))) : new std::optional<NStmt>(std::nullopt); }
#line 1917 "src/parser.cpp"
    break;

  case 89: /* stmt: TVAL TIDENTIFIER TEQUAL expr  */
#line 302 "parser.y"
                                    { (yyval.stmt_maybe) = new std::optional<NStmt>(NStmt(new NStmtVal((yyloc), (yyvsp[-2].str), *(yyvsp[0].expr)))); }
#line 1923 "src/parser.cpp"
    break;

  case 90: /* stmt: TVAR TIDENTIFIER TCOLONEQ expr  */
#line 303 "parser.y"
                                      { (yyval.stmt_maybe) = new std::optional<NStmt>(NStmt(new NStmtVar((yyloc), (yyvsp[-2].str), *(yyvsp[0].expr)))); }
#line 1929 "src/parser.cpp"
    break;


#line 1933 "src/parser.cpp"

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
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

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

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  ++yylsp;
  YYLLOC_DEFAULT (*yylsp, yyerror_range, 2);

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
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
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 307 "parser.y"

