package main

import "fmt"
import "reflect"
import "log"
import "strconv"

type SecondaryKeys []interface{}

func main() {
	type Bytes []byte
	Bs := Bytes([]byte("hello"))
	bs := []byte(Bs)
	fmt.Println(Bs, bs)

	int64Touint64()
	dumpTypes()
}

func int64Touint64() {
	s := "9223372036854775808"
	a, err := strconv.Atoi(s) // Atoi: value out of range
	if err != nil {
		log.Fatal(err)
	}
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
