#include "tipofuncion.h"
#include <iostream>

TipoFuncion::TipoFuncion()
  :  tam(0)
{
}

TipoFuncion::~TipoFuncion()
{
  for(unsigned int i=0; i<listaParametros.size(); i++)
    delete listaParametros[i];
}

unsigned int TipoFuncion::getTam (  ){
  return tam;
}

void TipoFuncion::insertar(Simbolo* simbolo)
{
  listaParametros.push_back(simbolo);
  return;
}

int TipoFuncion::numeroParametros(void)
{
  return listaParametros.size();
}
Simbolo* TipoFuncion::getParametro(int i)
{
  if( i < listaParametros.size() )
    return listaParametros[i];
  else
    return NULL;
}



void TipoFuncion::setTipo(Tipo* tipo)
{
  tipoRetorno = tipo;
  return;
}
Tipo* TipoFuncion::getTipo(void)
{
  return tipoRetorno;
}

int TipoFuncion::calcularM(void)
{
  int suma = 0;
  for(unsigned int i=0; i<listaParametros.size(); i++)
    if( listaParametros[i]->getTipo()->pasoPorReferencia() )
      suma += 2;
    else
      suma += listaParametros[i]->getTipo()->getTam();
  return suma;
}
    
