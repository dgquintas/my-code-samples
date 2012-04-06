package main

import "fmt"

func pump() chan int {
    ch := make(chan int)
    go func() {
        for i := 0; i < 100000; i++ {
            ch <- i
        }
        close(ch) //signal to receiver that we dont have more values
    }()
    return ch
}

func suck(ch chan int){
        for v := range ch { fmt.Println(v) } 
}

func main() {
    suck(pump())
}
