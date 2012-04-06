package main

import (
    "os"
    )

func sum(a []int) int {
  res := 0
  for i := 0; i < len(a); i++ {
    res += a[i]
  }
  return res
}


func main() {
  os.Stdout.Write(sum([3]int{1,2,3}[:]))
  os.Stdout.Write(sum([...]int{1,2,3}[:]))
  os.Stdout.Write(sum([]int{1,2,3}))
}
    




    
