#ifndef _CONTEXT_H
#define _CONTEXT_H

#include <vector>
#include <utility>
#include "symboltable.h"
#include <inttypes.h>

using namespace std;

//typedef union { int entero; double real; } Valor;
//typedef pair< char, Valor > TValue;
typedef uint8_t TValue;
typedef unsigned short TDir;

class Memory
{
  public:
    Memory(size_t size = 65536);
    
    void assignInt(TDir, short valor);
    void assignReal(TDir, float valor);
    
    short getValInt(TDir);
    float getValReal(TDir);
 
    size_t getSize();

    // pila
    void pushInt(const short&);
    void pushReal(const float&);

    short popInt();
    float popReal();
    
    void setStackp(unsigned int);
    unsigned int getStackp(void);
    
    void setBp(unsigned int);
    unsigned int getBp(void);

  private:
    size_t _size;
    vector<TValue> _store;
    void checkRange(TDir n);

    //pila
    unsigned int _sp;
    unsigned int _bp;

};

class Context
{
  public:
    Context();
    void setCount(int);
    int getCount();
    void incICount();

    Memory memoria;
    SymbolTable ts;

  private:
    int _count;
};

#endif
