package main

import "fmt"
import "./x"

type myLogger struct{}

func (l *myLogger) Print(s string) {
    fmt.Println(s)
}

func main() {
    checkinit.Myfunc(&myLogger{})
}
