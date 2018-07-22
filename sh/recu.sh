#!/bin/bash

rec () {
	echo hello
}

cd "$1" && rec "$1/a" && echo "done"

