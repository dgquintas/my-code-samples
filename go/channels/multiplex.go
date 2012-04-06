package main

import "fmt";

type request struct {
  a,b    int;
  replyc chan int;
}

type binOp func(a, b int) int

func run(op binOp, req *request) {
  reply := op(req.a, req.b);
  req.replyc <- reply;
}

func server(op binOp, service chan *request, quit chan bool) {
  for {
    select {
      case req := <-service:
        go run(op, req);
      case <-quit:
        fmt.Println("Server quitting...");
        return;
    }
  }
}

func startServer(op binOp) ( service chan *request, quit chan bool) {
  service = make(chan *request);
  quit = make(chan bool);
  go server(op, service, quit);
  return service, quit;
}

func main() {
  adder, quit := startServer(func(a,b int) int { return a + b });
  const N = 100;
  var reqs [N]request;
  for i := 0; i < N; i++ {
    req := &reqs[i];
    req.a = i;
    req.b = i + N;
    req.replyc = make(chan int);
    adder <- req;
  }

  for i := N-1; i >= 0; i-- {
    res := <-reqs[i].replyc;
    if res != N + 2*i {
      fmt.Println("fail at", i);
    }
    fmt.Println("res for", i, "=", res);
    
  }
  quit <- true;
  fmt.Println("done");

}

