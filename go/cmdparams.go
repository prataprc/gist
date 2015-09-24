package main

import "flag"
import "fmt"

var options struct {
	input string
}

func argParse() {
	flag.StringVar(&options.input, "input", "",
		"validate the supplite json string")
	flag.Parse()
}

func main() {
	argParse()
	fmt.Printf("%v\n", []byte(options.input))
}
