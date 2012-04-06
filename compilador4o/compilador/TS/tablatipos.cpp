#include "tablatipos.h"

TablaTipos::TablaTipos()
{}

TablaTipos::~TablaTipos()
{
//  for(std::map< std::string, Tipo* >::iterator it = tabla.begin(); 
//      it != tabla.end(); 
//      it++)
//    delete (*it).second;
//    FIXME
}

void TablaTipos::insertar ( std::string nombre, Tipo* tipo )
{
  tabla[nombre] = tipo;
  return;
}

Tipo* TablaTipos::buscar ( std::string nombre )
{
  std::map< std::string, Tipo* >::iterator it;
  it = tabla.find(nombre);
  if( it != tabla.end() )
    return (*it).second;
  else
    return NULL;
}

