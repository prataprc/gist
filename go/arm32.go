package main

import "unsafe"
import "fmt"

type Profile struct {
	Userdir string `json:"userdir"`
	Repodir string `json:"repodir"`
	Type    string `json:"type"`
	Url     string `json:"url"`
	First   string `json:"first"`
	Prev    string `json:"prev"`
	Next    string `json:"next"`
	Last    string `json:"last"`
	// local state
	name    string
	finch   chan bool
	n_reqs  int32
	n_users int32
}

func main() {
	p := Profile{}
	fmt.Println(unsafe.Sizeof(p))
	fmt.Printf("%p %p, %p %p\n", &p, &p.finch, &p.n_reqs, &p.n_users)
}
