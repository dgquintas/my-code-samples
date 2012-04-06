package main

import "fmt"

type Point struct {
    x,y float64
}


func main(){
    var p Point
    p.x = 7
    p.y = 23.4

    var pp *Point = new(Point)
    //the previous statement just allocates
    //space for a Point struct, with "pp" 
    //pointing to this allocated space

    *pp = p
    pp.x = 3.1416 // == (*pp).x

    fmt.Println("p = ", p)
    fmt.Println("pp = ", pp)
    fmt.Println("*pp = ", *pp)
    
}

