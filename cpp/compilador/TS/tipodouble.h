#ifndef TIPODOUBLE_H
#define TIPODOUBLE_H

#include "tipo.h"

class TipoDouble: public Tipo {
  public:
    TipoDouble();
    virtual size_t getTam ();
    virtual std::string getNombre() { return "double";};
    virtual char getPrefijo() { return 'F';}; 
    virtual bool esImprimible() { return true; };
  private:
    static size_t tam;

};

#endif
