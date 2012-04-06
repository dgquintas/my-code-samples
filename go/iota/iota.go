package main

import "fmt"

func main(){

    const (
            // iotas are incrased per (implicit) semicolon
            loc0, bit0 uint32 = iota, 1 << iota ;
            loc1, bit1
            loc2, bit2
          )

    fmt.Println(loc0, bit0)
    fmt.Println(loc1, bit1)
    fmt.Println(loc2, bit2)
}

