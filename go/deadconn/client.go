package main

import "net"
import "log"
import "time"

func main() {
	_, err := net.Dial("tcp", "localhost:8080")
	if err != nil {
		log.Println(err)
	}
	time.Sleep(1 * time.Hour)
}
