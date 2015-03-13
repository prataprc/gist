package main

import "reflect"
import "fmt"

func main() {
	m := map[string]interface{}{"a": []byte("hello")}
	clearMap(reflect.TypeOf("a"), reflect.TypeOf([]byte{}), m)
	fmt.Println(m)
}

func clearMap(key, elem reflect.Type, m interface{}) {
	n := reflect.Value{}
	v := reflect.ValueOf(m)
	for _, k_ := range v.MapKeys() {
		v.SetMapIndex(k_, n)
	}
}
