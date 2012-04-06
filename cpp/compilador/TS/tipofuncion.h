#ifndef TIPOFUNCION_H
#define TIPOFUNCION_H

#include "tipo.h"
#include <vector>
#include "simbolo.h"

class TipoFuncion: public Tipo {


  public:
    TipoFuncion();
    ~TipoFuncion();
//    void insertar(std::string nombre, Tipo* tipo); 
    void insertar(Simbolo* simbolo);//en la lista de parametros
    int numeroParametros(void);
    Simbolo* getParametro(int);
    virtual size_t getTam();
    virtual std::string getNombre() {return "funcion";}
    void setTipo(Tipo*);
    Tipo* getTipo(void);
    int calcularM(void); //para ver el nº de bytes a liberar al
                         //retornar por los parametros
                         
private:
    std::vector < Simbolo* > listaParametros;
    Tipo* tipoRetorno;    
    size_t tam;

};

#endif
