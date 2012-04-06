#ifndef TIPOSTRUCT_H
#define TIPOSTRUCT_H

#include "campo.h"
#include "tipo.h"
#include <vector>

class TipoStruct: public Tipo {
  public:
    TipoStruct();
    ~TipoStruct();
    void insertar(std::string nombre, Tipo* tipo);
    void insertar(Campo* campo);
    Campo* buscar(std::string nombre);
    virtual unsigned int getTam();
    virtual std::string getNombre() { return "struct"; };
    Campo* getCampo(int);
    virtual bool admitePunto() { return true; }; 
    virtual bool pasoPorReferencia() { return true; };
  private:
    std::vector < Campo* > _listaComponentes;
    size_t _tam;

};

#endif
