#include "tipoarray.h"
#include <iostream>

using namespace std;

TipoArray::TipoArray(Tipo* tipo, size_t tam)
  : tipo(tipo), tam(tam)
{}
TipoArray::TipoArray(size_t tam)
  : tipo(NULL), tam(tam)
{}

size_t TipoArray::getTam (  )
{
  return (tam * tipo->getTam());
}

Tipo* TipoArray::getTipo (  )
{
  return tipo;
}
void TipoArray::setTipo( Tipo* tipo )
{
  this->tipo = tipo;
  return;
}
