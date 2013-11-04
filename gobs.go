package main
import (
    "encoding/gob"
    "bytes"
    "fmt"
)

func main() {
    count := 16
    for i := 0; i < 16; i++ {
        bz, iz := gobsize(count)
        fmt.Println(
            count, bz, iz, float64(bz)/float64(count), float64(iz)/float64(count))
        count *= 2
    }
}

func gobsize(count int) (int, int) {
    var ch [1000000]byte
    for i := 0; i < count; i++ {
        ch[i] = 255
    }
    var in6 [1000000]uint64
    for i := 0; i < count; i++ {
        in6[i] = 18446744073709551616-1
    }
    x := ch[:count]
    z := in6[:count]

    buf1 := new(bytes.Buffer)
    genc := gob.NewEncoder(buf1)
    genc.Encode(x)

    buf2 := new(bytes.Buffer)
    genc = gob.NewEncoder(buf2)
    genc.Encode(z)
    return len(buf1.Bytes()), len(buf2.Bytes())
}
