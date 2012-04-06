package rot13

import ("os"; "io")

type Rotate13 struct {
  source  io.Reader;
}

func newRotate13(source io.Reader) *Rotate13 {
  return &Rotate13{source};
}
func rot13(b byte) byte {
  if b >= 'a' && b <= 'z' {
    b = 'a' + (( b - 'a' ) + 13) % 26
  }
  if b >= 'A' && b <= 'Z' {
    b = 'A' + (( b - 'A' ) + 13) % 26
  }
  return b
}

func (r13 *Rotate13) Read(b []byte) (ret int, err os.Error) {
  r, e := r13.source.Read(b);
  for i := 0; i < r; i++ {
    b[i] = rot13(b[i])
  }
  return r,e
}

func Rottify(r io.Reader) io.Reader {
  return newRotate13(r)
}

