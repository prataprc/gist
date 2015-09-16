package main

import (
	"encoding/json"
	"fmt"
	"log"
)

func main() {
	controlCharsInStrings()
	//tryUnmarshalGenericy()
	//marshalInterface()
}

func controlCharsInStrings() {
	var val interface{}
	s := `"hello\bworld"`
	if err := json.Unmarshal([]byte(s), &val); err != nil {
		log.Fatal(err)
	}
	fmt.Printf("controlCharsInStrings/unmarshal: %q\n", val)
}

func tryUnmarshalGenericy() {
	var val = `{ "name": "Franklin",
    "members": ["Kriton","Ernie","Margot","Sundaresan","Lenora","Robin","Rick","Ranjit","Kathryn","Tracey","Bob","Charley","Andre","Miek"],
    "language": "python" }`

	// Map of interfaces can receive any value types
	value := map[string]interface{}{}

	fmt.Println(json.Unmarshal([]byte(val), &value))
	fmt.Println(value)
}

type someInterface interface {
	this()
	that()
}

type someStruct struct {
	n int
	s string
}

func (st *someStruct) this() {}

func (st *someStruct) that() {}

type EmbeddInterface struct {
	M int    `json:"m"`
	Y string `json:"y"`
	I someInterface
}

func marshalInterface() {
	st := someStruct{
		n: 10,
		s: "hello world",
	}
	v := EmbeddInterface{
		M: 20,
		Y: "good morning",
		I: &st,
	}
	data, err := json.Marshal(&v)
	fmt.Println(err)
	fmt.Println(string(data))

	var u EmbeddInterface
	err = json.Unmarshal(data, &u)
	fmt.Println(err)
	fmt.Println(u)
}
