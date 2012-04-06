package main

import "fmt";

func generate(ch chan int) {
  for i := 2; ; i++ {
    ch <- i 
  }
}

// filtrara todo lo que llega por "in", respecto
// a ser multiplo de "prime". ergo habra una gorutina
// por primo
func filter(in, out chan int, prime int){
  for {
    i := <-in; //will block 
    if i % prime != 0 {
      out <- i
    }
  }
}

func main() {
  in := make(chan int); // new int channel
  go generate(in); //lanzar proc para la func generate sobre el chan 
  for {
    prime := <-in;
    fmt.Println("Prime", prime);
    out := make(chan int);
    go filter(in, out, prime);
    in = out; // tras filtrar, el resultado es el nuevo input pa la iter i+1
  }
}


