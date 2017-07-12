package main

import (
	"fmt"
	"net/http"
)

func main() {
	err := http.ListenAndServe(":8088", http.HandlerFunc(func(w http.ResponseWriter, r *http.Request) {
		fmt.Fprint(w, "hello")
	}))
	fmt.Println(err)
}
