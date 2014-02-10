package main

import "fmt"

func main() {
	var temp struct {
		Type string `json:"type"`
	}
	fmt.Println(temp)
}
