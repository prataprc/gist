package main
import (
    "fmt"; "unsafe"
)

func main() {
    var sl = []byte{1,2,3,4,5,6}
    var cl = []byte{1,2,3,4,5,6}

    fmt.Println( unsafe.Pointer(&sl), len(sl), cap(sl) );
    sl_ := sl[2:4]
    fmt.Println( unsafe.Pointer(&sl_), len(sl_), cap(sl_) );

    copy(sl[2:], cl[1:4])  // Shift existing data out of the way
    fmt.Println(cap(sl), len(sl), sl)
}
