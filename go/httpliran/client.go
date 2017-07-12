package main

import (
	"flag"
	"fmt"
	"io/ioutil"
	"math/rand"
	"net/http"
	"os"
	"sync"
	"sync/atomic"
	"time"
)

var (
	wg                   = &sync.WaitGroup{}
	currentRequest int64 = 0
	totalRequests  int64 = 100000
	parallelConn         = 1000
	port                 = 8080
)

func init() {
	flag.IntVar(&port, "port", 8080, "8080 test server, 8081 main server")
	flag.IntVar(&parallelConn, "p", 1000, "default 100 parallel connection")
	flag.Int64Var(&totalRequests, "t", 100000, "default 10000 requests")
	flag.Parse()
}

func main() {
	wg.Add(parallelConn)

	for i := 0; i < parallelConn; i++ {
		go requestRoutine()
	}

	wg.Wait()
	fmt.Println("done")
}

func doRequest(client *http.Client, i int64) {
	req, _ := http.NewRequest("GET", fmt.Sprintf("http://localhost:%d/", port), nil)

	resp, err := client.Do(req)
	if err != nil {
		fmt.Printf("error on request: %d (%s)\n", i, err)
		os.Exit(1)
		return
	}

	_, err = ioutil.ReadAll(resp.Body)
	resp.Body.Close()
	if err != nil {
		fmt.Printf("error on body read: %d (%s)\n", i, err)
		os.Exit(1)
		return
	}

	fmt.Printf("request: %d\n", i)
}

func requestRoutine() {
	defer wg.Done()
	tr := &http.Transport{}
	client := &http.Client{Transport: tr}
	sleepn := time.Duration(rand.Intn(10000) / 100)
	time.Sleep(sleepn * time.Millisecond)

	for {
		curr := atomic.AddInt64(&currentRequest, 1)
		if curr >= totalRequests {
			break
		}
		doRequest(client, curr)
	}

	tr.CloseIdleConnections()
}
