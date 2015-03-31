package main

import "compress/gzip"

//import "math/rand"
import "bytes"
import "log"
import "fmt"
import "flag"

//import "strconv"
import "os"
import "io/ioutil"

var options struct {
	count int
	par   int
	zip   bool
	store bool
}

func argParse() {
	flag.IntVar(&options.count, "count", 1, "generate count values")
	flag.IntVar(&options.par, "par", 1, "concurrently generate count values ")
	flag.BoolVar(&options.zip, "zip", false, "zip values before calling done")
	flag.BoolVar(&options.store, "store", false, "concurrently generate count values ")
	flag.Parse()
}

func main() {
	argParse()
	ch1 := make(chan []byte, 10000)
	ch2 := make(chan []byte, 10000)
	ch3 := make(chan []byte, 1000000)
	in, out := chan []byte(nil), ch1
	for i := 0; i < options.par; i++ {
		go generateValues(options.count, out)
	}
	if options.zip {
		in, out = out, ch2
		for i := 0; i < options.par; i++ {
			go zipValues(in, out)
		}
	}
	if options.store {
		in, out = out, ch3
		go storeValues(in, out)
	}
	till := options.count * options.par
	total := 0
	for till > 0 {
		outdata := <-out
		till--
		total += len(outdata)
	}
	fmt.Printf("Total %v bytes\n", total)
}

func generateValues(count int, out chan<- []byte) {
	data, err := ioutil.ReadFile("zipappend.go")
	if err != nil {
		log.Fatal(err)
	}
	for i := 0; i < count; i++ {
		//out <- []byte(strconv.Itoa(int(rand.Int63())))
		out <- data
	}
}

func zipValues(in, out chan []byte) {
	var buf bytes.Buffer
	writer, err := gzip.NewWriterLevel(&buf, gzip.DefaultCompression)
	if err != nil {
		log.Fatal(err)
	}
	for {
		indata := <-in
		buf.Reset()
		writer.Reset(&buf)
		_, err = writer.Write(indata)
		if err != nil {
			log.Fatal(err)
		} else if err := writer.Flush(); err != nil {
			log.Fatal(err)
		}
		out <- buf.Bytes()
	}
}

func storeValues(in, out chan []byte) {
	fd, err := os.Create("zipappend.data")
	if err != nil {
		log.Fatal(err)
	}
	for {
		indata := <-in
		if n, err := fd.Write(indata); err != nil {
			log.Fatal(err)
		} else if n != len(indata) {
			log.Fatalf("Error writing data")
		}
		go func() { out <- indata }()
	}
}
