#include "code.h"
#include "excepciones.h"
#include <iostream>
#include <cassert>
#include <cmath>

using namespace std;

IPUSH::IPUSH(short cte)
  : argumento(cte)
{}

void
IPUSH::exec(Context &ctx)
{
  ctx.memoria.pushInt(argumento);
}

//////////////////////////////////////


 FPUSH::FPUSH(float cte)
  : argumento(cte)
{}

void
FPUSH::exec(Context &ctx)
{
  ctx.memoria.pushReal(argumento);
}

//////////////////////////////////////
IPUSHBP::IPUSHBP(int cte)
  : argumento(cte)
{}

void
IPUSHBP::exec(Context &ctx)
{
  unsigned int bp = ctx.memoria.getBp();
  if( (bp-argumento) >= 65536 ){
    cout << "BP = " << bp << endl;
    cout << "ARG = " << argumento << endl;
    exit(-1);
  }
  ctx.memoria.pushInt((unsigned short)(bp-argumento));
}

//////////////////////////////////////

void
IPOP::exec(Context &ctx)
{
  ctx.memoria.popInt();
}
void
FPOP::exec(Context &ctx)
{
  ctx.memoria.popReal();
}


//////////////////////////////////////


void
ILOAD::exec(Context &ctx)
{
  unsigned short d = (unsigned short)ctx.memoria.popInt();
  short arg;
  arg = ctx.memoria.getValInt(d);
  ctx.memoria.pushInt(arg);
  return; 
}

/////////////////////////////////////
void
FLOAD::exec(Context &ctx)
{
  unsigned short d = (unsigned short)ctx.memoria.popInt();
  float arg;
  arg = ctx.memoria.getValReal(d);
  ctx.memoria.pushReal(arg);
  return; 
}

/////////////////////////////////////
void
ISTORE::exec(Context &ctx)
{
  short v;
  unsigned short d;
  v = ctx.memoria.popInt();
  d = (unsigned short)ctx.memoria.popInt();
  ctx.memoria.assignInt(d, v);

  return;
}

/////////////////////////////////////
void
FSTORE::exec(Context &ctx)
{
  float v;
  unsigned short d;
  v = ctx.memoria.popReal();
  d = (unsigned short)ctx.memoria.popInt(); 

  ctx.memoria.assignReal(d, v);

  return;
}

/////////////////////////////////////

void
IADD::exec(Context &ctx)
{
  short v1;
  short v2;
  v1 = ctx.memoria.popInt();
  v2 = ctx.memoria.popInt();
  
  short res;
  res = v1 + v2;
  ctx.memoria.pushInt(res);
  
  return;
}

void
FADD::exec(Context &ctx)
{
  float v1;
  float v2;
  v1 = ctx.memoria.popReal();
  v2 = ctx.memoria.popReal();
  
  float res;
  res = v1 + v2;
  ctx.memoria.pushReal(res);

  return;
}

/////////////////////////////////////

void
ISUB::exec(Context &ctx)
{ 
  short v1;
  short v2;
  v1 = ctx.memoria.popInt();
  v2 = ctx.memoria.popInt();
  
  short res;
  res = v2 - v1;
  ctx.memoria.pushInt(res);
  
  return;

}

void
FSUB::exec(Context &ctx)
{
  float v1;
  float v2;
  v1 = ctx.memoria.popReal();
  v2 = ctx.memoria.popReal();
  
  float res;
  res = v2 - v1;
  ctx.memoria.pushReal(res);

  return;

}

/////////////////////////////////////

void
IMUL::exec(Context &ctx)
{
  short v1;
  short v2;
  v1 = ctx.memoria.popInt();
  v2 = ctx.memoria.popInt();
  
  short res;
  res = v1 * v2;
  ctx.memoria.pushInt(res);
  
  return;

}

void
FMUL::exec(Context &ctx)
{
  float v1;
  float v2;
  v1 = ctx.memoria.popReal();
  v2 = ctx.memoria.popReal();
  
  float res;
  res = v1 * v2;
  ctx.memoria.pushReal(res);

  return;

}

/////////////////////////////////////

void
IDIV::exec(Context &ctx)
{
  short v1;
  short v2;
  v1 = ctx.memoria.popInt();
  v2 = ctx.memoria.popInt();
  
  short res;
  res = v2 / v1;
  ctx.memoria.pushInt(res);
  
  return;
}

void
FDIV::exec(Context &ctx)
{
  float v1;
  float v2;
  v1 = ctx.memoria.popReal();
  v2 = ctx.memoria.popReal();
  
  float res;
  res = v2 / v1;
  ctx.memoria.pushReal(res);

  return;

}

/////////////////////////////////////
void
IMOD::exec(Context &ctx)
{
  short v1;
  short v2;
  v1 = ctx.memoria.popInt();
  v2 = ctx.memoria.popInt();
  
  short res;
  res = v2 % v1;
  ctx.memoria.pushInt(res);
  
  return;
}

void
FMOD::exec(Context &ctx)
{ 
  float v1;
  float v2;
  v1 = ctx.memoria.popReal();
  v2 = ctx.memoria.popReal();
  
  float res;
  res = fmod(v2, v1);
  ctx.memoria.pushReal(res);

  return;
}


/////////////////////////////////////
void
ICHSGN::exec(Context &ctx)
{
  short v = ctx.memoria.popInt();
  v = -v;

  ctx.memoria.pushInt(v);
  return;
}
void
FCHSGN::exec(Context &ctx)
{
  float v = ctx.memoria.popReal();
  v = -v;

  ctx.memoria.pushReal(v);
  return;
}

/////////////////////////////////////




void
CAST::exec(Context &ctx)
{
  short v;
  v = ctx.memoria.popInt();
  ctx.memoria.pushReal((float)v);
  return;
}
void 
FToI::exec(Context &ctx)
{
  float v;
  v = ctx.memoria.popReal();
  ctx.memoria.pushInt((short)v);
  return;
}
void 
CAST2::exec(Context &ctx)
{
  float v1;
  short v2;
  v1 = ctx.memoria.popReal();
  v2 = ctx.memoria.popInt();
  
  ctx.memoria.pushReal((float)v2);
  ctx.memoria.pushReal(v1);
  
  return;
} 

/////////////////////////////////////////////

void 
IOUTPUT::exec(Context &ctx)
{
  short v;
  v = ctx.memoria.popInt();
  cout << v << endl; 
  
  return;
}
void 
FOUTPUT::exec(Context &ctx)
{
  float v;
  v = ctx.memoria.popReal();
  cout << v << endl;
  
  return;
}

void
IINPUT::exec(Context &ctx)
{

  short v;
  unsigned short d;
  cin >> v;
  d = (unsigned short)ctx.memoria.popInt();
//  if( d == (ctx.memoria.getStackp()-2) ) // apilar
//    ctx.memoria.pushInt(v);
//  else
    ctx.memoria.assignInt(d, v);

  return;
}
void
FINPUT::exec(Context &ctx)
{ 
  float v;
  unsigned short d;
  cin >> v;
  d = (unsigned short)ctx.memoria.popInt(); 
//  if( d == (ctx.memoria.getStackp()-4) ) // apilar
//    ctx.memoria.pushReal(v);
//  else
    ctx.memoria.assignReal(d, v);

  ctx.memoria.assignReal(d, v);
  return;
}

//////////////////////////////////////

Call::Call(string str)
  : etiqueta(str)
{}

void
Call::exec(Context &ctx)
{
  /* 
   * 1) apilar la dir de retorno
   * 2) apilar el valor de BP
   * 3) asignar a BP la dir del tope de la pila
  */
  ctx.memoria.pushInt((short)ctx.getCount());
  ctx.memoria.pushInt((short)ctx.memoria.getBp());
  ctx.memoria.setBp(ctx.memoria.getStackp());
  
  //ahora se salta
  int newI = ctx.ts.lookupLabel( etiqueta );
  ctx.setCount(newI-1);

  return;

}

Return::Return(int n, int m)
  : _n(n), _m(m)
{}

void
Return::exec(Context &ctx)
{
  // sacar n bytes de la cima de la pila (vbles locales)
  ctx.memoria.setStackp( ctx.memoria.getStackp() + _n);
  unsigned int bpAntiguo = (unsigned short)ctx.memoria.popInt();
  if( bpAntiguo == 0 )
    bpAntiguo = 65536;

  ctx.memoria.setBp(bpAntiguo);
  short ipAntiguo = ctx.memoria.popInt();
  ctx.setCount(ipAntiguo);
  // sacar m bytes de la cima de la pila (parametros)
  ctx.memoria.setStackp( ctx.memoria.getStackp() + _m );

  return;
}



IReturn::IReturn(int n, int m)
  : _n(n), _m(m)
{}
void
IReturn::exec(Context &ctx)
{
  //guardar el valor de retorno (entero)
  short vRet = ctx.memoria.popInt();
  //  sacar n bytes de la cima de la pila (vbles locales)
  ctx.memoria.setStackp( ctx.memoria.getStackp() + _n);
  
  unsigned int bpAntiguo = (unsigned short)ctx.memoria.popInt(); 
  if( bpAntiguo == 0 )
    bpAntiguo = 65536;

  ctx.memoria.setBp(bpAntiguo);
  
  short ipAntiguo = ctx.memoria.popInt();
  ctx.setCount(ipAntiguo);
  
  // sacar m bytes de la cima de la pila (parametros)
  ctx.memoria.setStackp( ctx.memoria.getStackp() + _m );
  //volver a apilar el valor de ret
  ctx.memoria.pushInt(vRet);
  
  return;
}
FReturn::FReturn(int n, int m)
  : _n(n), _m(m)
{}

void
FReturn::exec(Context &ctx)
{
  //guardar el valor de retorno (real)
  float vRet = ctx.memoria.popReal();
  // sacar n bytes de la cima de la pila (vbles locales)
  ctx.memoria.setStackp( ctx.memoria.getStackp() + _n);
  unsigned int bpAntiguo = (unsigned short)ctx.memoria.popInt();
  if( bpAntiguo == 0 )
    bpAntiguo = 65536;
 
  ctx.memoria.setBp(bpAntiguo);
  short ipAntiguo = ctx.memoria.popInt();
  ctx.setCount(ipAntiguo);
  //  sacar m bytes de la cima de la pila (parametros)
  ctx.memoria.setStackp( ctx.memoria.getStackp() + _m );
  //volver a apilar el valor de ret
  ctx.memoria.pushReal(vRet);

  return;
}
/////////////////////////////////////

JMP::JMP(string str)
  : etiqueta(str)
{}
void
JMP::exec(Context &ctx)
{
  int newI = ctx.ts.lookupLabel( etiqueta );
  ctx.setCount(newI-1);
  return;
}


JMPZero::JMPZero(string str)
  : etiqueta(str)
{}
void
JMPZero::exec(Context &ctx)
{
  short v;
  v = ctx.memoria.popInt();
  if( v == 0 ){ 
    int newI = ctx.ts.lookupLabel( etiqueta );
    ctx.setCount(newI-1);
  }
  return;
}

JMPNotZero::JMPNotZero(string str)
  : etiqueta(str)
{}
void
JMPNotZero::exec(Context &ctx)
{
  short v;
  v = ctx.memoria.popInt();
  if( v != 0 ){ 
    int newI = ctx.ts.lookupLabel( etiqueta );
    ctx.setCount(newI-1);
  }
  return;
}

/////////////////////////////////////////

void
IEqual::exec(Context &ctx)
{
  short v1 = ctx.memoria.popInt();
  short v2 = ctx.memoria.popInt();

  if( v1 == v2 )
    ctx.memoria.pushInt(1);
  else
    ctx.memoria.pushInt(0);

  return;
}

void
INotEqual::exec(Context &ctx)
{ 
  short v1 = ctx.memoria.popInt();
  short v2 = ctx.memoria.popInt();

  if( v1 != v2 )
    ctx.memoria.pushInt(1);
  else
    ctx.memoria.pushInt(0);

  return;
}

void
IGreater::exec(Context &ctx)
{
  short v1 = ctx.memoria.popInt();
  short v2 = ctx.memoria.popInt();

  //ojo al orden
  if( v2 > v1 )
    ctx.memoria.pushInt(1);
  else
    ctx.memoria.pushInt(0);

  return;
}

void
ILess::exec(Context &ctx)
{
  short v1 = ctx.memoria.popInt();
  short v2 = ctx.memoria.popInt();

  //ojo al orden
  if( v2 < v1 )
    ctx.memoria.pushInt(1);
  else
    ctx.memoria.pushInt(0);

  return;
}


void
IGreaterEqual::exec(Context &ctx)
{
  short v1 = ctx.memoria.popInt();
  short v2 = ctx.memoria.popInt();

  //ojo al orden
  if( v2 >= v1 )
    ctx.memoria.pushInt(1);
  else
    ctx.memoria.pushInt(0);

  return;
}

void
ILessEqual::exec(Context &ctx)
{
  short v1 = ctx.memoria.popInt();
  short v2 = ctx.memoria.popInt();

  //ojo al orden
  if( v2 <= v1 )
    ctx.memoria.pushInt(1);
  else
    ctx.memoria.pushInt(0);

  return;
}

void
FEqual::exec(Context &ctx)
{
  float v1 = ctx.memoria.popReal();
  float v2 = ctx.memoria.popReal();

  if( v1 == v2 )
    ctx.memoria.pushInt(1);
  else
    ctx.memoria.pushInt(0);

  return;
}

void
FNotEqual::exec(Context &ctx)
{ 
  float v1 = ctx.memoria.popReal();
  float v2 = ctx.memoria.popReal();

  if( v1 != v2 )
    ctx.memoria.pushInt(1);
  else
    ctx.memoria.pushInt(0);

  return;
}

void
FGreater::exec(Context &ctx)
{
  float v1 = ctx.memoria.popReal();
  float v2 = ctx.memoria.popReal();

  //ojo al orden
  if( v2 > v1 )
    ctx.memoria.pushInt(1);
  else
    ctx.memoria.pushInt(0);

  return;
}

void
FLess::exec(Context &ctx)
{
  float v1 = ctx.memoria.popReal();
  float v2 = ctx.memoria.popReal();

  //ojo al orden
  if( v2 < v1 )
    ctx.memoria.pushInt(1);
  else
    ctx.memoria.pushInt(0);

  return;
}
void
FGreaterEqual::exec(Context &ctx)
{
  float v1 = ctx.memoria.popReal();
  float v2 = ctx.memoria.popReal();

  //ojo al orden
  if( v2 >= v1 )
    ctx.memoria.pushInt(1);
  else
    ctx.memoria.pushInt(0);

  return;
}

void
FLessEqual::exec(Context &ctx)
{
  float v1 = ctx.memoria.popReal();
  float v2 = ctx.memoria.popReal();

  //ojo al orden
  if( v2 <= v1 )
    ctx.memoria.pushInt(1);
  else
    ctx.memoria.pushInt(0);

  return;
}





void 
AND::exec(Context &ctx)
{
  short v1,v2;
  v1 = ctx.memoria.popInt();
  v2 = ctx.memoria.popInt();
  short res;
  if( v1 && v2 )
    res = 1;
  else
    res = 0;
  ctx.memoria.pushInt(res);
  
  return;
}

void 
OR::exec(Context &ctx)
{
  short v1,v2;
  v1 = ctx.memoria.popInt();
  v2 = ctx.memoria.popInt();
  short res;
  if( v1 || v2 )
    res = 1;
  else
    res = 0;
  ctx.memoria.pushInt(res);
  
  return;

}

void 
NOT::exec(Context &ctx)
{
  short v1;
  v1 = ctx.memoria.popInt();
  short res;
  if( !v1 )
    res = 1;
  else
    res = 0;
  ctx.memoria.pushInt(res);
  
  return;
}

////////////////////
RESRV::RESRV(unsigned short numBytes)
  : _numBytes(numBytes)
{}

void
RESRV::exec(Context &ctx)
{
  //reservar espacio para _numBytes bytes
  //(ie, restar al SP ese valor)
  ctx.memoria.setStackp( ctx.memoria.getStackp() - _numBytes );
  return;
}
////////////////////
PRINT::PRINT(string cadena)
  : _cadena(cadena)
{}

void
PRINT::exec(Context &ctx)
{
  cout << _cadena.substr(1, _cadena.size()-2) << endl;
  return;
}
