#!/bin/bash

global=first

func () {
set second ${!1}
echo ${1} ${!1}
}

func global
echo outside $global
