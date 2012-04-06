#ifndef CAMPO_H
#define CAMPO_H

#include "tipo.h"
#include <string>

class Campo {
  // Associations
  // Attributes
  private:
    std::string nombre;
    Tipo* tipo;
    int desplazamiento;
  public:
    Campo(std::string nombre, Tipo* tipo, int desplazamiento);
    Campo(std::string nombre, Tipo* tipo);
    std::string getNombre();
    Tipo* getTipo();
    void setDesplazamiento(int);
    int getDesplazamiento();
  // Operations
};

#endif
