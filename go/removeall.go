package main

import "os"
import "fmt"

func main() {
	err := os.RemoveAll("/Users/prataprc/devgit/gist/go/removethis")
	fmt.Println(err)
}
