package main

import (
        "fmt"
        "os"
        )

func main() {
    fmt.Println("# of args: ", len(os.Args))
    fmt.Println("Args:")
    for i, v := range os.Args {
        fmt.Printf("%d -> %s\n", i, v);
    }

    os.Exit(0)
}
