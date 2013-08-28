package main
import (
    "fmt"; "unsafe"; "sync/atomic"; "runtime";
)

var keys unsafe.Pointer = unsafe.Pointer( &map[string]bool{} )

func SafeCoW( addr *unsafe.Pointer, cow func(unsafe.Pointer) unsafe.Pointer ) {
    for {
        opp := atomic.LoadPointer(addr)
        newaddr := cow( opp )
		if atomic.CompareAndSwapPointer(addr, opp, newaddr) {
			return
		}
	}
}

func EnableKey(key string) {
    SafeCoW( &keys, func(oldkeys unsafe.Pointer) unsafe.Pointer {
        oldk := (*map[string]bool)(oldkeys)
        newk := map[string]bool{key: true}
        for k := range *oldk {
            newk[k] = true
        }
        return unsafe.Pointer(&newk);
    })
}

// Check to see if logging is enabled for a key
func KeyEnabled(key string) bool {
	m := *(*map[string]bool)(atomic.LoadPointer(&keys))
	return m[key]
}

func main() {
    EnableKey("lmn")
    ch := make(chan byte);
    go routineA(ch)
    go routineB(ch)
    fmt.Println(<-ch)
    fmt.Println(<-ch)
}

func routineA(ch chan byte) {
    EnableKey("xyz")
    fmt.Println("A ...", KeyEnabled("xyz") )
    fmt.Println("A ...", KeyEnabled("abc") )
    ch <- 10;
}

func routineB(ch chan byte) {
    EnableKey("abc")
    fmt.Println("B ...", KeyEnabled("xyz") )
    fmt.Println("B ...", KeyEnabled("abc") )
    ch <- 20;
}

