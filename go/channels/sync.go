package main

import "fmt"
import "time"

func main() {
    c := make(chan int)
    go func() {
        time.Sleep(3*1e9) //time in nanos. 3 secs
        x := <-c
        fmt.Println("received at", time.LocalTime())
    }()

    fmt.Println("sending at", time.LocalTime())
    c <- 10
    fmt.Println("sent at", time.LocalTime())
}
       
