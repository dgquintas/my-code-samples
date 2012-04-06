#ifndef TIPOINT_H
#define TIPOINT_H

#include "tipo.h"

class TipoInt: public Tipo {
  public:
    TipoInt();
    virtual unsigned int getTam (  );
    virtual std::string getNombre() { return "int";};
    virtual char getPrefijo() { return 'I';};
    virtual bool esImprimible() { return true; }; 
  private:
    static size_t tam ;

};

#endif
