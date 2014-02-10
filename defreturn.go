package main

import (
	"fmt"
)

type chainCost struct {
	rawCost       int
	tagViolations int
}

func main() {
	chainCost{10, 20}
}
