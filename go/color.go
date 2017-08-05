package main

import (
	"fmt"
	"github.com/prataprc/color"
	"os"
	"strconv"
	"text/tabwriter"
)

type Formatter struct {
	Writer *tabwriter.Writer
}

func main() {
	w := new(tabwriter.Writer)
	w.Init(os.Stdout, 0, 8, 0, '\t', 0)
	f := &Formatter{Writer: w}

	yellow := color.New(color.FgYellow)
	yellow.Add(color.Italic)
	yellow.Add(color.Bold)

	arg := yellow.SprintFunc()(strconv.Itoa(43))
	fmt.Fprintf(f.Writer, " %s\t%s\t%s\n", arg, "[ ]", "Just a simple text")
	f.Writer.Flush()

	fmtarg := yellow.FormatFunc()(strconv.Itoa(43))
	fmt.Fprintf(f.Writer, " %s\t%s\t%s\n", fmtarg, "[ ]", "Just a simple text")
	f.Writer.Flush()
}
