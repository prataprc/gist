package main

import (
	"bytes"
	"fmt"
	"text/template"
)

func main() {
	var tstring = `Hello {{.name}}`
	var err error
	t := template.New("example")
	if t, err = t.Parse(tstring); err != nil {
		panic(err)
	}
	m := map[string]interface{}{
		"mname": "batman",
	}
	buf := bytes.NewBuffer([]byte{})
	if err = t.Execute(buf, m); err != nil {
		panic(err)
	}
	fmt.Println(string(buf.Bytes()))
}
