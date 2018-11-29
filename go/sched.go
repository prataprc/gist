package main

import "fmt"
import "time"
import "runtime"

func main() {
	runtime.GOMAXPROCS(1)
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
