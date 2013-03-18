package main

import (
	"io"
	"os"
	"strings"
	"fmt"
)

type rot13Reader struct {
	r io.Reader
}

// al crear el metodo Read sobre rot13Reader, estamos haciendo que este
// tipo implemente el interfaz io.Reader
func (r13 rot13Reader) Read(p []byte) (n int, err error) {
	buf := make([]byte, len(p))
	for {
		n, err = r13.r.Read(buf)
		if n > 0 {
			for i := 0; i < n; i++ {
                v := buf[i]
				if v >= 'a' && v <= 'z'  {
					p[i] = 'a' + (v - 'a' + 13) % 26
				} else if v >= 'A' && v <= 'Z'  {
					p[i] = 'A' + (v - 'A' + 13) % 26
				}
			}	
		}
        if err != nil && err != io.EOF  {
            fmt.Fprintf(os.Stderr, "Error: %v", err)
        }
        return 
	}
    return
}


func main() {
	s := strings.NewReader(
		"Lbh penpxrq gur pbqr!")
	r := rot13Reader{s}
    io.Copy(os.Stdout, &r)
}
