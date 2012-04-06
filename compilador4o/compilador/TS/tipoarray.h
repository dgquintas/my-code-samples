#ifndef TIPOARRAY_H
#define TIPOARRAY_H

#include "tipo.h"
#include <string>

using namespace std;


class TipoArray: public Tipo {
  public:
    TipoArray(Tipo*, size_t tam);
    TipoArray(unsigned int tam);

    virtual unsigned int getTam (  );
    virtual string getNombre() { return "array";};
    Tipo* getTipo (  );
    void  setTipo (Tipo* tipo);
    virtual bool pasoPorReferencia() { return true; };
  private:
    size_t tam;
    Tipo* tipo;
};

#endif
