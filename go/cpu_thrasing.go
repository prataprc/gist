package main

import "time"
import "runtime"
import "fmt"

func main() {
	runtime.GOMAXPROCS(runtime.NumCPU())
	fmt.Println("cpus: ", runtime.NumCPU())
	n := 10
	for i := 0; i < n; i++ {
		go percore()
	}
	time.Sleep(1 * time.Hour)
}

func percore() {
	i := 0
	for {
		i++
	}
}
