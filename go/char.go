package main

import "fmt"
import "unicode/utf8"

func main() {
	fmt.Println(utf8.RuneLen('a'), utf8.RuneLen('汉'))
}
