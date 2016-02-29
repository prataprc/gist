package main

import "os/exec"
import "fmt"

func main() {
	//cmd := exec.Command("bash", "-c", "ls -R")
	//s, err := cmd.Output()
	//out, err := exec.Command("/bin/sh", "-c", "cd /Users/prataprc/devgo/src/github.com/couchbase/indexing/secondary/tools/n1qlperf/; /Users/prataprc/devgo/src/github.com/couchbase/indexing/secondary/tools/n1qlperf/n1qlperf.sh -cluster 127.0.0.1:9000 -configfile lookup.json -resultfile result.json").CombinedOutput()
	cmd := exec.Command("find", "./", "-name", "*.go")
	cmd.Env = append(cmd.Env, "", "", "", "", "")
	out, err := cmd.CombinedOutput()
	fmt.Println(err)
	fmt.Println(string(out))
}
