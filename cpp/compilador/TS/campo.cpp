#include "campo.h"
#include "tipo.h"

Campo::Campo(std::string nombre, Tipo* tipo, int desplazamiento)
  : nombre(nombre), tipo(tipo), desplazamiento(desplazamiento)
{}

Campo::Campo(std::string nombre, Tipo* tipo)
  : nombre(nombre), tipo(tipo)
{}


std::string Campo::getNombre()
{
  return nombre;
}

int Campo::getDesplazamiento()
{
  return desplazamiento;
}

void Campo::setDesplazamiento(int desp)
{
  desplazamiento = desp;
  return;
}

Tipo* Campo::getTipo()
{
  return tipo;
}
