package main

import "testing"

func decode1(opmode byte) (argsMode, argAMode, argBMode, argCMode, isJmpNext byte) {
    var temp byte

    temp = 3
    argsMode = opmode & temp

    temp = temp << 2
    argCMode = (opmode & temp) >> 2

    temp = temp << 2
    argBMode = (opmode & temp) >> 4

    temp = (1) << 6
    argAMode = (opmode & temp) >> 6

    temp = temp << 1
    isJmpNext = (opmode & temp) >> 7
    return
}

func decode2(opmode byte) (t, a, b, c, m byte) {
    return opmode & 0x3, (opmode & 0xc) >> 2,
        (opmode & 0x30) >> 4, (opmode & 0x40) >> 6, (opmode & 0x80) >> 7
}

func BenchmarkDecode1(b *testing.B) {
    for i := 0; i < b.N; i++ {
        decode1(byte(i))
    }
}

func BenchmarkDecode2(b *testing.B) {
    for i := 0; i < b.N; i++ {
        decode2(byte(i))
    }
}
