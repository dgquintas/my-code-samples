/* 
 * Consider the divisors of 30: 1,2,3,5,6,10,15,30.
 * It can be seen that for every divisor d of 30, d+30/d is prime.
 * 
 * Find the sum of all positive integers n not exceeding 100 000 000
 * such that for every divisor d of n, d+n/d is prime. */

#include <iostream>
#include <vector>
#include <bitset>
#include <utility>
#include <functional>
#include <numeric>
#include <algorithm>

#define N 100000000
//#define N 100000

template<typename T>
void print(const std::vector<T> v){
    std::cout << '{';
    int i;
   for(i=0; i < ((int)v.size())-1; i++){
       std::cout << "(" << v[i].first << ", " << v[i].second << ")" << ", ";
   }
   if( i < v.size() ){
       std::cout << "(" << v[i].first << ", " << v[i].second << ")" << "}" << std::endl;
   }
}
template<typename T>
void print2(const std::vector<T> v){
    std::cout << '{';
    int i;
   for(i=0; i < ((int)v.size())-1; i++){
       std::cout << v[i] << ", ";
   }
   if( i < v.size() ){
       std::cout << v[i] << "}" << std::endl;
   }
}
class Primes {
    public:
        Primes() 
            : _nums(new std::bitset<N>()) {
                _nums->flip();
                this->_sieve();
            }
        ~Primes(){
            delete _nums;
        }
        inline
        int nextPrime(int ini) const {
            int i = ini+1;
            for(; i < _nums->size() && (*_nums)[i] == 0; i++);
            return i < _nums->size() ? i : 0;
        } 
        inline
        bool isPrime(int n) const {
            return (*_nums)[n];
        }


    private:
        std::bitset<N>* _nums; 
        void _sieve(){
            (*_nums).set(0, false);
            (*_nums).set(1, false);
            (*_nums).set(2, true);
            for(int i=2; i*i < N; i++){
                if( (*_nums)[i] ){
                    // if it's prime, remove all its multiples
                    for( int j = i*i; j < N; j += i ){
                        (*_nums).set(j, false);
                    }
                }
            }
        }
};

Primes g_primes;

std::vector< std::pair<int, int> > getFactors(int n){
    std::vector< std::pair<int, int> > factors;
    int p = 2;
    do{
        int multiplicity = 0;
        while( n % p == 0 ){
            multiplicity++;
            n /= p;
        }
        if( multiplicity ){
            factors.push_back( std::make_pair(p, multiplicity) );
        }
        if( g_primes.isPrime(n) ){
            factors.push_back( std::make_pair(n, 1) );
           break;
        }
    } while( (n > 1) && (p = g_primes.nextPrime(p)) );
    return factors;
}



std::vector<int> getDivisors(int n) {
    const std::vector< std::pair<int, int> > factors( getFactors(n) );
    //std::cout << "Factors of " << n << ": "; print(factors);
    
    // there will be (v1 + 1) * (v2 + 1) * ... * (vn +1) divisors, with
    // vi the multiplicity of the ith factor
    // each of the divisors will be of the form p1^m1 * p2^m2 * ... * pn^mn
    // where 1 <= mi <= vi 
    
    // calculate number of divisors
    int num_divs = 1;
    for(int i=0; i < factors.size(); i++){
        num_divs *= (factors[i].second+1);
    }

    std::vector<int> divisors(num_divs);
    divisors[0] = 1;
    // if we are considering n, it's because it's got a single 
    // 2 among its factors
    divisors[1] = 2;
 
    int sz; 
    std::vector<int>::iterator ini(divisors.begin());
    std::vector<int>::iterator end(divisors.begin() + 2);
    for(int i=1; i < factors.size(); i++){ // skip the 2
        const int multiplicity = factors[i].second;
        const int factor =       factors[i].first;

        std::binder1st<std::multiplies<int> > 
            op(std::bind1st(std::multiplies<int>(), factor));

        ini = divisors.begin();
        sz = end-ini;
        for(int m=0; m < multiplicity; m++){
            std::transform( ini, end, end, op);
            ini = end;
            end += sz;
        }
    }
    //print(divisors);

    return divisors;
}


bool test(int n){
    --n;
    // test that its two least significant digits are 01
    if( !(n & 0x1) && ( (n>>1) & 0x1) ){
        // factor
        std::vector<int> divs( getDivisors(n) );
        std::vector<int>::iterator it;
        for(it = divs.begin(); it != divs.end(); it++){
            if( !g_primes.isPrime(*it + n/(*it)) ){
                return false;
            }
        }
        return true;
    }
    else{
        return false;
    }
}




int main(){
    long long sum = 1; // we include 1 because it's not going to
    // come out of the list of primes but 1+1 = 2, which is prime
    int p = 0;
    while( (p = g_primes.nextPrime(p) ) > 0 ){
        if( test(p) ){
            //std::cout << (p-1) << '\n';
            sum += (p-1);
        }
    }
    std::cout << sum << std::endl;
    return 0;
}

