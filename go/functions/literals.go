package main

import "fmt"

func f() {
    for i := 0; i < 10; i++ {
        g := func(i int) { fmt.Printf("%d ", i) }
        g(i)
    }
}

func main() {
    f()
    fmt.Println()
}
