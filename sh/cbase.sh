#! /bin/bash

if [ $# == 0 ] ; then
    total=`find ./ | grep -v "/CVS/"| wc -l` 
    dirc=`find ./ -type d | grep -v "/CVS" | wc -l`
    files=`find ./ -type f | grep -v "/CVS/" | wc -l` 
    c_files=`find ./ -name "*.[c]" -type f | wc -l` 
    h_files=`find ./ -name "*.[h]" -type f | wc -l` 
    asm_files=`find ./ -name "*.[s]" -type f | wc -l` 
    Make_files=`find ./ -name "Makefile" -type f | wc -l` 
    make_files=`find ./ -name "makefile" -type f | wc -l`
    exe_files=`find ./ -type f -perm +111 | wc -l`
    echo -n "$dirc dirs $c_files c $h_files h $asm_files asm "
    echo -n $((Make_files + make_files)) make" "
    echo $exe_files exec
    count_files=$((c_files + h_files + asm_files + Make_files + make_files +
    exe_files))
    echo -n "$count_files known files "
    echo and $(( files - count_files )) unknown files
    exit
fi

while getopts fdchsmxu option ; do 
    case $option in
        f|d|x)
            find ./ -type "$option" ;;
        c|h|s)
            find ./ -name "*.$option" ;;
        m)
            find ./ -name "[mM]akefile" -type f ;;
        u)
            find ./ -type f | grep -v "/CVS" | \
                grep -v ".*\.[chs]$" | grep -v "[Mm]akefile" ;;
        *)
            # Search for the variables of the given type
            find ./ -name "*.[ch]" -exec egrep "$1" -Hn {} \; ;;
    esac
done

