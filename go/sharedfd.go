package main

import "os"
import "io"
import "fmt"
import "runtime"
import "math/rand"

import "golang.org/x/exp/mmap"

var filename = "testfile.data"
var block [4096]byte
var nblocks = 10000

func main() {
	fd, err := os.Create(filename)
	if err != nil {
		panic(err)
	}
	for i := 0; i < nblocks; i++ {
		for j := range block {
			block[j] = byte(i)
		}
		if n, err := fd.Write(block[:]); err != nil {
			panic(err)
		} else if n < len(block) {
			panic("less")
		}
	}
	//normalfile(filename)
	mmapfile(filename)
	<-make(chan struct{})
	return
}

func normalfile(filename string) io.ReaderAt {
	file, err := os.Open(filename)
	if err != nil {
		panic(err)
	}
	for i := 0; i < runtime.GOMAXPROCS(-1); i++ {
		go reader(file)
	}
	return file
}

func mmapfile(filename string) io.ReaderAt {
	file, err := mmap.Open(filename)
	if err != nil {
		panic(err)
	}
	for i := 0; i < runtime.GOMAXPROCS(-1); i++ {
		go reader(file)
	}
	return file
}

func reader(r io.ReaderAt) {
	fmt.Println("reader")
	rblock := make([]byte, len(block))
	for {
		i := rand.Intn(nblocks)
		at := int64(i * len(rblock))
		if n, err := r.ReadAt(rblock, at); err != nil {
			panic(err)
		} else if n < len(rblock) {
			panic("less")
		} else {
			for _, ch := range rblock {
				if ch != byte(i) {
					panic("not equal")
				}
			}
		}
	}
}
