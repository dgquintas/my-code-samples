package main

import (
    "./file"
    "fmt"
    "os"
    )

func main() {
  hello := []byte("hello, world\n")
  file.Stdout.Write(hello)
  file, err := file.Open("/does/not/exist", 0,0)
  if file == nil {
    fmt.Printf("cant open file; err=%s\n", err.String())
    os.Exit(1)
  }
}


         
