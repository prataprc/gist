package main

import "fmt"
import "math/big"

func main() {
    bi := new(big.Int)
    xi := new(big.Int)
    fmt.Sscan("0xFFFFFFFFFFFFFFFFFFFFFFFF", bi)
    xi.Div( bi, big.NewInt(100) )
    fmt.Printf("%v \n", bi)
    fmt.Printf("%v \n", xi)
}
