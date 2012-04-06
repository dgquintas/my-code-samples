#include "accionesCompilacion.h"
#include "tipoint.h"
#include "tipodouble.h"
#include "tipoarray.h"
#include "tipovoid.h"
#include "tipostruct.h"
#include <stdio.h>
#include <cassert>

using namespace std;

extern TablaTipos tablaTipos;
extern TablaSimbolos tablaSimbolos;
extern int yyerror(const char*);

void inicializarCompilador(void)
{

  // meter los tipos básicos soportados en la tabla de tipos
  TipoInt* tipoint = new TipoInt;
  TipoDouble* tipodouble = new TipoDouble;
  TipoVoid* tipovoid = new TipoVoid;
  tablaTipos.insertar("int", tipoint);
  tablaTipos.insertar("double", tipodouble);
  tablaTipos.insertar("void", tipovoid);

  tablaSimbolos.set();

  return;
}


Tipo* buscaYapilaDireccion(string nombre)
{
  Simbolo *simbolo;
  simbolo = tablaSimbolos.buscar(nombre);
  if( !simbolo ){
    char error[64];
    sprintf(error, "Identificador %s no encontrado", nombre.c_str());
    yyerror(error);
  }
  if( simbolo->getGlobal() )
    printf("IPUSH %d\n", simbolo->getDireccion());
  else{
    printf("IPUSHBP %d\n", simbolo->getDireccion()); 
    if(simbolo->getParametroPorRef()){
      printf("ILOAD\n"); 
      //cargar el entero que representa la
      //direccion de memoria de la referencia
    }
  }


  return simbolo->getTipo();
}


 

///////////////////////////////////////////////////7

Tipo* castImplicito(Tipo* tipoIzq, Tipo* tipoDer)
{
  if( tipoIzq == tipoDer )
    return tipoIzq;

  if( dynamic_cast< TipoInt* >(tipoIzq) ){
    if( dynamic_cast< TipoDouble* >(tipoDer) ){
      // el operando de la izquierda debe ser convertido a float
      // éste es el de DEBAJO la cima de la pila
      printf("CAST2\n");
      return tipoDer; //double
    }
  }
  else if ( dynamic_cast< TipoDouble* >(tipoIzq) ) {
    if( dynamic_cast< TipoInt* >(tipoDer) ) {
      // el operando de la derecha debe ser convertido a float
      // éste es el que esta en la cima de la pila
      printf("CAST\n");
      return tipoIzq; //double
    }
  }
  
  return NULL; //error
}
Tipo* castExplicito(Tipo* tipoDest, Tipo* tipoOrig)
{
  if( tipoDest == tipoOrig ) //no hace falta cast alguno
    return tipoDest;

  if( dynamic_cast< TipoInt* >(tipoOrig) ){
    if( dynamic_cast< TipoDouble* >(tipoDest) ){
      printf("CAST\n");
      return tipoDest; //double
    }
  }
  else if ( dynamic_cast< TipoDouble* >(tipoOrig) ) {
    if( dynamic_cast< TipoInt* >(tipoDest) ) {
      printf("FToI\n");
      return tipoDest; // int
    }
  }
  
  return NULL; //error
}


///////////////////////////////////////////////////7


Tipo* compilaSuma(Tipo* tipoIzq, Tipo* tipoDer)
{
  Tipo* tipoRet = castImplicito(tipoIzq, tipoDer);
  if( dynamic_cast< TipoInt* >(tipoRet) ){
    printf("IADD\n");
    return tipoRet;
  } 
  if( dynamic_cast< TipoDouble* >(tipoRet) ){
    printf("FADD\n");
    return tipoRet;
  }
  else 
    yyerror("Tipos incompatibles en suma");

  return NULL;
}

Tipo* compilaResta(Tipo* tipoIzq, Tipo* tipoDer)
{ 
  Tipo* tipoRet = castImplicito(tipoIzq, tipoDer);
  if( dynamic_cast< TipoInt* >(tipoRet) ){
    printf("ISUB\n");
    return tipoRet;
  } 
  if( dynamic_cast< TipoDouble* >(tipoRet) ){
    printf("FSUB\n");
    return tipoRet;
  }
  else 
    yyerror("Tipos incompatibles en resta");

  return NULL;
}

Tipo* compilaProducto(Tipo* tipoIzq, Tipo* tipoDer)
{ 
  Tipo* tipoRet = castImplicito(tipoIzq, tipoDer);
  if( dynamic_cast< TipoInt* >(tipoRet) ){
    printf("IMUL\n");
    return tipoRet;
  } 
  if( dynamic_cast< TipoDouble* >(tipoRet) ){
    printf("FMUL\n");
    return tipoRet;
  }
  else 
    yyerror("Tipos incompatibles en multiplicación");

  return NULL;
}

Tipo* compilaDivision(Tipo* tipoIzq, Tipo* tipoDer)
{ 
  Tipo* tipoRet = castImplicito(tipoIzq, tipoDer);
  if( dynamic_cast< TipoInt* >(tipoRet) ){
    printf("IDIV\n");
    return tipoRet;
  } 
  if( dynamic_cast< TipoDouble* >(tipoRet) ){
    printf("FDIV\n");
    return tipoRet;
  }
  else 
    yyerror("Tipos incompatibles en división");

  return NULL;

}

Tipo* compilaModulo(Tipo* tipoIzq, Tipo* tipoDer)
{ 
  Tipo* tipoRet = castImplicito(tipoIzq, tipoDer);
  if( dynamic_cast< TipoInt* >(tipoRet) ){
    printf("IMOD\n");
    return tipoRet;
  } 
  if( dynamic_cast< TipoDouble* >(tipoRet) ){
    printf("FMOD\n");
    return tipoRet;
  }
  else 
    yyerror("Tipos incompatibles en módulo");

  return NULL;

}

Tipo* compilaMenosUnario(Tipo* tipo)
{
  Tipo* tipoRet;
  if( tipoRet = dynamic_cast< TipoDouble* >(tipo) ){ 
    printf("FCHSGN\n");
    return tipoRet;
  }
  else if ( tipoRet = dynamic_cast< TipoInt* >(tipo) ){ 
    printf("ICHSGN\n");
    return tipoRet;
  }
  else
    yyerror("Tipo incompatible para menos unario");

  return NULL;
}
/////////////////////////////////////////////////////////////////

Tipo* compilaMayor(Tipo* tipoIzq, Tipo* tipoDer)
{
  Tipo* tipoRet = castImplicito(tipoIzq, tipoDer);
  if( dynamic_cast< TipoInt* >(tipoRet) ){
    printf("IGreater\n");
    return tablaTipos.buscar("int");
  } 
  if( dynamic_cast< TipoDouble* >(tipoRet) ){
    printf("FGreater\n");
    return tablaTipos.buscar("int"); //siempre devuelve entero
  } 
  else 
    yyerror("Tipos incompatibles en >");

  return NULL;
}

Tipo* compilaMenor(Tipo* tipoIzq, Tipo* tipoDer)
{ 
  Tipo* tipoRet = castImplicito(tipoIzq, tipoDer);
  if( dynamic_cast< TipoInt* >(tipoRet) ){
    printf("ILess\n");
    return tablaTipos.buscar("int"); //siempre devuelve entero
  } 
  if( dynamic_cast< TipoDouble* >(tipoRet) ){
    printf("FLess\n");
    return tablaTipos.buscar("int"); //siempre devuelve entero
  }
  else 
    yyerror("Tipos incompatibles en >");

  return NULL;

}

Tipo* compilaIgual(Tipo* tipoIzq, Tipo* tipoDer)
{
  Tipo* tipoRes;
  tipoRes = castImplicito(tipoIzq, tipoDer);
  if( dynamic_cast< TipoInt* >(tipoRes)){
    printf("IEqual\n");
    return tablaTipos.buscar("int"); //siempre devuelve entero
  }
  else if( dynamic_cast< TipoDouble* >(tipoRes)){
    printf("FEqual\n");
    return tablaTipos.buscar("int"); //siempre devuelve entero
  }
  else
    yyerror("Tipos incompatibles en ==");

  return NULL;
  
}

Tipo* compilaDistinto(Tipo* tipoIzq, Tipo* tipoDer)
{
  Tipo* tipoRes;
  tipoRes = castImplicito(tipoIzq, tipoDer);
  if( dynamic_cast< TipoInt* >(tipoRes)){
    printf("INotEqual\n");
    return tablaTipos.buscar("int"); //siempre devuelve entero
  }
  else if( dynamic_cast< TipoDouble* >(tipoRes)){
    printf("FNotEqual\n");
    return tablaTipos.buscar("int"); //siempre devuelve entero
  }
  else
    yyerror("Tipos incompatibles en !=");

  return NULL;
}

Tipo* compilaMayorIgual(Tipo* tipoIzq, Tipo* tipoDer)
{
  Tipo* tipoRes;
  tipoRes = castImplicito(tipoIzq, tipoDer);
  if( dynamic_cast< TipoInt* >(tipoRes)){
    printf("IGreaterEqual\n");
    return tablaTipos.buscar("int"); //siempre devuelve entero
  }
  else if( dynamic_cast< TipoDouble* >(tipoRes)){
    printf("FGreaterEqual\n");
    return tablaTipos.buscar("int"); //siempre devuelve entero
  }
  else
    yyerror("Tipos incompatibles en !=");

  return NULL;
}
   
Tipo* compilaMenorIgual(Tipo* tipoIzq, Tipo* tipoDer) 
{
  Tipo* tipoRes;
  tipoRes = castImplicito(tipoIzq, tipoDer);
  if( dynamic_cast< TipoInt* >(tipoRes)){
    printf("ILessEqual\n");
    return tablaTipos.buscar("int"); //siempre devuelve entero
  }
  else if( dynamic_cast< TipoDouble* >(tipoRes)){
    printf("FLessEqual\n");
    return tablaTipos.buscar("int"); //siempre devuelve entero
  }
  else
    yyerror("Tipos incompatibles en <=");

  return NULL;
}

////////////////////////////////////////////////////////////////


Tipo* compilaAND(Tipo* tipoIzq, Tipo* tipoDer)
{ 
  if( (!dynamic_cast< TipoInt* >(tipoIzq)) || (!dynamic_cast< TipoInt* >(tipoDer))){
    yyerror("Los operandos de AND han de ser de tipo entero");
    return NULL;
  }
  else{
    printf("AND\n");
    return tablaTipos.buscar("int"); //siempre devuelve entero
  }
}
Tipo* compilaOR(Tipo* tipoIzq, Tipo* tipoDer)
{ 
  if( (!dynamic_cast< TipoInt* >(tipoIzq)) || (!dynamic_cast< TipoInt* >(tipoDer))){
    yyerror("Los operandos de OR han de ser de tipo entero");
    return NULL;
  }
  else{
    printf("OR\n");
    return tablaTipos.buscar("int"); //siempre devuelve entero
  }

}   
Tipo* compilaNOT(Tipo* tipo)
{
  if( (!dynamic_cast< TipoInt* >(tipo)) ){
    yyerror("El operando de NOT ha de ser de tipo entero");
    return NULL;
  }
  else{
    printf("NOT\n");
    return tablaTipos.buscar("int"); //siempre devuelve entero
  }

}    


/////////////////////////////////////////////////////////////////

bool comprobarParametros(Simbolo* simb, vector<Simbolo*>* vectorSimbolos)
{
  TipoFuncion* func;
  if( !(func = dynamic_cast<TipoFuncion*>(simb->getTipo())) )
    //no sería una funcion
    return false;
  if( vectorSimbolos->size() != func->numeroParametros())
    //no coincide el nº de parametros
    return false;
  for(int i=0; i < func->numeroParametros(); i++){
    Tipo* tipo1 = (*vectorSimbolos)[i]->getTipo();
    Tipo* tipo2 = func->getParametro(i)->getTipo();
    if( dynamic_cast< TipoArray* >(tipo1) && dynamic_cast< TipoArray* >(tipo2) ){
      if( ((TipoArray*)tipo1)->getTipo() != ((TipoArray*)tipo2)->getTipo())
        return false;
    }
    else if( tipo1 != tipo2) 
      return false;
  }

  return true;

}

Tipo* compilarInvocacionFuncion(string ident, vector<Simbolo*>* vectorSimbolos)
{
  TipoFuncion* func=NULL;
  Simbolo* simb=NULL; 
  int findex = 1;
  char nombreFunc[128];
  snprintf(nombreFunc, 128, "%s_%d", ident.c_str(), findex);
  
  while( (simb = tablaSimbolos.buscar(nombreFunc) )){
    if( !comprobarParametros(simb, vectorSimbolos) ){
      findex++;
      snprintf(nombreFunc, 128, "%s_%d", ident.c_str(), findex);
      continue;
    }
    else{
      func = dynamic_cast<TipoFuncion*>(simb->getTipo());
      break;
    }
  }
  if (!(simb && func)){
    string tmp;
    tmp = "No se ha encontrado una función adecuada con el nombre " + ident;
    yyerror(tmp.c_str());
  }
 // if( !(func = dynamic_cast<TipoFuncion*>(simb->getTipo())) ){
 //   string tmp = string(simb->getNombre()) + " no es una función";
 //   yyerror(tmp.c_str());
 // }
 // if( vectorSimbolos->size() != func->numeroParametros()){
 //   string tmp = "El número de argumentos no es el adecuado para la función " + ident;
 //   yyerror(tmp.c_str());
 // }
 // for(int i=0; i < func->numeroParametros(); i++){
 //   Tipo* tipo1 = (*vectorSimbolos)[i]->getTipo();
 //   Tipo* tipo2 = func->getParametro(i)->getTipo();
 //   if( dynamic_cast< TipoArray* >(tipo1) && dynamic_cast< TipoArray* >(tipo2) ){
 //     if( ((TipoArray*)tipo1)->getTipo() != ((TipoArray*)tipo2)->getTipo()){
 //       string tmp;
 //       tmp = "Se esperaba un array sobre " +((TipoArray*)tipo2)->getTipo()->getNombre() + 
 //         " pero se tiene uno sobre " + ((TipoArray*)tipo1)->getTipo()->getNombre() ;
 //       yyerror(tmp.c_str());
 //     }
 //   }
 //   else if( tipo1 != tipo2){ //FIXME
 //     string tmp;
 //     tmp = "El argumento " + (*vectorSimbolos)[i]->getNombre() +
 //       " no es del tipo adecuado (se esperaba "+tipo2->getNombre()+" y se tiene "+tipo1->getNombre() ;
 //     yyerror(tmp.c_str());
 //   }
 // }
  delete vectorSimbolos; 

  printf("Call %s\n", nombreFunc); 
  return( func->getTipo());
}



///////////////////////////////////////////////////////////////
void compilarImprimir(Tipo* tipo)
{
  if( dynamic_cast< TipoInt* >(tipo) )
    printf("IOUTPUT\n");
  else if ( dynamic_cast< TipoDouble* >(tipo) )
    printf("FOUTPUT\n");
  else
    yyerror( "Tipo inválido en OUTPUT" );

  return;
}
///////////////////////////////////////////////////////////////
void compilarObtener(Tipo* tipo)
{
  if( dynamic_cast< TipoInt* >(tipo) )
    printf("IINPUT\n");
  else if ( dynamic_cast< TipoDouble* >(tipo) )
    printf("FINPUT\n");
  else
    yyerror( "Tipo inválido en INPUT" );

  return;
}
//////////////////////////////////////////////////////////////
void compilarDeclaracion(vector< Simbolo* > &vectorSimbolos, Tipo *tipo, bool global)
{
  for(int i=0; i < vectorSimbolos.size(); i++ ){
    //antes de insertar el nuevo simbolo, comprobar que no
    //hay otro ya con el mismo nombre presente
    if( existeSimbolo( tablaSimbolos, vectorSimbolos[i] ) ){
      string err;
      err = "Existe declaración previa del símbolo " +  (vectorSimbolos[i]->getNombre());
      yyerror(err.c_str());
    }

    if( vectorSimbolos[i]->getDimension() > 0 ){ //array
      size_t tamArray = vectorSimbolos[i]->getDimension();
      Simbolo* simboloArray = vectorSimbolos[i];
      
      TipoArray* nuevoArray = new TipoArray(tipo, tamArray);
      
      simboloArray->setTipo( nuevoArray );
      tablaTipos.insertar("array", nuevoArray); 
    }
    else
      vectorSimbolos[i]->setTipo(tipo);

    if( global )
      vectorSimbolos[i]->setGlobal();
    
    
    tablaSimbolos.insertar(vectorSimbolos[i]);
  }
}


Tipo* compilarAccesoArray(TipoExpr& exprArray, TipoExpr& exprIndice)
{
  TipoArray* tipoArray;
  if( !(tipoArray = dynamic_cast<TipoArray*>(exprArray.tipo)) ){
    string tmp = "El tipo " + (exprArray.tipo)->getNombre() + " no es un array";
    yyerror(tmp.c_str());
  }
  if( !dynamic_cast<TipoInt*>(exprIndice.tipo) ){
    string tmp = "El tipo " + (exprIndice.tipo)->getNombre() + " no puede utilizarse como índice de un array";
    yyerror(tmp.c_str());
  }
  //en la cima de la pila esta el índice y debajo de éste, la direccion del elemento 0 del
  //array. Habra de sumarsele el desplazamiento fruto del indice
  if( !(exprIndice.cargado) )
    printf("ILOAD\n");
  //tamaño del tipo almacenado en el array
  printf("IPUSH %d\n", tipoArray->getTipo()->getTam());
  printf("IMUL\n");
  printf("IADD\n");

  return tipoArray->getTipo();
}
 
int nextLabel(void)
{
  static int contador = 1;

  return contador++;
}

bool existeSimbolo(TablaSimbolos &TS, Simbolo* simbolo)
{
  if( TS.buscarEnBloque(simbolo->getNombre()) )
    return true;
  else
    return false;
}

void cargarDato(TipoExpr& tipoExpr)
{
  if (tipoExpr.tipo->pasoPorReferencia()){
    //ya que se pasa por referencia, no cargar nada 
    //(la direccion de memoria ya esta en la pila
    ;
  }
  else if( !tipoExpr.cargado)
    printf("%cLOAD\n", tipoExpr.tipo->getPrefijo());
  return;
}



