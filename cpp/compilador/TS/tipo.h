#ifndef TIPO_H
#define TIPO_H

#include <string>

class Tipo {
  public:
    virtual unsigned int getTam (  ) = 0;
    virtual std::string getNombre() = 0;
    virtual bool pasoPorReferencia() { return false; };
    virtual bool admitePunto() { return false; };
    virtual bool esImprimible() { return false; };
    virtual char getPrefijo() { return 0; };
    
};


typedef struct {
  Tipo* tipo;
  bool lvalue;
  bool cargado;
} TipoExpr;

#endif
