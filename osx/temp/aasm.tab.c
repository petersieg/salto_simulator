/* original parser id follows */
/* yysccsid[] = "@(#)yaccpar	1.9 (Berkeley) 02/21/93" */
/* (use YYMAJOR/YYMINOR for ifdefs dependent on parser version) */

#define YYBYACC 1
#define YYMAJOR 2
#define YYMINOR 0
#define YYPATCH 20240109

#define YYEMPTY        (-1)
#define yyclearin      (yychar = YYEMPTY)
#define yyerrok        (yyerrflag = 0)
#define YYRECOVERING() (yyerrflag != 0)
#define YYENOMEM       (-2)
#define YYEOF          0
#undef YYBTYACC
#define YYBTYACC 0
#define YYDEBUGSTR YYPREFIX "debug"
#define YYPREFIX "yy"

#define YYPURE 0

#line 2 "tools/aasm.y"
/**********************************************************
 * Xerox Alto Assembler.
 *
 * Parser of the Xerox Alto assembler.
 *
 * (C) 2007 by Juergen Buchmueller <pullmoll@t-online.de>
 *
 * $Id: aasm.y,v 1.1.1.1 2008/07/22 19:02:07 pm Exp $
 **********************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "emu_ops.h"

typedef unsigned char   byte;
typedef	unsigned short	word;

typedef	struct	tagSYM {
	struct tagSYM * next;
	int pass_no;
	int value;
	int refs;
	int *line_no;
	char *name;
}   SYM_t;

void emit(void);

void addsym(char * name, int value);
int getsym(char * name);

word *image = NULL;

int symb_no = 0;
int line_no = 1;
int pass_no = 1;
word cmd = 0x00;
int arg[4096] = {0, };
int expflg = 0;	/* print expression result */
int cmdflg = 0;
int argcnt = 0;
int arglow = 0;
int padflg = 0;	/* pad binary to new address */
word eexp = 0;
word end = 0;
word tmp = 0;
int pc	= 0;
int pcmax = -1;
int alloc = -1;

char lstbuff[256+1] = "";
char *plst  = NULL;

SYM_t *sym = NULL;
SYM_t *sym0 = NULL;

char inpname[256+1] = "";
char outname[256+1] = "";
char lstname[256+1] = "";

FILE *inpfile = NULL;
FILE *outfile = NULL;
FILE *lstfile = NULL;

int f_dump  = 0;		/* generate octal dump as output */
int f_list  = 0;		/* write listing file */
int f_syms  = 0;		/* write symbols into listing file */
int f_xref  = 0;		/* write cross references with symbols */
int f_octal = 1;		/* print numbers as octal in listing (default) */

extern void yyerror(const char *msg, ...);
extern int yylex(void);
extern void yyrestart(FILE *inputfile);

#ifdef YYSTYPE
#undef  YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#endif
#ifndef YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#line 82 "tools/aasm.y"
typedef union YYSTYPE {
	long long int i;
	char *s;
} YYSTYPE;
#endif /* !YYSTYPE_IS_DECLARED */
#line 113 "aasm.tab.c"

/* compatibility with bison */
#ifdef YYPARSE_PARAM
/* compatibility with FreeBSD */
# ifdef YYPARSE_PARAM_TYPE
#  define YYPARSE_DECL() yyparse(YYPARSE_PARAM_TYPE YYPARSE_PARAM)
# else
#  define YYPARSE_DECL() yyparse(void *YYPARSE_PARAM)
# endif
#else
# define YYPARSE_DECL() yyparse(void)
#endif

/* Parameters sent to lex. */
#ifdef YYLEX_PARAM
# define YYLEX_DECL() yylex(void *YYLEX_PARAM)
# define YYLEX yylex(YYLEX_PARAM)
#else
# define YYLEX_DECL() yylex(void)
# define YYLEX yylex()
#endif

#if !(defined(yylex) || defined(YYSTATE))
int YYLEX_DECL();
#endif

/* Parameters sent to yyerror. */
#ifndef YYERROR_DECL
#define YYERROR_DECL() yyerror(const char *s)
#endif
#ifndef YYERROR_CALL
#define YYERROR_CALL(msg) yyerror(msg)
#endif

extern int YYPARSE_DECL();

#define EOL 257
#define HASH 258
#define COMMA 259
#define COLON 260
#define LPAREN 261
#define RPAREN 262
#define QUOTE 263
#define PLUS 264
#define MINUS 265
#define ASTERISK 266
#define SLASH 267
#define SHL 268
#define SHR 269
#define AMPERSAND 270
#define BAR 271
#define CARET 272
#define TILDE 273
#define AT 274
#define IMM 275
#define REG 276
#define SYM 277
#define CHR 278
#define ARITH 279
#define AC 280
#define SKP 281
#define SZC 282
#define SNC 283
#define SZR 284
#define SNR 285
#define SEZ 286
#define SBN 287
#define JMP 288
#define JSR 289
#define DSZ 290
#define ISZ 291
#define LDA 292
#define STA 293
#define COM 294
#define NEG 295
#define MOV 296
#define INC 297
#define ADC 298
#define SUB 299
#define ADD 300
#define AND 301
#define CYCLE 302
#define MUL 303
#define DIV 304
#define JSRII 305
#define JSRIS 306
#define CONVERT 307
#define DIR 308
#define EIR 309
#define BRI 310
#define RCLK 311
#define SIO 312
#define BLT 313
#define BLKS 314
#define SIT 315
#define JMPRAM 316
#define RDRAM 317
#define WRTRAM 318
#define DIRS 319
#define VERS 320
#define DREAD 321
#define DWRITE 322
#define DEXCH 323
#define DIAGNOSE1 324
#define DIAGNOSE2 325
#define BITBLT 326
#define XMLDA 327
#define XMSTA 328
#define DB 329
#define DW 330
#define DD 331
#define DS 332
#define ALIGN 333
#define END 334
#define EQU 335
#define EVEN 336
#define ORG 337
#define YYERRCODE 256
typedef int YYINT;
static const YYINT yylhs[] = {                           -1,
    0,    0,   14,   14,   15,   15,   15,   15,   15,   15,
   15,   15,   15,   15,   15,   15,   15,   15,   15,   15,
   15,   15,   15,   15,   15,   15,   15,   15,   15,   15,
   15,   15,   15,   15,   15,   15,   15,   15,   15,   15,
   15,   15,   15,   15,   15,   15,   15,   15,   15,   15,
   15,   15,   15,   15,   15,   15,   15,   15,   15,   15,
   15,   15,   15,   15,   15,   16,   16,    5,    5,   10,
   10,   10,   10,   10,   10,   10,   10,   18,   18,    9,
    9,    6,    6,    7,    7,    8,    8,    8,   12,   13,
    1,    1,    1,    2,    2,    2,    2,    3,    3,    3,
    3,    3,    3,    3,    3,    4,    4,    4,   11,   22,
   19,   19,   23,   17,   17,   24,   21,   21,   25,   25,
   20,   20,
};
static const YYINT yylen[] = {                            2,
    1,    2,    2,    1,    1,    2,    3,    4,    4,    5,
    4,    5,    4,    5,    4,    5,    5,    6,    5,    6,
    7,    7,    7,    7,    7,    7,    7,    7,    4,    3,
    3,    4,    4,    5,    6,    3,    3,    3,    3,    3,
    3,    3,    3,    3,    3,    3,    3,    3,    3,    3,
    3,    3,    3,    3,    3,    3,    4,    4,    4,    4,
    4,    3,    4,    3,    4,    0,    2,    0,    1,    0,
    1,    1,    1,    1,    1,    1,    1,    1,    4,    1,
    4,    1,    4,    1,    4,    1,    2,    3,    1,    1,
    1,    3,    3,    1,    3,    3,    3,    1,    2,    2,
    2,    3,    3,    3,    3,    1,    1,    3,    1,    1,
    3,    1,    1,    3,    1,    1,    3,    1,    1,    1,
    3,    1,
};
static const YYINT yydefred[] = {                         0,
    5,    0,    0,    0,    0,    4,    0,   67,    0,    0,
    0,    0,    0,  106,  107,    0,    0,    0,   98,    2,
    3,    6,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  115,    0,    0,   99,  100,  101,   62,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,   69,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,   30,   31,    0,    0,    0,    0,    0,   36,
   37,   38,   39,   40,   41,   42,   43,   44,   45,   46,
   47,   48,   49,   50,   51,   52,   53,   54,   55,   56,
  119,    0,    0,    0,  112,  122,    0,    0,    0,  118,
    0,    0,    0,   64,    7,    0,    8,  108,    0,    0,
    0,    0,    0,  102,  103,  104,  105,    0,    0,    0,
    0,   87,    9,    0,   11,    0,   15,    0,   13,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,   29,   32,   33,    0,    0,    0,
    0,   57,    0,   58,    0,   59,   60,    0,   61,   63,
   65,  114,   10,   88,    0,   12,   16,   14,    0,    0,
   17,    0,   19,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,   34,  111,  120,  121,  117,    0,
   85,   18,   20,    0,   71,   72,   73,   74,   75,   76,
   77,    0,    0,    0,    0,    0,    0,    0,    0,   35,
    0,   81,   83,   21,   22,   23,   24,   25,   26,   27,
   28,   79,
};
#if defined(YYDESTRUCT_CALL) || defined(YYSTYPE_TOSTRING)
static const YYINT yystos[] = {                           0,
  257,  277,  337,  339,  353,  354,  355,  260,  335,  261,
  264,  265,  273,  275,  277,  340,  341,  342,  343,  256,
  354,  257,  288,  289,  290,  291,  292,  293,  294,  295,
  296,  297,  298,  299,  300,  301,  302,  303,  304,  305,
  306,  307,  308,  309,  310,  311,  312,  313,  314,  315,
  316,  317,  318,  319,  320,  321,  322,  323,  324,  325,
  326,  327,  328,  329,  330,  331,  332,  333,  334,  336,
  340,  356,  362,  340,  340,  343,  343,  343,  257,  268,
  269,  264,  265,  270,  266,  267,  271,  272,  274,  340,
  347,  274,  347,  274,  347,  274,  347,  280,  340,  346,
  346,  279,  344,  344,  344,  344,  344,  344,  344,  344,
  340,  350,  257,  257,  340,  351,  340,  352,  352,  257,
  257,  257,  257,  257,  257,  257,  257,  257,  257,  257,
  257,  257,  257,  257,  257,  257,  257,  257,  257,  257,
  278,  340,  358,  359,  361,  364,  356,  340,  360,  363,
  361,  275,  362,  257,  257,  259,  257,  262,  341,  341,
  342,  342,  342,  343,  343,  343,  343,  347,  259,  280,
  340,  348,  257,  347,  257,  347,  257,  347,  257,  261,
  274,  347,  274,  347,  280,  340,  345,  345,  345,  345,
  345,  345,  345,  345,  257,  257,  257,  259,  280,  340,
  357,  257,  259,  257,  259,  257,  257,  259,  257,  257,
  257,  362,  257,  348,  261,  257,  257,  257,  340,  347,
  257,  347,  257,  261,  346,  346,  346,  346,  346,  346,
  346,  346,  357,  261,  257,  361,  361,  364,  363,  340,
  262,  257,  257,  275,  281,  282,  283,  284,  285,  286,
  287,  349,  349,  349,  349,  349,  349,  349,  349,  257,
  340,  262,  262,  257,  257,  257,  257,  257,  257,  257,
  257,  262,
};
#endif /* YYDESTRUCT_CALL || YYSTYPE_TOSTRING */
static const YYINT yydgoto[] = {                          4,
   90,   17,   18,   19,  103,  187,  100,   91,  172,  252,
  112,  116,  118,    5,    6,    7,   72,  201,  143,  144,
  149,  145,   73,  150,  146,
};
static const YYINT yysindex[] = {                      -248,
    0, -255,  487,    0, -246,    0,   79,    0,  487,  487,
 -249, -249, -249,    0,    0, -236, -187, -158,    0,    0,
    0,    0, -189,  -19,  447,  452, -143, -143, -244, -244,
 -244, -244, -244, -244, -244, -244,  487, -230, -212,  487,
  487,  487, -211, -207, -197, -192, -184, -175, -147, -146,
 -132, -129, -128, -116, -113,  -78,  -77,  -74,  -64,  -60,
  -56,  -54,  -50, -221,  487,  487,  487, -239,  487,  -49,
 -252, -178,    0, -227, -142,    0,    0,    0,    0,  487,
  487,  487,  487,  487, -249, -249, -249, -249,  487,  384,
  -47,  487,  -42,  487,  -39,  487,  -38, -193, -252,  467,
  472,    0,  158,  158,  158,  158,  158,  158,  158,  158,
 -252,  -34,    0,    0, -252,  -33, -252,  -29,   86,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0, -252, -161, -160,    0,    0, -107, -252,  -95,    0,
  -27,  -17,  -16,    0,    0,  487,    0,    0, -187, -187,
 -158, -158, -158,    0,    0,    0,    0,  -13,  390, -191,
 -252,    0,    0,   -9,    0,   -8,    0,   -5,    0,  487,
  487,   18,  487,   27,    3, -252, -143, -143, -143, -143,
 -143, -143, -143, -143,    0,    0,    0,  407,   24, -252,
   29,    0,  487,    0, -221,    0,    0,  487,    0,    0,
    0,    0,    0,    0,  487,    0,    0,    0, -123,   30,
    0,   31,    0,  -22,   -4,   -4,   -4,   -4,   -4,   -4,
   -4,   -4,   81,  487,    0,    0,    0,    0,    0,  -87,
    0,    0,    0,   77,    0,    0,    0,    0,    0,    0,
    0,   84,   85,   89,   91,   92,   96,   98,  100,    0,
  -70,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,
};
static const YYINT yyrindex[] = {                       153,
    0,    0,    0,    0,    1,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0, -126,  -48,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  413,  413,
  413,  413,  413,  413,  413,  413,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  -94,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  101,
    0,    0,    0,    0,    0,    0,    0,    0,  -14,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  103,    0,    0,    0,  105,    0, -206,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  -81,    0,    0,    0,    0,    0,  -63,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  324,  355,
  231,  262,  293,    0,    0,    0,    0,    0,    0,    0,
  107,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  430,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  108,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  159,  159,  159,  159,  159,  159,
  159,  159,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,
};
#if YYBTYACC
static const YYINT yycindex[] = {                         0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,
};
#endif
static const YYINT yygindex[] = {                         0,
   -3,  -58,  -69,    7,  666,  649,  -20,   23,   88,  539,
    0,    0,  378,    0,  416,    0,  359,  227,    0,    0,
    0,  -65,  -66,  219,  224,
};
#define YYTABLESIZE 771
static const YYINT yytable[] = {                         16,
    1,  151,  153,   71,    8,   74,   75,  101,    1,   20,
    1,   10,  161,  162,  163,   80,   81,   76,   77,   78,
   79,  159,  160,   99,   99,   14,  113,   15,    2,  157,
    2,   80,   81,  111,  102,  152,  115,  117,  117,   10,
   80,   81,   11,   12,  114,  120,   93,   95,   97,  121,
   90,   13,   90,   14,   90,   15,  141,   90,   90,  122,
  142,   71,  148,  142,  123,   71,   90,  180,   90,  215,
   90,   10,  124,   90,   11,   12,   82,   83,  155,    9,
  156,  125,   84,   13,   89,   14,  171,   15,    3,  212,
    3,  164,  165,  166,  167,  202,  204,  203,  205,  186,
  186,  186,  186,  186,  186,  186,  186,   85,   86,  126,
  127,  168,   87,   88,  174,  200,  176,   10,  178,  158,
   11,   12,  182,  184,  128,   80,   81,  129,  130,   13,
   91,   14,   91,   15,   91,   91,   98,  236,  241,  237,
  131,   91,   91,  132,   80,   81,   91,   91,   91,  206,
   91,  156,   71,   91,   91,   91,   91,   91,   91,   91,
   91,  207,  113,  208,  113,  171,  225,  226,  227,  228,
  229,  230,  231,  232,  262,  110,  219,  110,  133,  134,
   80,   81,  135,   99,   99,   99,   99,   99,   99,   99,
   99,  272,  136,  116,  200,  116,  137,   80,   81,  142,
  138,  142,  139,  220,  148,  222,  140,  154,   94,  173,
   94,  240,   94,   94,  175,   94,   94,  177,  179,   94,
   94,   94,  195,  196,   94,   94,   94,  197,   94,  209,
  261,   94,   94,   94,   94,   94,   94,   94,   94,  210,
  211,   10,   84,  213,   11,   12,   84,  216,  217,   84,
   84,  218,  244,   13,   92,   14,  214,   15,   84,   84,
   84,   66,   84,  224,   66,   66,   84,   84,   84,   84,
   84,   84,   84,   66,  221,   66,  245,  246,  247,  248,
  249,  250,  251,  223,  234,  235,  242,  243,   66,   66,
   66,   66,   66,   66,   66,   66,   66,   66,   66,   66,
   66,   66,   66,   66,   66,   66,   66,   66,   66,   66,
   66,   66,   66,   66,   66,   66,   66,   66,   66,   66,
   66,   66,   66,   66,   66,   66,   66,   66,   66,   66,
   66,   66,   66,   66,   66,   22,   66,  260,  263,   10,
  264,  265,   11,   12,  198,  266,   10,  267,  268,   11,
   12,   13,  269,   14,  270,   15,  271,   86,   13,  109,
   14,   89,   15,   80,   78,  199,   23,   24,   25,   26,
   27,   28,   29,   30,   31,   32,   33,   34,   35,   36,
   37,   38,   39,   40,   41,   42,   43,   44,   45,   46,
   47,   48,   49,   50,   51,   52,   53,   54,   55,   56,
   57,   58,   59,   60,   61,   62,   63,   64,   65,   66,
   67,   68,   69,   66,   70,   70,   66,   66,   10,  119,
   21,   11,   12,  147,  233,   66,  239,   66,  238,    0,
   13,    0,   14,    0,   15,    0,    0,  185,    0,    0,
   66,   66,   66,   66,   66,   66,   66,   66,   66,   66,
   66,   66,   66,   66,   66,   66,   66,   66,   66,   66,
   66,   66,   66,   66,   66,   66,   66,   66,   66,   66,
   66,   66,   66,   66,   66,   66,   66,   66,   66,   66,
   66,   66,   66,   66,   66,   66,   66,   95,   66,   95,
    0,   95,   95,    0,   95,   95,    0,    0,   95,   95,
   95,    0,    0,   95,   95,   95,    0,   95,    0,    0,
   95,   95,   95,   95,   95,   95,   95,   95,   96,    0,
   96,    0,   96,   96,    0,   96,   96,    0,    0,   96,
   96,   96,    0,    0,   96,   96,   96,    0,   96,    0,
    0,   96,   96,   96,   96,   96,   96,   96,   96,   97,
    0,   97,    0,   97,   97,    0,   97,   97,    0,    0,
   97,   97,   97,    0,    0,   97,   97,   97,    0,   97,
    0,    0,   97,   97,   97,   97,   97,   97,   97,   97,
   92,    0,   92,    0,   92,   92,    0,    0,    0,    0,
    0,   92,   92,    0,    0,    0,   92,   92,   92,    0,
   92,    0,    0,   92,   92,   92,   92,   92,   92,   92,
   92,   93,    0,   93,    0,   93,   93,    0,    0,    0,
    0,    0,   93,   93,    0,    0,    0,   93,   93,   93,
    0,   93,    0,    0,   93,   93,   93,   93,   93,   93,
   93,   93,  169,    0,   10,    0,    0,   11,   12,    0,
   10,   80,   81,   11,   12,    0,   13,    0,   14,    0,
   15,    0,   13,  170,   14,    0,   15,   10,    0,  170,
   11,   12,    0,   68,    0,    0,   68,   68,    0,   13,
    0,   14,    0,   15,    0,   68,  199,   68,    0,   68,
   82,    0,   68,   82,   82,  104,  105,  106,  107,  108,
  109,  110,   82,    0,   82,    0,   82,   10,    0,   82,
   11,   12,   10,    0,    0,   11,   12,    0,    0,   13,
   94,   14,    0,   15,   13,   96,   14,   10,   15,    0,
   11,   12,   10,    0,    0,   11,   12,    0,    0,   13,
  181,   14,    0,   15,   13,  183,   14,   10,   15,    0,
   11,   12,  188,  189,  190,  191,  192,  193,  194,   13,
    0,   14,    0,   15,  253,  254,  255,  256,  257,  258,
  259,
};
static const YYINT yycheck[] = {                          3,
    0,   67,   69,    7,  260,    9,   10,   28,  257,  256,
  257,  261,   82,   83,   84,  268,  269,   11,   12,   13,
  257,   80,   81,   27,   28,  275,  257,  277,  277,  257,
  277,  268,  269,   37,  279,  275,   40,   41,   42,  261,
  268,  269,  264,  265,  257,  257,   24,   25,   26,  257,
  257,  273,  259,  275,  261,  277,  278,  264,  265,  257,
   64,   65,   66,   67,  257,   69,  273,  261,  275,  261,
  277,  261,  257,  280,  264,  265,  264,  265,  257,  335,
  259,  257,  270,  273,  274,  275,   90,  277,  337,  156,
  337,   85,   86,   87,   88,  257,  257,  259,  259,  103,
  104,  105,  106,  107,  108,  109,  110,  266,  267,  257,
  257,   89,  271,  272,   92,  119,   94,  261,   96,  262,
  264,  265,  100,  101,  257,  268,  269,  257,  257,  273,
  257,  275,  259,  277,  261,  262,  280,  203,  262,  205,
  257,  268,  269,  257,  268,  269,  273,  274,  275,  257,
  277,  259,  156,  280,  281,  282,  283,  284,  285,  286,
  287,  257,  257,  259,  259,  169,  187,  188,  189,  190,
  191,  192,  193,  194,  262,  257,  180,  259,  257,  257,
  268,  269,  257,  187,  188,  189,  190,  191,  192,  193,
  194,  262,  257,  257,  198,  259,  257,  268,  269,  203,
  257,  205,  257,  181,  208,  183,  257,  257,  257,  257,
  259,  215,  261,  262,  257,  264,  265,  257,  257,  268,
  269,  270,  257,  257,  273,  274,  275,  257,  277,  257,
  234,  280,  281,  282,  283,  284,  285,  286,  287,  257,
  257,  261,  257,  257,  264,  265,  261,  257,  257,  264,
  265,  257,  275,  273,  274,  275,  169,  277,  273,  274,
  275,  261,  277,  261,  264,  265,  281,  282,  283,  284,
  285,  286,  287,  273,  257,  275,  281,  282,  283,  284,
  285,  286,  287,  257,  261,  257,  257,  257,  288,  289,
  290,  291,  292,  293,  294,  295,  296,  297,  298,  299,
  300,  301,  302,  303,  304,  305,  306,  307,  308,  309,
  310,  311,  312,  313,  314,  315,  316,  317,  318,  319,
  320,  321,  322,  323,  324,  325,  326,  327,  328,  329,
  330,  331,  332,  333,  334,  257,  336,  257,  262,  261,
  257,  257,  264,  265,  259,  257,  261,  257,  257,  264,
  265,  273,  257,  275,  257,  277,  257,  257,  273,  257,
  275,  257,  277,  257,  257,  280,  288,  289,  290,  291,
  292,  293,  294,  295,  296,  297,  298,  299,  300,  301,
  302,  303,  304,  305,  306,  307,  308,  309,  310,  311,
  312,  313,  314,  315,  316,  317,  318,  319,  320,  321,
  322,  323,  324,  325,  326,  327,  328,  329,  330,  331,
  332,  333,  334,  261,  336,  257,  264,  265,  261,   42,
    5,  264,  265,   65,  198,  273,  208,  275,  205,   -1,
  273,   -1,  275,   -1,  277,   -1,   -1,  280,   -1,   -1,
  288,  289,  290,  291,  292,  293,  294,  295,  296,  297,
  298,  299,  300,  301,  302,  303,  304,  305,  306,  307,
  308,  309,  310,  311,  312,  313,  314,  315,  316,  317,
  318,  319,  320,  321,  322,  323,  324,  325,  326,  327,
  328,  329,  330,  331,  332,  333,  334,  257,  336,  259,
   -1,  261,  262,   -1,  264,  265,   -1,   -1,  268,  269,
  270,   -1,   -1,  273,  274,  275,   -1,  277,   -1,   -1,
  280,  281,  282,  283,  284,  285,  286,  287,  257,   -1,
  259,   -1,  261,  262,   -1,  264,  265,   -1,   -1,  268,
  269,  270,   -1,   -1,  273,  274,  275,   -1,  277,   -1,
   -1,  280,  281,  282,  283,  284,  285,  286,  287,  257,
   -1,  259,   -1,  261,  262,   -1,  264,  265,   -1,   -1,
  268,  269,  270,   -1,   -1,  273,  274,  275,   -1,  277,
   -1,   -1,  280,  281,  282,  283,  284,  285,  286,  287,
  257,   -1,  259,   -1,  261,  262,   -1,   -1,   -1,   -1,
   -1,  268,  269,   -1,   -1,   -1,  273,  274,  275,   -1,
  277,   -1,   -1,  280,  281,  282,  283,  284,  285,  286,
  287,  257,   -1,  259,   -1,  261,  262,   -1,   -1,   -1,
   -1,   -1,  268,  269,   -1,   -1,   -1,  273,  274,  275,
   -1,  277,   -1,   -1,  280,  281,  282,  283,  284,  285,
  286,  287,  259,   -1,  261,   -1,   -1,  264,  265,   -1,
  261,  268,  269,  264,  265,   -1,  273,   -1,  275,   -1,
  277,   -1,  273,  280,  275,   -1,  277,  261,   -1,  280,
  264,  265,   -1,  261,   -1,   -1,  264,  265,   -1,  273,
   -1,  275,   -1,  277,   -1,  273,  280,  275,   -1,  277,
  261,   -1,  280,  264,  265,   30,   31,   32,   33,   34,
   35,   36,  273,   -1,  275,   -1,  277,  261,   -1,  280,
  264,  265,  261,   -1,   -1,  264,  265,   -1,   -1,  273,
  274,  275,   -1,  277,  273,  274,  275,  261,  277,   -1,
  264,  265,  261,   -1,   -1,  264,  265,   -1,   -1,  273,
  274,  275,   -1,  277,  273,  274,  275,  261,  277,   -1,
  264,  265,  104,  105,  106,  107,  108,  109,  110,  273,
   -1,  275,   -1,  277,  226,  227,  228,  229,  230,  231,
  232,
};
#if YYBTYACC
static const YYINT yyctable[] = {                        -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
};
#endif
#define YYFINAL 4
#ifndef YYDEBUG
#define YYDEBUG 1
#endif
#define YYMAXTOKEN 337
#define YYUNDFTOKEN 365
#define YYTRANSLATE(a) ((a) > YYMAXTOKEN ? YYUNDFTOKEN : (a))
#if YYDEBUG
static const char *const yyname[] = {

"$end",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"error","EOL","HASH","COMMA","COLON",
"LPAREN","RPAREN","QUOTE","PLUS","MINUS","ASTERISK","SLASH","SHL","SHR",
"AMPERSAND","BAR","CARET","TILDE","AT","IMM","REG","SYM","CHR","ARITH","AC",
"SKP","SZC","SNC","SZR","SNR","SEZ","SBN","JMP","JSR","DSZ","ISZ","LDA","STA",
"COM","NEG","MOV","INC","ADC","SUB","ADD","AND","CYCLE","MUL","DIV","JSRII",
"JSRIS","CONVERT","DIR","EIR","BRI","RCLK","SIO","BLT","BLKS","SIT","JMPRAM",
"RDRAM","WRTRAM","DIRS","VERS","DREAD","DWRITE","DEXCH","DIAGNOSE1","DIAGNOSE2",
"BITBLT","XMLDA","XMSTA","DB","DW","DD","DS","ALIGN","END","EQU","EVEN","ORG",
"$accept","file","expr","simple","term","factor","arith","SrcAC","DstAC","ea",
"ac23","skip","imm4","disp","rel8","line","token","symdef","imm16list","ac2",
"imm8list","strlist","imm32list","imm8","imm16","imm32","str","illegal-symbol",
};
static const char *const yyrule[] = {
"$accept : file",
"file : line",
"file : line error",
"line : line token",
"line : token",
"token : EOL",
"token : symdef EOL",
"token : symdef imm16list EOL",
"token : SYM EQU expr EOL",
"token : symdef JMP ea EOL",
"token : symdef JMP AT ea EOL",
"token : symdef JSR ea EOL",
"token : symdef JSR AT ea EOL",
"token : symdef ISZ ea EOL",
"token : symdef ISZ AT ea EOL",
"token : symdef DSZ ea EOL",
"token : symdef DSZ AT ea EOL",
"token : symdef LDA DstAC ea EOL",
"token : symdef LDA DstAC AT ea EOL",
"token : symdef STA DstAC ea EOL",
"token : symdef STA DstAC AT ea EOL",
"token : symdef COM arith SrcAC DstAC skip EOL",
"token : symdef NEG arith SrcAC DstAC skip EOL",
"token : symdef MOV arith SrcAC DstAC skip EOL",
"token : symdef INC arith SrcAC DstAC skip EOL",
"token : symdef ADC arith SrcAC DstAC skip EOL",
"token : symdef SUB arith SrcAC DstAC skip EOL",
"token : symdef ADD arith SrcAC DstAC skip EOL",
"token : symdef AND arith SrcAC DstAC skip EOL",
"token : symdef CYCLE imm4 EOL",
"token : symdef MUL EOL",
"token : symdef DIV EOL",
"token : symdef JSRII disp EOL",
"token : symdef JSRIS rel8 EOL",
"token : symdef CONVERT rel8 ac2 EOL",
"token : symdef CONVERT rel8 COMMA ac2 EOL",
"token : symdef DIR EOL",
"token : symdef EIR EOL",
"token : symdef BRI EOL",
"token : symdef RCLK EOL",
"token : symdef SIO EOL",
"token : symdef BLT EOL",
"token : symdef BLKS EOL",
"token : symdef SIT EOL",
"token : symdef JMPRAM EOL",
"token : symdef RDRAM EOL",
"token : symdef WRTRAM EOL",
"token : symdef DIRS EOL",
"token : symdef VERS EOL",
"token : symdef DREAD EOL",
"token : symdef DWRITE EOL",
"token : symdef DEXCH EOL",
"token : symdef DIAGNOSE1 EOL",
"token : symdef DIAGNOSE2 EOL",
"token : symdef BITBLT EOL",
"token : symdef XMLDA EOL",
"token : symdef XMSTA EOL",
"token : symdef DB imm8list EOL",
"token : symdef DB strlist EOL",
"token : symdef DW imm16list EOL",
"token : symdef DD imm32list EOL",
"token : symdef DS imm8 EOL",
"token : ORG expr EOL",
"token : symdef ALIGN IMM EOL",
"token : symdef EVEN EOL",
"token : symdef END imm16 EOL",
"symdef :",
"symdef : SYM COLON",
"arith :",
"arith : ARITH",
"skip :",
"skip : SKP",
"skip : SZC",
"skip : SNC",
"skip : SZR",
"skip : SNR",
"skip : SEZ",
"skip : SBN",
"ac2 : expr",
"ac2 : AC LPAREN expr RPAREN",
"ac23 : expr",
"ac23 : AC LPAREN expr RPAREN",
"SrcAC : expr",
"SrcAC : AC LPAREN IMM RPAREN",
"DstAC : expr",
"DstAC : AC LPAREN expr RPAREN",
"ea : expr",
"ea : expr ac23",
"ea : expr COMMA ac23",
"disp : expr",
"rel8 : expr",
"expr : simple",
"expr : expr SHL simple",
"expr : expr SHR simple",
"simple : term",
"simple : simple PLUS term",
"simple : simple MINUS term",
"simple : simple AMPERSAND term",
"term : factor",
"term : PLUS factor",
"term : MINUS factor",
"term : TILDE factor",
"term : term ASTERISK factor",
"term : term SLASH factor",
"term : term BAR factor",
"term : term CARET factor",
"factor : IMM",
"factor : SYM",
"factor : LPAREN expr RPAREN",
"imm4 : expr",
"imm8 : expr",
"imm8list : imm8list COMMA imm8",
"imm8list : imm8",
"imm16 : expr",
"imm16list : imm16list COMMA imm16",
"imm16list : imm16",
"imm32 : expr",
"imm32list : imm32list COMMA imm32",
"imm32list : imm32",
"str : CHR",
"str : imm8",
"strlist : strlist COMMA str",
"strlist : str",

};
#endif

#if YYDEBUG
int      yydebug;
#endif

int      yyerrflag;
int      yychar;
YYSTYPE  yyval;
YYSTYPE  yylval;
int      yynerrs;

#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
YYLTYPE  yyloc; /* position returned by actions */
YYLTYPE  yylloc; /* position from the lexer */
#endif

#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
#ifndef YYLLOC_DEFAULT
#define YYLLOC_DEFAULT(loc, rhs, n) \
do \
{ \
    if (n == 0) \
    { \
        (loc).first_line   = YYRHSLOC(rhs, 0).last_line; \
        (loc).first_column = YYRHSLOC(rhs, 0).last_column; \
        (loc).last_line    = YYRHSLOC(rhs, 0).last_line; \
        (loc).last_column  = YYRHSLOC(rhs, 0).last_column; \
    } \
    else \
    { \
        (loc).first_line   = YYRHSLOC(rhs, 1).first_line; \
        (loc).first_column = YYRHSLOC(rhs, 1).first_column; \
        (loc).last_line    = YYRHSLOC(rhs, n).last_line; \
        (loc).last_column  = YYRHSLOC(rhs, n).last_column; \
    } \
} while (0)
#endif /* YYLLOC_DEFAULT */
#endif /* defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED) */
#if YYBTYACC

#ifndef YYLVQUEUEGROWTH
#define YYLVQUEUEGROWTH 32
#endif
#endif /* YYBTYACC */

/* define the initial stack-sizes */
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH  YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 10000
#define YYMAXDEPTH  10000
#endif
#endif

#ifndef YYINITSTACKSIZE
#define YYINITSTACKSIZE 200
#endif

typedef struct {
    unsigned stacksize;
    YYINT    *s_base;
    YYINT    *s_mark;
    YYINT    *s_last;
    YYSTYPE  *l_base;
    YYSTYPE  *l_mark;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    YYLTYPE  *p_base;
    YYLTYPE  *p_mark;
#endif
} YYSTACKDATA;
#if YYBTYACC

struct YYParseState_s
{
    struct YYParseState_s *save;    /* Previously saved parser state */
    YYSTACKDATA            yystack; /* saved parser stack */
    int                    state;   /* saved parser state */
    int                    errflag; /* saved error recovery status */
    int                    lexeme;  /* saved index of the conflict lexeme in the lexical queue */
    YYINT                  ctry;    /* saved index in yyctable[] for this conflict */
};
typedef struct YYParseState_s YYParseState;
#endif /* YYBTYACC */
/* variables for the parser stack */
static YYSTACKDATA yystack;
#if YYBTYACC

/* Current parser state */
static YYParseState *yyps = 0;

/* yypath != NULL: do the full parse, starting at *yypath parser state. */
static YYParseState *yypath = 0;

/* Base of the lexical value queue */
static YYSTYPE *yylvals = 0;

/* Current position at lexical value queue */
static YYSTYPE *yylvp = 0;

/* End position of lexical value queue */
static YYSTYPE *yylve = 0;

/* The last allocated position at the lexical value queue */
static YYSTYPE *yylvlim = 0;

#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
/* Base of the lexical position queue */
static YYLTYPE *yylpsns = 0;

/* Current position at lexical position queue */
static YYLTYPE *yylpp = 0;

/* End position of lexical position queue */
static YYLTYPE *yylpe = 0;

/* The last allocated position at the lexical position queue */
static YYLTYPE *yylplim = 0;
#endif

/* Current position at lexical token queue */
static YYINT  *yylexp = 0;

static YYINT  *yylexemes = 0;
#endif /* YYBTYACC */
#line 600 "tools/aasm.y"

int list(char * fmt, ...)
{
	va_list arg;
	int rc = 0;

	if (!f_list)
		return rc;
	if (pass_no < 2)
		return rc;
	va_start(arg, fmt);
	rc = vfprintf(lstfile, fmt, arg);
	va_end(arg);
	return rc;
}

int outw(word c)
{
	int rc = 0;
	if (pass_no == 1) {
		pc++;
		return rc;
	}
	if (f_octal)
		rc = list("%06o ", c);
	else
		rc = list("%04x ", c);
	if (f_dump) {
		if (pc != pcmax || 0 == (pcmax % 4)) {
			if (-1 != pcmax)
				fprintf(outfile, "\n");
			fprintf(outfile, "%07o:", pc);
			pcmax = pc;
		}
		fprintf(outfile, " %07o", c);
		pcmax = ++pc;
	} else {
		if (pc > alloc) {
			alloc = (pc | 0xffff) + 1;
			image = (word *)realloc(image, alloc * sizeof(word));
			if (!image) {
				fprintf(stderr, "fatal: could not realloc() %d words of memory\n",
					alloc);
				exit(1);
			}
		}
		image[pc] = c;
		pc++;
		if (pc > pcmax)
			pcmax = pc;
	}
	return rc;
}

void emit(void)
{
	int i;
	int x = 0;

	if (arglow) {
		argcnt++;
		arglow = 0;
	}

	if (cmdflg || argcnt) {
		if (f_octal)
			x += list("%06o: ", pc);
		else
			x += list("%04x: ", pc);
	}

	if (cmdflg)
		x += outw(cmd);
	for (i = 0; i < argcnt && i < 4; i++)
		x += outw(arg[i]);
	if (strchr(lstbuff, '\n')) {
		if (!(cmdflg || argcnt) && expflg) {
			if (f_octal)
				x += list("=%06o ", eexp);
			else
				x += list("=%04x ", eexp);
		}
		if (x >= 0 && x < 24)
			list("%*s", 24 - x, " ");
		list("%s", lstbuff);
	}
	if (argcnt > 4) {
		for (i = 4; i < argcnt; i++) {
			if ((i & 3) == 0) {
				if (f_octal)
					x = list("%06o: ", pc);
				else
					x = list("%04x: ", pc);
			}
			x += outw(arg[i]);
			if ((i & 3) == 3)
				x += list("\n");
		}
		if (i & 3)
			x += list("\n");
	}
	cmd = 0;
	arg[0] = 0;
	expflg = 0;
	cmdflg = 1;
	argcnt = 0;
	arglow = 0;
}

void addsym(char * name, int value)
{
	SYM_t *s, *s0, *s1;
	for (s = sym; (s); s = s->next) {
		if (strcasecmp(name, s->name) == 0) {
			if (s->pass_no == pass_no)
				fprintf(stderr, "line (%d) warning: double defined symbol %s\n",
					line_no, name);
			s->line_no[0] = line_no;
			s->pass_no = pass_no;
			if (s->value != value)
				fprintf(stderr, "line (%d) warning: %s has different value on pass 2\n",
					line_no, name);
			s->value   = value;
			return;
		}
	}
	for (s0 = NULL, s1 = sym; (s1); s0 = s1, s1 = s1->next)
		if (strcasecmp(name, s1->name) <= 0)
			break;
	s = (SYM_t *) calloc(1, sizeof(SYM_t));
	if (!s) {
		fprintf(stderr, "error: out of memory!\n");
		exit(1);
	}
	s->next = s1;
	s->pass_no = pass_no;
	s->refs = 0;
	s->line_no = malloc(sizeof(int));
	*s->line_no = line_no;
	s->value = value;
	s->name = strdup(name);
	if (s0)
		s0->next = s;
	else
		sym = s;
	symb_no++;
}

int getsym(char * name)
{
	SYM_t *s;
	for (s = sym; (s); s = s->next) {
		if (strcasecmp(name, s->name) == 0) {
			if (pass_no > 1) {
				s->refs += 1;
				s->line_no = (int *) realloc(s->line_no, (s->refs + 1) * sizeof(int));
				s->line_no[s->refs] = line_no;
			}
			return s->value;
		}
	}
	if (pass_no > 1)
		fprintf(stderr, "line (%d) undefined symbol: %s\n",
			line_no, name);
	return 0;
}

void prtsym(FILE * filp)
{
	SYM_t * s;
	int i;
	for (s = sym; (s); s = s->next) {
		fprintf(filp, "%-32.32s%04X line %d, %d references\n",
			s->name, s->value, s->line_no[0], s->refs);
		if (f_xref) {
			if (s->refs > 0) {
				for (i = 0; i < s->refs; i++) {
					if ((i & 7) == 0)
						fprintf(filp, "\t");
					if (i > 0)
						fprintf(filp, ",");
					fprintf(filp, "%d", s->line_no[i+1]);
					if ((i & 7) == 7)
						fprintf(filp,"\n");
					}
				if (i & 7)
					fprintf(filp, "\n");
			}
		}
	}
}

int main(int ac, char ** av)
{
	int i;
	char * p;

	if (ac < 2) {
		fprintf(stderr, "usage:\t%s [options] input[.asm] [output[.bin]] [filename[.lst]]\n", av[0]);
		fprintf(stderr, "options can be one or more of:\n");
		fprintf(stderr, "-a\tgenerate octal dump instead of binary\n");
		fprintf(stderr, "-l\tgenerate listing (to file input.lst)\n");
		fprintf(stderr, "-s\toutput symbol table\n");
		fprintf(stderr, "-o\tprint octal addresses and opcodes in listing\n");
		fprintf(stderr, "-x\toutput cross reference with symbol table (implies -s)\n");
#if	ASM_DEBUG
		fprintf(stderr, "-d\tgenerate parser debug output to stderr\n");
#endif
		exit(1);
	}
	for (i = 1; i < ac; i++) {
		if (av[i][0] == '-') {
			switch (av[i][1]) {
			case 'a':
				f_dump = 1;
				break;
			case 'l':
				f_list = 1;
				break;
			case 'h':
				f_octal = 0;
				break;
			case 's':
				f_syms = 1;
				break;
			case 'x':
				f_syms = 1;
				f_xref = 1;
				break;
			case 'o':
				if (++i >= ac) {
					fprintf(stderr, "-o output filename missing\n");
					exit(1);
				}
				snprintf(outname, sizeof(outname), "%s", av[i]);
				break;
#if	ASM_DEBUG
			case 'd':
				yydebug = 1;
				break;
#endif
			default:
				fprintf(stderr, "illegal option %s\n", av[i]);
				exit(1);
			}
		} else if (!strlen(inpname)) {
			snprintf(inpname, sizeof(inpname), "%s", av[i]);
		} else if (!strlen(outname)) {
			snprintf(outname, sizeof(outname), "%s", av[i]);
		} else if (!strlen(lstname)) {
			snprintf(lstname, sizeof(lstname), "%s", av[i]);
		} else {
			fprintf(stderr, "additional argument %s ignored\n", av[i]);
		}
	}
	if (!strlen(inpname)) {
		fprintf(stderr, "input filename missing!\n");
		exit(1);
	}
	if (!strlen(outname)) {
		strcpy(outname, inpname);
		p = strrchr(outname, '.');
		if (f_dump) {
			if (p)
				strcpy(p, ".oct");
			else
				strcat(outname, ".oct");
		} else {
			if (p)
				strcpy(p, ".bin");
			else
				strcat(outname, ".bin");
		}
	}
	if (f_list) {
		if (!strlen(lstname)) {
			strcpy(lstname, inpname);
			p = strrchr(lstname, '.');
			if (p)
				strcpy(p, ".lst");
			else
				strcat(lstname, ".lst");
		}
	} else if (strlen(lstname)) {
		f_list = 1;
		p = strrchr(lstname, '.');
		if (p)
			strcpy(p, ".lst");
		else
			strcat(lstname, ".lst");
	}
	p = strrchr(inpname, '.');
	if (!p)
		strcat(inpname, ".asm");
	inpfile = fopen(inpname, "r");
	if (!inpfile) {
		fprintf(stderr, "can't open %s\n", inpname);
		exit(1);
	}
	outfile = fopen(outname, "wb");
	if (!outfile) {
		fprintf(stderr, "can't create %s\n", outname);
		exit(1);
	}
	if (f_list) {
		lstfile = fopen(lstname, "w");
		if (!lstfile) {
			fprintf(stderr, "can't create %s\n", outname);
			exit(1);
		}
		plst = lstbuff;
		*plst = '\0';
	}
	printf("assembling %s\npass 1\n", inpname);
	yyrestart(inpfile);
	yyparse();
	list("\n");
	if (f_syms)
		prtsym((f_list) ? lstfile : stdout);
	fclose(inpfile);
	if (!f_dump) {
		if (pcmax != fwrite(image, sizeof(word), pcmax, outfile)) {
			fprintf(stderr, "error writing output %s\n", outname);
			exit(1);
		}
	}
	fclose(outfile);
	if (f_list)
		fclose(lstfile);
	printf("%d lines, %d symbols\n", line_no, symb_no);

	return 0;
}
#line 1286 "aasm.tab.c"

/* For use in generated program */
#define yydepth (int)(yystack.s_mark - yystack.s_base)
#if YYBTYACC
#define yytrial (yyps->save)
#endif /* YYBTYACC */

#if YYDEBUG
#include <stdio.h>	/* needed for printf */
#endif

#include <stdlib.h>	/* needed for malloc, etc */
#include <string.h>	/* needed for memset */

/* allocate initial stack or double stack size, up to YYMAXDEPTH */
static int yygrowstack(YYSTACKDATA *data)
{
    int i;
    unsigned newsize;
    YYINT *newss;
    YYSTYPE *newvs;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    YYLTYPE *newps;
#endif

    if ((newsize = data->stacksize) == 0)
        newsize = YYINITSTACKSIZE;
    else if (newsize >= YYMAXDEPTH)
        return YYENOMEM;
    else if ((newsize *= 2) > YYMAXDEPTH)
        newsize = YYMAXDEPTH;

    i = (int) (data->s_mark - data->s_base);
    newss = (YYINT *)realloc(data->s_base, newsize * sizeof(*newss));
    if (newss == 0)
        return YYENOMEM;

    data->s_base = newss;
    data->s_mark = newss + i;

    newvs = (YYSTYPE *)realloc(data->l_base, newsize * sizeof(*newvs));
    if (newvs == 0)
        return YYENOMEM;

    data->l_base = newvs;
    data->l_mark = newvs + i;

#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    newps = (YYLTYPE *)realloc(data->p_base, newsize * sizeof(*newps));
    if (newps == 0)
        return YYENOMEM;

    data->p_base = newps;
    data->p_mark = newps + i;
#endif

    data->stacksize = newsize;
    data->s_last = data->s_base + newsize - 1;

#if YYDEBUG
    if (yydebug)
        fprintf(stderr, "%sdebug: stack size increased to %d\n", YYPREFIX, newsize);
#endif
    return 0;
}

#if YYPURE || defined(YY_NO_LEAKS)
static void yyfreestack(YYSTACKDATA *data)
{
    free(data->s_base);
    free(data->l_base);
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    free(data->p_base);
#endif
    memset(data, 0, sizeof(*data));
}
#else
#define yyfreestack(data) /* nothing */
#endif /* YYPURE || defined(YY_NO_LEAKS) */
#if YYBTYACC

static YYParseState *
yyNewState(unsigned size)
{
    YYParseState *p = (YYParseState *) malloc(sizeof(YYParseState));
    if (p == NULL) return NULL;

    p->yystack.stacksize = size;
    if (size == 0)
    {
        p->yystack.s_base = NULL;
        p->yystack.l_base = NULL;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
        p->yystack.p_base = NULL;
#endif
        return p;
    }
    p->yystack.s_base    = (YYINT *) malloc(size * sizeof(YYINT));
    if (p->yystack.s_base == NULL) return NULL;
    p->yystack.l_base    = (YYSTYPE *) malloc(size * sizeof(YYSTYPE));
    if (p->yystack.l_base == NULL) return NULL;
    memset(p->yystack.l_base, 0, size * sizeof(YYSTYPE));
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    p->yystack.p_base    = (YYLTYPE *) malloc(size * sizeof(YYLTYPE));
    if (p->yystack.p_base == NULL) return NULL;
    memset(p->yystack.p_base, 0, size * sizeof(YYLTYPE));
#endif

    return p;
}

static void
yyFreeState(YYParseState *p)
{
    yyfreestack(&p->yystack);
    free(p);
}
#endif /* YYBTYACC */

#define YYABORT  goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR  goto yyerrlab
#if YYBTYACC
#define YYVALID        do { if (yyps->save)            goto yyvalid; } while(0)
#define YYVALID_NESTED do { if (yyps->save && \
                                yyps->save->save == 0) goto yyvalid; } while(0)
#endif /* YYBTYACC */

int
YYPARSE_DECL()
{
    int yym, yyn, yystate, yyresult;
#if YYBTYACC
    int yynewerrflag;
    YYParseState *yyerrctx = NULL;
#endif /* YYBTYACC */
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    YYLTYPE  yyerror_loc_range[3]; /* position of error start/end (0 unused) */
#endif
#if YYDEBUG
    const char *yys;

    if ((yys = getenv("YYDEBUG")) != 0)
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
    if (yydebug)
        fprintf(stderr, "%sdebug[<# of symbols on state stack>]\n", YYPREFIX);
#endif
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    memset(yyerror_loc_range, 0, sizeof(yyerror_loc_range));
#endif

#if YYBTYACC
    yyps = yyNewState(0); if (yyps == 0) goto yyenomem;
    yyps->save = 0;
#endif /* YYBTYACC */
    yym = 0;
    /* yyn is set below */
    yynerrs = 0;
    yyerrflag = 0;
    yychar = YYEMPTY;
    yystate = 0;

#if YYPURE
    memset(&yystack, 0, sizeof(yystack));
#endif

    if (yystack.s_base == NULL && yygrowstack(&yystack) == YYENOMEM) goto yyoverflow;
    yystack.s_mark = yystack.s_base;
    yystack.l_mark = yystack.l_base;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    yystack.p_mark = yystack.p_base;
#endif
    yystate = 0;
    *yystack.s_mark = 0;

yyloop:
    if ((yyn = yydefred[yystate]) != 0) goto yyreduce;
    if (yychar < 0)
    {
#if YYBTYACC
        do {
        if (yylvp < yylve)
        {
            /* we're currently re-reading tokens */
            yylval = *yylvp++;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
            yylloc = *yylpp++;
#endif
            yychar = *yylexp++;
            break;
        }
        if (yyps->save)
        {
            /* in trial mode; save scanner results for future parse attempts */
            if (yylvp == yylvlim)
            {   /* Enlarge lexical value queue */
                size_t p = (size_t) (yylvp - yylvals);
                size_t s = (size_t) (yylvlim - yylvals);

                s += YYLVQUEUEGROWTH;
                if ((yylexemes = (YYINT *)realloc(yylexemes, s * sizeof(YYINT))) == NULL) goto yyenomem;
                if ((yylvals   = (YYSTYPE *)realloc(yylvals, s * sizeof(YYSTYPE))) == NULL) goto yyenomem;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                if ((yylpsns   = (YYLTYPE *)realloc(yylpsns, s * sizeof(YYLTYPE))) == NULL) goto yyenomem;
#endif
                yylvp   = yylve = yylvals + p;
                yylvlim = yylvals + s;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                yylpp   = yylpe = yylpsns + p;
                yylplim = yylpsns + s;
#endif
                yylexp  = yylexemes + p;
            }
            *yylexp = (YYINT) YYLEX;
            *yylvp++ = yylval;
            yylve++;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
            *yylpp++ = yylloc;
            yylpe++;
#endif
            yychar = *yylexp++;
            break;
        }
        /* normal operation, no conflict encountered */
#endif /* YYBTYACC */
        yychar = YYLEX;
#if YYBTYACC
        } while (0);
#endif /* YYBTYACC */
        if (yychar < 0) yychar = YYEOF;
#if YYDEBUG
        if (yydebug)
        {
            if ((yys = yyname[YYTRANSLATE(yychar)]) == NULL) yys = yyname[YYUNDFTOKEN];
            fprintf(stderr, "%s[%d]: state %d, reading token %d (%s)",
                            YYDEBUGSTR, yydepth, yystate, yychar, yys);
#ifdef YYSTYPE_TOSTRING
#if YYBTYACC
            if (!yytrial)
#endif /* YYBTYACC */
                fprintf(stderr, " <%s>", YYSTYPE_TOSTRING(yychar, yylval));
#endif
            fputc('\n', stderr);
        }
#endif
    }
#if YYBTYACC

    /* Do we have a conflict? */
    if (((yyn = yycindex[yystate]) != 0) && (yyn += yychar) >= 0 &&
        yyn <= YYTABLESIZE && yycheck[yyn] == (YYINT) yychar)
    {
        YYINT ctry;

        if (yypath)
        {
            YYParseState *save;
#if YYDEBUG
            if (yydebug)
                fprintf(stderr, "%s[%d]: CONFLICT in state %d: following successful trial parse\n",
                                YYDEBUGSTR, yydepth, yystate);
#endif
            /* Switch to the next conflict context */
            save = yypath;
            yypath = save->save;
            save->save = NULL;
            ctry = save->ctry;
            if (save->state != yystate) YYABORT;
            yyFreeState(save);

        }
        else
        {

            /* Unresolved conflict - start/continue trial parse */
            YYParseState *save;
#if YYDEBUG
            if (yydebug)
            {
                fprintf(stderr, "%s[%d]: CONFLICT in state %d. ", YYDEBUGSTR, yydepth, yystate);
                if (yyps->save)
                    fputs("ALREADY in conflict, continuing trial parse.\n", stderr);
                else
                    fputs("Starting trial parse.\n", stderr);
            }
#endif
            save                  = yyNewState((unsigned)(yystack.s_mark - yystack.s_base + 1));
            if (save == NULL) goto yyenomem;
            save->save            = yyps->save;
            save->state           = yystate;
            save->errflag         = yyerrflag;
            save->yystack.s_mark  = save->yystack.s_base + (yystack.s_mark - yystack.s_base);
            memcpy (save->yystack.s_base, yystack.s_base, (size_t) (yystack.s_mark - yystack.s_base + 1) * sizeof(YYINT));
            save->yystack.l_mark  = save->yystack.l_base + (yystack.l_mark - yystack.l_base);
            memcpy (save->yystack.l_base, yystack.l_base, (size_t) (yystack.l_mark - yystack.l_base + 1) * sizeof(YYSTYPE));
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
            save->yystack.p_mark  = save->yystack.p_base + (yystack.p_mark - yystack.p_base);
            memcpy (save->yystack.p_base, yystack.p_base, (size_t) (yystack.p_mark - yystack.p_base + 1) * sizeof(YYLTYPE));
#endif
            ctry                  = yytable[yyn];
            if (yyctable[ctry] == -1)
            {
#if YYDEBUG
                if (yydebug && yychar >= YYEOF)
                    fprintf(stderr, "%s[%d]: backtracking 1 token\n", YYDEBUGSTR, yydepth);
#endif
                ctry++;
            }
            save->ctry = ctry;
            if (yyps->save == NULL)
            {
                /* If this is a first conflict in the stack, start saving lexemes */
                if (!yylexemes)
                {
                    yylexemes = (YYINT *) malloc((YYLVQUEUEGROWTH) * sizeof(YYINT));
                    if (yylexemes == NULL) goto yyenomem;
                    yylvals   = (YYSTYPE *) malloc((YYLVQUEUEGROWTH) * sizeof(YYSTYPE));
                    if (yylvals == NULL) goto yyenomem;
                    yylvlim   = yylvals + YYLVQUEUEGROWTH;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                    yylpsns   = (YYLTYPE *) malloc((YYLVQUEUEGROWTH) * sizeof(YYLTYPE));
                    if (yylpsns == NULL) goto yyenomem;
                    yylplim   = yylpsns + YYLVQUEUEGROWTH;
#endif
                }
                if (yylvp == yylve)
                {
                    yylvp  = yylve = yylvals;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                    yylpp  = yylpe = yylpsns;
#endif
                    yylexp = yylexemes;
                    if (yychar >= YYEOF)
                    {
                        *yylve++ = yylval;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                        *yylpe++ = yylloc;
#endif
                        *yylexp  = (YYINT) yychar;
                        yychar   = YYEMPTY;
                    }
                }
            }
            if (yychar >= YYEOF)
            {
                yylvp--;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                yylpp--;
#endif
                yylexp--;
                yychar = YYEMPTY;
            }
            save->lexeme = (int) (yylvp - yylvals);
            yyps->save   = save;
        }
        if (yytable[yyn] == ctry)
        {
#if YYDEBUG
            if (yydebug)
                fprintf(stderr, "%s[%d]: state %d, shifting to state %d\n",
                                YYDEBUGSTR, yydepth, yystate, yyctable[ctry]);
#endif
            if (yychar < 0)
            {
                yylvp++;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                yylpp++;
#endif
                yylexp++;
            }
            if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM)
                goto yyoverflow;
            yystate = yyctable[ctry];
            *++yystack.s_mark = (YYINT) yystate;
            *++yystack.l_mark = yylval;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
            *++yystack.p_mark = yylloc;
#endif
            yychar  = YYEMPTY;
            if (yyerrflag > 0) --yyerrflag;
            goto yyloop;
        }
        else
        {
            yyn = yyctable[ctry];
            goto yyreduce;
        }
    } /* End of code dealing with conflicts */
#endif /* YYBTYACC */
    if (((yyn = yysindex[yystate]) != 0) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == (YYINT) yychar)
    {
#if YYDEBUG
        if (yydebug)
            fprintf(stderr, "%s[%d]: state %d, shifting to state %d\n",
                            YYDEBUGSTR, yydepth, yystate, yytable[yyn]);
#endif
        if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM) goto yyoverflow;
        yystate = yytable[yyn];
        *++yystack.s_mark = yytable[yyn];
        *++yystack.l_mark = yylval;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
        *++yystack.p_mark = yylloc;
#endif
        yychar = YYEMPTY;
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if (((yyn = yyrindex[yystate]) != 0) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == (YYINT) yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag != 0) goto yyinrecovery;
#if YYBTYACC

    yynewerrflag = 1;
    goto yyerrhandler;
    goto yyerrlab; /* redundant goto avoids 'unused label' warning */

yyerrlab:
    /* explicit YYERROR from an action -- pop the rhs of the rule reduced
     * before looking for error recovery */
    yystack.s_mark -= yym;
    yystate = *yystack.s_mark;
    yystack.l_mark -= yym;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    yystack.p_mark -= yym;
#endif

    yynewerrflag = 0;
yyerrhandler:
    while (yyps->save)
    {
        int ctry;
        YYParseState *save = yyps->save;
#if YYDEBUG
        if (yydebug)
            fprintf(stderr, "%s[%d]: ERROR in state %d, CONFLICT BACKTRACKING to state %d, %d tokens\n",
                            YYDEBUGSTR, yydepth, yystate, yyps->save->state,
                    (int)(yylvp - yylvals - yyps->save->lexeme));
#endif
        /* Memorize most forward-looking error state in case it's really an error. */
        if (yyerrctx == NULL || yyerrctx->lexeme < yylvp - yylvals)
        {
            /* Free old saved error context state */
            if (yyerrctx) yyFreeState(yyerrctx);
            /* Create and fill out new saved error context state */
            yyerrctx                 = yyNewState((unsigned)(yystack.s_mark - yystack.s_base + 1));
            if (yyerrctx == NULL) goto yyenomem;
            yyerrctx->save           = yyps->save;
            yyerrctx->state          = yystate;
            yyerrctx->errflag        = yyerrflag;
            yyerrctx->yystack.s_mark = yyerrctx->yystack.s_base + (yystack.s_mark - yystack.s_base);
            memcpy (yyerrctx->yystack.s_base, yystack.s_base, (size_t) (yystack.s_mark - yystack.s_base + 1) * sizeof(YYINT));
            yyerrctx->yystack.l_mark = yyerrctx->yystack.l_base + (yystack.l_mark - yystack.l_base);
            memcpy (yyerrctx->yystack.l_base, yystack.l_base, (size_t) (yystack.l_mark - yystack.l_base + 1) * sizeof(YYSTYPE));
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
            yyerrctx->yystack.p_mark = yyerrctx->yystack.p_base + (yystack.p_mark - yystack.p_base);
            memcpy (yyerrctx->yystack.p_base, yystack.p_base, (size_t) (yystack.p_mark - yystack.p_base + 1) * sizeof(YYLTYPE));
#endif
            yyerrctx->lexeme         = (int) (yylvp - yylvals);
        }
        yylvp          = yylvals   + save->lexeme;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
        yylpp          = yylpsns   + save->lexeme;
#endif
        yylexp         = yylexemes + save->lexeme;
        yychar         = YYEMPTY;
        yystack.s_mark = yystack.s_base + (save->yystack.s_mark - save->yystack.s_base);
        memcpy (yystack.s_base, save->yystack.s_base, (size_t) (yystack.s_mark - yystack.s_base + 1) * sizeof(YYINT));
        yystack.l_mark = yystack.l_base + (save->yystack.l_mark - save->yystack.l_base);
        memcpy (yystack.l_base, save->yystack.l_base, (size_t) (yystack.l_mark - yystack.l_base + 1) * sizeof(YYSTYPE));
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
        yystack.p_mark = yystack.p_base + (save->yystack.p_mark - save->yystack.p_base);
        memcpy (yystack.p_base, save->yystack.p_base, (size_t) (yystack.p_mark - yystack.p_base + 1) * sizeof(YYLTYPE));
#endif
        ctry           = ++save->ctry;
        yystate        = save->state;
        /* We tried shift, try reduce now */
        if ((yyn = yyctable[ctry]) >= 0) goto yyreduce;
        yyps->save     = save->save;
        save->save     = NULL;
        yyFreeState(save);

        /* Nothing left on the stack -- error */
        if (!yyps->save)
        {
#if YYDEBUG
            if (yydebug)
                fprintf(stderr, "%sdebug[%d,trial]: trial parse FAILED, entering ERROR mode\n",
                                YYPREFIX, yydepth);
#endif
            /* Restore state as it was in the most forward-advanced error */
            yylvp          = yylvals   + yyerrctx->lexeme;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
            yylpp          = yylpsns   + yyerrctx->lexeme;
#endif
            yylexp         = yylexemes + yyerrctx->lexeme;
            yychar         = yylexp[-1];
            yylval         = yylvp[-1];
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
            yylloc         = yylpp[-1];
#endif
            yystack.s_mark = yystack.s_base + (yyerrctx->yystack.s_mark - yyerrctx->yystack.s_base);
            memcpy (yystack.s_base, yyerrctx->yystack.s_base, (size_t) (yystack.s_mark - yystack.s_base + 1) * sizeof(YYINT));
            yystack.l_mark = yystack.l_base + (yyerrctx->yystack.l_mark - yyerrctx->yystack.l_base);
            memcpy (yystack.l_base, yyerrctx->yystack.l_base, (size_t) (yystack.l_mark - yystack.l_base + 1) * sizeof(YYSTYPE));
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
            yystack.p_mark = yystack.p_base + (yyerrctx->yystack.p_mark - yyerrctx->yystack.p_base);
            memcpy (yystack.p_base, yyerrctx->yystack.p_base, (size_t) (yystack.p_mark - yystack.p_base + 1) * sizeof(YYLTYPE));
#endif
            yystate        = yyerrctx->state;
            yyFreeState(yyerrctx);
            yyerrctx       = NULL;
        }
        yynewerrflag = 1;
    }
    if (yynewerrflag == 0) goto yyinrecovery;
#endif /* YYBTYACC */

    YYERROR_CALL("syntax error");
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    yyerror_loc_range[1] = yylloc; /* lookahead position is error start position */
#endif

#if !YYBTYACC
    goto yyerrlab; /* redundant goto avoids 'unused label' warning */
yyerrlab:
#endif
    ++yynerrs;

yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if (((yyn = yysindex[*yystack.s_mark]) != 0) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == (YYINT) YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    fprintf(stderr, "%s[%d]: state %d, error recovery shifting to state %d\n",
                                    YYDEBUGSTR, yydepth, *yystack.s_mark, yytable[yyn]);
#endif
                if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM) goto yyoverflow;
                yystate = yytable[yyn];
                *++yystack.s_mark = yytable[yyn];
                *++yystack.l_mark = yylval;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                /* lookahead position is error end position */
                yyerror_loc_range[2] = yylloc;
                YYLLOC_DEFAULT(yyloc, yyerror_loc_range, 2); /* position of error span */
                *++yystack.p_mark = yyloc;
#endif
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    fprintf(stderr, "%s[%d]: error recovery discarding state %d\n",
                                    YYDEBUGSTR, yydepth, *yystack.s_mark);
#endif
                if (yystack.s_mark <= yystack.s_base) goto yyabort;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                /* the current TOS position is the error start position */
                yyerror_loc_range[1] = *yystack.p_mark;
#endif
#if defined(YYDESTRUCT_CALL)
#if YYBTYACC
                if (!yytrial)
#endif /* YYBTYACC */
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                    YYDESTRUCT_CALL("error: discarding state",
                                    yystos[*yystack.s_mark], yystack.l_mark, yystack.p_mark);
#else
                    YYDESTRUCT_CALL("error: discarding state",
                                    yystos[*yystack.s_mark], yystack.l_mark);
#endif /* defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED) */
#endif /* defined(YYDESTRUCT_CALL) */
                --yystack.s_mark;
                --yystack.l_mark;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                --yystack.p_mark;
#endif
            }
        }
    }
    else
    {
        if (yychar == YYEOF) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            if ((yys = yyname[YYTRANSLATE(yychar)]) == NULL) yys = yyname[YYUNDFTOKEN];
            fprintf(stderr, "%s[%d]: state %d, error recovery discarding token %d (%s)\n",
                            YYDEBUGSTR, yydepth, yystate, yychar, yys);
        }
#endif
#if defined(YYDESTRUCT_CALL)
#if YYBTYACC
        if (!yytrial)
#endif /* YYBTYACC */
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
            YYDESTRUCT_CALL("error: discarding token", yychar, &yylval, &yylloc);
#else
            YYDESTRUCT_CALL("error: discarding token", yychar, &yylval);
#endif /* defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED) */
#endif /* defined(YYDESTRUCT_CALL) */
        yychar = YYEMPTY;
        goto yyloop;
    }

yyreduce:
    yym = yylen[yyn];
#if YYDEBUG
    if (yydebug)
    {
        fprintf(stderr, "%s[%d]: state %d, reducing by rule %d (%s)",
                        YYDEBUGSTR, yydepth, yystate, yyn, yyrule[yyn]);
#ifdef YYSTYPE_TOSTRING
#if YYBTYACC
        if (!yytrial)
#endif /* YYBTYACC */
            if (yym > 0)
            {
                int i;
                fputc('<', stderr);
                for (i = yym; i > 0; i--)
                {
                    if (i != yym) fputs(", ", stderr);
                    fputs(YYSTYPE_TOSTRING(yystos[yystack.s_mark[1-i]],
                                           yystack.l_mark[1-i]), stderr);
                }
                fputc('>', stderr);
            }
#endif
        fputc('\n', stderr);
    }
#endif
    if (yym > 0)
        yyval = yystack.l_mark[1-yym];
    else
        memset(&yyval, 0, sizeof yyval);
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)

    /* Perform position reduction */
    memset(&yyloc, 0, sizeof(yyloc));
#if YYBTYACC
    if (!yytrial)
#endif /* YYBTYACC */
    {
        YYLLOC_DEFAULT(yyloc, &yystack.p_mark[-yym], yym);
        /* just in case YYERROR is invoked within the action, save
           the start of the rhs as the error start position */
        yyerror_loc_range[1] = yystack.p_mark[1-yym];
    }
#endif

    switch (yyn)
    {
case 3:
#line 117 "tools/aasm.y"
	{ emit(); }
#line 1959 "aasm.tab.c"
break;
case 4:
#line 118 "tools/aasm.y"
	{ emit(); }
#line 1964 "aasm.tab.c"
break;
case 5:
#line 122 "tools/aasm.y"
	{
			cmdflg = 0;
		}
#line 1971 "aasm.tab.c"
break;
case 6:
#line 126 "tools/aasm.y"
	{
			cmdflg = 0;
			expflg = 1;
			eexp = pc;
		}
#line 1980 "aasm.tab.c"
break;
case 7:
#line 132 "tools/aasm.y"
	{
			cmdflg = 0;
		}
#line 1987 "aasm.tab.c"
break;
case 8:
#line 136 "tools/aasm.y"
	{
			cmdflg = 0;
			argcnt = 0;
			expflg = 1;
			eexp = yystack.l_mark[-1].i;
			addsym(yystack.l_mark[-3].s, yystack.l_mark[-1].i);
			free(yystack.l_mark[-3].s);
		}
#line 1999 "aasm.tab.c"
break;
case 9:
#line 145 "tools/aasm.y"
	{ cmd |= op_JMP | ea_DIRECT | yystack.l_mark[-1].i; }
#line 2004 "aasm.tab.c"
break;
case 10:
#line 147 "tools/aasm.y"
	{ cmd |= op_JMP | ea_INDIRECT | yystack.l_mark[-1].i; }
#line 2009 "aasm.tab.c"
break;
case 11:
#line 149 "tools/aasm.y"
	{ cmd |= op_JSR | ea_DIRECT | yystack.l_mark[-1].i; }
#line 2014 "aasm.tab.c"
break;
case 12:
#line 151 "tools/aasm.y"
	{ cmd |= op_JSR | ea_INDIRECT | yystack.l_mark[-1].i; }
#line 2019 "aasm.tab.c"
break;
case 13:
#line 153 "tools/aasm.y"
	{ cmd |= op_ISZ | ea_DIRECT | yystack.l_mark[-1].i; }
#line 2024 "aasm.tab.c"
break;
case 14:
#line 155 "tools/aasm.y"
	{ cmd |= op_ISZ | ea_INDIRECT | yystack.l_mark[-1].i; }
#line 2029 "aasm.tab.c"
break;
case 15:
#line 157 "tools/aasm.y"
	{ cmd |= op_DSZ | ea_DIRECT | yystack.l_mark[-1].i; }
#line 2034 "aasm.tab.c"
break;
case 16:
#line 159 "tools/aasm.y"
	{ cmd |= op_DSZ | ea_INDIRECT | yystack.l_mark[-1].i; }
#line 2039 "aasm.tab.c"
break;
case 17:
#line 162 "tools/aasm.y"
	{ cmd |= op_LDA | ea_DIRECT | yystack.l_mark[-2].i | yystack.l_mark[-1].i; }
#line 2044 "aasm.tab.c"
break;
case 18:
#line 164 "tools/aasm.y"
	{ cmd |= op_LDA | ea_INDIRECT | yystack.l_mark[-3].i | yystack.l_mark[-1].i; }
#line 2049 "aasm.tab.c"
break;
case 19:
#line 166 "tools/aasm.y"
	{ cmd |= op_STA | ea_DIRECT | yystack.l_mark[-2].i | yystack.l_mark[-1].i; }
#line 2054 "aasm.tab.c"
break;
case 20:
#line 168 "tools/aasm.y"
	{ cmd |= op_STA | ea_INDIRECT | yystack.l_mark[-3].i | yystack.l_mark[-1].i; }
#line 2059 "aasm.tab.c"
break;
case 21:
#line 171 "tools/aasm.y"
	{ cmd |= op_COM | yystack.l_mark[-4].i | yystack.l_mark[-3].i | yystack.l_mark[-2].i | yystack.l_mark[-1].i; }
#line 2064 "aasm.tab.c"
break;
case 22:
#line 173 "tools/aasm.y"
	{ cmd |= op_NEG | yystack.l_mark[-4].i | yystack.l_mark[-3].i | yystack.l_mark[-2].i | yystack.l_mark[-1].i; }
#line 2069 "aasm.tab.c"
break;
case 23:
#line 175 "tools/aasm.y"
	{ cmd |= op_MOV | yystack.l_mark[-4].i | yystack.l_mark[-3].i | yystack.l_mark[-2].i | yystack.l_mark[-1].i; }
#line 2074 "aasm.tab.c"
break;
case 24:
#line 177 "tools/aasm.y"
	{ cmd |= op_INC | yystack.l_mark[-4].i | yystack.l_mark[-3].i | yystack.l_mark[-2].i | yystack.l_mark[-1].i; }
#line 2079 "aasm.tab.c"
break;
case 25:
#line 179 "tools/aasm.y"
	{ cmd |= op_ADC | yystack.l_mark[-4].i | yystack.l_mark[-3].i | yystack.l_mark[-2].i | yystack.l_mark[-1].i; }
#line 2084 "aasm.tab.c"
break;
case 26:
#line 181 "tools/aasm.y"
	{ cmd |= op_SUB | yystack.l_mark[-4].i | yystack.l_mark[-3].i | yystack.l_mark[-2].i | yystack.l_mark[-1].i; }
#line 2089 "aasm.tab.c"
break;
case 27:
#line 183 "tools/aasm.y"
	{ cmd |= op_ADD | yystack.l_mark[-4].i | yystack.l_mark[-3].i | yystack.l_mark[-2].i | yystack.l_mark[-1].i; }
#line 2094 "aasm.tab.c"
break;
case 28:
#line 185 "tools/aasm.y"
	{ cmd |= op_AND | yystack.l_mark[-4].i | yystack.l_mark[-3].i | yystack.l_mark[-2].i | yystack.l_mark[-1].i; }
#line 2099 "aasm.tab.c"
break;
case 29:
#line 188 "tools/aasm.y"
	{ cmd |= op_CYCLE | yystack.l_mark[-1].i; }
#line 2104 "aasm.tab.c"
break;
case 30:
#line 190 "tools/aasm.y"
	{ cmd |= op_MUL; }
#line 2109 "aasm.tab.c"
break;
case 31:
#line 192 "tools/aasm.y"
	{ cmd |= op_DIV; }
#line 2114 "aasm.tab.c"
break;
case 32:
#line 194 "tools/aasm.y"
	{ cmd |= op_JSRII | yystack.l_mark[-1].i; }
#line 2119 "aasm.tab.c"
break;
case 33:
#line 196 "tools/aasm.y"
	{ cmd |= op_JSRIS | yystack.l_mark[-1].i; }
#line 2124 "aasm.tab.c"
break;
case 34:
#line 198 "tools/aasm.y"
	{ cmd |= op_CONVERT | yystack.l_mark[-2].i; }
#line 2129 "aasm.tab.c"
break;
case 35:
#line 200 "tools/aasm.y"
	{ cmd |= op_CONVERT | yystack.l_mark[-3].i; }
#line 2134 "aasm.tab.c"
break;
case 36:
#line 202 "tools/aasm.y"
	{ cmd |= op_DIR; }
#line 2139 "aasm.tab.c"
break;
case 37:
#line 204 "tools/aasm.y"
	{ cmd |= op_EIR; }
#line 2144 "aasm.tab.c"
break;
case 38:
#line 206 "tools/aasm.y"
	{ cmd |= op_BRI; }
#line 2149 "aasm.tab.c"
break;
case 39:
#line 208 "tools/aasm.y"
	{ cmd |= op_RCLK; }
#line 2154 "aasm.tab.c"
break;
case 40:
#line 210 "tools/aasm.y"
	{ cmd |= op_SIO; }
#line 2159 "aasm.tab.c"
break;
case 41:
#line 212 "tools/aasm.y"
	{ cmd |= op_BLT; }
#line 2164 "aasm.tab.c"
break;
case 42:
#line 214 "tools/aasm.y"
	{ cmd |= op_BLKS; }
#line 2169 "aasm.tab.c"
break;
case 43:
#line 216 "tools/aasm.y"
	{ cmd |= op_SIT; }
#line 2174 "aasm.tab.c"
break;
case 44:
#line 218 "tools/aasm.y"
	{ cmd |= op_JMPRAM; }
#line 2179 "aasm.tab.c"
break;
case 45:
#line 220 "tools/aasm.y"
	{ cmd |= op_RDRAM; }
#line 2184 "aasm.tab.c"
break;
case 46:
#line 222 "tools/aasm.y"
	{ cmd |= op_WRTRAM; }
#line 2189 "aasm.tab.c"
break;
case 47:
#line 224 "tools/aasm.y"
	{ cmd |= op_DIRS; }
#line 2194 "aasm.tab.c"
break;
case 48:
#line 226 "tools/aasm.y"
	{ cmd |= op_VERS; }
#line 2199 "aasm.tab.c"
break;
case 49:
#line 228 "tools/aasm.y"
	{ cmd |= op_DREAD; }
#line 2204 "aasm.tab.c"
break;
case 50:
#line 230 "tools/aasm.y"
	{ cmd |= op_DWRITE; }
#line 2209 "aasm.tab.c"
break;
case 51:
#line 232 "tools/aasm.y"
	{ cmd |= op_DEXCH; }
#line 2214 "aasm.tab.c"
break;
case 52:
#line 234 "tools/aasm.y"
	{ cmd |= op_DIAGNOSE1; }
#line 2219 "aasm.tab.c"
break;
case 53:
#line 236 "tools/aasm.y"
	{ cmd |= op_DIAGNOSE2; }
#line 2224 "aasm.tab.c"
break;
case 54:
#line 238 "tools/aasm.y"
	{ cmd |= op_BITBLT; }
#line 2229 "aasm.tab.c"
break;
case 55:
#line 240 "tools/aasm.y"
	{ cmd |= op_XMLDA; }
#line 2234 "aasm.tab.c"
break;
case 56:
#line 242 "tools/aasm.y"
	{ cmd |= op_XMSTA; }
#line 2239 "aasm.tab.c"
break;
case 57:
#line 245 "tools/aasm.y"
	{ cmdflg = 0; }
#line 2244 "aasm.tab.c"
break;
case 58:
#line 247 "tools/aasm.y"
	{ cmdflg = 0; }
#line 2249 "aasm.tab.c"
break;
case 59:
#line 249 "tools/aasm.y"
	{ cmdflg = 0; }
#line 2254 "aasm.tab.c"
break;
case 60:
#line 251 "tools/aasm.y"
	{ cmdflg = 0; }
#line 2259 "aasm.tab.c"
break;
case 61:
#line 253 "tools/aasm.y"
	{
			cmdflg = 0;
			argcnt = arg[0];
			if (argcnt > sizeof(arg)/sizeof(arg[0])) {
				fprintf(stderr, "line (%d) warning: size clipped to assembler limits (%d : %d)\n", line_no, argcnt, sizeof(arg));
				argcnt = sizeof(arg)/sizeof(arg[0]);
			}
			memset(arg, 0, argcnt * sizeof(arg[0]));
		}
#line 2272 "aasm.tab.c"
break;
case 62:
#line 263 "tools/aasm.y"
	{
			cmdflg = 0;
			argcnt = 0;
			expflg = 1;
			eexp = yystack.l_mark[-1].i;
			pc = eexp;
		}
#line 2283 "aasm.tab.c"
break;
case 63:
#line 271 "tools/aasm.y"
	{
			cmdflg = 0;
			argcnt = 0;
			expflg = 1;
			eexp = pc;
			tmp = yystack.l_mark[-1].i - 1;
			while (((pc + argcnt) & tmp) && argcnt < (sizeof(arg)/sizeof(arg[0])))
				arg[argcnt++] = 0;
		}
#line 2296 "aasm.tab.c"
break;
case 64:
#line 281 "tools/aasm.y"
	{
			cmdflg = 0;
			argcnt = 0;
			expflg = 1;
			eexp = pc;
			if (pc & 1)
				arg[argcnt++] = 0;
		}
#line 2308 "aasm.tab.c"
break;
case 65:
#line 290 "tools/aasm.y"
	{
			cmdflg = 0;
			argcnt = 0;
			expflg = 1;
			eexp = arg[0];
			end = eexp;
		}
#line 2319 "aasm.tab.c"
break;
case 67:
#line 301 "tools/aasm.y"
	{
			addsym(yystack.l_mark[-1].s, pc);
			free(yystack.l_mark[-1].s);
		}
#line 2327 "aasm.tab.c"
break;
case 68:
#line 308 "tools/aasm.y"
	{
			yyval.i = 0;
		}
#line 2334 "aasm.tab.c"
break;
case 69:
#line 312 "tools/aasm.y"
	{
			yyval.i = yystack.l_mark[0].i;
		}
#line 2341 "aasm.tab.c"
break;
case 70:
#line 319 "tools/aasm.y"
	{
			yyval.i = 0;
		}
#line 2348 "aasm.tab.c"
break;
case 71:
#line 323 "tools/aasm.y"
	{
			yyval.i = sk_SKP;
		}
#line 2355 "aasm.tab.c"
break;
case 72:
#line 327 "tools/aasm.y"
	{
			yyval.i = sk_SZC;
		}
#line 2362 "aasm.tab.c"
break;
case 73:
#line 331 "tools/aasm.y"
	{
			yyval.i = sk_SNC;
		}
#line 2369 "aasm.tab.c"
break;
case 74:
#line 335 "tools/aasm.y"
	{
			yyval.i = sk_SZR;
		}
#line 2376 "aasm.tab.c"
break;
case 75:
#line 339 "tools/aasm.y"
	{
			yyval.i = sk_SNR;
		}
#line 2383 "aasm.tab.c"
break;
case 76:
#line 343 "tools/aasm.y"
	{
			yyval.i = sk_SEZ;
		}
#line 2390 "aasm.tab.c"
break;
case 77:
#line 347 "tools/aasm.y"
	{
			yyval.i = sk_SBN;
		}
#line 2397 "aasm.tab.c"
break;
case 78:
#line 353 "tools/aasm.y"
	{
			if (yystack.l_mark[0].i != 2) {
				fprintf(stderr, "line (%d) fatal: only AC(2) can be base register\n",
					line_no);
				exit(1);
			}
		}
#line 2408 "aasm.tab.c"
break;
case 79:
#line 361 "tools/aasm.y"
	{
			if (yystack.l_mark[-1].i != 2) {
				fprintf(stderr, "line (%d) fatal: only AC(2) can be base register\n",
					line_no);
				exit(1);
			}
		}
#line 2419 "aasm.tab.c"
break;
case 80:
#line 371 "tools/aasm.y"
	{
			if (yystack.l_mark[0].i < 2 || yystack.l_mark[0].i > 3) {
				fprintf(stderr, "line (%d) fatal: only AC(2) or AC(3) can be base register\n",
					line_no);
				exit(1);
			}
			yyval.i = (yystack.l_mark[0].i == 2) ? ea_AC2REL : ea_AC3REL;
		}
#line 2431 "aasm.tab.c"
break;
case 81:
#line 380 "tools/aasm.y"
	{
			if (yystack.l_mark[-1].i < 2 || yystack.l_mark[-1].i > 3) {
				fprintf(stderr, "line (%d) fatal: only AC(2) or AC(3) can be base register\n",
					line_no);
				exit(1);
			}
			yyval.i = (yystack.l_mark[-1].i == 2) ? ea_AC2REL : ea_AC3REL;
		}
#line 2443 "aasm.tab.c"
break;
case 82:
#line 391 "tools/aasm.y"
	{
			if (yystack.l_mark[0].i < 0 || yystack.l_mark[0].i > 3) {
				fprintf(stderr, "line (%d) fatal: invalid source AC(%lld)\n",
					line_no, yystack.l_mark[0].i);
				exit(1);
			}
			yyval.i = yystack.l_mark[0].i << 13;
		}
#line 2455 "aasm.tab.c"
break;
case 83:
#line 400 "tools/aasm.y"
	{
			if (yystack.l_mark[-1].i < 0 || yystack.l_mark[-1].i > 3) {
				fprintf(stderr, "line (%d) fatal: invalid source AC(%lld)\n",
					line_no, yystack.l_mark[-1].i);
				exit(1);
			}
			yyval.i = yystack.l_mark[-1].i << 13;
		}
#line 2467 "aasm.tab.c"
break;
case 84:
#line 411 "tools/aasm.y"
	{
			if (yystack.l_mark[0].i < 0 || yystack.l_mark[0].i > 3) {
				fprintf(stderr, "line (%d) fatal: invalid destination AC(%lld)\n",
					line_no, yystack.l_mark[0].i);
				exit(1);
			}
			yyval.i = yystack.l_mark[0].i << 11;
		}
#line 2479 "aasm.tab.c"
break;
case 85:
#line 420 "tools/aasm.y"
	{
			if (yystack.l_mark[-1].i < 0 || yystack.l_mark[-1].i > 3) {
				fprintf(stderr, "line (%d) fatal: invalid destination AC(%lld)\n",
					line_no, yystack.l_mark[-1].i);
				exit(1);
			}
			yyval.i = yystack.l_mark[-1].i << 11;
		}
#line 2491 "aasm.tab.c"
break;
case 86:
#line 431 "tools/aasm.y"
	{
			if (yystack.l_mark[0].i >= 0 && yystack.l_mark[0].i < 256) {
				/* page 0 address */
				yyval.i = yystack.l_mark[0].i;
			} else {
				int rel = yystack.l_mark[0].i - pc - argcnt;
				/* PC relative */
				if (pass_no > 1 && (rel < -128 || rel > 127))
					fprintf(stderr, "line (%d) warning: displacement range (%lld, %d)\n",
						line_no, yystack.l_mark[0].i, rel);
				yyval.i = ea_PCREL | (rel & 255);
			}
		}
#line 2508 "aasm.tab.c"
break;
case 87:
#line 445 "tools/aasm.y"
	{
			int rel = yystack.l_mark[-1].i;
			if (rel < -128 || rel > 127)
				fprintf(stderr, "line (%d) warning: displacement range (%lld, %d)\n",
					line_no, yystack.l_mark[-1].i, rel);
			yyval.i = yystack.l_mark[0].i | (rel & 255);
		}
#line 2519 "aasm.tab.c"
break;
case 88:
#line 453 "tools/aasm.y"
	{
			int rel = yystack.l_mark[-2].i;
			if (rel < -128 || rel > 127)
				fprintf(stderr, "line (%d) warning: displacement range (%lld, %d)\n",
					line_no, yystack.l_mark[-2].i, rel);
			yyval.i = yystack.l_mark[0].i | (rel & 255);
		}
#line 2530 "aasm.tab.c"
break;
case 89:
#line 463 "tools/aasm.y"
	{
			int rel = yystack.l_mark[0].i - pc - argcnt;
			if (pass_no > 1 && (rel < -128 || rel > 127))
				fprintf(stderr, "line (%d) warning: displacement out of range (%lld)\n",
					line_no, yystack.l_mark[0].i - pc - 1);
			cmd |= rel & 255;
		}
#line 2541 "aasm.tab.c"
break;
case 90:
#line 473 "tools/aasm.y"
	{
			int rel = yystack.l_mark[0].i;
			if (pass_no > 1 && (rel < -128 || rel > 127))
				fprintf(stderr, "line (%d) warning: displacement out of range (%lld)\n",
					line_no, yystack.l_mark[0].i - pc - 1);
			cmd |= rel & 255;
		}
#line 2552 "aasm.tab.c"
break;
case 91:
#line 483 "tools/aasm.y"
	{ yyval.i = yystack.l_mark[0].i; }
#line 2557 "aasm.tab.c"
break;
case 92:
#line 485 "tools/aasm.y"
	{ yyval.i = yystack.l_mark[-2].i << yystack.l_mark[0].i; }
#line 2562 "aasm.tab.c"
break;
case 93:
#line 487 "tools/aasm.y"
	{ yyval.i = yystack.l_mark[-2].i >> yystack.l_mark[0].i; }
#line 2567 "aasm.tab.c"
break;
case 94:
#line 491 "tools/aasm.y"
	{ yyval.i = yystack.l_mark[0].i; }
#line 2572 "aasm.tab.c"
break;
case 95:
#line 493 "tools/aasm.y"
	{ yyval.i = yystack.l_mark[-2].i + yystack.l_mark[0].i; }
#line 2577 "aasm.tab.c"
break;
case 96:
#line 495 "tools/aasm.y"
	{ yyval.i = yystack.l_mark[-2].i - yystack.l_mark[0].i; }
#line 2582 "aasm.tab.c"
break;
case 97:
#line 497 "tools/aasm.y"
	{ yyval.i = yystack.l_mark[-2].i & yystack.l_mark[0].i; }
#line 2587 "aasm.tab.c"
break;
case 98:
#line 501 "tools/aasm.y"
	{ yyval.i = yystack.l_mark[0].i; }
#line 2592 "aasm.tab.c"
break;
case 99:
#line 503 "tools/aasm.y"
	{ yyval.i = yystack.l_mark[0].i; }
#line 2597 "aasm.tab.c"
break;
case 100:
#line 505 "tools/aasm.y"
	{ yyval.i = -yystack.l_mark[0].i; }
#line 2602 "aasm.tab.c"
break;
case 101:
#line 507 "tools/aasm.y"
	{ yyval.i = ~yystack.l_mark[0].i; }
#line 2607 "aasm.tab.c"
break;
case 102:
#line 509 "tools/aasm.y"
	{ yyval.i = yystack.l_mark[-2].i * yystack.l_mark[0].i; }
#line 2612 "aasm.tab.c"
break;
case 103:
#line 511 "tools/aasm.y"
	{ yyval.i = yystack.l_mark[-2].i / yystack.l_mark[0].i; }
#line 2617 "aasm.tab.c"
break;
case 104:
#line 513 "tools/aasm.y"
	{ yyval.i = yystack.l_mark[-2].i | yystack.l_mark[0].i; }
#line 2622 "aasm.tab.c"
break;
case 105:
#line 515 "tools/aasm.y"
	{ yyval.i = yystack.l_mark[-2].i ^ yystack.l_mark[0].i; }
#line 2627 "aasm.tab.c"
break;
case 106:
#line 519 "tools/aasm.y"
	{ yyval.i = yystack.l_mark[0].i; }
#line 2632 "aasm.tab.c"
break;
case 107:
#line 521 "tools/aasm.y"
	{ yyval.i = getsym(yystack.l_mark[0].s); free(yystack.l_mark[0].s); }
#line 2637 "aasm.tab.c"
break;
case 108:
#line 523 "tools/aasm.y"
	{ yyval.i = yystack.l_mark[-1].i; }
#line 2642 "aasm.tab.c"
break;
case 109:
#line 527 "tools/aasm.y"
	{
			if (yystack.l_mark[0].i < 0 || yystack.l_mark[0].i > 15)
				fprintf(stderr, "line (%d) warning: bad cycle count (%lld)\n",
					line_no, yystack.l_mark[0].i);
			yyval.i = yystack.l_mark[0].i & 15;
		}
#line 2652 "aasm.tab.c"
break;
case 110:
#line 536 "tools/aasm.y"
	{
			if (yystack.l_mark[0].i < -128 || yystack.l_mark[0].i > 255)
				fprintf(stderr, "line (%d) warning: size exceeds 8 bits (%lld)\n",
					line_no, yystack.l_mark[0].i);
			if (arglow)
				arg[argcnt++] |= yystack.l_mark[0].i << 8;
			else
				arg[argcnt] = yystack.l_mark[0].i;
			arglow ^= 1;
		}
#line 2666 "aasm.tab.c"
break;
case 113:
#line 553 "tools/aasm.y"
	{
			if (yystack.l_mark[0].i < -32768 || yystack.l_mark[0].i > 65535)
				fprintf(stderr, "line (%d) warning: size exceeds 16 bits (%lld)\n",
					line_no, yystack.l_mark[0].i);
			arg[argcnt++] = yystack.l_mark[0].i;
		}
#line 2676 "aasm.tab.c"
break;
case 116:
#line 566 "tools/aasm.y"
	{
			if (yystack.l_mark[0].i < -2147483648ll || yystack.l_mark[0].i > 21474836647ll)
				fprintf(stderr, "line (%d) warning: size exceeds 32 bits (%lld)\n",
					line_no, yystack.l_mark[0].i);
			arg[argcnt++] = yystack.l_mark[0].i % 65536;
			arg[argcnt++] = yystack.l_mark[0].i / 65536;
		}
#line 2687 "aasm.tab.c"
break;
case 119:
#line 580 "tools/aasm.y"
	{
			int len = strlen(yystack.l_mark[0].s);
			int i;
			for (i = 0; i < len; i++) {
				if (arglow)
					arg[argcnt++] |= yystack.l_mark[0].s[i] << 8;
				else
					arg[argcnt] = yystack.l_mark[0].s[i];
				arglow ^= 1;
			}
			free(yystack.l_mark[0].s);
		}
#line 2703 "aasm.tab.c"
break;
#line 2705 "aasm.tab.c"
    default:
        break;
    }
    yystack.s_mark -= yym;
    yystate = *yystack.s_mark;
    yystack.l_mark -= yym;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    yystack.p_mark -= yym;
#endif
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
        {
            fprintf(stderr, "%s[%d]: after reduction, ", YYDEBUGSTR, yydepth);
#ifdef YYSTYPE_TOSTRING
#if YYBTYACC
            if (!yytrial)
#endif /* YYBTYACC */
                fprintf(stderr, "result is <%s>, ", YYSTYPE_TOSTRING(yystos[YYFINAL], yyval));
#endif
            fprintf(stderr, "shifting from state 0 to final state %d\n", YYFINAL);
        }
#endif
        yystate = YYFINAL;
        *++yystack.s_mark = YYFINAL;
        *++yystack.l_mark = yyval;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
        *++yystack.p_mark = yyloc;
#endif
        if (yychar < 0)
        {
#if YYBTYACC
            do {
            if (yylvp < yylve)
            {
                /* we're currently re-reading tokens */
                yylval = *yylvp++;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                yylloc = *yylpp++;
#endif
                yychar = *yylexp++;
                break;
            }
            if (yyps->save)
            {
                /* in trial mode; save scanner results for future parse attempts */
                if (yylvp == yylvlim)
                {   /* Enlarge lexical value queue */
                    size_t p = (size_t) (yylvp - yylvals);
                    size_t s = (size_t) (yylvlim - yylvals);

                    s += YYLVQUEUEGROWTH;
                    if ((yylexemes = (YYINT *)realloc(yylexemes, s * sizeof(YYINT))) == NULL)
                        goto yyenomem;
                    if ((yylvals   = (YYSTYPE *)realloc(yylvals, s * sizeof(YYSTYPE))) == NULL)
                        goto yyenomem;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                    if ((yylpsns   = (YYLTYPE *)realloc(yylpsns, s * sizeof(YYLTYPE))) == NULL)
                        goto yyenomem;
#endif
                    yylvp   = yylve = yylvals + p;
                    yylvlim = yylvals + s;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                    yylpp   = yylpe = yylpsns + p;
                    yylplim = yylpsns + s;
#endif
                    yylexp  = yylexemes + p;
                }
                *yylexp = (YYINT) YYLEX;
                *yylvp++ = yylval;
                yylve++;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                *yylpp++ = yylloc;
                yylpe++;
#endif
                yychar = *yylexp++;
                break;
            }
            /* normal operation, no conflict encountered */
#endif /* YYBTYACC */
            yychar = YYLEX;
#if YYBTYACC
            } while (0);
#endif /* YYBTYACC */
            if (yychar < 0) yychar = YYEOF;
#if YYDEBUG
            if (yydebug)
            {
                if ((yys = yyname[YYTRANSLATE(yychar)]) == NULL) yys = yyname[YYUNDFTOKEN];
                fprintf(stderr, "%s[%d]: state %d, reading token %d (%s)\n",
                                YYDEBUGSTR, yydepth, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == YYEOF) goto yyaccept;
        goto yyloop;
    }
    if (((yyn = yygindex[yym]) != 0) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == (YYINT) yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
    {
        fprintf(stderr, "%s[%d]: after reduction, ", YYDEBUGSTR, yydepth);
#ifdef YYSTYPE_TOSTRING
#if YYBTYACC
        if (!yytrial)
#endif /* YYBTYACC */
            fprintf(stderr, "result is <%s>, ", YYSTYPE_TOSTRING(yystos[yystate], yyval));
#endif
        fprintf(stderr, "shifting from state %d to state %d\n", *yystack.s_mark, yystate);
    }
#endif
    if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM) goto yyoverflow;
    *++yystack.s_mark = (YYINT) yystate;
    *++yystack.l_mark = yyval;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    *++yystack.p_mark = yyloc;
#endif
    goto yyloop;
#if YYBTYACC

    /* Reduction declares that this path is valid. Set yypath and do a full parse */
yyvalid:
    if (yypath) YYABORT;
    while (yyps->save)
    {
        YYParseState *save = yyps->save;
        yyps->save = save->save;
        save->save = yypath;
        yypath = save;
    }
#if YYDEBUG
    if (yydebug)
        fprintf(stderr, "%s[%d]: state %d, CONFLICT trial successful, backtracking to state %d, %d tokens\n",
                        YYDEBUGSTR, yydepth, yystate, yypath->state, (int)(yylvp - yylvals - yypath->lexeme));
#endif
    if (yyerrctx)
    {
        yyFreeState(yyerrctx);
        yyerrctx = NULL;
    }
    yylvp          = yylvals + yypath->lexeme;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    yylpp          = yylpsns + yypath->lexeme;
#endif
    yylexp         = yylexemes + yypath->lexeme;
    yychar         = YYEMPTY;
    yystack.s_mark = yystack.s_base + (yypath->yystack.s_mark - yypath->yystack.s_base);
    memcpy (yystack.s_base, yypath->yystack.s_base, (size_t) (yystack.s_mark - yystack.s_base + 1) * sizeof(YYINT));
    yystack.l_mark = yystack.l_base + (yypath->yystack.l_mark - yypath->yystack.l_base);
    memcpy (yystack.l_base, yypath->yystack.l_base, (size_t) (yystack.l_mark - yystack.l_base + 1) * sizeof(YYSTYPE));
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    yystack.p_mark = yystack.p_base + (yypath->yystack.p_mark - yypath->yystack.p_base);
    memcpy (yystack.p_base, yypath->yystack.p_base, (size_t) (yystack.p_mark - yystack.p_base + 1) * sizeof(YYLTYPE));
#endif
    yystate        = yypath->state;
    goto yyloop;
#endif /* YYBTYACC */

yyoverflow:
    YYERROR_CALL("yacc stack overflow");
#if YYBTYACC
    goto yyabort_nomem;
yyenomem:
    YYERROR_CALL("memory exhausted");
yyabort_nomem:
#endif /* YYBTYACC */
    yyresult = 2;
    goto yyreturn;

yyabort:
    yyresult = 1;
    goto yyreturn;

yyaccept:
#if YYBTYACC
    if (yyps->save) goto yyvalid;
#endif /* YYBTYACC */
    yyresult = 0;

yyreturn:
#if defined(YYDESTRUCT_CALL)
    if (yychar != YYEOF && yychar != YYEMPTY)
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
        YYDESTRUCT_CALL("cleanup: discarding token", yychar, &yylval, &yylloc);
#else
        YYDESTRUCT_CALL("cleanup: discarding token", yychar, &yylval);
#endif /* defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED) */

    {
        YYSTYPE *pv;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
        YYLTYPE *pp;

        for (pv = yystack.l_base, pp = yystack.p_base; pv <= yystack.l_mark; ++pv, ++pp)
             YYDESTRUCT_CALL("cleanup: discarding state",
                             yystos[*(yystack.s_base + (pv - yystack.l_base))], pv, pp);
#else
        for (pv = yystack.l_base; pv <= yystack.l_mark; ++pv)
             YYDESTRUCT_CALL("cleanup: discarding state",
                             yystos[*(yystack.s_base + (pv - yystack.l_base))], pv);
#endif /* defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED) */
    }
#endif /* defined(YYDESTRUCT_CALL) */

#if YYBTYACC
    if (yyerrctx)
    {
        yyFreeState(yyerrctx);
        yyerrctx = NULL;
    }
    while (yyps)
    {
        YYParseState *save = yyps;
        yyps = save->save;
        save->save = NULL;
        yyFreeState(save);
    }
    while (yypath)
    {
        YYParseState *save = yypath;
        yypath = save->save;
        save->save = NULL;
        yyFreeState(save);
    }
#endif /* YYBTYACC */
    yyfreestack(&yystack);
    return (yyresult);
}
