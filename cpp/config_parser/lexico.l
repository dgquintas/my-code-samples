%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string>
#include <map>

#include "y.tab.h"

extern void yyerror(const char*);
%}

%option yylineno


REAL [0-9]+"."[0-9]+
INTEGER [0-9]+
IDENT [a-zA-Z_][0-9a-zA-Z_]*
STR "\""[[:print:]]*"\""
BOOL "true"|"false"
%%
{REAL}   {
                    yylval.resultExp.real = atof(yytext);
                    yylval.resultExp.type = REAL;
                    return REAL;
          }
{INTEGER}  { 
                yylval.resultExp.integer = atoi(yytext);
                yylval.resultExp.type = INTEGER;
                return INTEGER;
          }
{BOOL}    { if( strcmp(yytext, "false") == 0){
              yylval.resultExp.boolean = false;
            }
            else{
              yylval.resultExp.boolean = true;
            }
            yylval.resultExp.type = BOOL;
            return BOOL;
           }
{IDENT}    {strncpy(yylval.ident, yytext, 128); 
                      yylval.resultExp.type = IDENT;
                      return IDENT;
           }
{STR}    { yylval.resultExp.str = new std::string(yytext+1); 
           yylval.resultExp.str->erase( yylval.resultExp.str->end()-1);
            yylval.resultExp.type = STR;
            return STR;
           }



[+\-*/=;(){},]       {return *yytext;}
[ \t\n]+  ;
"#".*      ;  /* comments */
.             {yyerror(yytext);}
%%


