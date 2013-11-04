package main

import (
    "compress/lzw"
    "bytes"
    "fmt"
    "io/ioutil"
    "time"
)

func main() {
    buf := bytes.NewBuffer([]byte{})
    text, _ := ioutil.ReadFile("./lzwbench.go")
    cw := lzw.NewWriter(buf, lzw.LSB, 8)
    cw.Write(text)
    cw.Close()
    fmt.Println(len(text), len(buf.Bytes()))
    fmt.Println(time.Now())
    for i := 0; i < 1000000; i++ {
        buf = bytes.NewBuffer([]byte{})
        cw := lzw.NewWriter(buf, lzw.LSB, 8)
        cw.Write(text)
        cw.Close()
    }
    fmt.Println(time.Now())
}
