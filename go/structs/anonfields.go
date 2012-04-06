package main

import "fmt"

func main(){
    type A struct {
        ax, ay int
    }
    type B struct {
        A //anonymous field
        bx, by float64
    }
    type C struct {
        x float64
        int
        string
    }

    b := B{A{1,2}, 3.0, 4.0}
    fmt.Println(b.ax, b.ay, b.bx, b.by)
    fmt.Println(b.A, b.bx, b.by)

    c := C{3.5, 7, "hello"}
    fmt.Println(c.x, c.int, c.string)
    fmt.Println(c)

}
