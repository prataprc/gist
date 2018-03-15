package main

import "os"
import "fmt"
import "io/ioutil"
import "path/filepath"

func main() {
	tempdir := os.TempDir()
	dname1 := filepath.Join(tempdir, "dname1")
	dname2 := filepath.Join(tempdir, "dname2")
	fname := filepath.Join(dname1, "file")
	fmt.Println(fname)

	if err := os.RemoveAll(dname2); err != nil {
		panic(err)
	}
	if err := os.RemoveAll(dname1); err != nil {
		panic(err)
	}

	if err := os.MkdirAll(dname1, 0777); err != nil {
		panic(err)
	}
	if err := ioutil.WriteFile(fname, []byte("hello world"), 0666); err != nil {
		panic(err)
	}
	if err := os.Symlink(dname1, dname2); err != nil {
		panic(err)
	}
	fname = filepath.Join(dname2, "file")
	if err := os.RemoveAll(fname); err != nil {
		panic(err)
	}
}
