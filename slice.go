package main
import "fmt"
func main() {
    var sl = []byte{1,2,3,4,5,6}
    var cl = []byte{1,2,3,4,5,6}
    fmt.Println(cap(sl), len(sl), sl)
    copy(sl[2:], cl[1:4])  // Shift existing data out of the way
    fmt.Println(cap(sl), len(sl), sl)
}
