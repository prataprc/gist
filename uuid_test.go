package main

import (
    "github.com/nu7hatch/gouuid"
    "testing"
)

func Benchmark_NewV3(b *testing.B) {
    for i := 0; i < b.N; i++ {
        uuid.NewV3(uuid.NamespaceDNS, []byte("hello world"))
    }
}

func Benchmark_NewV4(b *testing.B) {
    for i := 0; i < b.N; i++ {
        uuid.NewV4()
    }
}

func Benchmark_NewV5(b *testing.B) {
    for i := 0; i < b.N; i++ {
        uuid.NewV5(uuid.NamespaceDNS, []byte("hello world"))
    }
}
