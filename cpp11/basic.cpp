#include <thread>
#include <iostream>
#include <chrono>

using std::chrono::seconds;
using std::chrono::duration_cast;
using std::chrono::steady_clock;
using std::chrono::milliseconds;


void f() {
    std::this_thread::sleep_for(seconds(2));
    std::cout << "f()" << std::endl;
}

struct F {
    void operator()() {
        std::this_thread::sleep_for(seconds(4));
        std::cout << "F()()" << std::endl;
    }
};

int  main() {
    steady_clock::time_point start = steady_clock::now();
    std::thread t1{f};  // executes f() in a separate thread.
    std::thread t2{F()};  // executes F()() in a separate thread.

    t1.join();  // wait for t1.
    t2.join();  // wait for t2.
    steady_clock::time_point end = steady_clock::now();
    std::cout << "Running time: "
              // use duration_cast to properly convert between units.
              << duration_cast<milliseconds>(end - start).count()
              << "ms." << std::endl;
}
