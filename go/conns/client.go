package main

import "net"
import "os"
import "fmt"
import "time"
import "strconv"
import "io"
import "sync"
import "runtime"

var msg_size = 50
var tcpAddr, _ = net.ResolveTCPAddr("tcp", "0:7777")

func main() {
	runtime.GOMAXPROCS(runtime.NumCPU())
	var wg sync.WaitGroup

	perconn, _ := strconv.Atoi(os.Args[1])
	nconns, _ := strconv.Atoi(os.Args[2])

	conns := make([]net.Conn, 0)
	for i := 0; i < nconns; i++ {
		conn, err := net.DialTCP("tcp", nil, tcpAddr)
		if err != nil {
			fmt.Println(err)
			os.Exit(1)
		}
		conns = append(conns, conn)
	}

	t0 := time.Now()
	for i := 0; i < nconns; i++ {
		wg.Add(1)
		go worker(&wg, conns[i], perconn)
	}
	wg.Wait()
	dur := time.Now().Sub(t0)
	fmt.Println(dur)
	fmt.Printf("%d rows/sec\n", int(float64(perconn*nconns)/dur.Seconds()))
}

func worker(wg *sync.WaitGroup, conn net.Conn, n int) {
	defer wg.Done()
	resp := make([]byte, msg_size)
	conn, err := net.DialTCP("tcp", nil, tcpAddr)
	if err != nil {
		fmt.Println(err)
		os.Exit(1)
	}

	req := make([]byte, msg_size)
	i := 0
	for i = 1; i <= n; i++ {
		_, err = conn.Write(req)
		if err != nil {
			fmt.Println(err)
			break
		}
		io.ReadFull(conn, resp)
	}
}
