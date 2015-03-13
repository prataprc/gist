package main

import (
	"bufio"
	"fmt"
	"os"
)

func main() {
	fmt.Print("hello word")
	fmt.Print("\r")
	r := bufio.NewReader(os.Stdin)
	fmt.Print(r.ReadRune())
}
