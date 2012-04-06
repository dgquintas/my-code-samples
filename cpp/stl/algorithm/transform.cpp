#include <vector>
#include <iostream>
#include <algorithm>
#include <functional>

template<typename T>
void print(const std::vector<T> v){
    std::cout << '{';
    int i;
   for(i=0; i < ((int)v.size())-1; i++){
       std::cout << v[i] << ", ";
   }
   if( i < v.size() ){
       std::cout << v[i] << "}" << std::endl;
   }
}
int main(){
    std::vector<int> v;
    int acc = 1;
    for(int i=0; i <= 3; i++){
        v.push_back(acc);
        acc *= 2;
    }

    print(v);

    const int max_power_of_3 = 2;
    int sz = v.size();
    v.resize( sz * (1+max_power_of_3) ); 
    std::vector<int>::iterator ini(v.begin());
    std::vector<int>::iterator end(ini + sz);

    for(int i=0; i<max_power_of_3; i++){
        std::transform( ini, end, end,
                std::bind1st(std::multiplies<int>(), 3) );
        ini = end;
        end = ini+sz;
    }
    print(v);

    const int max_power_of_5 = 3;
    sz = v.size();
    v.resize( sz * (1+max_power_of_5) ); 
    ini = v.begin();
    end = ini + sz;
    for(int i=0; i<max_power_of_5; i++){
        std::transform( ini, end, end,
                std::bind1st(std::multiplies<int>(), 5) );
        ini = end;
        end = ini+sz;
    }
    print(v);
    std::cout << v.size() << std::endl;

    return 0;
}




