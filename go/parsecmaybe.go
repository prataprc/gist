package main

import "fmt"

import "github.com/prataprc/goparsec"

func main() {
	vector2scalar := func(nodes []parsec.ParsecNode) parsec.ParsecNode {
		return nodes[0]
	}
	y := parsec.And(
		func(nodes []parsec.ParsecNode) parsec.ParsecNode {
			fmt.Printf("parsed %v items\n", len(nodes))
			for i, node := range nodes {
				fmt.Printf("index:%v %T\n", i, node)
			}
			return nil
		},
		parsec.String(),
		parsec.Maybe(vector2scalar, parsec.Int()),
		parsec.Token("false", "BOOL"),
	)

	fmt.Println(`text: "hello" 10 false`)
	scanner := parsec.NewScanner([]byte(`"hello" 10 false`))
	y(scanner)

	fmt.Println("......")
	fmt.Println(`text: "hello" false`)
	scanner = parsec.NewScanner([]byte(`"hello" false`))
	y(scanner)
}
