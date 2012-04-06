%{
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
%}

%union {
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
  };

%token <entero> ENTERO
%token <real> REAL 
%token <tipo> INT DOUBLE VOID
%token <ident> IDENT 
%token <cadena> CADENA
%token READ WRITE MAIN IF ELSE STRUCT RETURN WHILE 
%token IGUAL DISTINTO MAYORIGUAL MENORIGUAL AND OR NOT

%type <tipo> tipo camposStruct devolver 
%type <tipo> paramsFunc
%type <tipoexpr> exp
%type <simbolo> elemListaVars declaracionParametros
%type <listaSimbolos> listaVars declaracionGlobal declaracion argumentos

%start prog

%nonassoc IF
%nonassoc ELSE

%nonassoc '='
%left OR
%left AND
%left '<' '>' IGUAL DISTINTO MAYORIGUAL MENORIGUAL
%left '+' '-'
%left '*' '/' '%'
%right NOT MENOSUNARIO CAST
%left '[' CORCHETES
%right '.'

%%

prog: /* vacio */ 
    | prog { $<listaSimbolos>$ = new vector< Simbolo *>; } globales
    ;

globales: declaracionGlobal ';'
        | declaracionFuncion
        ;


declaracionFuncion:  tipo IDENT { 
                                  int findex=0;
                                  char nombreFunc[128];
                                  do{
                                   findex++;
                                   snprintf(nombreFunc, 128, "%s_%d", $2, findex);
                                  } while( tablaTipos.buscar(nombreFunc) );
                                  printf("%s:\n", nombreFunc); 
                                  $<cadena>$ = new string(nombreFunc);
                                } '(' paramsFunc ')'
                      {  
                          /* no existia, insertarlo */
                          ((TipoFuncion*)$5)->setTipo($1);
                          tablaTipos.insertar(*($<cadena>3) , $5);

                          tablaSimbolos.insertar(new Simbolo(*($<cadena>3), $5)); 
                          delete $<cadena>3;
                      }
                    '{' 
                        { 
                          tablaSimbolos.set();
                          reservasLocales.push_back(0);

                          TipoFuncion* func = dynamic_cast< TipoFuncion* >($5);
                          int desp= -4; //hay que saltarse el BP antiguo y la dirección de retorno
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
                              desp-= 2; //ya que las referencias son  enteros (posiciones de memoria)
                            }
                            else{ //paso por valor
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
                        //cuerpo 
                        sents
                        devolver 
                        {
                          if ( $11 != $1 )
                            yyerror("Se intenta retornar un tipo"
                                    "incompatible con la declaración de la"
                                    "función");
                        }
                    '}'  
                    {
                      int m = ((TipoFuncion*)$5)->calcularM();
                      int n = reservasLocales.back();
                      if( string($2) != string("Main") ){
                      if( $1->getNombre() == "int" )
                        printf("IReturn %d %d\n", n,m); 
                      else if ( $1->getNombre() == "double" )
                        printf("FReturn %d %d\n", n,m); 
                      else if ( $1->getNombre() == "void" )
                        printf("Return %d %d\n", n,m); 
                      }
                      reservasLocales.pop_back();
                      tablaSimbolos.reset();
                    }
                  ;
devolver: RETURN exp ';'
        { //queda apilado el resultado a devolver
          cargarDato($2);
          $$ = $2.tipo; }
        | RETURN ';'/* para funcs de tipo void */ 
        { $$ = tablaTipos.buscar("void"); }
        ;
       
paramsFunc: declaracionParametros
               { TipoFuncion* nuevaFuncion = new TipoFuncion();
                 if( $1 )
                   nuevaFuncion->insertar($1);
                 $$ = nuevaFuncion; }
               | paramsFunc ',' declaracionParametros 
               { ((TipoFuncion*)$1)->insertar($3);
                  $$ = $1; }
               ;


declaracionParametros: tipo IDENT   
                     { $$ = new Simbolo($2, $1); }
                     | declaracionParametros '[' ENTERO ']'
                     {  TipoArray* tipoArray = new TipoArray( $1->getTipo(), $3 );
                        $$ = new Simbolo( $1->getNombre(), tipoArray ); 
                     }
                     | /* vacio */ { $$ = NULL; }
                     ;



declaracionGlobal: tipo listaVars { compilarDeclaracion(*$2, $1, true);
                                    $$ = $2; }
           ;
declaracion: tipo listaVars { compilarDeclaracion(*$2, $1, false); 
                              $$ = $2; }
            ;
listaVars: listaVars ',' elemListaVars { $$->push_back($3); }
         | elemListaVars { $$ = new vector< Simbolo *>;
                           $$->push_back($1); }
         ;

elemListaVars: IDENT { $$ = new Simbolo($1); }
             | IDENT '[' ENTERO ']' 
             {
               $$ = new Simbolo($1);
               $$->setDimension($3); 
             }
             ;

sent: sentSimple ';'
    | sentBloque
    ;

sents: sents sent
     | /*vacio*/
     ;

sentSimple: declaracion { //reservar el espacio en la pila  
                          size_t numBytes = 0;
                          for(int i=0; i < $1->size(); i++){
                            numBytes += (*$1)[i]->getTipo()->getTam();
                          }
                          printf("RESRV %d\n", numBytes);
                          reservasLocales.back() += numBytes;
                        }
          | READ exp { if( !$2.lvalue ){
                          string tmp = "El tipo " +
                          $2.tipo->getNombre() + " no es lvalue";
                          yyerror(tmp.c_str());
                        }
                        compilarObtener($2.tipo);
                      }
          | WRITE exp { if( !$2.tipo->esImprimible() ){
                          string tmp = "El tipo " +
                          $2.tipo->getNombre() + " no es imprimible";
                          yyerror(tmp.c_str());
                        }
                        cargarDato($2);
                        compilarImprimir($2.tipo);
                      }
          | WRITE CADENA {
                            printf("PRINT %s\n", yylval.cadena->c_str());
                            delete yylval.cadena;
                          } 
          | exp '=' exp {
                 if ( ! $1.lvalue )
                   yyerror("Expresion izquierda en asignación no es lvalue");
                 if( dynamic_cast< TipoInt *>($1.tipo)  ){
                   if( $3.tipo != $1.tipo ) // la expresion no es de tipo entero         
                     yyerror("Asignación a entero no válida");
                   cargarDato($3);
                   printf("ISTORE\n");
                 }
                 else if ( dynamic_cast< TipoDouble* >($1.tipo)  ){
                   if( $3.tipo != $1.tipo ) // si la expresion no es real...
                     if( dynamic_cast< TipoInt *>($3.tipo) ) // salvo que sea entera...
                       printf("CAST\n");
                     else
                       yyerror("Asignación a real no válida");
                   cargarDato($3);
                   printf("FSTORE\n");
                 }
         }
          | exp
          { /* dejan un valor en la pila que es basura */ 
            if( dynamic_cast< TipoInt*>($1.tipo) )
              printf("IPOP\n");
            else if ( dynamic_cast< TipoDouble* >($1.tipo))
              printf("FPOP\n");
          }
          | /*vacio*/
          ;

sentBloque: if 
          | while
          | '{' sents '}'
          ;

if: IF '(' exp ')' { 
                      $<etiqueta>$ = nextLabel();
                      cargarDato($3);
                      printf("JMPZero else%d\n", $<etiqueta>$);
                     }
     sent          { printf("JMP EndIf%d\n", $<etiqueta>5);
                     printf("else%d:\n", $<etiqueta>5);
                   }
     elseOpt { printf("EndIf%d:\n", $<etiqueta>5); }
     
  ;
elseOpt: ELSE sent
       | /* vacio */ %prec IF
       ;

while: 
      WHILE {
               $<etiqueta>$ = nextLabel();
               printf("BeginWhile%d:\n", $<etiqueta>$);
            }
      '(' exp ')' {  cargarDato($4);
                     printf("JMPZero EndWhile%d\n", $<etiqueta>2);
                  }
      sent         { printf("JMP BeginWhile%d\n", $<etiqueta>2);
                     printf("EndWhile%d:\n", $<etiqueta>2);
                   }

/* en los casos de tipos primitivos, estos ya se encuentran metidos en
 * la tabla de tipos desde el principio, y por tanto las acciones
 * basicamente no hacen nada.
 *
 * pero en los tipos compuestos, cada vez que se crea uno nuevo, han de
 * realizarse operaciones sobre la tabla de tipos
 */
tipo: INT { $$ = $1; }
    | DOUBLE  { $$ = $1; }
    | VOID { $$ = $1; }
    | STRUCT IDENT
      '{' { tablaSimbolos.set(); }
          camposStruct 
      '}' { tablaSimbolos.reset(); }
    {
        string nombreStruct = "struct " + string($2);
        tablaTipos.insertar(nombreStruct, (TipoStruct*)$5);
        $$ = (TipoStruct*)$5;
    } 
    | STRUCT IDENT
    {
      TipoStruct* tipoStruct;
      string nombreStruct = "struct " + string($2);
      if( tipoStruct = dynamic_cast< TipoStruct* >(tablaTipos.buscar(nombreStruct)))
        $$ = tipoStruct;
      else{
        string tmp = "Estructura " + string($2) + " no declarada previamente";
        yyerror(tmp.c_str());
      }
    }
    ;

/* desde "declaracion" se devuelve el vector de simbolos declarados */
camposStruct: camposStruct declaracion ';' { 
                for( int i = 0; i < $2->size(); i++ ){
                  //el control de declaraciones repetidas se lleva a
                  //cabo por la produccion "declaracion"
                  ((TipoStruct*)$1)->insertar( (*$2)[i]->getNombre(), (*$2)[i]->getTipo());
                }
                $$ = $1;
              }
            | /* vacio */ { $$= new TipoStruct(); }
            ;

exp : exp '+' { cargarDato($1); } 
      exp  {  cargarDato($4);
              $$.tipo = compilaSuma($1.tipo, $4.tipo); 
              $$.lvalue = false;
              $$.cargado = true;
            }
    | exp '-' { cargarDato($1); }
      exp { 
              cargarDato($4);
              $$.tipo = compilaResta($1.tipo, $4.tipo); 
              $$.lvalue = false;
              $$.cargado = true;
          }
    | exp '*' { cargarDato($1); }
      exp {  
              cargarDato($4);
              $$.tipo = compilaProducto($1.tipo, $4.tipo); 
              $$.lvalue = false;
              $$.cargado = true;
          }
    | exp '/' { cargarDato($1); }
      exp { 
              cargarDato($4);
              $$.tipo = compilaDivision($1.tipo, $4.tipo); 
              $$.lvalue = false;
              $$.cargado = true;
          }
    | exp '%' { cargarDato($1); }
      exp { 
              cargarDato($4);
              $$.tipo = compilaModulo($1.tipo, $4.tipo); 
              $$.lvalue = false;
              $$.cargado = true;
          }

    | '-' exp %prec MENOSUNARIO { cargarDato($2);
                                  $$.tipo = compilaMenosUnario($2.tipo); 
                                  $$.lvalue = false;
                                  $$.cargado = true;} 
    | exp '>' { cargarDato($1); }
      exp  { 
               cargarDato($4);
               $$.tipo = compilaMayor($1.tipo, $4.tipo); 
               $$.lvalue = false;
               $$.cargado = true;
           }
    | exp '<' { cargarDato($1); }
      exp  { 
               cargarDato($4);
               $$.tipo = compilaMenor($1.tipo, $4.tipo); 
               $$.lvalue = false;
               $$.cargado = true;
           }
    | exp MAYORIGUAL { cargarDato($1); } 
      exp { 
               cargarDato($4);
               $$.tipo = compilaMayorIgual($1.tipo, $4.tipo); 
               $$.lvalue = false;
               $$.cargado = true;
          }
    | exp MENORIGUAL { cargarDato($1); } 
    exp { 
               cargarDato($4);
               $$.tipo = compilaMenorIgual($1.tipo, $4.tipo); 
               $$.lvalue = false;
               $$.cargado = true;
          }
    | exp IGUAL { cargarDato($1); }
      exp { 
               cargarDato($4);
               $$.tipo = compilaIgual($1.tipo, $4.tipo); 
               $$.lvalue = false;
               $$.cargado = true;
          }
    | exp DISTINTO { cargarDato($1); }      
      exp { 
               cargarDato($4);
               $$.tipo = compilaDistinto($1.tipo, $4.tipo); 
               $$.lvalue = false;
               $$.cargado = true;
          }
    | exp AND { cargarDato($1); }      
      exp { 
               cargarDato($4);
               $$.tipo = compilaAND($1.tipo, $4.tipo); 
               $$.lvalue = false;
               $$.cargado = true;
          }
    | exp OR { cargarDato($1); } 
      exp { 
               cargarDato($4);
               $$.tipo = compilaOR($1.tipo, $4.tipo); 
               $$.lvalue = false;
               $$.cargado = true;
          }
    | NOT exp { 
               cargarDato($2);
               $$.tipo = compilaNOT($2.tipo); 
               $$.lvalue = false;
               $$.cargado = true;
              }
    | '(' exp ')' { $$ = $2; } 
    | '(' tipo ')' exp %prec CAST 
    { 
      cargarDato($4);
      if( !($$.tipo = castExplicito($2, $4.tipo)) )
        yyerror("Conversión explícita inválida");
      $$.lvalue = false;
      $$.cargado = true;
    } 
    | exp '[' exp ']' %prec CORCHETES
    {
      $$.cargado = false;
      $$.lvalue = true;
      $$.tipo = compilarAccesoArray($1,$3);
    }
    | exp '.' IDENT 
    {
      // comprobar que el tipo de "exp" es un struct
      TipoStruct* tipoStruct;
      if( !(tipoStruct = dynamic_cast<TipoStruct*>($1.tipo)) ){
        string tmp = "El tipo " + $1.tipo->getNombre() + " no es una estructura";
        yyerror(tmp.c_str());
      }
      else{
        Campo* campo;
        if( campo = tipoStruct->buscar($3) ){ //buscar el campo requerido dentro del struct
          //en la cima de la pila estara ahora, fruto de la produccion
          //IDENT de exp, la direccion base del struct. Habra de
          //sumarsele el desplazamiento del campo en cuestion
          printf("IPUSH %d\n", tipoStruct->getTam());
          printf("IADD\n"); 

          printf("IPUSH %d\n", campo->getDesplazamiento());
          printf("IADD\n"); 
          $$.tipo = campo->getTipo();
          $$.lvalue = true;
          $$.cargado = false;
        }
        else{
          string tmp = "El campo " + string($3) + " no pertenece a la estructura";
          yyerror(tmp.c_str());
        }
      }
    }
    | ENTERO      { printf("IPUSH %d\n", $1); 
                    $$.tipo = tablaTipos.buscar("int");
                    $$.lvalue = false;
                    $$.cargado = true; }
    | REAL        { printf("FPUSH %f\n", $1); 
                    $$.tipo = tablaTipos.buscar("double");
                    $$.lvalue = false;
                    $$.cargado = true;}
    | IDENT       {  if( !tablaSimbolos.buscar($1) ){
                       string tmp = "Variable " + string($1) + " no definida";
                       yyerror(tmp.c_str());
                     }
                     Tipo* tipo = buscaYapilaDireccion($1);
                     $$.tipo = tipo; 
                     $$.lvalue = true;
                     $$.cargado = false;
                  }
    | IDENT '(' argumentos ')'  //invocacion funcion
     { 
       $$.tipo = compilarInvocacionFuncion($1, $3);
       $$.lvalue = false;
       $$.cargado = true;
     }
    ;

argumentos: exp 
           { 
             $$ = new vector<Simbolo*>;
             $$->push_back( new Simbolo("argumento 1" ,$1.tipo)); 
             cargarDato($1);
           }
          | argumentos ',' exp
          { char tmp[16]; sprintf(tmp, "argumento %d", $1->size()+1);
            $1->push_back(new Simbolo(tmp,$3.tipo) );
            cargarDato($3);
            $$ = $1; 
          } 
          | /* vacio */ { $$ = new vector<Simbolo*>; }
          ;
%%
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
