package main
import (
    "fmt"; "unsafe"
)

type String struct {
    pointer uint64
    length uint64
}

func main() {
    s := "hello world"  // same string
    x := "hello world"  // stored in different locations
    y := "long string ......................................................."
    fmt.Printf( "s `%v` is at %v\n", s, &s );
    fmt.Printf( "x `%v` is at %v\n", x, &x );
    fmt.Printf( "Size of y %v\n", unsafe.Sizeof(y) );

    // Internals of string
    english := "Good morning"
    chinese := "早安"
    spanish := "Español"
    ep := (*String)(unsafe.Pointer(&english))
    cp := (*String)(unsafe.Pointer(&chinese))
    sp := (*String)(unsafe.Pointer(&spanish))
    fmt.Println(ep)
    fmt.Println(cp)
    fmt.Println(sp)
    fmt.Println(spanish[4:5], spanish[4:6])

    passby(spanish)

    fmt.Printf("%020v\n", 100)
}

func passby(str string) {
    sp := (*String)(unsafe.Pointer(&str))
    fmt.Println(&str, sp)
}
