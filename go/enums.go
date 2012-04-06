package main

import "fmt";

func main() {
  const (
      red = iota;
      green;
      blue;
      );
  fmt.Println( red );
  fmt.Println( green );
  fmt.Println( blue );
}
