# !/bin/bash

if [ -z $1 ] || [ -z $2 ] ; then
    echo "mdiff.sh <dir1> <dir2>"
    exit 0
fi

while getopts i option ; do 
    case $option in 
        i)
        chk_lower="yes";;
        d)
    esac
    shift
done

cd $1 ; list1=`find ./ | sort` ; cd -
cd $2 ; list2=`find ./ | sort` ; cd -

echo "Starting to differentiat $1 and $2 ..."

for file in $list1 ; do
    if [ "$chk_lower" == "yes" ] ; then
        file_lower=`echo $file | tr [A-Z] [a-z]`
    else 
        file_lower=$file
    fi
    for search in $list2 ; do
        if [ "$chk_lower" == "yes" ] ; then
            search_lower=`echo $search | tr [A-Z] [a-z]`
        else 
            search_lower=$search
        fi
        
        if [ "$file_lower" == "$search_lower" ] ; then
            if [ -d "$1/$file" ] ; then
                continue 2;
            fi
            if diff "$1/$file" "$2/$search" > /dev/null ; then
                continue 2;
            else
                echo "$file $search" >> .diff
                continue 2;
            fi
        fi
    done
    # The file is not found in the second list 
    if [ -d "$1/$file" ] ; then
        echo "$file/ #" >> .diff
    else
        echo "$file #" >> .diff
    fi
done

for file in $list2 ; do
    if [ "$chk_lower" == "yes" ] ; then
        file_lower=`echo $file | tr [A-Z] [a-z]`
    else 
        file_lower=$file
    fi
    for search in $list1 ; do
        if [ "$chk_lower" == "yes" ] ; then
            search_lower=`echo $search | tr [A-Z] [a-z]`
        else 
            search_lower=$search
        fi
        if [ "$file_lower" == "$search_lower" ] ; then
            continue 2;
        fi
    done
    # The file is not found in the second list 
    if [ -d "$2/$file" ] ; then
        echo "# $file/" >> .diff
    else
        echo "# $file" >> .diff
    fi
done
