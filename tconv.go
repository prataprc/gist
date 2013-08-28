package main
import "fmt"

type mystruct struct {
    t int
}

func main() {
    var (
        b bool              // Boolean
        c int8
        hw int16
        w int32
        lw int64
        f float32
        d float64
        s string            // String

        p *int64            // Pointer
        ar [10]int          // Array
        m map[string]int    // Map
        fn func(int) int    // Function
        inf interface{}     // Interface
        arinf [10]interface{}   // array of Interface
        ch chan int         // Channel
    )
    // You can assign any type to empty interface type. That is the key !!
    inf = b; inf = ar; inf = ar[1:]; inf = m; inf = fn; inf = ch;

    // arinf = ar // this is illegal

    c = int8(hw); c = int8(w); c = int8(lw); c = int8(f); c = int8(d)
    hw = int16(c); hw = int16(w); hw = int16(lw); hw = int16(f); hw = int16(d)
    w = int32(c); w = int32(hw); w = int32(lw); w = int32(f); w = int32(d)
    lw = int64(c); lw = int64(hw); lw = int64(w); lw = int64(f); lw = int64(d)
    f = float32(c); f = float32(hw); f = float32(w); f = float32(lw); f = float32(d)
    d = float64(c); d = float64(hw); d = float64(w); d = float64(lw); d = float64(f)
    s = string(c); s = string(hw); s = string(w); s = string(lw);

    fmt.Println(b)
    fmt.Println(c, hw, w, lw)
    fmt.Println(f, d)
    fmt.Println(s, ar, m, p, fn, inf, arinf, ch)
    var y byte = 10
    x := uint64(y)
    fmt.Println(x)
}
