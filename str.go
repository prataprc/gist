package main
import "fmt"

func main() {
    s := "hello world"  // same string
    x := "hello world"  // stored in different locations
    fmt.Printf( "This `%s` is at %x\n", s, &s );
    fmt.Printf( "This `%s` is at %x\n", x, &x );
    fmt.Printf( "But pointer comparison is %s \n", &x == &x ); // true !
}
