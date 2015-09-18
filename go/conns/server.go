package main

import "net"
import "runtime"

var msg_size = 50

func main() {
	runtime.GOMAXPROCS(runtime.NumCPU())
	res := make([]byte, msg_size)
	ln, _ := net.Listen("tcp", ":7777")
	for {
		conn, _ := ln.Accept()
		//conn.(*net.TCPConn).SetWriteBuffer(16 * 1024)
		//conn.(*net.TCPConn).SetReadBuffer(16 * 1024)

		go func() {
			b := make([]byte, msg_size)
			for {
				_, err := conn.Read(b)
				if err != nil {
					conn.Close()
					return
				}
				conn.Write(res)
			}
		}()
	}
}
