package main

import "fmt"

func main() {
  
  type T struct { a, b int };
  var t *T = new(T);

  fmt.Println(t);

  m := map[string]int{"one":1, "two":2};
  fmt.Println(m);

  for k, v := range m {
    fmt.Printf("%v -> %v\n", k, v);
  }

}
