#include <iostream>
#include <iomanip>


std::ostream &lol(std::ostream &Out){
  Out << "bla";
  return(Out);
}

int main(int argc,char *argv[]){
  float Num = 3452.2334;
  //will insert 3.45e+03 into the stream
  std::cout << lol << Num << std::endl;

  return 0;
}
