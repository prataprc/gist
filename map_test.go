package main

import (
    "fmt"
    "testing"
)

func Benchmark_maplookup(b *testing.B) {
    var m = make(map[string]int)
    var count int
    for i := 0 ; i < 1000000; i++ {
        m[fmt.Sprintln(i)] = i
    }
    b.ResetTimer()
    for i := 0 ; i < b.N; i++ {
        count += m["1000"]
    }
}

func Benchmark_mapdelete(b *testing.B) {
    var m = make(map[string]int)
    for i := 0 ; i < 1000000; i++ {
        m[fmt.Sprintln(i)] = i
    }
    b.ResetTimer()
    for i := 0 ; i < b.N; i++ {
        delete(m, "1000")
    }
}

func Benchmark_map(b *testing.B) {
    var m = make(map[string]int)
    for i := 0 ; i < 1000000; i++ {
        m[fmt.Sprintln(i)] = i
    }
    b.ResetTimer()
    for i := 0 ; i < b.N; i++ {
        m["long string as key"] = i
    }
}

func Benchmark_mapcpy(b *testing.B) {
    var src = make(map[string]int)
    for i := 0 ; i < 1000; i++ {
        src[fmt.Sprintln(i)] = i
    }
    b.ResetTimer()
    for i := 0 ; i < b.N; i++ {
        var dst = make(map[string]int)
        for key, value := range src {
            dst[key] = value
        }
    }
}
