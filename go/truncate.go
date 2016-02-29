package main

import "os"
import "fmt"

func main() {
	f, err := os.Create("/tmp/truncatefile.empty")
	if err != nil {
		panic(err)
	}
	fmt.Println(f.Truncate(32 * 1024 * 1024 * 1024))
}
