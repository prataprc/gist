package main

import (
	"flag"
	"fmt"
)

func main() {
	var i int

	f := flag.NewFlagSet("flag", flag.ExitOnError)
	f.IntVar(&i, "int", 0, "int flag with value")

	visitor := func(a *flag.Flag) {
		fmt.Println(">", a.Name, "value=", a.Value)
	}

	fmt.Println("First visit")
	f.Visit(visitor) // no value assigned

	f.Parse([]string{"-int", "108"}) // visit flag set earlier and assign value

	fmt.Println("Second visit")
	f.Visit(visitor)

}
