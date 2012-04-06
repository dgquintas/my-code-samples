package main

import ("container/vector"; "fmt")

// vector.Vector is define as type Vector []interface{}

func main(){
    var v vector.Vector
    v.Push(1234.) //stored as interface value
    i := v.At(0)
    if i.(float64) != 1234. {}
    //if i.(int) != 1234 {} //runtime err, as the cast fails
    //if i.(MyFloat) != 1234. {} //err, MyFloat unknown

    v.Push(666)
    v.Push("foobar")
    for _, elem := range v{
        if i, ok := elem.(int); ok {
            fmt.Printf("int: %d\n", i)
        } else if f, ok := elem.(float64); ok {
            fmt.Printf("float64: %g\n", f)
        } else {
            fmt.Print("unknown type\n")
        }
    }

    for _, elem := range v{
        switch v := elem.(type){
            case int: 
                fmt.Printf("is int: %d\n", v)
            case float64:
                fmt.Printf("is float64: %g\n", v)
            default:
                fmt.Print("unknown type\n")
        }
    }

}

