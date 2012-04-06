package main

import (
        "fmt"
        "fibo"
       )

func main(){
    next_func := fibo.Next()
    var op fibo.Operator = func(a int64, b int64) int64 { return a+b }
    for i := 0; i < 10; i++ {
        fmt.Println(next_func(op))
    }
}

