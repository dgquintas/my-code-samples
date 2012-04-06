#ifndef _CODE_H
#define _CODE_H

#include <string>
#include "context.h"

using namespace std;

class Code
{
  public:
    virtual void exec(Context &ctx) = 0;
    virtual string id() const = 0;
};


// y las clases (instrucciones) derivadas
class IPUSH: public Code
{
  public:
    IPUSH(short);
    virtual void exec(Context &ctx);
    virtual string id() const { return "IPUSH"; };
  private:
    short argumento;
};
class FPUSH: public Code
{
  public:
    FPUSH(float);
    virtual void exec(Context &ctx);
    virtual string id() const { return "FPUSH"; };
  private:
    float argumento;
};
class IPUSHBP: public Code
{
  public:
    IPUSHBP(int);
    virtual void exec(Context &ctx);
    virtual string id() const { return "IPUSHBP"; };
  private:
    int argumento;
};

class IPOP: public Code
{
  public:
    virtual void exec(Context &ctx);
    virtual string id() const { return "IPOP"; };
};
class FPOP: public Code
{
  public:
    virtual void exec(Context &ctx);
    virtual string id() const { return "IPOP"; };
};



class ILOAD: public Code
{
  public:
    virtual void exec(Context &ctx);
    virtual string id() const { return "ILOAD"; };
};
class FLOAD: public Code
{
  public:
    virtual void exec(Context &ctx);
    virtual string id() const { return "FLOAD"; };
};

class ISTORE: public Code
{
  public:
    virtual void exec(Context &ctx);
    virtual string id() const { return "ISTORE"; };
};
class FSTORE: public Code
{
  public:
    virtual void exec(Context &ctx);
    virtual string id() const { return "FSTORE"; };
};

class IADD: public Code
{
  public:
    virtual void exec(Context &ctx);
    virtual string id() const { return "IADD"; };
};
class FADD: public Code
{
  public:
    virtual void exec(Context &ctx);
    virtual string id() const { return "FADD"; };
};
class ISUB: public Code
{
  public:
    virtual void exec(Context &ctx);
    virtual string id() const { return "ISUB"; };
};
class FSUB: public Code
{
  public:
    virtual void exec(Context &ctx);
    virtual string id() const { return "FSUB"; };
};
class IMUL: public Code
{
  public:
    virtual void exec(Context &ctx);
    virtual string id() const { return "IMUL"; };
};
class FMUL: public Code
{
  public:
    virtual void exec(Context &ctx);
    virtual string id() const { return "FMUL"; };
};
class IDIV: public Code
{
  public:
    virtual void exec(Context &ctx);
    virtual string id() const { return "IDIV"; };
};
class FDIV: public Code
{
  public:
    virtual void exec(Context &ctx);
    virtual string id() const { return "FDIV"; };
};
class IMOD: public Code
{
  public:
    virtual void exec(Context &ctx);
    virtual string id() const { return "IMOD"; };
};
class FMOD: public Code
{
  public:
    virtual void exec(Context &ctx);
    virtual string id() const { return "FMOD"; };
};


class ICHSGN: public Code
{
  public:
    virtual void exec(Context &ctx);
    virtual string id() const { return "ICHSGN"; };
};
class FCHSGN: public Code
{
  public:
    virtual void exec(Context &ctx);
    virtual string id() const { return "FCHSGN"; };
};


class CAST: public Code
{
  public:
    virtual void exec(Context &ctx);
    virtual string id() const { return "CAST"; };
};
class FToI: public Code
{
  public:
    virtual void exec(Context &ctx);
    virtual string id() const { return "FToI"; };
};
class CAST2: public Code
{
  public:
    virtual void exec(Context &ctx);
    virtual string id() const { return "CAST2"; };
};


class IOUTPUT: public Code
{
  public:
    virtual void exec(Context &ctx);
    virtual string id() const { return "IOUTPUT"; };
};
class FOUTPUT: public Code
{
  public:
    virtual void exec(Context &ctx);
    virtual string id() const { return "FOUTPUT"; };
};
class IINPUT: public Code
{
  public:
    virtual void exec(Context &ctx);
    virtual string id() const { return "IINPUT"; };
};
class FINPUT: public Code
{
  public:
    virtual void exec(Context &ctx);
    virtual string id() const { return "FINPUT"; };
};

class Call: public Code
{
  public:
    Call(string);
    virtual void exec(Context &ctx);
    virtual string id() const { return "Call"; };
  private:
    string etiqueta;
};
class Return: public Code
{
  public:
    Return(int n, int m);
    virtual void exec(Context &ctx);
    virtual string id() const { return "Return"; };

  private:
    int _n;
    int _m;
};
class IReturn: public Code
{
  public:
    IReturn(int n, int m);
    virtual void exec(Context &ctx);
    virtual string id() const { return "IReturn"; };

  private:
    int _n;
    int _m;
};
class FReturn: public Code
{
  public:
    FReturn(int n, int m);
    virtual void exec(Context &ctx);
    virtual string id() const { return "FReturn"; };

  private:
    int _n;
    int _m;
};

class JMP: public Code
{
  public:
    JMP(string);
    virtual void exec(Context &ctx);
    virtual string id() const { return "JMP"; };
  private:
    string etiqueta;
};
class JMPZero: public Code
{
  public:
    JMPZero(string);
    virtual void exec(Context &ctx);
    virtual string id() const { return "JMPZero"; };
  private:
    string etiqueta;
};
class JMPNotZero: public Code
{
  public:
    JMPNotZero(string);
    virtual void exec(Context &ctx);
    virtual string id() const { return "JMPNotZero"; };
  private:
    string etiqueta;
};




class IEqual: public Code
{
  public:
    virtual void exec(Context &ctx);
    virtual string id() const { return "IEqual"; };
};
class INotEqual: public Code
{
  public:
    virtual void exec(Context &ctx);
    virtual string id() const { return "INotEqual"; };
};
class IGreater: public Code
{
  public:
    virtual void exec(Context &ctx);
    virtual string id() const { return "IGreater"; };
};
class ILess: public Code
{
  public:
    virtual void exec(Context &ctx);
    virtual string id() const { return "ILess"; };
};
class IGreaterEqual: public Code
{
  public:
    virtual void exec(Context &ctx);
    virtual string id() const { return "IGreaterEqual"; };
};
class ILessEqual: public Code
{
  public:
    virtual void exec(Context &ctx);
    virtual string id() const { return "ILessEqual"; };
};

class FEqual: public Code
{
  public:
    virtual void exec(Context &ctx);
    virtual string id() const { return "FEqual"; };
};
class FNotEqual: public Code
{
  public:
    virtual void exec(Context &ctx);
    virtual string id() const { return "FNotEqual"; };
};
class FGreater: public Code
{
  public:
    virtual void exec(Context &ctx);
    virtual string id() const { return "FGreater"; };
};
class FLess: public Code
{
  public:
    virtual void exec(Context &ctx);
    virtual string id() const { return "FLess"; };
};
class FGreaterEqual: public Code
{
  public:
    virtual void exec(Context &ctx);
    virtual string id() const { return "FGreaterEqual"; };
};
class FLessEqual: public Code
{
  public:
    virtual void exec(Context &ctx);
    virtual string id() const { return "FLessEqual"; };
};




class AND: public Code
{
  public:
    virtual void exec(Context &ctx);
    virtual string id() const { return "AND"; };
};
class OR: public Code
{
  public:
    virtual void exec(Context &ctx);
    virtual string id() const { return "OR"; };
};
class NOT: public Code
{
  public:
    virtual void exec(Context &ctx);
    virtual string id() const { return "NOT"; };
};

class RESRV: public Code
{
  public:
    RESRV(unsigned short numBytes);
    virtual void exec(Context &ctx);
    virtual string id() const { return "RESRV"; };
  private:
    unsigned short _numBytes;
};

class PRINT: public Code
{
  public:
    PRINT(string cadena);
    virtual void exec(Context &ctx);
    virtual string id() const { return "PRINT"; };
  private:
    string _cadena;
};


#endif
