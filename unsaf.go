package main

import "fmt"
import "unsafe"

type bkey struct {
    a int
    b int
}

func main() {
    fmt.Println( "Sizeof" )
    fmt.Println( "------" )
    fmt.Println(  "",
        "10           ", unsafe.Sizeof(10),               "\n",
        "10 int8      ", unsafe.Sizeof(int8(10)),         "\n",
        "10 int16     ", unsafe.Sizeof(int16(10)),        "\n",
        "10 int32     ", unsafe.Sizeof(int32(10)),        "\n",
        "10 int64     ", unsafe.Sizeof(int64(10)),        "\n",
        "10 int       ", unsafe.Sizeof(int(10)),          "\n",
        "10.0         ", unsafe.Sizeof(10.0),             "\n",
        "10.0 float32 ", unsafe.Sizeof(float32(10.0)),    "\n",
        "10.0 float64 ", unsafe.Sizeof(float64(10.0)),    "\n",
    )
    fmt.Println( "Alignof" )
    fmt.Println( "------" )
    fmt.Println(  "",
        "10           ", unsafe.Alignof(10),              "\n",
        "10 int8      ", unsafe.Alignof(int8(10)),        "\n",
        "10 int16     ", unsafe.Alignof(int16(10)),       "\n",
        "10 int32     ", unsafe.Alignof(int32(10)),       "\n",
        "10 int64     ", unsafe.Alignof(int64(10)),       "\n",
        "10 int       ", unsafe.Alignof(int(10)),         "\n",
        "10.0         ", unsafe.Alignof(10.0),            "\n",
        "10.0 float32 ", unsafe.Alignof(float32(10.0)),   "\n",
        "10.0 float64 ", unsafe.Alignof(float64(10.0)),   "\n",
    )
}
