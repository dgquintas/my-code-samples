package main

import (
	"http"
	"log"
    "io"
    "os"
    "fmt"
//    "./rot13"
)

type TextMangler func(io.Reader) io.Reader 

func newMangledFileServer(mangler TextMangler) http.HandlerFunc {
    mfs := func(w http.ResponseWriter, r *http.Request) {
        // open file from path in request
        path := r.URL.Path
        log.Println("Path: ", path)
        f, err := os.Open(path) //File types are readers 
        if f == nil {
            s := fmt.Sprintf("Error opening path %s: %s\n", path, err) 
            log.Print(s)
            io.WriteString(w, s)
            return
        }
        defer f.Close()
        mangledreader := mangler(f)
        const NBUF = 512;
        var buf [NBUF]byte;
        for {
            switch nr, err := mangledreader.Read(buf[:]); {
                case nr < 0:
                    log.Printf("error reading from path %s: %s\n", path, err)
                case nr > 0:
                        log.Printf("Read %d bytes: %s", nr, buf)
                        //write into the ResponseWriter
                        if nw, werr := w.Write(buf[:nr]); nw != nr {
                            log.Printf("error writing response: %s\n", werr)
                        }
                case nr == 0:
                        return
            }
        }
    }
    return mfs
}

func main() {
    var h http.HandlerFunc = newMangledFileServer(rot13.Rottify)
    //var h http.HandlerFunc = newMangledFileServer(func(r io.Reader) io.Reader { return r })
	http.HandleFunc("/", h)
	err := http.ListenAndServe(":12345", nil)
	if err != nil {
		log.Fatal("ListenAndServe: ", err.String())
	}
}
