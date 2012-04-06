#include <iostream>
#include <cmath>

/* Before even writing any code, we can calculate the first Fibonaccci
 * number larger than the given 227000:
 *
 * By Binet's formula, the nth Fibonacci number is (phi^n - psi^n)/sqrt(5),
 * where phi is the golden ratio and psi = 1-phi (the two solutions of the
 * quadratic equation x^2 = x + 1. 
 * By that, we know that the nth Fibonacci number is the integer closest to
 * phi^n / sqrt(5), because the psi^n/sqrt(5) becomes insignificant really 
 * fast, immediately in fact when it comes to integer "rounding". 
 *
 * Let k = 227000. We want the "n" from the following expression:
 *
 * k        <   phi^n / sqrt(5)
 * lg(k)    <   n*lg(phi) - 1/2 lg(5)
 *
 * lg(k) + 1/2 lg(5)          < n*lg(phi)
 * [lg(k) + 1/2 lg(5)]/ lg(phi) < n
 *
 * The left side are all constants. It's approximately 27.3. 
 * Meaning, we should start working from the 28th Fibonacci number. 
 *
 * HOWEVER, as we are looking for a *prime* Fibonacci, we also know
 * that its "n" must be a prime (because F_n divides F_kn for k >= 1).
 * We will hence test from the 29th Fibonacci onwards. 
 */

/* By considering all the primes until around 1000, we can check the primality
 * of number up to 1e6. To calculate a small list like this we can use Eratosthenes'
 * Sieve*/
const int PRIMES[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59,
    61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137,
    139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223,
    227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293, 307,
    311, 313, 317, 331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389, 397,
    401, 409, 419, 421, 431, 433, 439, 443, 449, 457, 461, 463, 467, 479, 487,
    491, 499, 503, 509, 521, 523, 541, 547, 557, 563, 569, 571, 577, 587, 593,
    599, 601, 607, 613, 617, 619, 631, 641, 643, 647, 653, 659, 661, 673, 677,
    683, 691, 701, 709, 719, 727, 733, 739, 743, 751, 757, 761, 769, 773, 787,
    797, 809, 811, 821, 823, 827, 829, 839, 853, 857, 859, 863, 877, 881, 883,
    887, 907, 911, 919, 929, 937, 941, 947, 953, 967, 971, 977, 983, 991, 997,
    1009, -1 /*sentinel*/};

int nth_fib(int n){
    static const double PHI = (1+sqrt(5))/2;
    static const double PSI = 1-PHI;
    static const double INV_SQRT5 = 1/sqrt(5);

    return (pow(PHI, n) - pow(PSI, n))*INV_SQRT5;
}

bool is_prime(int n){
    const float limit = sqrt(n);
    for(int i=0; 0 < PRIMES[i] && PRIMES[i] <= limit; i++){
        if( n % PRIMES[i] == 0 ){
            return false;
        }
    }
    return true;
}

int sum_prime_factors(int n){
    int sum = 0;

    for(int i=0; n > 1; i++ ){
        const int p_i = PRIMES[i];
        if( n % p_i == 0 ){
            sum += p_i;
            // extract all the powers of that prime factor
            while( n % p_i == 0 ){
                n /= p_i;
            }
        }
    }
    return sum;
}

int main(){
    int prime_idx = 9;  //29
    int fn = nth_fib(PRIMES[prime_idx++]);

    while( !is_prime(fn) ){
        // it's advantageous to use Binet's formula instead
        // of the usual recurrence to calculate the next fn, 
        // as we are only insterested in the prime "n"s
        fn = nth_fib(PRIMES[prime_idx++]);
    }

    std::cout << fn << " is a Fibonacci prime\n";
    std::cout << "Sum of X's prime factors: " << sum_prime_factors(fn+1) << std::endl;
    return 0;
}

