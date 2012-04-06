package linkedlist


type Element struct {
    next *Element
    Value interface{}
}

func (e *Element) Next() *Element { return e.next }


type SList struct {
    head *Element
    size int
}

/* FUNCTIONS */
//apparently this is just for convenience
func New() (l *SList) {
    l = new(SList) 
    l.Init()
    return 
}


/* METHODS */
func (l *SList) Size() int { return l.size }

func (l *SList) Init() *SList {
    l.head = nil
    l.size = 0
    return l
}

func (l *SList) Search(x interface{}) *Element {
    for e := l.head; e != nil; e = e.next {
        if v := e.Value; v == x {
            return e
        }
    }
    return nil
}

func (l *SList) Append(value interface{}) {
    //need to find last elem -> O(n)
    newElem := &Element{nil, value}
    if l.Size() == 0 {
        l.head = newElem
        l.size = 1
    } else {
        e := l.head
        for ;e.next != nil; e = e.next {}
        e.next = newElem
        l.size++
    }
}

func (l *SList) Prepend(value interface{}) {
    newElem := &Element{ l.head, value }
    l.head = newElem
    l.size++
}

func (l *SList) Remove(value interface{}) {
    if l.Size() == 0 {
        return
    }
    var prev *Element = nil

    for e := l.head; e != nil; prev, e = e, e.next{
        if e.Value == value {
            if prev == nil { // removing head of the list
                l.head = e.next
            } else{
                prev.next = e.next
            }
            l.size--
        }
    }
}





