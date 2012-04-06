#include <vector>
#include <exception>
#include <iostream>
#include <string>
#include <sstream>

#define QUOTE "

#define GEN_TRACE_INFO_OSS(oss) \
  oss << '(' << __FILE__ << ':' << __LINE__ << ')'


class x{
  public:
    x(const std::string& msg)
      : _msg (msg){}

    std::string what(){
      return _msg;
    }

  private:
    std::string _msg;
};

void f(int i) throw(x, std::exception);

void f(int i) throw(x, std::exception) {
  if( i < 0 ){
    std::ostringstream oss;
    oss << "error line ";
    GEN_TRACE_INFO_OSS(oss);
    throw x(oss.str());
  }else{
  std::vector<int> v;
  v.at(123);
  }
}


int main(){
  try{
    f(-1);
  } catch(std::exception& e){
    std::cout << e.what() << std::endl;
  }
  catch(x& e){
    std::cout << e.what() << std::endl;
  }



  return 0;
}
