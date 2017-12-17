package main

import "testing"

func BenchmarkChan(b *testing.B) {
	ch := make(chan int, 100000)
	for i := 0; i < 100; i++ {
		ch <- i
	}
	syncch := make(chan struct{})
	go func() {
		for i := 0; i < b.N; i++ {
			ch <- 100
		}
	}()
	go func() {
		for i := 0; i < b.N; i++ {
			<-ch
		}
		close(syncch)
	}()
	<-syncch
}
