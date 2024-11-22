#ifndef _yy_defines_h_
#define _yy_defines_h_

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
#ifdef YYSTYPE
#undef  YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#endif
#ifndef YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
typedef union YYSTYPE {
	long long int i;
	char *s;
} YYSTYPE;
#endif /* !YYSTYPE_IS_DECLARED */
extern YYSTYPE yylval;

#endif /* _yy_defines_h_ */
