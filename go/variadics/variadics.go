package main

import "fmt"

func Min(args ...int) int {
    min  := int(^uint(0)>>1) //largest int. ^ is XOR
    for _,x := range args {
        if min > x { min = x }
    }
    return min
}

func main(){
    fmt.Println( Min(1,2,3), Min(-27), Min(), Min(7,8,2))
    
    //turning slices into variadics, like in python
    slice := []int{1,-2,3}
    fmt.Println(Min(slice...))
    // Min(slice) doesn't work
}

