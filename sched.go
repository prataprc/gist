package main

import "fmt"
import "time"

func main() {
    go func() {
        for true {
            // noop
        }
    }()

    for true {
        fmt.Printf("Hello world!\n")
        time.Sleep(1 * time.Millisecond)
    }
}
