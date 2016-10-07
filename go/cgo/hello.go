package main

/*
int main2();
*/
import "C"
import "fmt"

func main() {
   fmt.Println("Hello from Go code")
   C.main2();
}
