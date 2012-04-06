package main

import "fmt"

func adder() (func(int) int) {
    var x int; //initialized to "zero" (0 here), as everything else in Go
    return func(delta int) int {
        x += delta;
        return x;
    }
}

func main() {
    f := adder(); //f is a func with an internal counter (x) which 
                  //is initially set to zero
    fmt.Println(f(1));
    fmt.Println(f(20));
    fmt.Println(f(300));
}

    
