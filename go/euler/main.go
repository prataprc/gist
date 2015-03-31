package main

import "flag"
import "log"
import "time"
import "fmt"

var options struct {
}

func argParse() []string {
    flag.Parse()
    args := flag.Args()
    if len(args) <=0 {
        log.Fatalf("enter problem number (in words)")
    }
    return args
}

var solutions = map[string]func() {
    "p1": p1,
    "p2": p2,
    "p3": p3,
}

func main() {
    args := argParse()
    pnum := args[0]
    defer timeTrack(time.Now(), pnum)
    fn, ok := solutions[pnum]
    if !ok {
        log.Fatalf("invalid problem number\n")
    }
    fn()
}

func timeTrack(start time.Time, name string) {
    elapsed := time.Since(start)
    fmt.Printf("time take to solve problem %q is: %v\n", name, elapsed)
}
