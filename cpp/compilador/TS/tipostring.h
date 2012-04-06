#ifndef TIPOARRAY_H
#define TIPOARRAY_H

#include "tipo.h"

class TipoString: public Tipo {
  // Associations
  // Attributes
  private:
    unsigned int tam;
  // Operations
  public:
    TipoString(unsigned int tam);
    virtual unsigned int getTam (  );
};

#endif
