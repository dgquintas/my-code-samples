#include "code.h"
#include "context.h"
#include "program.h"
#include "y.tab.h"
#include <iostream>

using namespace std;
extern int yyparse(void);
extern int yylex(void);
extern int yylineno;
Context ctx;
Program programa;


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

  yyparse();
  fclose(yyin);

  programa.exec(ctx);

  return 0;
}
