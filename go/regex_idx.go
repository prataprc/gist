package main

import "fmt"
import "errors"
import "regexp"

const IndexNamePattern = "^[A-Za-z0-9_-]+$"

func main() {
	fmt.Println(IsValidIndexName("axfAJH-asdf091-adsf"))
	fmt.Println(IsValidIndexName("axfAJH-asdf091-&dsf"))
	fmt.Println(IsValidIndexName("axfA:H-asdf091-dsf"))
}

func IsValidIndexName(n string) error {
	valid, _ := regexp.MatchString(IndexNamePattern, n)
	if !valid {
		return errors.New("ErrInvalidIndexName")
	}
	return nil
}
