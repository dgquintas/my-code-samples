#include "mixin.h"

class Gnral : public Mixin<Gnral>
{
  public:
    void setX(int x){ this->x = x;} 
    int getX() {return x;}
    virtual ~Gnral(){};

  private:
    Gnral() : x(123) {};
    int x;

    friend class Mixin<Gnral>;


};

