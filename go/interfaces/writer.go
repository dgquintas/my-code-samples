package main

import (
        "bufio"; "fmt"; "os"
       )

func main() {
    //unbuffered
    fmt.Fprintf(os.Stdout, "%s, ", "hello")
    
    //buffered: os.Stdout implements io.Writer
    buf := bufio.NewWriter(os.Stdout) //wraps the args with a buffered writer
    //buf also implements Writer, but in a buffered fashion now
    fmt.Fprintf(buf, "%s\n", "world!")
    buf.Flush() //it seems it doesnt flush upon destruction, so gotta enforce
}
