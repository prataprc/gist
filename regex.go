package main

import (
    "fmt"
    "regexp"
)

func main() {
    matched, err := regexp.MatchString("^foo.*", "seafood")
    fmt.Println(matched, err)
    matched, err = regexp.MatchString("bar.*", "seafood")
    fmt.Println(matched, err)
    matched, err = regexp.MatchString("a(b", "seafood")
    fmt.Println(matched, err)
    fmt.Println("Submatches\n")
    subMatches()
}

var digitsRegexp = regexp.MustCompile(`(\d+)\D+(\d+)`)
var hexRegexp = regexp.MustCompile(`(\D+)|(\d+)`)

func subMatches() {
    fmt.Println(digitsRegexp.FindStringSubmatch("1000abcd123"))
    fmt.Println(hexRegexp.FindAllStringSubmatch("1000", 1))
    fmt.Println(hexRegexp.FindAllStringSubmatch("abcd", 1))
}
