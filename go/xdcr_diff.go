package lib

import (
	"strings"

	"github.com/prataprc/goparsec"
)

// Terminal rats
var xopen = parsec.Token(`^\(\+-\) Entry differs between files`, "OPEN")
var xa = parsec.Token(`^in.*:`, "A")
var xkeyDocid = parsec.Token(`^Doc ID`, "KEYDOCID")
var xcolon = parsec.Token(`^:`, "COLON")
var xdocid = parsec.Token(`^.*\n`, "DOCID")
var xkeyMeta = parsec.Token(`^[^:]+`, "KEYMETA")
var xcomma = parsec.Token(`^,`, "COMMA")
var xkeyData = parsec.Token(`^data:`, "KEYDATA")
var xdata = parsec.Token(`^.*\n`, "DATA")

func XDCRDiffParse(text []byte) parsec.ParsecNode {
	s := parsec.NewScanner(text)
	xdata := parsec.And(
		func(ns []parsec.ParsecNode) parsec.ParsecNode {
			return map[string]interface{}{"data": ns[1]}
		},
		xkeyData, xdata)

	xprop := parsec.And(
		func(ns []parsec.ParsecNode) parsec.ParsecNode {
			key := strings.Trim(ns[0].(*parsec.Terminal).Value, " \t\n")
			return map[string]interface{}{key: ns[2]}
		},
		xkeyMeta, xcolon, parsec.Int(), parsec.Maybe(nil, xcomma))

	xdoc := parsec.And(
		func(ns []parsec.ParsecNode) parsec.ParsecNode {
			m := map[string]interface{}{
				"docid": ns[3],
			}
			for _, kv := range ns[4].([]parsec.ParsecNode) {
				for k, v := range kv.(map[string]interface{}) {
					m[k] = v
				}
			}
			return m
		},
		xa, xkeyDocid, xcolon, xdocid,
		parsec.Kleene(
			nil,
			parsec.OrdChoice(
				func(ns []parsec.ParsecNode) parsec.ParsecNode { return ns[0] },
				xdata, xprop),
		),
	)

	nt, _ := parsec.And(
		func(ns []parsec.ParsecNode) parsec.ParsecNode {
			return ns
		}, xopen, xdoc, xdoc)(s)
	return nt
}
