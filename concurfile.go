package main

import (
    "fmt"
    "time"
    "encoding/binary"
    "os"
)

var _ = fmt.Sprintln("keep 'fmt' import during debugging", time.Now());

var datafile = "testfile"
type Dat struct {
    fpos int64
    size int
    data string
}

func main() {
    var data = [2]string{"hello", "world"}

    wfd, _ := os.Create(datafile)

    items := 10000
    chans := []chan []interface{} {
        make(chan []interface{}), make(chan []interface{}),
        make(chan []interface{}), make(chan []interface{}),
    }
    //endchan := make(chan []interface{}, count)

    go doread(chans[0])
    go doread(chans[0])
    go doread(chans[0])

    for {
        dats := make([]Dat, 0, items)
        for i := 0; i < items; i++ {
            dat := data[i%2]
            fpos := appendData(wfd, dat)
            dats = append(dats, Dat{fpos, len(dat), dat})
        }
        chans[0] <- []interface{}{dats}
        chans[0] <- []interface{}{dats}
        chans[0] <- []interface{}{dats}
    }
    os.Remove(datafile)
}

func doread(in chan []interface{}) {
    rfd, _ := os.Open(datafile)
    for {
        dats := (<-in)[0].([]Dat)
        for _, dat := range dats {
            data := readData(rfd, dat.fpos)
            //fmt.Println(rfd, data, dat.data)
            if data != dat.data {
                panic("Data not equal")
            }
        }
    }
}

func readData(rfd *os.File, fpos int64) string {
    var size int32
    if _, err := rfd.Seek(fpos, os.SEEK_SET); err != nil {
        panic(err.Error())
    }
    binary.Read(rfd, binary.LittleEndian, &size)
    b := make([]byte, size)
    if _, err := rfd.Read(b); err != nil {
        panic(err.Error())
    }
    return string(b)
}

func appendData(wfd *os.File, val string) int64 {
    valb := []byte(val)
    fpos, _ := wfd.Seek(0, os.SEEK_END)
    binary.Write(wfd, binary.LittleEndian, int32(len(valb)))
    if _, err := wfd.Write(valb); err != nil {
        panic(err.Error())
    }
    return fpos
}
