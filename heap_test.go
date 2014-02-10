package main

import (
	"fmt"
	"math/rand"
	"testing"
)

func main() {
	var v int
	arr := make([]int, 0, 100)
	res := make([]int, 0, 100)
	count := 10
	for i := 0; i < count; i++ {
		arr = insert(arr, rand.Intn(1000))
	}
	for i := 0; len(arr) > 0; i++ {
		arr, v = pop(arr)
		res = append(res, v)
	}
	fmt.Println(arr)
	fmt.Println(res)
}

func insert(arr []int, val int) []int {
	arr = arr[:len(arr)+1]
	arr[len(arr)-1] = val
	if len(arr) > 1 {
		arr = shiftUp(arr, len(arr))
	}
	return arr
}

func pop(arr []int) ([]int, int) {
	var max int
	max, arr[0] = arr[0], arr[len(arr)-1]
	arr = arr[:len(arr)-1]
	shiftDown(arr, 0)
	return arr, max
}

func shiftUp(arr []int, n int) []int {
	if n == 1 || arr[n/2-1] > arr[n-1] {
		return arr
	}
	arr[n/2-1], arr[n-1] = arr[n-1], arr[n/2-1] // swap
	arr = shiftUp(arr, n/2)
	return arr
}

func shiftDown(arr []int, n int) []int {
	x, y := n, -1
	if (2*n+1 < len(arr)) && arr[n] < arr[2*n+1] {
		y = 2*n + 1
	}
	if (2*n+2 < len(arr)) && arr[n] < arr[2*n+2] {
		if arr[y] < arr[2*n+2] {
			y = 2*n + 2
		}
	}
	if y > 0 {
		arr[x], arr[y] = arr[y], arr[x] // swap
		arr = shiftDown(arr, y)
	}
	return arr
}

func Test_heap(t *testing.T) {
	for i := 0; i < 100000; i++ {
		fmt.Println(i)
		arr := make([]int, 0, i)
		res := make([]int, 0, i)
		for j := 0; j < i; j++ {
			arr = insert(arr, rand.Intn(1000000))
		}
		refval, v := 10000000, 0
		for j := 0; len(arr) > 0; j++ {
			arr, v = pop(arr)
			res = append(res, v)
			if v > refval {
				fmt.Println(res)
				panic("")
			}
			refval = v
		}
	}
}
