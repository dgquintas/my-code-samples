#include "tipostruct.h"
#include <iostream>

TipoStruct::TipoStruct()
  :  _tam(0)
{}

TipoStruct::~TipoStruct()
{
  for(unsigned int i=0; i<_listaComponentes.size(); i++)
    delete _listaComponentes[i];
}

unsigned int TipoStruct::getTam (  ){
  return _tam;
}

void TipoStruct::insertar(std::string nombre, Tipo* tipo)
{
  Campo* campo = new Campo(nombre, tipo, _tam);
  _tam += tipo->getTam();

  _listaComponentes.push_back(campo);

  return;
}

void TipoStruct::insertar(Campo* campo)
{
  campo->setDesplazamiento(_tam);
  _tam += campo->getTipo()->getTam();

  _listaComponentes.push_back(campo);

  return;
}

Campo* TipoStruct::buscar(std::string nombre)
{
  for(unsigned int i=0; i < _listaComponentes.size(); i++){
    if( _listaComponentes[i]->getNombre() == nombre )
      return _listaComponentes[i];
  }
  return NULL;
}

  
Campo* TipoStruct::getCampo(int i)
{
  if( i < _listaComponentes.size() )
    return _listaComponentes[i];
  else
    return NULL;
}
