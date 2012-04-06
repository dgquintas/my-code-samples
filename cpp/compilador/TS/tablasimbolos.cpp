#include "tablasimbolos.h"
#include <cassert>

TablaSimbolos::TablaSimbolos()
{}

TablaSimbolos::~TablaSimbolos()
{
  for(unsigned int i=0; i<tabla.size(); i++)
    delete tabla[i];
/*
  while( !tabla.empty() ){
    std::map<std::string, Simbolo*>* hashTemp = tabla.top();
    for(std::map < std::string, Simbolo* >::iterator it = hashTemp->begin(); 
        it != hashTemp->end(); 
        it++)
      delete (*it).second;
  }
*/
}

void TablaSimbolos::insertar ( Simbolo *simbolo )
{
  assert(tabla.size());
  tabla.back()->operator[](simbolo->getNombre()) = simbolo;

  return;
}

Simbolo* TablaSimbolos::buscar ( std::string nombre )
{
  for(int i = tabla.size()-1; i >= 0; i--){
    std::map< std::string, Simbolo* >::iterator itMap;
    itMap = tabla[i]->find(nombre);
    if ( itMap != tabla[i]->end() )
      return (*itMap).second;
  }
  return NULL;
}

/** Busca solamente en el bloque "más externo". 
 *
 * Se utiliza, por ejemplo, para comprobar si hay más de un símbolo
 * con el mismo nombre en el mismo contexto */
Simbolo* TablaSimbolos::buscarEnBloque( std::string nombre )
{
  std::map< std::string, Simbolo* >::iterator itMap;
  itMap = tabla.back()->find(nombre);
  if ( itMap != tabla.back()->end() )
    return (*itMap).second;
  return NULL;
}

void TablaSimbolos::set (  )
{
  tabla.push_back(new std::map< std::string, Simbolo*>);

  Simbolo::resetUltimaDir();
  return;
}

void TablaSimbolos::reset (  )
{
  for(std::map< std::string, Simbolo*>::iterator it = tabla.back()->begin(); 
      it != tabla.back()->end(); 
      it++)
    delete (*it).second;
  
  tabla.pop_back();
  return;
}

