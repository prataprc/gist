package main

import "fmt"
import "unsafe"

type String struct {
	pointer uint64
	length  uint64
}

func main() {
	// escapes
	escapes()

	s := "hello world" // same string
	x := "hello world" // stored in different locations
	y := "long string ......................................................."
	fmt.Printf("s `%v` is at %v\n", s, &s)
	fmt.Printf("x `%v` is at %v\n", x, &x)
	fmt.Printf("Size of y %v\n", unsafe.Sizeof(y))

	// Internals of string
	english := "Good morning"
	chinese := "早安"
	spanish := "Español"
	ep := (*String)(unsafe.Pointer(&english))
	cp := (*String)(unsafe.Pointer(&chinese))
	sp := (*String)(unsafe.Pointer(&spanish))
	fmt.Println(ep)
	fmt.Println(cp)
	fmt.Println(sp)
	fmt.Println(spanish[4:5], spanish[4:6])

	passby(spanish)

	fmt.Printf("%020v\n", 100)
	fmt.Println("a\x00b")
	fmt.Println([]byte("a\x00b"))

	unicode()
}

func passby(str string) {
	sp := (*String)(unsafe.Pointer(&str))
	fmt.Println(&str, sp)
}

func unicode() {
	s := `"汉语 / 漢語; Hàn\b \t\uef24yǔ "`
	for i, ch := range s {
		fmt.Printf("%v %v; ", i, ch)
	}
	fmt.Println()
}

func escapes() {
	s := "\"hello\xffworld\""
	b := []byte(s)
	fmt.Println(len(s), s)
	fmt.Println(len(b), b)
}
