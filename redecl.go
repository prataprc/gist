package main
import "fmt"

func main() {
    v := 10
    //v := 20               // Illegal - no new variable on left side of :=
    x, v := false, 30
    y, v := true, 10.3      // 10.3 implicitly converted to 10
    y, v := true, "hello"   // Illegal - re-declaration must preserve the type
    fmt.Printf("%v %v %v", x, y, v);
}
