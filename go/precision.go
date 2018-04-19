package main

import "fmt"
import "math/big"

func main() {
	u := uint64(18446744073709551615)
	bf := big.NewFloat(0)
	bf.SetUint64(u)
	fmt.Println(bf.Text('e', -1))

	bf.SetPrec(64)
	bf.SetUint64(u)
	fmt.Println(bf.Text('e', -1))

	bf.SetUint64(199)
	fmt.Println(bf.Text('e', -1))

	bf.SetPrec(100)
	bf.Parse("10001234.123131313121312", 10)
	fmt.Println(bf.Text('e', -1), bf.Acc())
}
