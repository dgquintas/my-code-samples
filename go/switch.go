package main

import (
    "flag";
    "fmt";
    "strconv";
    )

func main() {
  flag.Parse();
  x,_ := strconv.Atoi(flag.Arg(0));

  fmt.Println(x);
  switch x {
    default:
      fmt.Println("blabla")
    case 1:
      fmt.Println("foo")
    case 2:
      fmt.Println("bar")
    }
}

