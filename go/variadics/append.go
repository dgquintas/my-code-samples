package main

import "fmt"


func main() {
    //append is builtin: append(s []T, x ...T) []T

    slice := []int{1,2,3}
    slice = append(slice, 4,5,6)
    fmt.Println(slice)

    slice = []int{1,2,3}
    slice2 := []int{4,5,6}
    slice = append(slice, slice2...)
    fmt.Println(slice)
}

