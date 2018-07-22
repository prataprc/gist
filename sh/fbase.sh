#!/bin/bash

# Build and analyse the file database

# FIXME : Check whether the script has root permissions to 
# read into the directory
base_dir=$1
if [ -z "$base_dir" ] ; then
	base_dir="/"
fi

if [ ! -d "$base_dir" ] ; then
	echo "Invalid Directory ..."
	exit 1
fi

dbdir=$HOME/.dbase
if [ ! -d "$dbdir" ] ; then
    if ! mkdir "$dbdir" ; then
        echo "Error creating the $dbdir ..." 1>&2
        exit 1
    fi
fi

# create the data base file for the mentioned base directory
dbfile="$dbdir/${1##*/}"
echo "The data file $dbfile will be created "
touch "$dbfile"

# FIXME : Check if the database file already exists and update it, instead of
# creating a new file.

file_engine () {
	local dlist=$(ls -a )
	for name in $dlist ; do
		if [ "$name" == "." ] ||  [ "$name" == ".." ] ; then 
			continue;
		fi
		name="${1%%/}/$name"
		file "$name" >> $dbfile
		if [ -d "$name" ] ; then
			cd "$name" && file_engine "$name" && cd ..
		fi
	done
}

cd $base_dir && file_engine $base_dir
