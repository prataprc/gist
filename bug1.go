package main
import ("fmt"; "time")

func main() {
    req := make(chan []interface{})
    go routine(req)
    for i := 0; i < 10; i++ {
        req <- []interface{}{i}
    }
}

func routine(req chan []interface{}) {
    commitQ := make(map[int64]int)
    for {
        fmt.Println("commitQ", commitQ)
        cmd := <-req
        fmt.Println("commitQ1", commitQ)
        val := cmd[0].(int)
        commitQ[time.Now().UnixNano()] = val
    }
}

