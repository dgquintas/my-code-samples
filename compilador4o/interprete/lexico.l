%{

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string>

using namespace std;
#include "y.tab.h"


extern void yyerror(const char*);
%}

%option yylineno

REAL [0-9]+"."[0-9]+
ENTERO -?[0-9]+
ETIQUETA [a-zA-Z][0-9a-zA-Z_]*
CADENA \".*\"
%%
"IPUSH" return IPUSH_TOK;
"FPUSH" return FPUSH_TOK;
"IPUSHBP" return IPUSHBP_TOK;
"IPOP" return IPOP_TOK;
"FPOP" return FPOP_TOK;
"ILOAD" return ILOAD_TOK;
"FLOAD" return FLOAD_TOK;
"ISTORE" return ISTORE_TOK;
"FSTORE" return FSTORE_TOK;

"IADD" return IADD_TOK;
"FADD" return FADD_TOK;
"ISUB" return ISUB_TOK;
"FSUB" return FSUB_TOK;
"IMUL" return IMUL_TOK;
"FMUL" return FMUL_TOK;
"IDIV" return IDIV_TOK;
"FDIV" return FDIV_TOK;
"IMOD" return IMOD_TOK;
"FMOD" return FMOD_TOK;
"ICHSGN" return ICHSGN_TOK;
"FCHSGN" return FCHSGN_TOK;


"CAST" return CAST_TOK;
"CAST2" return CAST2_TOK;
"FToI" return FToI_TOK;

"IOUTPUT" return IOUTPUT_TOK;
"FOUTPUT" return FOUTPUT_TOK;
"IINPUT" return  IINPUT_TOK;
"FINPUT" return  FINPUT_TOK;

"Call" return Call_TOK;
"Return" return Return_TOK;
"IReturn" return IReturn_TOK;
"FReturn" return FReturn_TOK;

"JMP" return JMP_TOK;
"JMPZero" return JMPZero_TOK;
"JMPNotZero" return JMPNotZero_TOK;
 
"IEqual" return IEQUAL_TOK;
"INotEqual" return INOTEQUAL_TOK;
"IGreater" return IGREATER_TOK;
"ILess" return ILESS_TOK;
"IGreaterEqual" return IGREATEREQUAL_TOK;
"ILessEqual" return ILESSEQUAL_TOK;


"FEqual" return FEQUAL_TOK;
"FNotEqual" return FNOTEQUAL_TOK;
"FGreater" return FGREATER_TOK;
"FLess" return FLESS_TOK;
"FGreaterEqual" return FGREATEREQUAL_TOK;
"FLessEqual" return FLESSEQUAL_TOK;

"PRINT" return PRINT_TOK;
 
"AND" return AND_TOK;
"OR" return OR_TOK;
"NOT" return NOT_TOK;

"RESRV" return RESRV_TOK;

{REAL}   {
          yylval.real = atof(yytext);
          return REAL;
         }
{ENTERO} { 
          yylval.entero = atoi(yytext);
          return ENTERO;
          }
{ETIQUETA}   {
            strncpy(yylval.label, yytext, 33); 
            return ETIQUETA;
          }
{CADENA}  {
            yylval.cadena = new string(yytext);
            return CADENA;
           }
[:\n]       {return *yytext;}
[ \t]+  ;
.             {yyerror(yytext);}
%%


