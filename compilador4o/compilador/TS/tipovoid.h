#ifndef TIPOVOID_H
#define TIPOVOID_H

#include "tipo.h"

class TipoVoid: public Tipo {
  // Associations
  // Attributes
  private:
    static unsigned int tam ;
  // Operations
  public:
    TipoVoid();
    virtual unsigned int getTam (  );
    virtual std::string getNombre() {return "void";};
};

#endif
