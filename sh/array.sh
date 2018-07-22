# !/bin/bash

declare -a list1
list1=`find ./`
for (( count=0 ; ; count++ )) ; do
    echo "$list1[count]"
    exit 0
done
