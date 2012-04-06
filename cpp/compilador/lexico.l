%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "tipo.h"
#include "tablatipos.h"
#include "campo.h"
#include "simbolo.h"
#include <vector>
#include <string>

using namespace std;
#include "y.tab.h"


extern void yyerror(const char*);
%}

%option yylineno

REAL [0-9]+"."[0-9]+
ENTERO [0-9]+
IDENT [a-zA-Z_][0-9a-zA-Z_]*
CADENA \".*\"
%%
"READ" return READ;
"WRITE" return WRITE;
"if" return IF;
"else" return ELSE;
"while" return WHILE;
"struct" return STRUCT;
"return" return RETURN;
"int" {
       extern TablaTipos tablaTipos;
       if( !(yylval.tipo = tablaTipos.buscar("int")) )
         yyerror("Tipo int no encontrado");
       return INT;
      }
"double" {
       extern TablaTipos tablaTipos;
       if( !(yylval.tipo = tablaTipos.buscar("double")) )
         yyerror("Tipo double no encontrado");
       return DOUBLE;
         }
"void" {
       extern TablaTipos tablaTipos;
       if( !(yylval.tipo = tablaTipos.buscar("void")) )
         yyerror("Tipo void no encontrado");
       return VOID;
         }
"AND"     {return AND;}    
"OR"      {return OR;}
"NOT"     {return NOT;}

{REAL}   {
          yylval.real = atof(yytext);
          return REAL;
         }
{ENTERO} { 
          yylval.entero = atoi(yytext);
          return ENTERO;
          }
{IDENT}   {
            strncpy(yylval.ident, yytext, 128); 
            return IDENT;
          }
{CADENA}  {
            yylval.cadena = new string(yytext);
            return CADENA;
           }
"=="      {return IGUAL;}
"!="      {return DISTINTO;} 
">="      {return MAYORIGUAL;}         
"<="      {return MENORIGUAL;}   
[+\-*/%=;(){},\.<>\[\]]       {return *yytext;}
[ \t\n]+  ;
"#".*      ;  /* para comentarios */
    
.             {yyerror(yytext);}
%%


