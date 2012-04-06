#ifndef ACCIONESCOMPILACION_H
#define ACCIONESCOMPILACION_H

#include "tipo.h"
#include <string>
#include "tablasimbolos.h"
#include "tablatipos.h"
#include "tipofuncion.h"
#include "simbolo.h"
#include <vector>

using namespace std;

Tipo* buscaYapilaDireccion(string nombre);
Tipo* compilaSuma(Tipo* tipoIzq, Tipo* tipoDer);
Tipo* compilaResta(Tipo* tipoIzq, Tipo* tipoDer) ;
Tipo* compilaProducto(Tipo* tipoIzq, Tipo* tipoDer) ;
Tipo* compilaDivision(Tipo* tipoIzq, Tipo* tipoDer) ;
Tipo* compilaModulo(Tipo* tipoIzq, Tipo* tipoDer) ;

Tipo* compilaMayor(Tipo* tipoIzq, Tipo* tipoDer) ;
Tipo* compilaMenor(Tipo* tipoIzq, Tipo* tipoDer) ;
Tipo* compilaIgual(Tipo* tipoIzq, Tipo* tipoDer) ;
Tipo* compilaDistinto(Tipo* tipoIzq, Tipo* tipoDer) ;
Tipo* compilaMayorIgual(Tipo* tipoIzq, Tipo* tipoDer) ;
Tipo* compilaMenorIgual(Tipo* tipoIzq, Tipo* tipoDer) ;

Tipo* compilaAND(Tipo* tipoIzq, Tipo* tipoDer);
Tipo* compilaOR(Tipo* tipoIzq, Tipo* tipoDer);
Tipo* compilaNOT(Tipo* tipo);

Tipo* compilaMenosUnario(Tipo* tipo);

Tipo* compilarInvocacionFuncion(string ident, vector<Simbolo*>* vectorSimbolos);

void compilarDeclaracion(vector< Simbolo* > &vectorSimbolos, Tipo* tipo, bool global);

Tipo* compilarAccesoArray(TipoExpr& exprArray, TipoExpr& indice);

void compilarImprimir(Tipo* tipo);
void compilarObtener(Tipo* tipo);

int nextLabel(void);
void inicializarCompilador(void);

bool existeSimbolo(TablaSimbolos &TS, Simbolo* simbolo);

void cargarDato(TipoExpr& tipoExpr);

Tipo* castImplicito(Tipo* tipoIzq, Tipo* tipoDer);
Tipo* castExplicito(Tipo* tipoDest, Tipo* tipoOrig);
#endif
