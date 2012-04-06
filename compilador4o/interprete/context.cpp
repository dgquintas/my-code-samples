#include "context.h"
#include "excepciones.h"
#include <cstring>
#include <iostream>

using namespace std;

/////////////////////////////

Memory::Memory(size_t size)
  : _size(size), _store(size), _sp(size), _bp(size)
{ }

void
Memory::assignInt(TDir dir, short valor)
{
  //pasar a bytes y almacenar en "dir"
  //lanzara una excepcion out_of_range si dir esta fuera
  //de rango
  int8_t bytes[2];
  memcpy(bytes, &valor, 2);
  
  _store.at(dir+0) = bytes[0]; 
  _store.at(dir+1) = bytes[1];

  return;
}

void
Memory::assignReal(TDir dir, float valor)
{
  //pasar a bytes y almacenar en "dir"
  //lanzara una excepcion out_of_range si dir esta fuera
  //de rango

  int8_t bytes[4];
  memcpy(bytes, &valor, 4);

  _store.at(dir+0) = bytes[0]; 
  _store.at(dir+1) = bytes[1];
  _store.at(dir+2) = bytes[2];
  _store.at(dir+3) = bytes[3]; 
  return; 
}


short
Memory::getValInt(TDir dir)
{ 
  //lanzara una excepcion out_of_range si dir esta fuera
  //de rango
  short res;
  int8_t bytes[4];
  
  bytes[1] = _store.at(dir+1);
  bytes[0] = _store.at(dir+0); 

  memcpy(&res, bytes, 2);
  
  return res;
}

float
Memory::getValReal(TDir dir)
{ 
  //lanzara una excepcion out_of_range si dir esta fuera
  //de rango
  float res;
  int8_t bytes[4];
  
  bytes[3] = _store.at(dir+3); // parte alta
  bytes[2] = _store.at(dir+2);
  bytes[1] = _store.at(dir+1);
  bytes[0] = _store.at(dir+0); // parte baja

  memcpy(&res, bytes, 4);

  return res;
}


size_t
Memory::getSize()
{
  return _size;
}

//pila
void 
Memory::setStackp(unsigned int p)
{
  _sp = p;
  return;
}

unsigned int
Memory::getStackp(void)
{
  return _sp;
}

void 
Memory::setBp(unsigned int p)
{
  _bp = p;
  return;
}

unsigned int
Memory::getBp(void)
{
  return _bp;
}


void
Memory::pushInt(const short& valor)
{
  _sp -= 2;
  assignInt(_sp, valor);
  return;
}

void
Memory::pushReal(const float& valor)
{
  _sp -= 4;
  assignReal(_sp, valor);
  return;
}

short
Memory::popInt()
{
  short value;
  if( (_sp+2) <= _size ){
    value = getValInt(_sp);
    _sp += 2;
  }
  else
    throw ErrPilaVacia();

  return value;
}

float
Memory::popReal()
{
  float value;
  if( (_sp+4) <= _size ){
    value = getValReal(_sp);
    _sp += 4;
  }
  else
    throw ErrPilaVacia();

  return value;
}



////////////////////////////////////////77

Context::Context()
  : _count(0)
{}

void
Context::setCount(int c)
{
  _count = c;
  return;
}

int
Context::getCount(void)
{
  return _count;
}

void
Context::incICount(void)
{
  _count++;
  return;
}

