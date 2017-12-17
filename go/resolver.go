package main

import (
	"context"
	"fmt"
	"net"
	"os"
)

func main() {
	if len(os.Args) != 2 {
		fmt.Fprintf(os.Stderr, "Usage: %s hostname\n", os.Args[0])
		fmt.Println("Usage: ", os.Args[0], "hostname")
		os.Exit(1)
	}
	name := os.Args[1]

	var resolv net.Resolver
	ctx := context.Background()
	addrs, err := resolv.LookupIPAddr(ctx, name)
	if err != nil {
		fmt.Println("Resolution error", err.Error())
		os.Exit(1)
	}
	fmt.Println("Resolved address is ", addrs)

	ipaddrs, err := net.LookupIP(name)
	if err != nil {
		fmt.Println("Resolution error", err)
		os.Exit(1)
	}
	fmt.Printf("LookupIP(%v): %v\n", name, ipaddrs)
	os.Exit(0)
}
