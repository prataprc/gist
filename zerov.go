package main
import "fmt"

func main() {
    var ( 
        i int
        c int8
        s string
        f float32
        d float64
        b bool
        ar []int
        m map[string]int
        p *int
        fn func(int) int
        inf interface{}
        ch chan int
    )

    fmt.Printf("zero values for data types \n\n")
    fmt.Printf("int       %#v\n", i)
    fmt.Printf("int8      %#v\n", c)
    fmt.Printf("string    %#v\n", s)
    fmt.Printf("float32   %#v\n", f)
    fmt.Printf("float64   %#v\n", d)
    fmt.Printf("bool      %#v\n", b)
    fmt.Printf("array     %#v\n", ar)
    fmt.Printf("map       %#v\n", m)
    fmt.Printf("pointer   %#v\n", p)
    fmt.Printf("function  %#v\n", fn)
    fmt.Printf("interface %#v\n", inf)
    fmt.Printf("channel   %#v\n", ch)
}
