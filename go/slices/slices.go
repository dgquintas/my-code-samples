package main

import "fmt"

func main(){
    var slice = []int{1,2,3,4,5} //creates an array of length 5 and then a slice to it
    //or, equivalently
    var s100 = make([]int, 100) //slice: 100 ints

    var ar = [10]int{0,1,2,3,4,5,6,7,8,9}
    var a = ar[5:7] // {5,6}
    
    fmt.Println("len a[5:7]= ", len(a))
    fmt.Println("cap a[5:7]= ", cap(a))

    a = a[0:4]
    fmt.Println("len a[0:4]= ", len(a))
    fmt.Println("cap a[0:4]= ", cap(a))


    //resizing slices
    var sl = make([]int, 0, 10) // len 0, cap 10
    for i := 0; i < 10; i++ {
        sl=appendToSlice(i, sl)
    }

    fmt.Println(sl);


}


func appendToSlice(i int, sl []int) []int {
    if len(sl) == cap(sl) { 
        fmt.Println("wooops, error apending")
    } else{
        n := len(sl)
        sl = sl[0:n+1] //extend by 1
        sl[n] = i
    }
    return sl
}

