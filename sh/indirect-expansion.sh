#/bin/bash

var=hello
var1=var

echo ${!var1} ${is_set:-$var}
