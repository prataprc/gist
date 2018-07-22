package main

import (
    "net"
    "fmt"
    "unsafe"
)

func main() {
    ip, ipnet, err := net.ParseCIDR("192.168.23.1/22")
    fmt.Println(ip, ipnet, err)
    fmt.Println("Default mask :", ip.DefaultMask())
    // Interface
    ifaces, _ := net.Interfaces()
    for _, iface := range ifaces {
        fmt.Printf(
            "interface %v %v : mtu(%v), hw(%v), flags(%v) \n",
            iface.Index, iface.Name, iface.MTU, iface.HardwareAddr, iface.Flags,
        )
    }
    // Interface address
    iaddrs, _ := net.InterfaceAddrs()
    for _, iaddr := range iaddrs {
        fmt.Println("interface addrs :", iaddr.Network(), iaddr.String())
    }
    // Lookups
    cname, _ := net.LookupCNAME("google.com")
    ips, _ := net.LookupIP("google.com") // net.LookupHost("google.com")
    mx, _ := net.LookupMX("google.com")
    ns, _ := net.LookupNS("google.com")
    fmt.Println("google.com :", cname)
    fmt.Println("  ", ips)
    for _, x := range mx {
        fmt.Println("  ", x.Host, x.Pref)
    }
    for _, x := range ns {
        fmt.Println("  ", x.Host)
    }
    ip =net.IPv4(192, 168, 1, 1)
    ipbytes := (*[]byte)(unsafe.Pointer(&ip))
    fmt.Println(ipbytes)
}
