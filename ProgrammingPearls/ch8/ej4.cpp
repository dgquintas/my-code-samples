#include <vector>
#include <cstdlib>
#include <iostream>
#include <ctime>

template<class T>
T get_max_sub(const std::vector<T>& v, size_t& ini, size_t& end){
    size_t i_max(0), j_max(0);
    T maxsofar(0); 
    T acum(0);

    for(size_t i=0; i < v.size(); i++){
        acum += v[i];
        if( acum >= maxsofar ){
            maxsofar = acum; 
            j_max = i;
        }
        if( acum < 0 ){
            i_max = j_max = i+1;
            acum = 0;
        }
    }
    
    ini = i_max;
    end = j_max;
    return maxsofar;
}

float rand(int a, int b){
    const float p(rand()/float(RAND_MAX));
    return ((b-a)*p) + a;
}

#define TIMES 1000000
#define N 200

int main(){

    float acc(0);
    srand(time(NULL));
    for(int t=0; t < TIMES; t++){
        std::vector<float> v;

        for(int i=0; i < N; i++){
            v.push_back(rand(0,1));
        }
    //    for(int i=0; i < N; i++){
    //        std::cout<< v[i] << " " << std::endl;
    //    }
    //    std::cout<< std::endl;

        size_t ini, end;
        const float max( get_max_sub(v, ini, end) );
        acc += max;
    }

    std::cout << acc/TIMES << std::endl;

    return 0;
}


