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
  #include "tablasimbolos.h"
  #include "tablatipos.h"
  #include "tipoint.h"
  #include "tipodouble.h"
  #include "tipoarray.h"
  #include "tipostruct.h"
  #include "tipofuncion.h"
  #include "tipo.h"
  #include "simbolo.h"
  #include "campo.h"
  #include <string>
  #include <vector>
  #include <iostream>

  #include "accionesCompilacion.h"

  using namespace std;

extern int yyparse(void);
extern int yylex(void);
extern int yylineno;

  TablaSimbolos tablaSimbolos;
  TablaTipos tablaTipos;
  Tipo* tipo;

  /* Donde se almacenara, para cada bloque, el nº de bytes reservados
   * para las vbles locales. Será el "n" que usará el return al salir
   * de la función 
   
   En cada nuevo bloque, push_back(0).
   En cada reserva, back() += 
   Al salir de un bloque, pop_back()
   */
  vector< size_t > reservasLocales;
#line 40 "gram.y"
typedef union {
  int entero;
  double real;
  Campo* campo;
  TipoExpr tipoexpr;
  Tipo* tipo;
  Simbolo* simbolo;
  vector< Simbolo* > *listaSimbolos;
  char ident[128];
  int etiqueta;
  string* cadena;
  } YYSTYPE;
#line 72 "y.tab.c"
#define ENTERO 257
#define REAL 258
#define INT 259
#define DOUBLE 260
#define VOID 261
#define IDENT 262
#define CADENA 263
#define READ 264
#define WRITE 265
#define MAIN 266
#define IF 267
#define ELSE 268
#define STRUCT 269
#define RETURN 270
#define WHILE 271
#define IGUAL 272
#define DISTINTO 273
#define MAYORIGUAL 274
#define MENORIGUAL 275
#define AND 276
#define OR 277
#define NOT 278
#define MENOSUNARIO 279
#define CAST 280
#define CORCHETES 281
#define YYERRCODE 256
short yylhs[] = {                                        -1,
    0,   13,    0,   12,   12,   15,   16,   18,   19,   14,
    3,    3,    4,    4,    7,    7,    7,    9,   10,    8,
    8,    6,    6,   20,   20,   17,   17,   21,   21,   21,
   21,   21,   21,   21,   22,   22,   22,   25,   27,   23,
   26,   26,   28,   29,   24,    1,    1,    1,   30,   31,
    1,    1,    2,    2,   32,    5,   33,    5,   34,    5,
   35,    5,   36,    5,    5,   37,    5,   38,    5,   39,
    5,   40,    5,   41,    5,   42,    5,   43,    5,   44,
    5,    5,    5,    5,    5,    5,    5,    5,    5,    5,
   11,   11,   11,
};
short yylen[] = {                                         2,
    0,    0,    3,    2,    1,    0,    0,    0,    0,   13,
    3,    2,    1,    3,    2,    4,    0,    2,    2,    3,
    1,    1,    4,    2,    1,    2,    0,    1,    2,    2,
    2,    3,    1,    0,    1,    1,    3,    0,    0,    8,
    2,    0,    0,    0,    7,    1,    1,    1,    0,    0,
    7,    2,    3,    0,    0,    4,    0,    4,    0,    4,
    0,    4,    0,    4,    2,    0,    4,    0,    4,    0,
    4,    0,    4,    0,    4,    0,    4,    0,    4,    0,
    4,    2,    3,    4,    4,    3,    1,    1,    1,    4,
    1,    3,    0,
};
short yydefred[] = {                                      1,
    2,    0,   46,   47,   48,    0,    0,    0,    3,    5,
    0,    0,   21,    0,    4,   49,    0,    0,    0,   54,
    0,    0,    0,   20,    0,   23,    0,    0,    0,   50,
    0,    0,   15,    7,    0,    0,   51,    0,   53,    0,
    0,    0,    8,   16,   27,    0,   87,   88,    0,    0,
    0,    0,    0,   43,    0,    0,    0,   27,    9,    0,
   28,   26,    0,   25,   35,   36,    0,    0,   31,    0,
    0,   12,    0,    0,    0,    0,    0,    0,    0,    0,
   74,   76,   70,   72,   78,   80,    0,   68,   66,   55,
   57,   59,   61,   63,    0,    0,   24,    0,    0,    0,
   11,    0,    0,   83,   37,   10,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,   86,   90,    0,   38,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
   85,    0,    0,   44,   39,    0,    0,   45,    0,   40,
   41,
};
short yydgoto[] = {                                       1,
   31,   25,   59,   28,   60,   13,   29,   14,    8,   61,
   99,    9,    2,   10,   18,   40,   46,   45,   80,   62,
   63,   64,   65,   66,  143,  150,  147,   74,  146,   20,
   37,  116,  117,  118,  119,  120,  115,  114,  109,  110,
  107,  108,  111,  112,
};
short yysindex[] = {                                      0,
    0, -210,    0,    0,    0, -259, -249,  -45,    0,    0,
  -92,  -52,    0,   -3,    0,    0, -192,   26, -178,    0,
   -2, -210,  -52,    0, -124,    0, -170,  -14,    9,    0,
 -178,   42,    0,    0, -210, -155,    0,   -3,    0,  -13,
    9,   24,    0,    0,    0,  252,    0,    0,   79,  216,
  188,   86,  227,    0,  216,  216,  280,    0,    0,   97,
    0,    0,   52,    0,    0,    0,  216,  380,    0,  380,
  216,    0,  123,   87,  -34,  -34,  107,  130,  286,   13,
    0,    0,    0,    0,    0,    0,  216,    0,    0,    0,
    0,    0,    0,    0,  216, -110,    0,  380,   14,  162,
    0,  216,  216,    0,    0,    0,  216,  216,  216,  216,
  216,  216,  380,  216,  216,  216,  216,  216,  216,  216,
  223,    0,    0,  216,    0,  317,  -34,  104,  104,  104,
  104,  417,  410,  104,  104,  164,  164,  -34,  -34,  -34,
    0,  380,  310,    0,    0,  310, -114,    0,  310,    0,
    0,
};
short yyrindex[] = {                                      0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  -39,  -12,    0,  102,    0,    0,    0,    0,    0,    0,
    0,  -15,   -7,    0,    0,    0,    0,    0,   41,    0,
    0,    0,    0,    0,  -15,    0,    0,  103,    0,    0,
   49,    0,    0,    0,    0,  115,    0,    0,  -37,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  120,
    0,    0,    0,    0,    0,    0,   84,  121,    0,  127,
    0,    0,    0,    0,  -26,    1,    0,    0,  115,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  112,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  134,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,   27,  586,  634,  656,
  662,  137,  695,  669,  691,  573,  580,   36,   62,   71,
    0,  143,  115,    0,    0,  115,  342,    0,  115,    0,
    0,
};
short yygindex[] = {                                      0,
   18,    0,    0,    0,  690,  144,  154,  169,    0,  177,
    0,    0,    0,    0,    0,    0,  155,    0,    0,   48,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,
};
#define YYTABLESIZE 972
short yytable[] = {                                      89,
   30,   52,   11,   89,   89,   89,   89,   89,   89,   89,
   82,   96,   12,   15,   82,   82,   82,   82,   82,    7,
   82,   89,   89,   89,   89,   17,   34,    6,   17,   35,
   16,   22,   82,   82,   82,   82,   22,   65,   17,   27,
   19,   65,   65,   65,   65,   65,   22,   65,    3,    4,
    5,   22,   27,   89,  123,   89,   95,  124,    6,   65,
   65,   65,   65,   84,   21,   22,   82,   84,   84,   84,
   84,   84,   60,   84,   77,   17,   60,   60,   60,   60,
   60,   13,   60,   23,   13,   84,   84,   84,   84,   14,
   26,   33,   14,   65,   60,   60,   60,   60,   62,   36,
   39,   42,   62,   62,   62,   62,   62,   64,   62,   43,
   97,   64,   64,   64,   64,   64,   44,   64,   67,   84,
   62,   62,   62,   62,   93,   71,  102,   93,   60,   64,
   64,   64,   64,   94,    3,    4,    5,  106,   92,   90,
   94,   91,   96,   93,    6,   92,   90,  103,   91,   96,
   93,  122,   91,  149,   62,   91,   88,   87,   89,   94,
   18,   19,   24,   64,   92,   90,   94,   91,   96,   93,
  104,   92,   90,   34,   91,   96,   93,   79,   33,   29,
   79,  101,   88,   92,   89,   30,   92,   95,   41,   88,
  145,   89,   32,  148,   95,   79,  151,   79,   94,   38,
   94,   32,  125,   92,   90,   92,   91,   96,   93,   96,
   93,    0,   79,   95,    0,    0,    0,    0,    0,    0,
   95,   88,   52,   89,    0,    0,    0,   57,    0,   79,
    0,    0,   56,    0,   89,   89,   89,   89,   89,   89,
    0,    0,    0,    0,    0,   82,   82,   82,   82,   82,
   82,    0,   95,    0,   95,   57,    0,    0,    0,   94,
   56,    0,    0,    0,   92,   90,   57,   91,   96,   93,
    0,   56,   65,   65,   65,   65,   65,   65,    0,    0,
    0,    0,   88,    0,   89,   72,    0,    0,    0,    0,
    0,   57,    0,    0,    0,    0,   56,    0,   84,   84,
   84,   84,   84,   84,    0,    0,    0,   60,   60,   60,
   60,   60,   60,   95,    0,  141,    0,    0,    0,   57,
    0,    0,    0,    0,   56,   57,    0,    0,    0,    0,
   56,    0,    0,   62,   62,   62,   62,   62,   62,    0,
    0,    0,   64,   64,   64,   64,   64,   64,    0,   57,
    0,    0,    0,   94,   56,    0,    0,  144,   92,   90,
    0,   91,   96,   93,    0,    0,    0,    0,   81,   82,
   83,   84,   85,   86,   58,    0,   88,    0,   89,    0,
    0,   42,    0,    0,    0,    0,   42,    0,    0,    0,
    0,    0,    0,    0,   81,   82,   83,   84,   85,   86,
   42,   81,   82,   83,   84,   85,   86,   95,   58,    0,
  105,    0,   79,   79,    0,    0,   94,    0,    0,    0,
    0,   92,   90,    0,   91,   96,   93,    0,    0,    0,
    0,    0,   58,   81,   82,   83,   84,   85,   86,   88,
    0,   89,    0,    0,   47,   48,   94,    0,    0,   49,
   69,   92,   90,   94,   91,   96,   93,    0,   92,   90,
    0,   91,   96,   93,   42,   55,   42,    0,    0,   88,
   95,   89,   47,   48,    0,    0,   88,   49,   89,    0,
    0,    0,    0,   47,   48,    0,    0,    0,   49,    0,
    0,    0,    0,   55,   81,   82,   83,   84,   85,   86,
   95,    0,    0,    0,   55,    0,    0,   95,   47,   48,
    3,    4,    5,   49,    0,   50,   51,    0,   52,    0,
    6,   53,   54,    0,    0,    0,    0,    0,    0,   55,
    0,    0,    0,    0,    0,    0,   47,   48,    3,    4,
    5,   49,   47,   48,    3,    4,    5,   49,    6,   50,
   51,    0,   52,    0,    6,    0,   54,   55,    0,    0,
    0,    0,    0,   55,    0,    0,   47,   48,    3,    4,
    5,   49,    0,   50,   51,    0,   52,    0,    6,    0,
   54,    0,    0,    0,    0,    0,    0,   55,   81,   82,
   83,   84,   85,   86,    0,    0,    0,    0,   42,   42,
   42,   42,   42,   42,    0,   42,   42,    0,   42,    0,
   42,   42,   42,   56,    0,   56,   56,   56,    0,   42,
   58,    0,   58,   58,   58,    0,   75,    0,    0,   75,
    0,   56,   56,   56,   56,    0,    0,    0,   58,   58,
   58,   58,    0,    0,   75,   75,   75,   75,    0,    0,
    0,   81,   82,   83,   84,   85,   86,    0,    0,    0,
    0,    0,    0,    0,    0,   56,    0,    0,    0,    0,
    0,    0,   58,    0,   77,    0,    0,   77,   75,    0,
    0,   81,   82,   83,   84,   85,    0,    0,   81,   82,
   83,   84,   77,   77,   77,   77,   71,    0,    0,   71,
    0,    0,   73,    0,    0,   73,    0,    0,    0,   69,
    0,    0,   69,    0,   71,   71,   71,   71,    0,    0,
   73,   73,   73,   73,    0,    0,   77,   69,   69,   69,
   69,   67,    0,    0,   67,   81,    0,    0,   81,   68,
   70,    0,   73,    0,   75,   76,   78,    0,   71,   67,
   67,   67,   67,   81,   73,   81,   98,    0,    0,    0,
  100,   69,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  113,    0,    0,    0,
    0,    0,    0,   67,  121,    0,    0,   81,    0,    0,
    0,  126,  127,    0,    0,    0,  128,  129,  130,  131,
  132,  133,    0,  134,  135,  136,  137,  138,  139,  140,
    0,    0,    0,  142,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,   56,   56,   56,   56,   56,   56,
    0,   58,   58,   58,   58,   58,   58,   75,   75,   75,
   75,   75,   75,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,   77,   77,   77,   77,   77,
   77,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,   71,   71,   71,
   71,   71,   71,   73,   73,   73,   73,   73,   73,    0,
   69,   69,   69,   69,   69,   69,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,   67,   67,   67,   67,   67,   67,    0,    0,
    0,   81,
};
short yycheck[] = {                                      37,
  125,   41,  262,   41,   42,   43,   44,   45,   46,   47,
   37,   46,  262,   59,   41,   42,   43,   44,   45,    2,
   47,   59,   60,   61,   62,   41,   41,   40,   44,   44,
  123,   44,   59,   60,   61,   62,   44,   37,   91,   22,
   44,   41,   42,   43,   44,   45,   59,   47,  259,  260,
  261,   59,   35,   91,   41,   93,   91,   44,  269,   59,
   60,   61,   62,   37,  257,   40,   93,   41,   42,   43,
   44,   45,   37,   47,   57,   91,   41,   42,   43,   44,
   45,   41,   47,  262,   44,   59,   60,   61,   62,   41,
   93,  262,   44,   93,   59,   60,   61,   62,   37,   91,
   59,  257,   41,   42,   43,   44,   45,   37,   47,  123,
   59,   41,   42,   43,   44,   45,   93,   47,   40,   93,
   59,   60,   61,   62,   41,   40,   40,   44,   93,   59,
   60,   61,   62,   37,  259,  260,  261,  125,   42,   43,
   37,   45,   46,   47,  269,   42,   43,   41,   45,   46,
   47,  262,   41,  268,   93,   44,   60,   61,   62,   37,
   59,   59,   19,   93,   42,   43,   37,   45,   46,   47,
   41,   42,   43,   59,   45,   46,   47,   41,   59,   59,
   44,   59,   60,   41,   62,   59,   44,   91,   35,   60,
  143,   62,   59,  146,   91,   59,  149,   61,   37,   31,
   37,   25,   41,   42,   43,   42,   45,   46,   47,   46,
   47,   -1,   58,   91,   -1,   -1,   -1,   -1,   -1,   -1,
   91,   60,  262,   62,   -1,   -1,   -1,   40,   -1,   93,
   -1,   -1,   45,   -1,  272,  273,  274,  275,  276,  277,
   -1,   -1,   -1,   -1,   -1,  272,  273,  274,  275,  276,
  277,   -1,   91,   -1,   91,   40,   -1,   -1,   -1,   37,
   45,   -1,   -1,   -1,   42,   43,   40,   45,   46,   47,
   -1,   45,  272,  273,  274,  275,  276,  277,   -1,   -1,
   -1,   -1,   60,   -1,   62,   59,   -1,   -1,   -1,   -1,
   -1,   40,   -1,   -1,   -1,   -1,   45,   -1,  272,  273,
  274,  275,  276,  277,   -1,   -1,   -1,  272,  273,  274,
  275,  276,  277,   91,   -1,   93,   -1,   -1,   -1,   40,
   -1,   -1,   -1,   -1,   45,   40,   -1,   -1,   -1,   -1,
   45,   -1,   -1,  272,  273,  274,  275,  276,  277,   -1,
   -1,   -1,  272,  273,  274,  275,  276,  277,   -1,   40,
   -1,   -1,   -1,   37,   45,   -1,   -1,   41,   42,   43,
   -1,   45,   46,   47,   -1,   -1,   -1,   -1,  272,  273,
  274,  275,  276,  277,  123,   -1,   60,   -1,   62,   -1,
   -1,   40,   -1,   -1,   -1,   -1,   45,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  272,  273,  274,  275,  276,  277,
   59,  272,  273,  274,  275,  276,  277,   91,  123,   -1,
  125,   -1,  276,  277,   -1,   -1,   37,   -1,   -1,   -1,
   -1,   42,   43,   -1,   45,   46,   47,   -1,   -1,   -1,
   -1,   -1,  123,  272,  273,  274,  275,  276,  277,   60,
   -1,   62,   -1,   -1,  257,  258,   37,   -1,   -1,  262,
  263,   42,   43,   37,   45,   46,   47,   -1,   42,   43,
   -1,   45,   46,   47,  123,  278,  125,   -1,   -1,   60,
   91,   62,  257,  258,   -1,   -1,   60,  262,   62,   -1,
   -1,   -1,   -1,  257,  258,   -1,   -1,   -1,  262,   -1,
   -1,   -1,   -1,  278,  272,  273,  274,  275,  276,  277,
   91,   -1,   -1,   -1,  278,   -1,   -1,   91,  257,  258,
  259,  260,  261,  262,   -1,  264,  265,   -1,  267,   -1,
  269,  270,  271,   -1,   -1,   -1,   -1,   -1,   -1,  278,
   -1,   -1,   -1,   -1,   -1,   -1,  257,  258,  259,  260,
  261,  262,  257,  258,  259,  260,  261,  262,  269,  264,
  265,   -1,  267,   -1,  269,   -1,  271,  278,   -1,   -1,
   -1,   -1,   -1,  278,   -1,   -1,  257,  258,  259,  260,
  261,  262,   -1,  264,  265,   -1,  267,   -1,  269,   -1,
  271,   -1,   -1,   -1,   -1,   -1,   -1,  278,  272,  273,
  274,  275,  276,  277,   -1,   -1,   -1,   -1,  257,  258,
  259,  260,  261,  262,   -1,  264,  265,   -1,  267,   -1,
  269,  270,  271,   41,   -1,   43,   44,   45,   -1,  278,
   41,   -1,   43,   44,   45,   -1,   41,   -1,   -1,   44,
   -1,   59,   60,   61,   62,   -1,   -1,   -1,   59,   60,
   61,   62,   -1,   -1,   59,   60,   61,   62,   -1,   -1,
   -1,  272,  273,  274,  275,  276,  277,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   93,   -1,   -1,   -1,   -1,
   -1,   -1,   93,   -1,   41,   -1,   -1,   44,   93,   -1,
   -1,  272,  273,  274,  275,  276,   -1,   -1,  272,  273,
  274,  275,   59,   60,   61,   62,   41,   -1,   -1,   44,
   -1,   -1,   41,   -1,   -1,   44,   -1,   -1,   -1,   41,
   -1,   -1,   44,   -1,   59,   60,   61,   62,   -1,   -1,
   59,   60,   61,   62,   -1,   -1,   93,   59,   60,   61,
   62,   41,   -1,   -1,   44,   41,   -1,   -1,   44,   50,
   51,   -1,   53,   -1,   55,   56,   57,   -1,   93,   59,
   60,   61,   62,   59,   93,   61,   67,   -1,   -1,   -1,
   71,   93,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   87,   -1,   -1,   -1,
   -1,   -1,   -1,   93,   95,   -1,   -1,   93,   -1,   -1,
   -1,  102,  103,   -1,   -1,   -1,  107,  108,  109,  110,
  111,  112,   -1,  114,  115,  116,  117,  118,  119,  120,
   -1,   -1,   -1,  124,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  272,  273,  274,  275,  276,  277,
   -1,  272,  273,  274,  275,  276,  277,  272,  273,  274,
  275,  276,  277,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  272,  273,  274,  275,  276,
  277,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  272,  273,  274,
  275,  276,  277,  272,  273,  274,  275,  276,  277,   -1,
  272,  273,  274,  275,  276,  277,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  272,  273,  274,  275,  276,  277,   -1,   -1,
   -1,  277,
};
#define YYFINAL 1
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 281
#if YYDEBUG
char *yyname[] = {
"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,"'%'",0,0,"'('","')'","'*'","'+'","','","'-'","'.'","'/'",0,0,0,0,0,0,0,0,
0,0,0,"';'","'<'","'='","'>'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,"'['",0,"']'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
"'{'",0,"'}'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"ENTERO","REAL","INT","DOUBLE","VOID",
"IDENT","CADENA","READ","WRITE","MAIN","IF","ELSE","STRUCT","RETURN","WHILE",
"IGUAL","DISTINTO","MAYORIGUAL","MENORIGUAL","AND","OR","NOT","MENOSUNARIO",
"CAST","CORCHETES",
};
char *yyrule[] = {
"$accept : prog",
"prog :",
"$$1 :",
"prog : prog $$1 globales",
"globales : declaracionGlobal ';'",
"globales : declaracionFuncion",
"$$2 :",
"$$3 :",
"$$4 :",
"$$5 :",
"declaracionFuncion : tipo IDENT $$2 '(' paramsFunc ')' $$3 '{' $$4 sents devolver $$5 '}'",
"devolver : RETURN exp ';'",
"devolver : RETURN ';'",
"paramsFunc : declaracionParametros",
"paramsFunc : paramsFunc ',' declaracionParametros",
"declaracionParametros : tipo IDENT",
"declaracionParametros : declaracionParametros '[' ENTERO ']'",
"declaracionParametros :",
"declaracionGlobal : tipo listaVars",
"declaracion : tipo listaVars",
"listaVars : listaVars ',' elemListaVars",
"listaVars : elemListaVars",
"elemListaVars : IDENT",
"elemListaVars : IDENT '[' ENTERO ']'",
"sent : sentSimple ';'",
"sent : sentBloque",
"sents : sents sent",
"sents :",
"sentSimple : declaracion",
"sentSimple : READ exp",
"sentSimple : WRITE exp",
"sentSimple : WRITE CADENA",
"sentSimple : exp '=' exp",
"sentSimple : exp",
"sentSimple :",
"sentBloque : if",
"sentBloque : while",
"sentBloque : '{' sents '}'",
"$$6 :",
"$$7 :",
"if : IF '(' exp ')' $$6 sent $$7 elseOpt",
"elseOpt : ELSE sent",
"elseOpt :",
"$$8 :",
"$$9 :",
"while : WHILE $$8 '(' exp ')' $$9 sent",
"tipo : INT",
"tipo : DOUBLE",
"tipo : VOID",
"$$10 :",
"$$11 :",
"tipo : STRUCT IDENT '{' $$10 camposStruct '}' $$11",
"tipo : STRUCT IDENT",
"camposStruct : camposStruct declaracion ';'",
"camposStruct :",
"$$12 :",
"exp : exp '+' $$12 exp",
"$$13 :",
"exp : exp '-' $$13 exp",
"$$14 :",
"exp : exp '*' $$14 exp",
"$$15 :",
"exp : exp '/' $$15 exp",
"$$16 :",
"exp : exp '%' $$16 exp",
"exp : '-' exp",
"$$17 :",
"exp : exp '>' $$17 exp",
"$$18 :",
"exp : exp '<' $$18 exp",
"$$19 :",
"exp : exp MAYORIGUAL $$19 exp",
"$$20 :",
"exp : exp MENORIGUAL $$20 exp",
"$$21 :",
"exp : exp IGUAL $$21 exp",
"$$22 :",
"exp : exp DISTINTO $$22 exp",
"$$23 :",
"exp : exp AND $$23 exp",
"$$24 :",
"exp : exp OR $$24 exp",
"exp : NOT exp",
"exp : '(' exp ')'",
"exp : '(' tipo ')' exp",
"exp : exp '[' exp ']'",
"exp : exp '.' IDENT",
"exp : ENTERO",
"exp : REAL",
"exp : IDENT",
"exp : IDENT '(' argumentos ')'",
"argumentos : exp",
"argumentos : argumentos ',' exp",
"argumentos :",
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
#line 543 "gram.y"
int yyerror(const char* str)
{
  printf("Error: %s. Construcción incorrecta finaliza en línea %d\n", str, yylineno);
  exit(-1);
  
}

int main(int argc, char** argv)
{
  extern FILE* yyin;
  extern FILE* yyout;

  switch( argc ){
  case 3:
    yyout = fopen( argv[2], "w" );
  case 2:
    yyin = fopen( argv[1], "r" );
    break;
  default:
    yyin = stdin;
    yyout = stdout;
  }

  inicializarCompilador();
  yyparse();
  fclose(yyin);
  return 0;
}
#line 570 "y.tab.c"
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
case 2:
#line 85 "gram.y"
{ yyval.listaSimbolos = new vector< Simbolo *>; }
break;
case 6:
#line 93 "gram.y"
{ 
                                  int findex=0;
                                  char nombreFunc[128];
                                  do{
                                   findex++;
                                   snprintf(nombreFunc, 128, "%s_%d", yyvsp[0].ident, findex);
                                  } while( tablaTipos.buscar(nombreFunc) );
                                  printf("%s:\n", nombreFunc); 
                                  yyval.cadena = new string(nombreFunc);
                                }
break;
case 7:
#line 103 "gram.y"
{  
                          /* no existia, insertarlo */
                          ((TipoFuncion*)yyvsp[-1].tipo)->setTipo(yyvsp[-5].tipo);
                          tablaTipos.insertar(*(yyvsp[-3].cadena) , yyvsp[-1].tipo);

                          tablaSimbolos.insertar(new Simbolo(*(yyvsp[-3].cadena), yyvsp[-1].tipo)); 
                          delete yyvsp[-3].cadena;
                      }
break;
case 8:
#line 112 "gram.y"
{ 
                          tablaSimbolos.set();
                          reservasLocales.push_back(0);

                          TipoFuncion* func = dynamic_cast< TipoFuncion* >(yyvsp[-3].tipo);
                          int desp= -4; /*hay que saltarse el BP antiguo y la dirección de retorno*/
                          for(int i=func->numeroParametros()-1; i>=0;i--){
                            Simbolo* campoParam = func->getParametro(i);
                            Tipo* tipoParam = campoParam->getTipo();
                            Simbolo* nuevoSimbolo;
  
                            if( tipoParam->pasoPorReferencia() ){
                              nuevoSimbolo = 
                                new Simbolo(
                                  campoParam->getNombre(), 
                                  tipoParam, 
                                  desp);
                              nuevoSimbolo->setParametroPorRef();
                              desp-= 2; /*ya que las referencias son  enteros (posiciones de memoria)*/
                            }
                            else{ /*paso por valor*/
                              nuevoSimbolo = 
                                new Simbolo(
                                  campoParam->getNombre(), 
                                  tipoParam, 
                                  desp);
                              desp-=tipoParam->getTam();
                            }

                            tablaSimbolos.insertar(nuevoSimbolo);
                          }
                         }
break;
case 9:
#line 147 "gram.y"
{
                          if ( yyvsp[0].tipo != yyvsp[-10].tipo )
                            yyerror("Se intenta retornar un tipo"
                                    "incompatible con la declaración de la"
                                    "función");
                        }
break;
case 10:
#line 154 "gram.y"
{
                      int m = ((TipoFuncion*)yyvsp[-8].tipo)->calcularM();
                      int n = reservasLocales.back();
                      if( string(yyvsp[-11].ident) != string("Main") ){
                      if( yyvsp[-12].tipo->getNombre() == "int" )
                        printf("IReturn %d %d\n", n,m); 
                      else if ( yyvsp[-12].tipo->getNombre() == "double" )
                        printf("FReturn %d %d\n", n,m); 
                      else if ( yyvsp[-12].tipo->getNombre() == "void" )
                        printf("Return %d %d\n", n,m); 
                      }
                      reservasLocales.pop_back();
                      tablaSimbolos.reset();
                    }
break;
case 11:
#line 170 "gram.y"
{ /*queda apilado el resultado a devolver*/
          cargarDato(yyvsp[-1].tipoexpr);
          yyval.tipo = yyvsp[-1].tipoexpr.tipo; }
break;
case 12:
#line 174 "gram.y"
{ yyval.tipo = tablaTipos.buscar("void"); }
break;
case 13:
#line 178 "gram.y"
{ TipoFuncion* nuevaFuncion = new TipoFuncion();
                 if( yyvsp[0].simbolo )
                   nuevaFuncion->insertar(yyvsp[0].simbolo);
                 yyval.tipo = nuevaFuncion; }
break;
case 14:
#line 183 "gram.y"
{ ((TipoFuncion*)yyvsp[-2].tipo)->insertar(yyvsp[0].simbolo);
                  yyval.tipo = yyvsp[-2].tipo; }
break;
case 15:
#line 189 "gram.y"
{ yyval.simbolo = new Simbolo(yyvsp[0].ident, yyvsp[-1].tipo); }
break;
case 16:
#line 191 "gram.y"
{  TipoArray* tipoArray = new TipoArray( yyvsp[-3].simbolo->getTipo(), yyvsp[-1].entero );
                        yyval.simbolo = new Simbolo( yyvsp[-3].simbolo->getNombre(), tipoArray ); 
                     }
break;
case 17:
#line 194 "gram.y"
{ yyval.simbolo = NULL; }
break;
case 18:
#line 199 "gram.y"
{ compilarDeclaracion(*yyvsp[0].listaSimbolos, yyvsp[-1].tipo, true);
                                    yyval.listaSimbolos = yyvsp[0].listaSimbolos; }
break;
case 19:
#line 202 "gram.y"
{ compilarDeclaracion(*yyvsp[0].listaSimbolos, yyvsp[-1].tipo, false); 
                              yyval.listaSimbolos = yyvsp[0].listaSimbolos; }
break;
case 20:
#line 205 "gram.y"
{ yyval.listaSimbolos->push_back(yyvsp[0].simbolo); }
break;
case 21:
#line 206 "gram.y"
{ yyval.listaSimbolos = new vector< Simbolo *>;
                           yyval.listaSimbolos->push_back(yyvsp[0].simbolo); }
break;
case 22:
#line 210 "gram.y"
{ yyval.simbolo = new Simbolo(yyvsp[0].ident); }
break;
case 23:
#line 212 "gram.y"
{
               yyval.simbolo = new Simbolo(yyvsp[-3].ident);
               yyval.simbolo->setDimension(yyvsp[-1].entero); 
             }
break;
case 28:
#line 226 "gram.y"
{ /*reservar el espacio en la pila  */
                          size_t numBytes = 0;
                          for(int i=0; i < yyvsp[0].listaSimbolos->size(); i++){
                            numBytes += (*yyvsp[0].listaSimbolos)[i]->getTipo()->getTam();
                          }
                          printf("RESRV %d\n", numBytes);
                          reservasLocales.back() += numBytes;
                        }
break;
case 29:
#line 234 "gram.y"
{ if( !yyvsp[0].tipoexpr.lvalue ){
                          string tmp = "El tipo " +
                          yyvsp[0].tipoexpr.tipo->getNombre() + " no es lvalue";
                          yyerror(tmp.c_str());
                        }
                        compilarObtener(yyvsp[0].tipoexpr.tipo);
                      }
break;
case 30:
#line 241 "gram.y"
{ if( !yyvsp[0].tipoexpr.tipo->esImprimible() ){
                          string tmp = "El tipo " +
                          yyvsp[0].tipoexpr.tipo->getNombre() + " no es imprimible";
                          yyerror(tmp.c_str());
                        }
                        cargarDato(yyvsp[0].tipoexpr);
                        compilarImprimir(yyvsp[0].tipoexpr.tipo);
                      }
break;
case 31:
#line 249 "gram.y"
{
                            printf("PRINT %s\n", yylval.cadena->c_str());
                            delete yylval.cadena;
                          }
break;
case 32:
#line 253 "gram.y"
{
                 if ( ! yyvsp[-2].tipoexpr.lvalue )
                   yyerror("Expresion izquierda en asignación no es lvalue");
                 if( dynamic_cast< TipoInt *>(yyvsp[-2].tipoexpr.tipo)  ){
                   if( yyvsp[0].tipoexpr.tipo != yyvsp[-2].tipoexpr.tipo ) /* la expresion no es de tipo entero         */
                     yyerror("Asignación a entero no válida");
                   cargarDato(yyvsp[0].tipoexpr);
                   printf("ISTORE\n");
                 }
                 else if ( dynamic_cast< TipoDouble* >(yyvsp[-2].tipoexpr.tipo)  ){
                   if( yyvsp[0].tipoexpr.tipo != yyvsp[-2].tipoexpr.tipo ) /* si la expresion no es real...*/
                     if( dynamic_cast< TipoInt *>(yyvsp[0].tipoexpr.tipo) ) /* salvo que sea entera...*/
                       printf("CAST\n");
                     else
                       yyerror("Asignación a real no válida");
                   cargarDato(yyvsp[0].tipoexpr);
                   printf("FSTORE\n");
                 }
         }
break;
case 33:
#line 273 "gram.y"
{ /* dejan un valor en la pila que es basura */ 
            if( dynamic_cast< TipoInt*>(yyvsp[0].tipoexpr.tipo) )
              printf("IPOP\n");
            else if ( dynamic_cast< TipoDouble* >(yyvsp[0].tipoexpr.tipo))
              printf("FPOP\n");
          }
break;
case 38:
#line 287 "gram.y"
{ 
                      yyval.etiqueta = nextLabel();
                      cargarDato(yyvsp[-1].tipoexpr);
                      printf("JMPZero else%d\n", yyval.etiqueta);
                     }
break;
case 39:
#line 292 "gram.y"
{ printf("JMP EndIf%d\n", yyvsp[-1].etiqueta);
                     printf("else%d:\n", yyvsp[-1].etiqueta);
                   }
break;
case 40:
#line 295 "gram.y"
{ printf("EndIf%d:\n", yyvsp[-3].etiqueta); }
break;
case 43:
#line 303 "gram.y"
{
               yyval.etiqueta = nextLabel();
               printf("BeginWhile%d:\n", yyval.etiqueta);
            }
break;
case 44:
#line 307 "gram.y"
{  cargarDato(yyvsp[-1].tipoexpr);
                     printf("JMPZero EndWhile%d\n", yyvsp[-3].etiqueta);
                  }
break;
case 45:
#line 310 "gram.y"
{ printf("JMP BeginWhile%d\n", yyvsp[-5].etiqueta);
                     printf("EndWhile%d:\n", yyvsp[-5].etiqueta);
                   }
break;
case 46:
#line 321 "gram.y"
{ yyval.tipo = yyvsp[0].tipo; }
break;
case 47:
#line 322 "gram.y"
{ yyval.tipo = yyvsp[0].tipo; }
break;
case 48:
#line 323 "gram.y"
{ yyval.tipo = yyvsp[0].tipo; }
break;
case 49:
#line 325 "gram.y"
{ tablaSimbolos.set(); }
break;
case 50:
#line 327 "gram.y"
{ tablaSimbolos.reset(); }
break;
case 51:
#line 328 "gram.y"
{
        string nombreStruct = "struct " + string(yyvsp[-5].ident);
        tablaTipos.insertar(nombreStruct, (TipoStruct*)yyvsp[-2].tipo);
        yyval.tipo = (TipoStruct*)yyvsp[-2].tipo;
    }
break;
case 52:
#line 334 "gram.y"
{
      TipoStruct* tipoStruct;
      string nombreStruct = "struct " + string(yyvsp[0].ident);
      if( tipoStruct = dynamic_cast< TipoStruct* >(tablaTipos.buscar(nombreStruct)))
        yyval.tipo = tipoStruct;
      else{
        string tmp = "Estructura " + string(yyvsp[0].ident) + " no declarada previamente";
        yyerror(tmp.c_str());
      }
    }
break;
case 53:
#line 347 "gram.y"
{ 
                for( int i = 0; i < yyvsp[-1].listaSimbolos->size(); i++ ){
                  /*el control de declaraciones repetidas se lleva a*/
                  /*cabo por la produccion "declaracion"*/
                  ((TipoStruct*)yyvsp[-2].tipo)->insertar( (*yyvsp[-1].listaSimbolos)[i]->getNombre(), (*yyvsp[-1].listaSimbolos)[i]->getTipo());
                }
                yyval.tipo = yyvsp[-2].tipo;
              }
break;
case 54:
#line 355 "gram.y"
{ yyval.tipo= new TipoStruct(); }
break;
case 55:
#line 358 "gram.y"
{ cargarDato(yyvsp[-1].tipoexpr); }
break;
case 56:
#line 359 "gram.y"
{  cargarDato(yyvsp[0].tipoexpr);
              yyval.tipoexpr.tipo = compilaSuma(yyvsp[-3].tipoexpr.tipo, yyvsp[0].tipoexpr.tipo); 
              yyval.tipoexpr.lvalue = false;
              yyval.tipoexpr.cargado = true;
            }
break;
case 57:
#line 364 "gram.y"
{ cargarDato(yyvsp[-1].tipoexpr); }
break;
case 58:
#line 365 "gram.y"
{ 
              cargarDato(yyvsp[0].tipoexpr);
              yyval.tipoexpr.tipo = compilaResta(yyvsp[-3].tipoexpr.tipo, yyvsp[0].tipoexpr.tipo); 
              yyval.tipoexpr.lvalue = false;
              yyval.tipoexpr.cargado = true;
          }
break;
case 59:
#line 371 "gram.y"
{ cargarDato(yyvsp[-1].tipoexpr); }
break;
case 60:
#line 372 "gram.y"
{  
              cargarDato(yyvsp[0].tipoexpr);
              yyval.tipoexpr.tipo = compilaProducto(yyvsp[-3].tipoexpr.tipo, yyvsp[0].tipoexpr.tipo); 
              yyval.tipoexpr.lvalue = false;
              yyval.tipoexpr.cargado = true;
          }
break;
case 61:
#line 378 "gram.y"
{ cargarDato(yyvsp[-1].tipoexpr); }
break;
case 62:
#line 379 "gram.y"
{ 
              cargarDato(yyvsp[0].tipoexpr);
              yyval.tipoexpr.tipo = compilaDivision(yyvsp[-3].tipoexpr.tipo, yyvsp[0].tipoexpr.tipo); 
              yyval.tipoexpr.lvalue = false;
              yyval.tipoexpr.cargado = true;
          }
break;
case 63:
#line 385 "gram.y"
{ cargarDato(yyvsp[-1].tipoexpr); }
break;
case 64:
#line 386 "gram.y"
{ 
              cargarDato(yyvsp[0].tipoexpr);
              yyval.tipoexpr.tipo = compilaModulo(yyvsp[-3].tipoexpr.tipo, yyvsp[0].tipoexpr.tipo); 
              yyval.tipoexpr.lvalue = false;
              yyval.tipoexpr.cargado = true;
          }
break;
case 65:
#line 393 "gram.y"
{ cargarDato(yyvsp[0].tipoexpr);
                                  yyval.tipoexpr.tipo = compilaMenosUnario(yyvsp[0].tipoexpr.tipo); 
                                  yyval.tipoexpr.lvalue = false;
                                  yyval.tipoexpr.cargado = true;}
break;
case 66:
#line 397 "gram.y"
{ cargarDato(yyvsp[-1].tipoexpr); }
break;
case 67:
#line 398 "gram.y"
{ 
               cargarDato(yyvsp[0].tipoexpr);
               yyval.tipoexpr.tipo = compilaMayor(yyvsp[-3].tipoexpr.tipo, yyvsp[0].tipoexpr.tipo); 
               yyval.tipoexpr.lvalue = false;
               yyval.tipoexpr.cargado = true;
           }
break;
case 68:
#line 404 "gram.y"
{ cargarDato(yyvsp[-1].tipoexpr); }
break;
case 69:
#line 405 "gram.y"
{ 
               cargarDato(yyvsp[0].tipoexpr);
               yyval.tipoexpr.tipo = compilaMenor(yyvsp[-3].tipoexpr.tipo, yyvsp[0].tipoexpr.tipo); 
               yyval.tipoexpr.lvalue = false;
               yyval.tipoexpr.cargado = true;
           }
break;
case 70:
#line 411 "gram.y"
{ cargarDato(yyvsp[-1].tipoexpr); }
break;
case 71:
#line 412 "gram.y"
{ 
               cargarDato(yyvsp[0].tipoexpr);
               yyval.tipoexpr.tipo = compilaMayorIgual(yyvsp[-3].tipoexpr.tipo, yyvsp[0].tipoexpr.tipo); 
               yyval.tipoexpr.lvalue = false;
               yyval.tipoexpr.cargado = true;
          }
break;
case 72:
#line 418 "gram.y"
{ cargarDato(yyvsp[-1].tipoexpr); }
break;
case 73:
#line 419 "gram.y"
{ 
               cargarDato(yyvsp[0].tipoexpr);
               yyval.tipoexpr.tipo = compilaMenorIgual(yyvsp[-3].tipoexpr.tipo, yyvsp[0].tipoexpr.tipo); 
               yyval.tipoexpr.lvalue = false;
               yyval.tipoexpr.cargado = true;
          }
break;
case 74:
#line 425 "gram.y"
{ cargarDato(yyvsp[-1].tipoexpr); }
break;
case 75:
#line 426 "gram.y"
{ 
               cargarDato(yyvsp[0].tipoexpr);
               yyval.tipoexpr.tipo = compilaIgual(yyvsp[-3].tipoexpr.tipo, yyvsp[0].tipoexpr.tipo); 
               yyval.tipoexpr.lvalue = false;
               yyval.tipoexpr.cargado = true;
          }
break;
case 76:
#line 432 "gram.y"
{ cargarDato(yyvsp[-1].tipoexpr); }
break;
case 77:
#line 433 "gram.y"
{ 
               cargarDato(yyvsp[0].tipoexpr);
               yyval.tipoexpr.tipo = compilaDistinto(yyvsp[-3].tipoexpr.tipo, yyvsp[0].tipoexpr.tipo); 
               yyval.tipoexpr.lvalue = false;
               yyval.tipoexpr.cargado = true;
          }
break;
case 78:
#line 439 "gram.y"
{ cargarDato(yyvsp[-1].tipoexpr); }
break;
case 79:
#line 440 "gram.y"
{ 
               cargarDato(yyvsp[0].tipoexpr);
               yyval.tipoexpr.tipo = compilaAND(yyvsp[-3].tipoexpr.tipo, yyvsp[0].tipoexpr.tipo); 
               yyval.tipoexpr.lvalue = false;
               yyval.tipoexpr.cargado = true;
          }
break;
case 80:
#line 446 "gram.y"
{ cargarDato(yyvsp[-1].tipoexpr); }
break;
case 81:
#line 447 "gram.y"
{ 
               cargarDato(yyvsp[0].tipoexpr);
               yyval.tipoexpr.tipo = compilaOR(yyvsp[-3].tipoexpr.tipo, yyvsp[0].tipoexpr.tipo); 
               yyval.tipoexpr.lvalue = false;
               yyval.tipoexpr.cargado = true;
          }
break;
case 82:
#line 453 "gram.y"
{ 
               cargarDato(yyvsp[0].tipoexpr);
               yyval.tipoexpr.tipo = compilaNOT(yyvsp[0].tipoexpr.tipo); 
               yyval.tipoexpr.lvalue = false;
               yyval.tipoexpr.cargado = true;
              }
break;
case 83:
#line 459 "gram.y"
{ yyval.tipoexpr = yyvsp[-1].tipoexpr; }
break;
case 84:
#line 461 "gram.y"
{ 
      cargarDato(yyvsp[0].tipoexpr);
      if( !(yyval.tipoexpr.tipo = castExplicito(yyvsp[-2].tipo, yyvsp[0].tipoexpr.tipo)) )
        yyerror("Conversión explícita inválida");
      yyval.tipoexpr.lvalue = false;
      yyval.tipoexpr.cargado = true;
    }
break;
case 85:
#line 469 "gram.y"
{
      yyval.tipoexpr.cargado = false;
      yyval.tipoexpr.lvalue = true;
      yyval.tipoexpr.tipo = compilarAccesoArray(yyvsp[-3].tipoexpr,yyvsp[-1].tipoexpr);
    }
break;
case 86:
#line 475 "gram.y"
{
      /* comprobar que el tipo de "exp" es un struct*/
      TipoStruct* tipoStruct;
      if( !(tipoStruct = dynamic_cast<TipoStruct*>(yyvsp[-2].tipoexpr.tipo)) ){
        string tmp = "El tipo " + yyvsp[-2].tipoexpr.tipo->getNombre() + " no es una estructura";
        yyerror(tmp.c_str());
      }
      else{
        Campo* campo;
        if( campo = tipoStruct->buscar(yyvsp[0].ident) ){ /*buscar el campo requerido dentro del struct*/
          /*en la cima de la pila estara ahora, fruto de la produccion*/
          /*IDENT de exp, la direccion base del struct. Habra de*/
          /*sumarsele el desplazamiento del campo en cuestion*/
          printf("IPUSH %d\n", tipoStruct->getTam());
          printf("IADD\n"); 

          printf("IPUSH %d\n", campo->getDesplazamiento());
          printf("IADD\n"); 
          yyval.tipoexpr.tipo = campo->getTipo();
          yyval.tipoexpr.lvalue = true;
          yyval.tipoexpr.cargado = false;
        }
        else{
          string tmp = "El campo " + string(yyvsp[0].ident) + " no pertenece a la estructura";
          yyerror(tmp.c_str());
        }
      }
    }
break;
case 87:
#line 503 "gram.y"
{ printf("IPUSH %d\n", yyvsp[0].entero); 
                    yyval.tipoexpr.tipo = tablaTipos.buscar("int");
                    yyval.tipoexpr.lvalue = false;
                    yyval.tipoexpr.cargado = true; }
break;
case 88:
#line 507 "gram.y"
{ printf("FPUSH %f\n", yyvsp[0].real); 
                    yyval.tipoexpr.tipo = tablaTipos.buscar("double");
                    yyval.tipoexpr.lvalue = false;
                    yyval.tipoexpr.cargado = true;}
break;
case 89:
#line 511 "gram.y"
{  if( !tablaSimbolos.buscar(yyvsp[0].ident) ){
                       string tmp = "Variable " + string(yyvsp[0].ident) + " no definida";
                       yyerror(tmp.c_str());
                     }
                     Tipo* tipo = buscaYapilaDireccion(yyvsp[0].ident);
                     yyval.tipoexpr.tipo = tipo; 
                     yyval.tipoexpr.lvalue = true;
                     yyval.tipoexpr.cargado = false;
                  }
break;
case 90:
#line 521 "gram.y"
{ 
       yyval.tipoexpr.tipo = compilarInvocacionFuncion(yyvsp[-3].ident, yyvsp[-1].listaSimbolos);
       yyval.tipoexpr.lvalue = false;
       yyval.tipoexpr.cargado = true;
     }
break;
case 91:
#line 529 "gram.y"
{ 
             yyval.listaSimbolos = new vector<Simbolo*>;
             yyval.listaSimbolos->push_back( new Simbolo("argumento 1" ,yyvsp[0].tipoexpr.tipo)); 
             cargarDato(yyvsp[0].tipoexpr);
           }
break;
case 92:
#line 535 "gram.y"
{ char tmp[16]; sprintf(tmp, "argumento %d", yyvsp[-2].listaSimbolos->size()+1);
            yyvsp[-2].listaSimbolos->push_back(new Simbolo(tmp,yyvsp[0].tipoexpr.tipo) );
            cargarDato(yyvsp[0].tipoexpr);
            yyval.listaSimbolos = yyvsp[-2].listaSimbolos; 
          }
break;
case 93:
#line 540 "gram.y"
{ yyval.listaSimbolos = new vector<Simbolo*>; }
break;
#line 1357 "y.tab.c"
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
