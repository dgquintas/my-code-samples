#include "simbolo.h"
#include <iostream> 

using namespace std;

unsigned int Simbolo::ultimaDireccion = 0;

Simbolo::Simbolo(std::string nombre, Tipo* tipo)
  : nombre(nombre), tipo(tipo), global(false), dimension(0), parametroPorRef(false)
{
  ultimaDireccion += tipo->getTam();
  direccion = Simbolo::ultimaDireccion;
}

Simbolo::Simbolo(std::string nombre)
  : nombre(nombre), tipo(NULL), global(false), dimension(0), parametroPorRef(false)

{
}

Simbolo::Simbolo(std::string nombre, Tipo* tipo, int despBP) 
  : nombre(nombre), tipo(tipo), global(false), dimension(0), parametroPorRef(false)

{
  direccion = despBP;
}

void Simbolo::setTipo ( Tipo* tipo )
{
  this->tipo = tipo;
  ultimaDireccion += tipo->getTam();     
  direccion = Simbolo::ultimaDireccion;
  return;
}
Tipo* Simbolo::getTipo (  )
{
  return tipo;
}

std::string Simbolo::getNombre (  )
{
  return nombre;
}

unsigned int Simbolo::getDireccion (  )
{
  return direccion;
}

unsigned int Simbolo::getDimension()
{
  return dimension;
}

void Simbolo::setDimension(unsigned int dim)
{
  dimension = dim;
  return;
}

