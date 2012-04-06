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
extern YYSTYPE yylval;
