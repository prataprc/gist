package main

import (
    "fmt"
    "github.com/couchbase/indexing/secondary/collatejson"
)

func main() {
    var err1, err2 error
    jsoncodec := collatejson.NewCodec(16)
    data := []byte("{ \"state\": \"Wisconsin\n\" }")
    buf1 := make([]byte, 0, 1024)
    if buf1, err1 = jsoncodec.Encode(data, buf1); err1 != nil {
        panic(err1)
    }
    buf2 := make([]byte, 0, 1024)
    if buf2, err2 = jsoncodec.Decode(buf1, buf2); err2 != nil {
        panic(err2)
    }
    fmt.Println(string(buf2))
}
