#! /bin/bash

# Clean all the CVS directory

PNAME=fclean.sh

help ()
{
    echo "$PNAME [-c] [-h]"
    echo -e "\t -c \t clean the CVS directory"
    echo -e "\t -h \t help"
}

while getopts cnh option ; do 
    case $option in
        n)
            find ./ -name "*CVS*" ;;
        c)
            rm -rf `find ./ -name "*CVS*"` ;;
        h)
            help ;;
        *)
            help ;;
    esac
done
