#ifndef TABLASIMBOLOS_H
#define TABLASIMBOLOS_H

#include "simbolo.h"
#include <vector>
#include <map>

class TablaSimbolos {
  public:
    TablaSimbolos();
    ~TablaSimbolos();
    void insertar ( Simbolo* simbolo );
    Simbolo* buscar ( std::string nombre );
    Simbolo* buscarEnBloque ( std::string nombre );
    void set (  );
    void reset (  );

  private:
    std::vector< std::map < std::string, Simbolo *>* > tabla;
};

#endif
