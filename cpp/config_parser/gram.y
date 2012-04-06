%{
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

%}

%union {
  struct resultExp_t
  {
    int integer;
    double real;
    std::string* str;
    bool boolean;
    short type;
  } resultExp;
  char ident[128];
  };

%token <resultExp> INTEGER
%token <resultExp> REAL
%token <resultExp> STR
%token <resultExp> BOOL 
%token <ident> IDENT 
%token READ WRITE MAIN

%type <resultExp> exp
%type <resultExp> assign

%start prog

%right '='
%left '+' '-'
%left '*' '/'

%%

prog: /* vacio */
    | prog configSet
    ;

configSet: IDENT  {  currConfigSet = $1;  } '{' body '}' 
       ;

body: /*vacio*/
      | body sent
      ;

sent: assign ';'  ;

assign: IDENT '=' exp { 
      GenericValue gv;
      switch( $3.type ){
      case INTEGER:
        gv.setValue($3.integer);
        break;
      case REAL:
        gv.setValue($3.real);
        break;
      case STR:
        gv.setValue( *($3.str) );
        delete $3.str;
        break;
      case BOOL:
        gv.setValue( $3.boolean );
        break;

      }
      ConfigParser::getInstance()->appendPairToSet( currConfigSet, $1, gv);
  }
       ;

exp : exp '+' exp {  
      if( $1.type == STR ){
         yyerror("Cannot use string inside arithmetic operations");
      }
      if( $1.type == INTEGER ){
        if ( $3.type == INTEGER ){
          $$.integer = $1.integer + $3.integer;
          $$.type = INTEGER; 
        }
        else{ /* REAL */
          $$.real = (double)$1.integer + $3.real;
          $$.type = REAL;
        }
      }
      else{ /* REAL */
        if ( $3.type == INTEGER ){
          $$.real = $1.real + (double)$3.integer;
          $$.type = REAL; 
        }
        else{ /* REAL */
          $$.real = $1.real + $3.real;
          $$.type = REAL;
        }
      }
    }
    | exp '-' exp {   
    if( $1.type == STR ){
         yyerror("Cannot use string inside arithmetic operations");
      }
      if( $1.type == INTEGER ){
        if ( $3.type == INTEGER ){
          $$.integer = $1.integer - $3.integer;
          $$.type = INTEGER; 
        }
        else{ /* REAL */
          $$.real = (double)$1.integer - $3.real;
          $$.type = REAL;
        }
      }
      else{ /*  REAL */
        if ( $3.type == INTEGER ){
          $$.real = $1.real - (double)$3.integer;
          $$.type = REAL; 
        }
        else{ /* REAL */
          $$.real = $1.real - $3.real;
          $$.type = REAL;
        }
      }
    }
    | exp '*' exp {  
      if( $1.type == STR ){
         yyerror("Cannot use string inside arithmetic operations");
      }
      if( $1.type == INTEGER ){
        if ( $3.type == INTEGER ){
          $$.integer = $1.integer * $3.integer;
          $$.type = INTEGER;
        }
        else{ /* REAL */
          $$.real = (double)$1.integer * $3.real;
          $$.type = REAL;
        }
      }
      else{ /* REAL */
        if ( $3.type == INTEGER ){
          $$.real = $1.real * (double)$3.integer;
          $$.type = REAL; 
        }
        else{ /* REAL */
          $$.real = $1.real * $3.real;
          $$.type = REAL;
        }
      }
    }
    | exp '/' exp {  
      if( $1.type == STR ){
         yyerror("Cannot use string inside arithmetic operations");
      }
      if( $1.type == INTEGER ){
        if ( $3.type == INTEGER ){
          $$.integer = $1.integer / $3.integer;
          $$.type = INTEGER; 
        }
        else{ /* REAL */
          $$.real = (double)$1.integer / $3.real;
          $$.type = REAL;
        }
      }
      else{ /* REAL */
        if ( $3.type == INTEGER ){
          $$.real = $1.real / (double)$3.integer;
          $$.type = REAL; 
        }
        else{ /* REAL */
          $$.real = $1.real / $3.real;
          $$.type = REAL;
        }
      }
    }
    | '(' exp ')' { $$ = $2; } 
    | INTEGER      { $$ = $1; }
    | REAL        { $$ = $1; }
    | STR         { $$ = $1; }
    | BOOL        { $$ = $1; }
    ;

%%
int yyerror(const char* str)
{
  printf("Error: %s. Line %d\n", str, yylineno);
  exit(-1);
  return 0;
}


