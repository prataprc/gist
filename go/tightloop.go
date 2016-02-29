package main

import "time"
import "fmt"

func main() {
	count := 0
	begin := time.Now()
	for i := 0; i < 1000000; i++ {
		count += i
	}
	fmt.Printf("elapsed %v\n", time.Since(begin))
}
