package main

import "fmt"

func main() {
  fmt.Printf("Hello world!!!1\n");
  fmt.Println(`this is a raw string\n\n\n`);
  fmt.Println(bla(-1));
  fmt.Println(bla(1));

}

func bla(i int) (res int) {
  if i < 0 {
    res = 1;
  }
  return res;
}

