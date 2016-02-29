package main

import "math/rand"
import "fmt"

func main() {
	repeat, n := 10, 10
	for i := 0; i < repeat; i++ {
		initial := rand.Int31n(10000000)
		nums := randoms(n)
		fmt.Printf("initial: %v nums: %v\n", initial, nums)
		i64, f64 := movingavgInt64(initial, nums), movingavgF64(initial, nums)
		fmt.Printf("i64: %v f64: %v\n\n", i64, f64)
	}
}

func randoms(n int) []int32 {
	nums := make([]int32, n)
	for i := 0; i < n; i++ {
		nums[i] = rand.Int31n(10000000)
	}
	return nums
}

func movingavgInt64(initial int32, nums []int32) int64 {
	for _, x := range nums {
		initial = (initial + x) / 2
	}
	return int64(initial)
}

func movingavgF64(initial int32, nums []int32) float64 {
	f := float64(initial)
	for _, x := range nums {
		f = (f + float64(x)) / 2.0
	}
	return f
}
