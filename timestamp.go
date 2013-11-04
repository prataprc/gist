package main
import (
    "time"
    "log"
)

func main() {
    tsold := time.Now().UnixNano()
    for i := 0; i < 10000000000000000; i++ {
        tsnew := time.Now().UnixNano()
        if tsold > tsnew {
            log.Panicln("fail", tsold, tsnew, i)
        }
        tsold = tsnew
    }
}
