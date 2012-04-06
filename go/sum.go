package main

import "fmt"

func sum(a []int, out chan int) {
	s := 0
	for i := 0; i < len(a); i++ {
		s += a[i]
	}
	out <- s
}

func main() {
	var arr []int = []int{1, 2, 3, 4, 5}
    ch := make(chan int)
    go sum(arr[:], ch)
	res := <-ch
	fmt.Println(res)
}
