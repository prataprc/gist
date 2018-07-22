# !/bin/bash

all_name=`grep -v -e "^#.*" "$1"`
for file in $all_name ; do
    cp $file "$2"
    echo "copied $file"
done
