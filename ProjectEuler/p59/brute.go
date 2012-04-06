package main

import (
        "fmt"
        "os"
        "io/ioutil"
        "strings"
        "strconv"
       )

type key_t [3]byte;

var words [100]string = [100]string{
    "the", "of", "and", "a", "to", "in", "is", "you", "that", "it", "he",
    "was", "for", "on", "are", "as",  "with",  "his", "they", "I", "at",
    "be", "this", "have", "from", "or", "one", "had", "by", "word",
    "but", "not", "what", "all", "were", "we", "when", "your", "can",
    "said", "there", "use", "an", "each", "which", "she", "do", "how",
    "their", "if", "will", "up", "other", "about", "out", "many",
    "then",  "them",  "these", "so", "some",  "her", "would", "make",
    "like", "him", "into", "time", "has",  "look", "two", "more",
    "write",  "go",  "see",  "number",  "no",  "way", "could", "people",
    "my", "than", "first", "water", "been", "call", "who", "oil", "its",
    "now", "find", "long", "down", "day", "did", "get", "come", "made",
    "may", "part"}

func keyGenerator() chan key_t {
    //generate from 99 (a) to 122 (z)
    ch := make(chan key_t)
    go func() {
        var i,j,k byte;
        for i = 99; i < 122+1; i++ {
            for j = 99; j < 122+1; j++ {
                for k = 99; k < 122+1; k++ {
                    ch <- key_t {i,j,k}
                }
            }
        }
        close(ch)
    }()
    return ch
}

func decript(txtints []byte, key key_t) []byte {
    out := make([]byte, len(txtints))
    for i,c := range txtints {
        out[i] = c ^ (key[i%3])
    }
    return out
}

func sum(stream *strings.Reader) (s int) {
    v, err := stream.ReadByte()
    for ; v != 0 && err != os.EOF ; v, err = stream.ReadByte(){
        s += int(v)
    }

    return;
}


func main() {
    //read ciphertext from file
    f, _ := os.Open("cipher1.txt")
    bytes, _ := ioutil.ReadAll(f)
    txt := strings.TrimSpace(string(bytes))
    intStrs := strings.Split(txt, ",", -1)
    ints := make([]byte, len(intStrs))
    for i, is := range intStrs {
        ii, _ := strconv.Atoi(is)
        ints[i] = byte(ii)
    }

    keys := keyGenerator() 
    for key := range keys {
        dec := decript(ints, key)
        decStr := string(dec)
        if strings.Contains(decStr, " the "){
            fmt.Println(decStr)
            fmt.Println(string(key[:]))
            fmt.Println( sum( strings.NewReader(decStr)) )

        }
    }
    
}



