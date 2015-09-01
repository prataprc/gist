package main

import "fmt"
import "reflect"

type SecondaryKeys []interface{}

func main() {
	type Bytes []byte
	Bs := Bytes([]byte("hello"))
	bs := []byte(Bs)
	fmt.Println(Bs, bs)

	dumpTypes()
}

func dumpTypes() {
	val1 := SecondaryKeys([]interface{}{})
	val2 := []interface{}{}
	fmt.Printf("%v %v\n", reflect.TypeOf(val1), reflect.TypeOf(val2))
	fmt.Println(reflect.DeepEqual(val1, val2))

	val3 := []interface{}{}
	var val4 []interface{} = nil
	fmt.Printf("%v %v\n", reflect.TypeOf(val3), reflect.TypeOf(val4))
	fmt.Println(reflect.DeepEqual(val3, val4))
}
