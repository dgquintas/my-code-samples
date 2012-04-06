package main

import "fmt"

func f(a [3]int){ fmt.Println(a) }
func fp(a *[3]int){ fmt.Println(a) }

func main() {
    var ar [3]int
    f(ar)
    fp(&ar)

    fmt.Println( [3]int{1,2,3} );
    fmt.Printf("%p\n", &[3]int{1,2,3} ); //a pointer to newly created instance

    fmt.Println( [10]int{1,2,3} ); //only first 3 elements initialized

    fmt.Println( [...]int{1,2,3} ); //compiler does the counting

    fmt.Println( [10]int{2:12, 3:34, 5:56, 7:78} ); //pos. 2 == 12, pos. 3 == 34 ....
}
