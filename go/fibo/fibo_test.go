package fibo

import "testing"

var nextExpected = []int64 { 1,2,3,5,8,13,21,34,55,89 }

func TestNext(t *testing.T){
    var op Operator = func(a int64, b int64) int64 { return a+b }
    next_f := Next()
    for _, v := range nextExpected {
        _, fn := next_f(op)
        if v != fn {
            t.Errorf("Got %d. Expected %d", fn, v)
        }
    }
}




