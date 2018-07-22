#! /bin/bash

count=`grep -c "" $1`
for (( off=1; off <= count ; off++ )) ; do
    file=`head -n $off $1 | tail -n 1`
    cp "$file" "$2"
    #echo  $off
done
