package main

import "fmt"

func main() {
    //a map "m" indexed by strings and value type float64
    //it's analogous to C++'s *map<string,float64> (note the *)
    var m map[string]float64

    
    //as with slices, a map variable ("m" in this example)
    //refers to nothing (it's just a reference!). We must 
    //make it reference something "real" before it can be used

    //three ways
    // 1) literal
    m = map[string]float64{"1": 1, "pi":3.1416}

    // 2) creating
    m = make(map[string]float64) //make, not new

    // 3) assignment 
    var m1 map[string]float64
    m1 = m // m1 and m now refer to the same map


    //lets consider
    m = map[string]float64{"1": 1, "pi":3.1416}
    fmt.Println("Number of keys: ", len(m))

    //access
    one := m["1"]
    zero := m["not present"] // set zero to 0.0 (float64)

    //insert new elem
    m["2"] = 2
    m["2"] = 3 //update, same way

    //test if key is present
    value, present := m["foo"]  // type(present) == bool 
    fmt.Println("Value for non-present key: ", value)
    fmt.Println("present? :", present)


    //range 
    m = map[string]float64{"1": 1, "pi":3.1416}
    for key, value := range m {
        fmt.Printf("key %s, value %g\n", key, value)
    }
    // for just the key
    for key := range m {
        fmt.Printf("key %s\n", key)
    }

    //deletion
    //via multivariate assignment
    var keep bool
    var x string = "1"

    //if keep is false, the value associated with key x is removed
    //if true, the value for key x is updated with v
    keep = false
    v := 0.0 //why not
    m["1"] = v, keep

    fmt.Println("After deleting \"1\"...")
    for key, value := range m {
        fmt.Printf("key %s, value %g\n", key, value)
    }
  

}


