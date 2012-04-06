#ifndef lint
static const char yysccsid[] = "@(#)yaccpar	1.9 (Berkeley) 02/21/93";
#endif

#include <stdlib.h>

#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define YYPATCH 20050813

#define YYEMPTY (-1)
#define yyclearin    (yychar = YYEMPTY)
#define yyerrok      (yyerrflag = 0)
#define YYRECOVERING (yyerrflag != 0)

extern int yyparse(void);

static int yygrowstack(void);
#define YYPREFIX "yy"
#line 2 "gram.y"
  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  #include "context.h"
  #include "program.h"
  #include "code.h"
  #include "symboltable.h"
  #include <string>

using namespace std;

extern int yyparse(void);
extern int yylex(void);
extern int yylineno;

extern  Context ctx;
extern  Program programa;

#line 22 "gram.y"
typedef union {
  int entero;
  float real;
  char label[33];
  string* cadena;
  } YYSTYPE;
#line 48 "y.tab.c"
#define ENTERO 257
#define REAL 258
#define ETIQUETA 259
#define CADENA 260
#define IPUSH_TOK 261
#define FPUSH_TOK 262
#define IPOP_TOK 263
#define FPOP_TOK 264
#define IPUSHBP_TOK 265
#define ILOAD_TOK 266
#define FLOAD_TOK 267
#define ISTORE_TOK 268
#define FSTORE_TOK 269
#define IADD_TOK 270
#define FADD_TOK 271
#define IMUL_TOK 272
#define FMUL_TOK 273
#define ISUB_TOK 274
#define FSUB_TOK 275
#define IDIV_TOK 276
#define FDIV_TOK 277
#define IMOD_TOK 278
#define FMOD_TOK 279
#define CAST_TOK 280
#define CAST2_TOK 281
#define FINPUT_TOK 282
#define FOUTPUT_TOK 283
#define IINPUT_TOK 284
#define IOUTPUT_TOK 285
#define Call_TOK 286
#define Return_TOK 287
#define IReturn_TOK 288
#define FReturn_TOK 289
#define JMP_TOK 290
#define JMPZero_TOK 291
#define JMPNotZero_TOK 292
#define Equal_TOK 293
#define NotEqual_TOK 294
#define Greater_TOK 295
#define Less_TOK 296
#define AND_TOK 297
#define OR_TOK 298
#define NOT_TOK 299
#define IEQUAL_TOK 300
#define FEQUAL_TOK 301
#define INOTEQUAL_TOK 302
#define FNOTEQUAL_TOK 303
#define IGREATER_TOK 304
#define FGREATER_TOK 305
#define ILESS_TOK 306
#define FLESS_TOK 307
#define IGREATEREQUAL_TOK 308
#define ILESSEQUAL_TOK 309
#define FGREATEREQUAL_TOK 310
#define FLESSEQUAL_TOK 311
#define ICHSGN_TOK 312
#define FCHSGN_TOK 313
#define FToI_TOK 314
#define RESRV_TOK 315
#define PRINT_TOK 316
#define YYERRCODE 256
short yylhs[] = {                                        -1,
    0,    0,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,   11,    2,    2,    2,    2,
    2,    3,    3,    4,    4,   13,   13,   13,    5,    5,
    5,    5,    5,    5,    5,    5,    5,    5,    5,    5,
    6,    6,    6,    6,    6,    6,    6,    6,    6,    6,
    6,    6,    7,    7,    7,    8,    8,    8,    8,    8,
    9,    9,    9,   10,   10,   10,   10,   12,
};
short yylen[] = {                                         2,
    0,    2,    2,    2,    2,    2,    2,    2,    2,    2,
    2,    2,    2,    2,    1,    2,    2,    2,    2,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    2,
    2,    2,    2,    2,    3,    3,    3,    2,
};
short yydefred[] = {                                      1,
    0,    0,    0,    0,   20,   21,    0,   22,   23,   24,
   25,   29,   30,   31,   32,   33,   34,   35,   36,   37,
   38,   53,   54,   57,   59,   56,   58,    0,    0,    0,
    0,    0,    0,    0,   26,   27,   28,   41,   42,   43,
   44,   45,   46,   47,   48,   49,   51,   50,   52,   39,
   40,   55,    0,    0,   15,    2,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,   16,   17,
   18,   19,   64,    0,    0,    0,   61,   62,   63,   68,
   60,    3,    4,    5,    6,    7,    8,    9,   10,   11,
   12,   13,   14,   65,   66,   67,
};
short yydgoto[] = {                                       1,
   56,   57,   58,   59,   60,   61,   62,   63,   64,   65,
   66,   67,   68,
};
short yysindex[] = {                                      0,
  -10,  -57, -255, -254,    0,    0, -252,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0, -256, -251, -250,
 -249, -248, -247, -246,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0, -243, -245,    0,    0,   -1,    6,    7,    8,
    9,   10,   11,   12,   13,   14,   15,   16,    0,    0,
    0,    0,    0, -230, -229, -228,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,
};
short yyrindex[] = {                                      0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,
};
short yygindex[] = {                                      0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,
};
#define YYTABLESIZE 306
short yytable[] = {                                      55,
   69,   70,   73,   71,   72,   74,   75,   76,   82,    0,
   77,   78,   79,   80,   81,   83,   84,   85,   86,   87,
   88,   89,   90,   91,   92,   93,   94,   95,   96,    0,
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
    0,    0,    0,    0,    0,    0,    0,    0,    2,    0,
    3,    4,    5,    6,    7,    8,    9,   10,   11,   12,
   13,   14,   15,   16,   17,   18,   19,   20,   21,   22,
   23,   24,   25,   26,   27,   28,   29,   30,   31,   32,
   33,   34,    0,    0,    0,    0,   35,   36,   37,   38,
   39,   40,   41,   42,   43,   44,   45,   46,   47,   48,
   49,   50,   51,   52,   53,   54,
};
short yycheck[] = {                                      10,
   58,  257,  259,  258,  257,  257,  257,  257,   10,   -1,
  259,  259,  259,  257,  260,   10,   10,   10,   10,   10,
   10,   10,   10,   10,   10,   10,  257,  257,  257,   -1,
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
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  259,   -1,
  261,  262,  263,  264,  265,  266,  267,  268,  269,  270,
  271,  272,  273,  274,  275,  276,  277,  278,  279,  280,
  281,  282,  283,  284,  285,  286,  287,  288,  289,  290,
  291,  292,   -1,   -1,   -1,   -1,  297,  298,  299,  300,
  301,  302,  303,  304,  305,  306,  307,  308,  309,  310,
  311,  312,  313,  314,  315,  316,
};
#define YYFINAL 1
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 316
#if YYDEBUG
char *yyname[] = {
"end-of-file",0,0,0,0,0,0,0,0,0,"'\\n'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"':'",0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"ENTERO","REAL",
"ETIQUETA","CADENA","IPUSH_TOK","FPUSH_TOK","IPOP_TOK","FPOP_TOK","IPUSHBP_TOK",
"ILOAD_TOK","FLOAD_TOK","ISTORE_TOK","FSTORE_TOK","IADD_TOK","FADD_TOK",
"IMUL_TOK","FMUL_TOK","ISUB_TOK","FSUB_TOK","IDIV_TOK","FDIV_TOK","IMOD_TOK",
"FMOD_TOK","CAST_TOK","CAST2_TOK","FINPUT_TOK","FOUTPUT_TOK","IINPUT_TOK",
"IOUTPUT_TOK","Call_TOK","Return_TOK","IReturn_TOK","FReturn_TOK","JMP_TOK",
"JMPZero_TOK","JMPNotZero_TOK","Equal_TOK","NotEqual_TOK","Greater_TOK",
"Less_TOK","AND_TOK","OR_TOK","NOT_TOK","IEQUAL_TOK","FEQUAL_TOK",
"INOTEQUAL_TOK","FNOTEQUAL_TOK","IGREATER_TOK","FGREATER_TOK","ILESS_TOK",
"FLESS_TOK","IGREATEREQUAL_TOK","ILESSEQUAL_TOK","FGREATEREQUAL_TOK",
"FLESSEQUAL_TOK","ICHSGN_TOK","FCHSGN_TOK","FToI_TOK","RESRV_TOK","PRINT_TOK",
};
char *yyrule[] = {
"$accept : cuerpo",
"cuerpo :",
"cuerpo : cuerpo sent",
"sent : op_apilar '\\n'",
"sent : op_cargar '\\n'",
"sent : op_guardar '\\n'",
"sent : op_aritmetica '\\n'",
"sent : op_comparacion '\\n'",
"sent : op_cast '\\n'",
"sent : op_io '\\n'",
"sent : op_salto '\\n'",
"sent : op_func '\\n'",
"sent : etiqueta '\\n'",
"sent : op_reserva '\\n'",
"sent : op_logica '\\n'",
"sent : '\\n'",
"etiqueta : ETIQUETA ':'",
"op_apilar : IPUSH_TOK ENTERO",
"op_apilar : FPUSH_TOK REAL",
"op_apilar : IPUSHBP_TOK ENTERO",
"op_apilar : IPOP_TOK",
"op_apilar : FPOP_TOK",
"op_cargar : ILOAD_TOK",
"op_cargar : FLOAD_TOK",
"op_guardar : ISTORE_TOK",
"op_guardar : FSTORE_TOK",
"op_logica : AND_TOK",
"op_logica : OR_TOK",
"op_logica : NOT_TOK",
"op_aritmetica : IADD_TOK",
"op_aritmetica : FADD_TOK",
"op_aritmetica : IMUL_TOK",
"op_aritmetica : FMUL_TOK",
"op_aritmetica : ISUB_TOK",
"op_aritmetica : FSUB_TOK",
"op_aritmetica : IDIV_TOK",
"op_aritmetica : FDIV_TOK",
"op_aritmetica : IMOD_TOK",
"op_aritmetica : FMOD_TOK",
"op_aritmetica : ICHSGN_TOK",
"op_aritmetica : FCHSGN_TOK",
"op_comparacion : IEQUAL_TOK",
"op_comparacion : FEQUAL_TOK",
"op_comparacion : INOTEQUAL_TOK",
"op_comparacion : FNOTEQUAL_TOK",
"op_comparacion : IGREATER_TOK",
"op_comparacion : FGREATER_TOK",
"op_comparacion : ILESS_TOK",
"op_comparacion : FLESS_TOK",
"op_comparacion : IGREATEREQUAL_TOK",
"op_comparacion : FGREATEREQUAL_TOK",
"op_comparacion : ILESSEQUAL_TOK",
"op_comparacion : FLESSEQUAL_TOK",
"op_cast : CAST_TOK",
"op_cast : CAST2_TOK",
"op_cast : FToI_TOK",
"op_io : IINPUT_TOK",
"op_io : FINPUT_TOK",
"op_io : IOUTPUT_TOK",
"op_io : FOUTPUT_TOK",
"op_io : PRINT_TOK CADENA",
"op_salto : JMP_TOK ETIQUETA",
"op_salto : JMPZero_TOK ETIQUETA",
"op_salto : JMPNotZero_TOK ETIQUETA",
"op_func : Call_TOK ETIQUETA",
"op_func : Return_TOK ENTERO ENTERO",
"op_func : IReturn_TOK ENTERO ENTERO",
"op_func : FReturn_TOK ENTERO ENTERO",
"op_reserva : RESRV_TOK ENTERO",
};
#endif
#if YYDEBUG
#include <stdio.h>
#endif

/* define the initial stack-sizes */
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH  YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 500
#define YYMAXDEPTH  500
#endif
#endif

#define YYINITSTACKSIZE 500

int      yydebug;
int      yynerrs;
int      yyerrflag;
int      yychar;
short   *yyssp;
YYSTYPE *yyvsp;
YYSTYPE  yyval;
YYSTYPE  yylval;

/* variables for the parser stack */
static short   *yyss;
static short   *yysslim;
static YYSTYPE *yyvs;
static int      yystacksize;
#line 145 "gram.y"
int yyerror(const char* str)
{
  printf("Error: %s. Linea %d\n", str, yylineno-1);
  exit(-1);
  
}


#line 378 "y.tab.c"
/* allocate initial stack or double stack size, up to YYMAXDEPTH */
static int yygrowstack(void)
{
    int newsize, i;
    short *newss;
    YYSTYPE *newvs;

    if ((newsize = yystacksize) == 0)
        newsize = YYINITSTACKSIZE;
    else if (newsize >= YYMAXDEPTH)
        return -1;
    else if ((newsize *= 2) > YYMAXDEPTH)
        newsize = YYMAXDEPTH;

    i = yyssp - yyss;
    newss = (yyss != 0)
          ? (short *)realloc(yyss, newsize * sizeof(*newss))
          : (short *)malloc(newsize * sizeof(*newss));
    if (newss == 0)
        return -1;

    yyss  = newss;
    yyssp = newss + i;
    newvs = (yyvs != 0)
          ? (YYSTYPE *)realloc(yyvs, newsize * sizeof(*newvs))
          : (YYSTYPE *)malloc(newsize * sizeof(*newvs));
    if (newvs == 0)
        return -1;

    yyvs = newvs;
    yyvsp = newvs + i;
    yystacksize = newsize;
    yysslim = yyss + newsize - 1;
    return 0;
}

#define YYABORT goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR goto yyerrlab
int
yyparse(void)
{
    register int yym, yyn, yystate;
#if YYDEBUG
    register const char *yys;

    if ((yys = getenv("YYDEBUG")) != 0)
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    yynerrs = 0;
    yyerrflag = 0;
    yychar = YYEMPTY;

    if (yyss == NULL && yygrowstack()) goto yyoverflow;
    yyssp = yyss;
    yyvsp = yyvs;
    *yyssp = yystate = 0;

yyloop:
    if ((yyn = yydefred[yystate]) != 0) goto yyreduce;
    if (yychar < 0)
    {
        if ((yychar = yylex()) < 0) yychar = 0;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, reading %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
    }
    if ((yyn = yysindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: state %d, shifting to state %d\n",
                    YYPREFIX, yystate, yytable[yyn]);
#endif
        if (yyssp >= yysslim && yygrowstack())
        {
            goto yyoverflow;
        }
        *++yyssp = yystate = yytable[yyn];
        *++yyvsp = yylval;
        yychar = YYEMPTY;
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if ((yyn = yyrindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag) goto yyinrecovery;

    yyerror("syntax error");

#ifdef lint
    goto yyerrlab;
#endif

yyerrlab:
    ++yynerrs;

yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if ((yyn = yysindex[*yyssp]) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yyssp, yytable[yyn]);
#endif
                if (yyssp >= yysslim && yygrowstack())
                {
                    goto yyoverflow;
                }
                *++yyssp = yystate = yytable[yyn];
                *++yyvsp = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yyssp);
#endif
                if (yyssp <= yyss) goto yyabort;
                --yyssp;
                --yyvsp;
            }
        }
    }
    else
    {
        if (yychar == 0) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
        yychar = YYEMPTY;
        goto yyloop;
    }

yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    yyval = yyvsp[1-yym];
    switch (yyn)
    {
case 16:
#line 69 "gram.y"
{ int instr = programa.getCount(); 
                         ctx.ts.addEntry(yyvsp[-1].label, new LabelNode(instr));
                       }
break;
case 17:
#line 73 "gram.y"
{ programa.addCode( new IPUSH(yyvsp[0].entero) );  }
break;
case 18:
#line 74 "gram.y"
{ programa.addCode( new FPUSH(yyvsp[0].real) );  }
break;
case 19:
#line 75 "gram.y"
{ programa.addCode( new IPUSHBP(yyvsp[0].entero) );  }
break;
case 20:
#line 76 "gram.y"
{ programa.addCode( new IPOP() );  }
break;
case 21:
#line 77 "gram.y"
{ programa.addCode( new FPOP() );  }
break;
case 22:
#line 79 "gram.y"
{ programa.addCode( new ILOAD() ); }
break;
case 23:
#line 80 "gram.y"
{ programa.addCode( new FLOAD() ); }
break;
case 24:
#line 82 "gram.y"
{programa.addCode( new ISTORE() ); }
break;
case 25:
#line 83 "gram.y"
{programa.addCode( new FSTORE() ); }
break;
case 26:
#line 86 "gram.y"
{ programa.addCode( new AND() ); }
break;
case 27:
#line 87 "gram.y"
{ programa.addCode( new OR() ); }
break;
case 28:
#line 88 "gram.y"
{ programa.addCode( new NOT() ); }
break;
case 29:
#line 90 "gram.y"
{programa.addCode( new IADD() ); }
break;
case 30:
#line 91 "gram.y"
{programa.addCode( new FADD() ); }
break;
case 31:
#line 92 "gram.y"
{programa.addCode( new IMUL() ); }
break;
case 32:
#line 93 "gram.y"
{programa.addCode( new FMUL() ); }
break;
case 33:
#line 94 "gram.y"
{programa.addCode( new ISUB() ); }
break;
case 34:
#line 95 "gram.y"
{programa.addCode( new FSUB() ); }
break;
case 35:
#line 96 "gram.y"
{programa.addCode( new IDIV() ); }
break;
case 36:
#line 97 "gram.y"
{programa.addCode( new FDIV() ); }
break;
case 37:
#line 98 "gram.y"
{programa.addCode( new IMOD() ); }
break;
case 38:
#line 99 "gram.y"
{programa.addCode( new FMOD() ); }
break;
case 39:
#line 100 "gram.y"
{programa.addCode( new ICHSGN() ); }
break;
case 40:
#line 101 "gram.y"
{programa.addCode( new FCHSGN() ); }
break;
case 41:
#line 104 "gram.y"
{ programa.addCode( new IEqual() ); }
break;
case 42:
#line 105 "gram.y"
{ programa.addCode( new FEqual() ); }
break;
case 43:
#line 106 "gram.y"
{ programa.addCode( new INotEqual() ); }
break;
case 44:
#line 107 "gram.y"
{ programa.addCode( new FNotEqual() ); }
break;
case 45:
#line 108 "gram.y"
{ programa.addCode( new IGreater() ); }
break;
case 46:
#line 109 "gram.y"
{ programa.addCode( new FGreater() ); }
break;
case 47:
#line 110 "gram.y"
{ programa.addCode( new ILess() ); }
break;
case 48:
#line 111 "gram.y"
{ programa.addCode( new FLess() ); }
break;
case 49:
#line 112 "gram.y"
{ programa.addCode( new IGreaterEqual() ); }
break;
case 50:
#line 113 "gram.y"
{ programa.addCode( new FGreaterEqual() ); }
break;
case 51:
#line 114 "gram.y"
{ programa.addCode( new ILessEqual() ); }
break;
case 52:
#line 115 "gram.y"
{ programa.addCode( new FLessEqual() ); }
break;
case 53:
#line 119 "gram.y"
{programa.addCode( new CAST() ); }
break;
case 54:
#line 120 "gram.y"
{programa.addCode( new CAST2() ); }
break;
case 55:
#line 121 "gram.y"
{programa.addCode( new FToI() ); }
break;
case 56:
#line 123 "gram.y"
{ programa.addCode( new IINPUT() ); }
break;
case 57:
#line 124 "gram.y"
{ programa.addCode( new FINPUT() ); }
break;
case 58:
#line 125 "gram.y"
{ programa.addCode( new IOUTPUT() ); }
break;
case 59:
#line 126 "gram.y"
{ programa.addCode( new FOUTPUT() ); }
break;
case 60:
#line 127 "gram.y"
{ programa.addCode( new PRINT(*yyvsp[0].cadena) ); delete yyvsp[0].cadena;}
break;
case 61:
#line 130 "gram.y"
{ programa.addCode( new JMP(yyvsp[0].label) ); }
break;
case 62:
#line 131 "gram.y"
{ programa.addCode( new JMPZero(yyvsp[0].label) ); }
break;
case 63:
#line 132 "gram.y"
{ programa.addCode( new JMPNotZero(yyvsp[0].label) ); }
break;
case 64:
#line 135 "gram.y"
{ programa.addCode( new Call(yyvsp[0].label) ); }
break;
case 65:
#line 136 "gram.y"
{ programa.addCode( new Return(yyvsp[-1].entero,yyvsp[0].entero) ); }
break;
case 66:
#line 137 "gram.y"
{ programa.addCode( new IReturn(yyvsp[-1].entero,yyvsp[0].entero) ); }
break;
case 67:
#line 138 "gram.y"
{ programa.addCode( new FReturn(yyvsp[-1].entero,yyvsp[0].entero) ); }
break;
case 68:
#line 141 "gram.y"
{ programa.addCode( new RESRV(yyvsp[0].entero) ); }
break;
#line 770 "y.tab.c"
    }
    yyssp -= yym;
    yystate = *yyssp;
    yyvsp -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        yystate = YYFINAL;
        *++yyssp = YYFINAL;
        *++yyvsp = yyval;
        if (yychar < 0)
        {
            if ((yychar = yylex()) < 0) yychar = 0;
#if YYDEBUG
            if (yydebug)
            {
                yys = 0;
                if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
                if (!yys) yys = "illegal-symbol";
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == 0) goto yyaccept;
        goto yyloop;
    }
    if ((yyn = yygindex[yym]) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: after reduction, shifting from state %d \
to state %d\n", YYPREFIX, *yyssp, yystate);
#endif
    if (yyssp >= yysslim && yygrowstack())
    {
        goto yyoverflow;
    }
    *++yyssp = yystate;
    *++yyvsp = yyval;
    goto yyloop;

yyoverflow:
    yyerror("yacc stack overflow");

yyabort:
    return (1);

yyaccept:
    return (0);
}
