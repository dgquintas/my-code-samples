#ifndef TABLATIPOS_H
#define TABLATIPOS_H

#include "tipo.h"
#include <string>
#include <map>

class TablaTipos {
  public:
    TablaTipos();
    ~TablaTipos();
    void insertar ( std::string nombre, Tipo* tipo );
    Tipo* buscar ( std::string nombre);
  private:
    std::map < std::string, Tipo* > tabla;
};

#endif
