package main

import "fmt";

/*
func generate(ch chan int) {
  for i := 2; ; i++ {
    ch <- i 
  }
}
*/

func generate() chan int {
  ch := make(chan int);
  go func() {
    for i := 2; ; i++ {
      ch <- i
    }
  }(); //y esto invoca la gorutina anonima
  return ch;
}

// filtrara todo lo que llega por "in", respecto
// a ser multiplo de "prime". ergo habra una gorutina
// por primo
func filter(in chan int, prime int) chan int {
  out := make(chan int);
  go func() {
    for {
      if i := <-in /*will block*/; i % prime != 0 {
        out <- i
      }
    }
  }();
  return out;
}

func sieve() chan int {
  out := make(chan int);
  go func() {
    in := generate(); //obtener el generador de input inicial
    for {
      prime := <-in;
      out <- prime;
      // tras filtrar, el resultado es el nuevo input pa la iter i+1
      in = filter(in, prime);
    }
  }();
  return out;
}

func main() {
   primesCh := sieve();
   for {
     fmt.Println("Prime", <-primesCh);
   }
}


