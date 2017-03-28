package main

import "fmt"

func main() {
	seqno := make([]uint16, 128)
	fmt.Printf("%p %p %p %p %p\n", &seqno, &seqno[0], &seqno[1], &seqno[126], &seqno[127])
}
