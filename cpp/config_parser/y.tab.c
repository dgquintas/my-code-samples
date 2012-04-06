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
  #include <string.h>
  #include <iostream>
  #include <cstdlib>
  #include <string>

  #include <map>
  #include "GenericValue.h"
  #include "ConfigParser.h"

extern int yyparse(void);
extern int yylex(void);
extern int yylineno;

std::string currConfigSet;

#line 20 "gram.y"
typedef union {
  struct resultExp_t
  {
    int integer;
    double real;
    std::string* str;
    bool boolean;
    short type;
  } resultExp;
  char ident[128];
  } YYSTYPE;
#line 51 "y.tab.c"
#define INTEGER 257
#define REAL 258
#define STR 259
#define BOOL 260
#define IDENT 261
#define READ 262
#define WRITE 263
#define MAIN 264
#define YYERRCODE 256
short yylhs[] = {                                        -1,
    0,    0,    4,    3,    5,    5,    6,    2,    1,    1,
    1,    1,    1,    1,    1,    1,    1,
};
short yylen[] = {                                         2,
    0,    2,    0,    5,    0,    2,    2,    3,    3,    3,
    3,    3,    3,    1,    1,    1,    1,
};
short yydefred[] = {                                      1,
    0,    3,    2,    0,    5,    0,    0,    4,    0,    6,
    0,    7,   14,   15,   16,   17,    0,    0,    0,    0,
    0,    0,    0,   13,    0,    0,   11,   12,
};
short yydgoto[] = {                                       1,
   18,    9,    3,    4,    6,   10,
};
short yysindex[] = {                                      0,
 -250,    0,    0, -108,    0, -124,  -35,    0,  -31,    0,
  -40,    0,    0,    0,    0,    0,  -40,  -20,  -33,  -40,
  -40,  -40,  -40,    0,  -18,  -18,    0,    0,
};
short yyrindex[] = {                                      0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  -29,    0,    0,
    0,    0,    0,    0,  -39,  -38,    0,    0,
};
short yygindex[] = {                                      0,
   -4,    0,    0,    0,    0,    0,
};
#define YYTABLESIZE 220
short yytable[] = {                                      17,
    8,    9,   10,    9,   10,    9,   10,   24,   22,   20,
    2,   21,   19,   23,    5,   25,   26,   27,   28,    9,
   10,   22,   20,   22,   21,   11,   23,   12,   23,    8,
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
    0,    0,    0,    0,    0,    0,    7,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,   13,   14,   15,   16,
};
short yycheck[] = {                                      40,
  125,   41,   41,   43,   43,   45,   45,   41,   42,   43,
  261,   45,   17,   47,  123,   20,   21,   22,   23,   59,
   59,   42,   43,   42,   45,   61,   47,   59,   47,   59,
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
   -1,   -1,   -1,   -1,   -1,   -1,  261,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  257,  258,  259,  260,
};
#define YYFINAL 1
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 264
#if YYDEBUG
char *yyname[] = {
"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,"'('","')'","'*'","'+'",0,"'-'",0,"'/'",0,0,0,0,0,0,0,0,0,0,0,"';'",
0,"'='",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"'{'",0,"'}'",0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,"INTEGER","REAL","STR","BOOL","IDENT","READ","WRITE","MAIN",
};
char *yyrule[] = {
"$accept : prog",
"prog :",
"prog : prog configSet",
"$$1 :",
"configSet : IDENT $$1 '{' body '}'",
"body :",
"body : body sent",
"sent : assign ';'",
"assign : IDENT '=' exp",
"exp : exp '+' exp",
"exp : exp '-' exp",
"exp : exp '*' exp",
"exp : exp '/' exp",
"exp : '(' exp ')'",
"exp : INTEGER",
"exp : REAL",
"exp : STR",
"exp : BOOL",
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
#line 193 "gram.y"
int yyerror(const char* str)
{
  printf("Error: %s. Line %d\n", str, yylineno);
  exit(-1);
  return 0;
}


#line 218 "y.tab.c"
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
case 3:
#line 54 "gram.y"
{  currConfigSet = yyvsp[0].ident;  }
break;
case 8:
#line 63 "gram.y"
{ 
      GenericValue gv;
      switch( yyvsp[0].resultExp.type ){
      case INTEGER:
        gv.setValue(yyvsp[0].resultExp.integer);
        break;
      case REAL:
        gv.setValue(yyvsp[0].resultExp.real);
        break;
      case STR:
        gv.setValue( *(yyvsp[0].resultExp.str) );
        delete yyvsp[0].resultExp.str;
        break;
      case BOOL:
        gv.setValue( yyvsp[0].resultExp.boolean );
        break;

      }
      ConfigParser::getInstance()->appendPairToSet( currConfigSet, yyvsp[-2].ident, gv);
  }
break;
case 9:
#line 85 "gram.y"
{  
      if( yyvsp[-2].resultExp.type == STR ){
         yyerror("Cannot use string inside arithmetic operations");
      }
      if( yyvsp[-2].resultExp.type == INTEGER ){
        if ( yyvsp[0].resultExp.type == INTEGER ){
          yyval.resultExp.integer = yyvsp[-2].resultExp.integer + yyvsp[0].resultExp.integer;
          yyval.resultExp.type = INTEGER; 
        }
        else{ /* REAL */
          yyval.resultExp.real = (double)yyvsp[-2].resultExp.integer + yyvsp[0].resultExp.real;
          yyval.resultExp.type = REAL;
        }
      }
      else{ /* REAL */
        if ( yyvsp[0].resultExp.type == INTEGER ){
          yyval.resultExp.real = yyvsp[-2].resultExp.real + (double)yyvsp[0].resultExp.integer;
          yyval.resultExp.type = REAL; 
        }
        else{ /* REAL */
          yyval.resultExp.real = yyvsp[-2].resultExp.real + yyvsp[0].resultExp.real;
          yyval.resultExp.type = REAL;
        }
      }
    }
break;
case 10:
#line 110 "gram.y"
{   
    if( yyvsp[-2].resultExp.type == STR ){
         yyerror("Cannot use string inside arithmetic operations");
      }
      if( yyvsp[-2].resultExp.type == INTEGER ){
        if ( yyvsp[0].resultExp.type == INTEGER ){
          yyval.resultExp.integer = yyvsp[-2].resultExp.integer - yyvsp[0].resultExp.integer;
          yyval.resultExp.type = INTEGER; 
        }
        else{ /* REAL */
          yyval.resultExp.real = (double)yyvsp[-2].resultExp.integer - yyvsp[0].resultExp.real;
          yyval.resultExp.type = REAL;
        }
      }
      else{ /*  REAL */
        if ( yyvsp[0].resultExp.type == INTEGER ){
          yyval.resultExp.real = yyvsp[-2].resultExp.real - (double)yyvsp[0].resultExp.integer;
          yyval.resultExp.type = REAL; 
        }
        else{ /* REAL */
          yyval.resultExp.real = yyvsp[-2].resultExp.real - yyvsp[0].resultExp.real;
          yyval.resultExp.type = REAL;
        }
      }
    }
break;
case 11:
#line 135 "gram.y"
{  
      if( yyvsp[-2].resultExp.type == STR ){
         yyerror("Cannot use string inside arithmetic operations");
      }
      if( yyvsp[-2].resultExp.type == INTEGER ){
        if ( yyvsp[0].resultExp.type == INTEGER ){
          yyval.resultExp.integer = yyvsp[-2].resultExp.integer * yyvsp[0].resultExp.integer;
          yyval.resultExp.type = INTEGER;
        }
        else{ /* REAL */
          yyval.resultExp.real = (double)yyvsp[-2].resultExp.integer * yyvsp[0].resultExp.real;
          yyval.resultExp.type = REAL;
        }
      }
      else{ /* REAL */
        if ( yyvsp[0].resultExp.type == INTEGER ){
          yyval.resultExp.real = yyvsp[-2].resultExp.real * (double)yyvsp[0].resultExp.integer;
          yyval.resultExp.type = REAL; 
        }
        else{ /* REAL */
          yyval.resultExp.real = yyvsp[-2].resultExp.real * yyvsp[0].resultExp.real;
          yyval.resultExp.type = REAL;
        }
      }
    }
break;
case 12:
#line 160 "gram.y"
{  
      if( yyvsp[-2].resultExp.type == STR ){
         yyerror("Cannot use string inside arithmetic operations");
      }
      if( yyvsp[-2].resultExp.type == INTEGER ){
        if ( yyvsp[0].resultExp.type == INTEGER ){
          yyval.resultExp.integer = yyvsp[-2].resultExp.integer / yyvsp[0].resultExp.integer;
          yyval.resultExp.type = INTEGER; 
        }
        else{ /* REAL */
          yyval.resultExp.real = (double)yyvsp[-2].resultExp.integer / yyvsp[0].resultExp.real;
          yyval.resultExp.type = REAL;
        }
      }
      else{ /* REAL */
        if ( yyvsp[0].resultExp.type == INTEGER ){
          yyval.resultExp.real = yyvsp[-2].resultExp.real / (double)yyvsp[0].resultExp.integer;
          yyval.resultExp.type = REAL; 
        }
        else{ /* REAL */
          yyval.resultExp.real = yyvsp[-2].resultExp.real / yyvsp[0].resultExp.real;
          yyval.resultExp.type = REAL;
        }
      }
    }
break;
case 13:
#line 185 "gram.y"
{ yyval.resultExp = yyvsp[-1].resultExp; }
break;
case 14:
#line 186 "gram.y"
{ yyval.resultExp = yyvsp[0].resultExp; }
break;
case 15:
#line 187 "gram.y"
{ yyval.resultExp = yyvsp[0].resultExp; }
break;
case 16:
#line 188 "gram.y"
{ yyval.resultExp = yyvsp[0].resultExp; }
break;
case 17:
#line 189 "gram.y"
{ yyval.resultExp = yyvsp[0].resultExp; }
break;
#line 555 "y.tab.c"
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
