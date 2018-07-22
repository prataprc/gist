package main
import (
    "log";
    "fmt";
    "os";
    "runtime";
)

func main() {
    log.Println("Starting ...")
    ch := make(chan int, 10000000);
    go out(ch)
    for i:=0; i<1000000; i++ {
        ch <- i;
    }
    runtime.Gosched()
    os.Exit(0);
}

func out(ch chan int) {
    for {
        fmt.Println(<-ch)
    }
}
