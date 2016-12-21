package main

import (
	"log"
	"os/exec"
	"time"
)

func main() {
	cmd := exec.Command("sleep", "500")
	err := cmd.Start()
	if err != nil {
		log.Fatal(err)
	}
	log.Printf("Waiting for command to finish...")
	time.Sleep(10 * time.Second)
	err = cmd.Wait()
	log.Printf("Command finished with error: %v", err)
}
