appending string to byte-slice
------------------------------

Following snippet copies a greeting string to a byte-slice.

    var greeting []byte

    append(greeting, "hello world")
    fmt.Println(greeting)

What will be the o/p of this program ?

closing channel
---------------

The following program does not compile !

    package main

    import "fmt"

    func main() {
        var c <-chan int
        C := make(chan int, 4)
        c = C

        startsend(C)
        for x := range c {
            fmt.Println("received", x)
        }
        fmt.Println("done")
        close(c)
    }

    func startsend(c <-chan int) {
        items := [4]int{10, 20, 30, 40}
        for i, x := range items {
            c <- x
        }
    }

* cannot close receive only channel.
* send to receive only type.
* unused variable `i`.
* deadlock.
