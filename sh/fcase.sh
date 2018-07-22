# !/bin/bash
# This program converts all the filenames from lower case to upper case.
# 
# Directory names are left as is.

PNAME=fcase.sh

help ()
{
    echo "$PNAME [-h] [-r]"
}

all_files=`ls -1 $1`

while getopts rh option ; do 
    case $option in
        r)
            all_files = find ./ -type f
        h)
            help
        *)
            # Search for the variables of the given type
            find ./ -name "*.[ch]" -exec egrep "$1" -Hn {} \; ;;
    esac
done

for file in $all_files ; do
    mv $file `echo $file | tr [A-Z] [a-z]`
done
