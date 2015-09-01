package main

import "math/big"
import "fmt"

func main() {
	bigx := big.NewInt(9223372036854775807)
	bigy := big.NewInt(10000)
	bigz := big.NewInt(0).Mul(bigx, bigy)

	buf := bigz.Bytes()
	fmt.Println(len(buf), buf)

	bign := big.NewInt(0).SetBytes(buf)
	fmt.Println(bign)
}
