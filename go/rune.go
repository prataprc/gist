package main

import "fmt"

func main() {
	text := "國哲學書電子化計劃 - Pre-Qin and Han"
	fmt.Println(text)
	for i, ch := range text {
		fmt.Printf("%v %c %x\n", i, ch, ch)
	}
}
