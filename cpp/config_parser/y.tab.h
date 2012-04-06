#define INTEGER 257
#define REAL 258
#define STR 259
#define BOOL 260
#define IDENT 261
#define READ 262
#define WRITE 263
#define MAIN 264
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
extern YYSTYPE yylval;
