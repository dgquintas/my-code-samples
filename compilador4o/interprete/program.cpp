#include "program.h"
#include <iostream>

void 
Program::addCode(Code *c)
{
  _code.push_back(c);
  _icount++;
  return;
}

int
Program::getCount()
{
  return _icount;
}

void
Program::setCount(int i)
{
  _icount = i;
  return;
}

void 
Program::exec(Context &ctx)
{
  int i;
  //buscar donde esta Main: para empezar a ejecutar
  i = ctx.ts.lookupLabel( "Main_1" );
  if(i < 0){
    std::cerr << "No ha sido posible encontrar la etiqueta inicial Main... saliendo." << std::endl;
    exit(-1);
  }
  ctx.setCount(i);

  while( (i=ctx.getCount()) < _icount ){
    _code[i]->exec(ctx);
    ctx.incICount();
  }
  return;
}

