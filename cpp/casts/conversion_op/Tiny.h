//from c++ prog lang 3rd ed, p 275

class Tiny{
  char v;
  void assign(int i) {
    if (i & ~077) 
      throw Bad_range();
    v = i;
  }

  public:
  class Bad_range {};
  Tiny(int i){ assign(i); }
  Tiny& operator=(int i) {
    assign(i);
    return *this;
  }

  //XXX: conversion to (primitive type) int
  operator int() const { return v; }
};


