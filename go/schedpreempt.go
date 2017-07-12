package main

import "fmt"
import "runtime"

func main() {
	runtime.GOMAXPROCS(1)
	x := make(chan bool)
	y := make(chan bool)

	go func() {
		for {
			//if fn(x, y) {
			//	return
			//}
			select {
			case <-x:
				//	fmt.Println("x")
				return
			case <-y:
				//fmt.Println("y")
				break
			default:
				//fmt.Println("default")
			}
		}
	}()
	y <- true
	x <- true
}

func fn(x, y chan bool) bool {
	select {
	case <-x:
		fmt.Println("x")
		return true
	case <-y:
		fmt.Println("y")
		break
	default:
		fmt.Println("default")
	}
	return false
}

// if i uncomment y, it does not work
