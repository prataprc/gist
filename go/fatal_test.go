package fataltest

import "testing"
import "fmt"

func TestFatal(t *testing.T) {
    t.Fatal("fail %v %v\n", 10, 20)
    go printA()
    go printB()
}

func printA() {
    fmt.Println("goroutine a")
}

func printB() {
    fmt.Println("goroutine b")
}
