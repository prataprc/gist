package main
import "fmt"
import "os"

func main() {
    if fd, err := os.Open("./control.go"); err != nil {
        panic( err.Error() )
    } else {
        fmt.Println(fd)
    }
}
