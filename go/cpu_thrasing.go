package main

import "time"
import "runtime"
import "fmt"

func main() {
	n := runtime.NumCPU()
	runtime.GOMAXPROCS(n)
	fmt.Println("cpus: ", n)
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
