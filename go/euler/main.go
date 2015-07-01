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
	if len(args) <= 0 {
		log.Fatalf("enter problem number (in words)")
	}
	return args
}

var solutions = map[string]func(){
	"p1": p1,
	"p2": p2,
	"p3": p3,
}

var prob_list = []string{
	"p1", "p2", "p3",
}

func main() {
	args := argParse()
	if args[0] == "all" {
		for _, pno := range prob_list {
			solve(pno, solutions[pno])
		}
	} else if fn, ok := solutions[args[0]]; ok {
		solve(args[0], fn)
	} else {
		log.Fatalf("invalid problem number\n")
	}
}

func solve(name string, fn func()) {
	start := time.Now()
	defer func() {
		elapsed := time.Since(start)
		fmt.Printf("%q time taken: %v\n", name, elapsed)
		fmt.Println("")
	}()
	fn()
}
