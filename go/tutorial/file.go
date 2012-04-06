package file

import (
    "os"
    "syscall"
    )

type File struct { //capitalized name means it's exported (visible)
  fd int 
  name string
}

func newFile(fd int, name string) *File { //internal
  if fd < 0 {
    return nil
  }
  return &File{fd, name}
  // equiv to:
  // n := new(File), n being *File
  // n.fd = fd
  // n.name = name
  // return n
}

var (
    Stdin = newFile(0, "/dev/stdin")
    Stdout = newFile(1, "/dev/stdout")
    Stderr = newFile(2, "/dev/stderr")
    )

func Open(name string, mode int, perm uint32) (file *File, err os.Error){
  r, e := syscall.Open(name, mode, perm)
  if e != 0 {
    err = os.Errno(e)
  }
  return newFile(r, name), err
}

func (file *File) Close() os.Error {
  if file == nil {
    return os.EINVAL
  }
  e := syscall.Close(file.fd)
  file.fd = -1 // so that it can't be closed again
  if e != 0 {
    return os.Errno(e)
  }
  return nil
}

func (file *File) Read(b []byte) (ret int, err os.Error){
  if file == nil {
    return -1, os.EINVAL
  }
  r, e := syscall.Read(file.fd, b)
  if e != 0 {
    err = os.Errno(e)
  }
  return r, err
}

func (file *File) Write(b []byte) (ret int, err os.Error) {
  if file == nil {
    return -1, os.EINVAL
  }
  r, e := syscall.Write(file.fd, b)
  if e != 0 {
    err = os.Errno(e)
  }
  return r, err
}
  
func (file *File) String() string {
  return file.name
}
