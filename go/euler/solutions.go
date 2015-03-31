package main

import "fmt"
import "math"

func p1() {
	sum := 0
	for i := 0; i < 1000; i++ {
		if (i%3) == 0 || (i%5) == 0 {
			sum += i
		}
	}
	fmt.Printf("the sum of all the multiples of 3 or 5 below 1000: %v\n", sum)
}

func p2() {
	till := int64(4 * 1000 * 1000)
	a, b := int64(1), int64(2)
	sum := a
	for b < till {
		sum += b
		a, b = b, a+b
	}
	fmt.Printf(
		"sum of even-valued terms in the fibonacci sequence 1,2...\n"+
			"   whose values do not exceed four million: %v\n", sum)
}

func p3() {
	primes := []int64{2, 3, 5, 7, 11}
	factors := []int64{}
	firstFactor := func(num, max int64) (p, quot int64) {
		for _, p := range primes {
			if p > max {
				return num, 1
			} else if num%p == 0 {
				return p, num / p
			}
		}
		primes = append(primes, num)
		return num, 1
	}
	num, max := int64(600851475143), int64(math.Sqrt(float64(600851475143)))+1
	p, quot := firstFactor(num, max)
	for quot != 1 {
		factors = append(factors, p)
		num, max := int64(quot), int64(math.Sqrt(float64(quot)))+1
		p, quot = firstFactor(num, max)
	}
	fmt.Println(factors)
	//fmt.Printf(
	//    "the largest prime factor of the number 600851475143: %v\n", largest)
}
