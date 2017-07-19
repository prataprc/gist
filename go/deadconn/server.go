package main

import "net"
import "fmt"
import "log"

func main() {
	ln, err := net.Listen("tcp", ":8080")
	if err != nil {
		log.Println(err)
	}
	for {
		log.Println("waiting for connection")
		conn, err := ln.Accept()
		if err != nil {
			log.Println(err)
		}
		log.Println("connection accepted")
		buf, n := make([]byte, 10000), 0
		for i := 0; i < 10000000000; i++ {
			x, err := conn.Write(buf)
			n += x
			if err != nil {
				log.Println(err)
			} else if x != len(buf) {
				log.Printf("wrote only %v\n", x)
			} else {
				fmt.Printf("written %v\n", n)
			}
		}
	}
}
