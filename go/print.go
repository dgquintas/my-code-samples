package main

import "fmt"

type testType struct{
    a int
    b string
}

func (t *testType) String() string {
    return fmt.Sprint(t.a) + " " + t.b
}

func main() {
    t := &testType{77, "Sunset Strip"}
    fmt.Println(t)
}
