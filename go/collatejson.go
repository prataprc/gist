package main

import (
    "encoding/json"
    "fmt"
    "github.com/couchbase/indexing/secondary/collatejson"
)

func main() {
    //data := []byte("[\"user_profile\", \"Cherise_76743910\"]")
    x := []string{"hello"}
    data, _ := json.Marshal(x)
    fmt.Println("json ", string(data))
    //data := []byte("[\"hello\"]")

    jsoncodec := collatejson.NewCodec(128)
    bufcode := make([]byte, 0, 1024)
    code1, e1 := jsoncodec.Encode(data, bufcode)

    code2, e2 := jsoncodec.Decode(code1, bufcode)

    fmt.Println("encoded", e1, string(code1))
    fmt.Println("decoded", e2, string(code2))
}
