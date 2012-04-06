package linkedlist

import "testing"
import "rand"



func TestAppend(t *testing.T){
    l := New()
    l.Append(1)
    if l.Size() != 1 {
        t.Fail()
    }
    l.Append(2)
    if l.Size() != 2 {
        t.Fail()
    }
}

func BenchmarkAppend(b *testing.B) {
    l := New()
    for i := 0; i < b.N; i++ {
        l.Append(i)
    }
}
func BenchmarkPrepend(b *testing.B) {
    l := New()
    for i := 0; i < b.N; i++ {
        l.Prepend(i)
    }
}

func BenchmarkSearch(b *testing.B) {
    b.StopTimer()
    l := New()
    for i := 0; i < 10000; i++ {
        l.Prepend( rand.Intn(10000) )
    }
    b.StartTimer()

    for i := 0; i < b.N; i++ {
        x := rand.Intn(10000)
        l.Search(x)
    }


}

func TestSearch(t *testing.T){
    l := New()
    l.Append(1)
    if l.Search(1) == nil {
        t.Fail()
    } 
    if l.Search(2) != nil {
        t.Fail()
    }
}
func TestRemove(t *testing.T){
    l := New()
    l.Append(1)
    l.Append(2)
    l.Append(3)
    if l.Search(1) == nil {
        t.Fail()
    }
    l.Remove(1)
    if l.Search(1) != nil {
        t.Fail()
    }
    if l.Search(2) == nil {
        t.Fail()
    }
    l.Remove(3)
    if l.Size() != 1 { t.Fail() }
    l.Remove(2)
    if l.Size() != 0 { t.Fail() }
    l.Remove(123)
    if l.Size() != 0 { t.Fail() }
}
