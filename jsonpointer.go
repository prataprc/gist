package main

import (
    "flag"
    "os"
    "io/ioutil"
    "log"
    "fmt"
    "github.com/prataprc/go-jsonpointer"
)

var options struct {
    list bool
}

func argParse() {
    flag.BoolVar(&options.list, "list", false, "list pointers")
    flag.Parse()
}

func usage() {
    fmt.Fprintf(os.Stderr, "Usage : %s [OPTIONS] <json-doc> \n", os.Args[0])
    flag.PrintDefaults()
}

func main() {
    argParse()
    args := flag.Args()
    if len(args) == 0 {
        usage()
    }

    jdoc, err := ioutil.ReadFile(args[0])
    if err != nil {
        log.Fatal(err)
    }
    if options.list {
        if ptrs, err := jsonpointer.ListPointers(jdoc); err != nil {
            log.Fatal(err)
        } else {
            for _, ptr := range ptrs {
                fmt.Printf("%q\n", ptr)
            }
        }
    }
}
