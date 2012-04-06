package main

import "fmt"
import "math"

type Point struct {x,y float64}
func (p* Point) Abs() float64 {
    return math.Sqrt(p.x*p.x + p.y*p.y)
}

//this method will override Point's Abs
func (n *NamedPoint) Abs() float64 {
    return n.Point.Abs() * 100.
}

type NamedPoint struct {
    Point //anon field
    name string
}


func main(){
    n := &NamedPoint{ Point{3,4}, "FooBar"}
    fmt.Println( n.Abs() ) //as "inhereted" from Point (or not, if 
        //the Abs() method has been also defined for the parent
        //type NamedPoint
}
