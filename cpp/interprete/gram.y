%{
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

%}

%union {
  int entero;
  float real;
  char label[33];
  string* cadena;
  };

%token <entero> ENTERO
%token <real> REAL
%token <label> ETIQUETA 
%token <cadena> CADENA
%token IPUSH_TOK FPUSH_TOK IPOP_TOK FPOP_TOK IPUSHBP_TOK ILOAD_TOK FLOAD_TOK 
%token ISTORE_TOK FSTORE_TOK FPUSH_TOK 
%token IADD_TOK FADD_TOK IMUL_TOK FMUL_TOK ISUB_TOK FSUB_TOK IDIV_TOK FDIV_TOK IMOD_TOK FMOD_TOK
%token CAST_TOK CAST2_TOK FINPUT_TOK FOUTPUT_TOK IINPUT_TOK IOUTPUT_TOK 
%token Call_TOK Return_TOK IReturn_TOK FReturn_TOK 
%token JMP_TOK JMPZero_TOK JMPNotZero_TOK
%token Equal_TOK NotEqual_TOK Greater_TOK Less_TOK
%token AND_TOK OR_TOK NOT_TOK
%token IEQUAL_TOK FEQUAL_TOK INOTEQUAL_TOK FNOTEQUAL_TOK IGREATER_TOK
%token FGREATER_TOK ILESS_TOK FLESS_TOK IGREATEREQUAL_TOK ILESSEQUAL_TOK 
%token FGREATEREQUAL_TOK FLESSEQUAL_TOK
%token ICHSGN_TOK FCHSGN_TOK
%token FToI_TOK 
%token RESRV_TOK PRINT_TOK

%%

cuerpo: /*vacio*/
      | cuerpo sent 
      ;

sent: op_apilar  '\n'
    | op_cargar '\n'
    | op_guardar '\n'
    | op_aritmetica '\n'
    | op_comparacion '\n'
    | op_cast '\n'
    | op_io '\n'
    | op_salto '\n'
    | op_func '\n'
    | etiqueta '\n'
    | op_reserva '\n'
    | op_logica '\n'
    | '\n'
    ;

etiqueta: ETIQUETA ':' { int instr = programa.getCount(); 
                         ctx.ts.addEntry($1, new LabelNode(instr));
                       }

op_apilar: IPUSH_TOK ENTERO { programa.addCode( new IPUSH($2) );  }
         | FPUSH_TOK REAL   { programa.addCode( new FPUSH($2) );  }
         | IPUSHBP_TOK ENTERO { programa.addCode( new IPUSHBP($2) );  }
         | IPOP_TOK { programa.addCode( new IPOP() );  }
         | FPOP_TOK { programa.addCode( new FPOP() );  }
         ;
op_cargar: ILOAD_TOK  { programa.addCode( new ILOAD() ); }
         | FLOAD_TOK  { programa.addCode( new FLOAD() ); }
         ;
op_guardar: ISTORE_TOK {programa.addCode( new ISTORE() ); }
         | FSTORE_TOK  {programa.addCode( new FSTORE() ); }
         ;

op_logica: AND_TOK { programa.addCode( new AND() ); }
         | OR_TOK { programa.addCode( new OR() ); }
         | NOT_TOK { programa.addCode( new NOT() ); }
         ;
op_aritmetica: IADD_TOK {programa.addCode( new IADD() ); }
             | FADD_TOK {programa.addCode( new FADD() ); }
             | IMUL_TOK {programa.addCode( new IMUL() ); }
             | FMUL_TOK {programa.addCode( new FMUL() ); }
             | ISUB_TOK {programa.addCode( new ISUB() ); }
             | FSUB_TOK {programa.addCode( new FSUB() ); }
             | IDIV_TOK {programa.addCode( new IDIV() ); }
             | FDIV_TOK {programa.addCode( new FDIV() ); }
             | IMOD_TOK {programa.addCode( new IMOD() ); }
             | FMOD_TOK {programa.addCode( new FMOD() ); }
             | ICHSGN_TOK {programa.addCode( new ICHSGN() ); }
             | FCHSGN_TOK {programa.addCode( new FCHSGN() ); }
             ;

op_comparacion: IEQUAL_TOK { programa.addCode( new IEqual() ); }
              | FEQUAL_TOK { programa.addCode( new FEqual() ); }
              | INOTEQUAL_TOK { programa.addCode( new INotEqual() ); }
              | FNOTEQUAL_TOK { programa.addCode( new FNotEqual() ); }
              | IGREATER_TOK  { programa.addCode( new IGreater() ); }
              | FGREATER_TOK  { programa.addCode( new FGreater() ); }
              | ILESS_TOK     { programa.addCode( new ILess() ); }
              | FLESS_TOK     { programa.addCode( new FLess() ); }
              | IGREATEREQUAL_TOK  { programa.addCode( new IGreaterEqual() ); }
              | FGREATEREQUAL_TOK  { programa.addCode( new FGreaterEqual() ); }
              | ILESSEQUAL_TOK     { programa.addCode( new ILessEqual() ); }
              | FLESSEQUAL_TOK     { programa.addCode( new FLessEqual() ); }

              ;

op_cast: CAST_TOK  {programa.addCode( new CAST() ); }
       | CAST2_TOK {programa.addCode( new CAST2() ); }
       | FToI_TOK  {programa.addCode( new FToI() ); }
       ;
op_io: IINPUT_TOK   { programa.addCode( new IINPUT() ); }
     | FINPUT_TOK   { programa.addCode( new FINPUT() ); }
     | IOUTPUT_TOK  { programa.addCode( new IOUTPUT() ); }
     | FOUTPUT_TOK  { programa.addCode( new FOUTPUT() ); }
     | PRINT_TOK CADENA   { programa.addCode( new PRINT(*$2) ); delete $2;}
     ;
       
op_salto: JMP_TOK ETIQUETA { programa.addCode( new JMP($2) ); }
        | JMPZero_TOK ETIQUETA { programa.addCode( new JMPZero($2) ); }
        | JMPNotZero_TOK ETIQUETA { programa.addCode( new JMPNotZero($2) ); }
        ;

op_func: Call_TOK ETIQUETA { programa.addCode( new Call($2) ); }
       | Return_TOK ENTERO ENTERO { programa.addCode( new Return($2,$3) ); }
       | IReturn_TOK ENTERO ENTERO { programa.addCode( new IReturn($2,$3) ); }
       | FReturn_TOK ENTERO ENTERO { programa.addCode( new FReturn($2,$3) ); }
       ;

op_reserva: RESRV_TOK ENTERO { programa.addCode( new RESRV($2) ); }
          ;

%%
int yyerror(const char* str)
{
  printf("Error: %s. Linea %d\n", str, yylineno-1);
  exit(-1);
  
}


