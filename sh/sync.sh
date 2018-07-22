#! /bin/bash
# This program takes in two directories as arguments and attempts to 
# synchronise the files recursively

if [ ! -d $1 ] ; then
	echo "sorry the directory $1 does not exist"	
fi

if [ ! -d $2 ] ; then
	echo "sorry the directory $2 does not exist"	
fi

comp_file () {
}

sync_dir () {
	local dir1=$1
	local dir2=$2
	cd "$dir1"
	local dlist1=`ls -1 $dir1`

	for file1 in "$dlist1" ; do
		file2="${dir2%%/}/$file1"
		if [ -f "$file1" ] ; then
			if [ -f "$file2" ] ; then
				comp_file $file1 $file2
			else 
				cp file1 file2
			fi
		elif [ -d "$file1" ] ; then
			sync_dir `pwd`/$file1 $dir2/$file1
		fi
	done
}
