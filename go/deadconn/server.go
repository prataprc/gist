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
		buf, n := []byte{0, 1, 2, 3, 4, 5, 6, 7, 8, 9}, 0
		for i := 0; i < 10000000000; i++ {
			x, err := conn.Write(buf)
			if err != nil {
				log.Println(err)
			} else if x != 10 {
				log.Printf("wrote only %v\n", x)
			} else {
				fmt.Printf("written %v\n", n)
			}
		}
	}
}
