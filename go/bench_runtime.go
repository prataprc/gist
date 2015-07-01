package main

import "time"
import "flag"
import "fmt"

var options struct {
	routines int
}

type data struct {
	a int
	b int
	c int
	d int
	e int
	f int
	g int
	h int
}

func argParse() {
	flag.IntVar(&options.routines, "routines", 10,
		"Number of parallel routines")
	flag.Parse()
}

func main() {
	argParse()
	startch, outch := make(chan *data, 100), make(chan *data, 100)
	inch := startch
	for i := 0; i < options.routines; i++ {
		go routine(i, inch, outch)
		inch, outch = outch, make(chan *data, 100)
	}
	tick := time.Tick(2 * time.Second)
	for {
		count := 500
		for i := 0; i < count; i++ {
			startch <- &data{}
		}
		for count > 0 {
			select {
			case <-outch:
				count--
			case <-tick:
				fmt.Printf("main is ticking\n")
			}
		}
		<-tick
	}
}

func routine(i int, inch chan *data, outch chan *data) {
	tick := time.Tick(1 * time.Second)
	for {
		select {
		case d := <-inch:
			outch <- d
		case <-tick:
			fmt.Printf("%v ticking\n", i)
		}
	}
}
