#include <vector>
#include <iostream>

class C {
    public:
        C(int i) : _i(i) {
            std::cerr << "Ctor invoked" << std::endl;
        };
        C(const C& c){
            std::cerr << "Copy ctor invoked" << std::endl;
            this->_i = c._i;
        }
        void incr(){ 
            _i++;
        }
        int get_i() const { return _i;} ; 
    private:
        int _i;
};

int main(){
    std::vector<C> v( 10, C(5) );
    for( std::vector<C>::iterator it = v.begin(); it != v.end(); it++){
        std::cout << it->get_i() << std::endl;
    }
    std::cout << std::endl;
    v[3].incr();
    for( std::vector<C>::iterator it = v.begin(); it != v.end(); it++){
        std::cout << it->get_i() << std::endl;
    }
   
    return 0;
}
