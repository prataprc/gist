package main

import "os"
import "fmt"
import "time"

func main() {
	// If the file doesn't exist, create it, or append to the file
	f, err := os.OpenFile("write.data", os.O_APPEND|os.O_CREATE|os.O_WRONLY, 0644)
	if err != nil {
		panic(err)
	}
	f.Close()

	// If the file doesn't exist, create it, or append to the file
	f, err = os.OpenFile("write.data", os.O_APPEND|os.O_WRONLY, 0644)
	if err != nil {
		panic(err)
	}

	block := make([]byte, 4096)
	for i := 0; i < len(block); i++ {
		block[i] = byte(i)
	}

	finch, quitch := make(chan struct{}), make(chan struct{})
	for i := 0; i < 4; i++ {
		go randomread(finch, quitch)
	}

	now := time.Now()
	for i := 0; i < 13107200; i++ {
		if _, err := f.Write(block); err != nil {
			panic(err)
		}
	}
	if err := f.Sync(); err != nil {
		panic(err)
	}
	fmt.Printf("Took %v to write 50GB\n", time.Since(now))
	if err := f.Close(); err != nil {
		panic(err)
	}
	close(quitch)
	<-finch
}

func randomread(finch chan struct{}, quitch chan struct{}) {
	// If the file doesn't exist, create it, or append to the file
	f, err := os.OpenFile("read.data", os.O_RDONLY, 0644)
	if err != nil {
		panic(err)
	}
	block := make([]byte, 4096)
	time.Sleep(1 * time.Second)
	now := time.Now()
	n := 0
loop:
	for {
		for i := 1; i < 13107100; i++ {
			if _, err := f.ReadAt(block, int64(i*4096)); err != nil {
				panic(err)
			}
			n += 4096
			select {
			case <-quitch:
				break loop
			default:
			}
		}
	}
	fmt.Printf("Took %v to read %v\n", time.Since(now), n)
	func() {
		defer func() { recover() }()
		close(finch)
	}()
}
