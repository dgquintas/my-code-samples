package main

import "fmt"
import "math"

type Point struct {x,y float64}


func (p* Point) Abs() float64 {
    p.x = 4
    return math.Sqrt(p.x*p.x + p.y*p.y)
}
// same, but "p" is passed by value, more expensive
func (p Point) AbsByValue() float64 {
    p.x = 4
    return math.Sqrt(p.x*p.x + p.y*p.y)
}

//////////////////////////

type IntVector []int
func (v IntVector) Sum() (s int){
    for _, x := range v {
        s += x
    }
    return
}


func main() {
    p := &Point{ 3, 4 } 
    
    fmt.Println(p.AbsByValue())
    fmt.Println(p.x) // will still be 3

    fmt.Println(p.Abs())
    fmt.Println(p.x) // will have changed to 4

    v := IntVector{1,2,3}
    fmt.Printf("Sum of %v = %d\n", v, v.Sum())
}
