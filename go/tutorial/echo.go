package main

import (
    "os"
    "flag"
    )
var omitNewline = flag.Bool("n", false, "don't print final newline")

const (
    Space = " "
    Newline = "\n"
    )

func main() {
  flag.Parse()
  //var s string = ""
  s := ""
  for i := 0; i < flag.NArg(); i++ {
    if i > 0 {
      s += Space // previously defined const
    }
    s += flag.Arg(i)
  }
  if !*omitNewline {
    s += Newline// previously defined const
  }
  os.Stdout.WriteString(s)
}
    




    
