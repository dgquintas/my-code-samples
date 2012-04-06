#include <iostream>

template<typename T>
  class Base{
    public:
      void commonMethod(){
        std::cout << "base" << std::endl;
      };
  };

class Deriv1 : public Base<Deriv1>
{
  public:
  void commonMethod(){
    std::cout << "deriv1" << std::endl;
  };

};

class Deriv2 : public Deriv1, public Base<Deriv2>
{
  public:
  void commonMethod(){
    std::cout << "deriv2" << std::endl;
  };


};

class Deriv3 : public Deriv2, public Base<Deriv3>
{
};


template<typename S>
  class TemplateS{

    public:
      void doSthOnBla(){
//        _bla.Deriv2::commonMethod();
//        _bla.Base<Deriv2>::commonMethod();
        _bla.Base<S>::commonMethod();


        //if the BaseClass:: part is not specified, we get this:
        //templates.h: In member function ‘void TemplateS<S>::doSthOnBla() [with S = Deriv2]’:
        //main.cpp:6:   instantiated from here
        //templates.h:30: error: request for member ‘commonMethod’ is ambiguous
        //templates.h:6: error: candidates are: void Base<T>::commonMethod() [with T = Deriv2]
        //templates.h:14: error:                 virtual void Deriv1::commonMethod()

        //if Deriv1 doesnt override the virtual method:
        //templates.h: In member function ‘void TemplateS<S>::doSthOnBla() [with S = Deriv2]’:
        //main.cpp:6:   instantiated from here
        //templates.h:18: error: request for member ‘commonMethod’ is ambiguous
        //templates.h:4: error: candidates are: void Base<T>::commonMethod() [with T = Deriv2]
        //templates.h:4: error:                 void Base<T>::commonMethod() [with T = Deriv1]
        

      }
    private:
      S _bla;
  };
