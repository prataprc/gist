package main

import "time"
import "fmt"

import "golang.org/x/sync/singleflight"

func main() {
	group := &singleflight.Group{}
	go func() {
		x, err, shared := group.Do("memoize", fn)
		fmt.Println(x, err, shared)
	}()
	go func() {
		x, err, shared := group.Do("memoize", fn)
		fmt.Println(x, err, shared)
	}()
	go func() {
		x, err, shared := group.Do("memoize", fn)
		fmt.Println(x, err, shared)
	}()
	time.Sleep(2 * time.Second)
}

func fn() (interface{}, error) {
	time.Sleep(1 * time.Second)
	return time.Now().UnixNano(), nil
}
