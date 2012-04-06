#ifndef SIMBOLO_H
#define SIMBOLO_H

#include "tipo.h"
#include <string>

using namespace std;

class Simbolo {
public:
    Simbolo(string nombre, Tipo* tipo);
    Simbolo(string nombre);
    Simbolo(string nombre, Tipo* tipo, int despBP);
    void setTipo( Tipo* tipo );
    Tipo* getTipo (  );
    std::string getNombre (  );
    size_t getDireccion (  );
    size_t getDimension();
    void setDimension(size_t dim);
    bool getGlobal() {return global;};
    void setGlobal() { global = true; direccion -= tipo->getTam();};
    bool getParametroPorRef () { return parametroPorRef; };
    void setParametroPorRef () { parametroPorRef = true; };
    static void resetUltimaDir(void) { ultimaDireccion = 0; }
    static size_t getUltimaDir(void) { return ultimaDireccion; };

    void setLvalue(bool lv) { lvalue = lv; };
    bool getLvalue() { return lvalue; };

  private:
    std::string nombre;
    size_t direccion;
    size_t dimension;
    static size_t ultimaDireccion;
    Tipo* tipo;
    bool global;
    bool parametroPorRef;
    bool lvalue;
      
};

#endif
