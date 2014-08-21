package main

import (
    "net"
    "log"
    "time"
)

func main() {
    go server()
    _, err := net.Dial("tcp", "localhost:8080")
    if err != nil { // handle error
        log.Fatal(err)
    }
    <-time.After(1000 * time.Second)
}

func server() {
    addr := &net.TCPAddr{IP: []byte{0x7f,0,0,1}, Port: 8080}
    ln, err := net.ListenTCP("tcp", addr)
    if err != nil { // handle error
        log.Fatal(err)
    }
    for {
        conn, err := ln.AcceptTCP()
        if err != nil { // handle error
            log.Fatal(err)
        }
        go handle(conn)
    }
}

func handle(conn *net.TCPConn) {
    conn.SetKeepAlive(true)
    conn.SetKeepAlivePeriod(time.Duration(20*time.Second))
}
