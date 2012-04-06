/** Ensures at compile time that class @a D derives from base class
 * @B. 
 *
 * From Imperfect C++, by Matthew Wilson, page 5, section 1.2.1   
 * @note This check has no runtime cost whatsoever.
 *
 */
template<typename D, typename B>
struct must_have_base{
  ~must_have_base(){
    void(*p)(D*, B*) = constraints;
  }
  private:
  static void constraints(D* pd, B* pb){
    pb = pd;
  }
};

template<typename T>
  class TB {};

class TD : public TB<TD> {};

class B1 {};
class B2 {};
class D1 : public B1 {};
class D2 : public B2 {};
class DD1 : public D1 {};

template<typename T>
class Parametrized {
  public:
    Parametrized() {}
    ~Parametrized() {
      must_have_base<T, TB<T> > dummy;
    }

};

int main(){

  DD1 dd1;
  D1 d1;
  B1 b1;
  D2 d2;
  Parametrized< TD > param;

  must_have_base<DD1, B1>();
  must_have_base<D1, B1>();
  must_have_base<B1, B1>();
//  must_have_base<D2, B1>(); //error


  return 0;
}
