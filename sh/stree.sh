# Variables and its initialisation.
build_source=$1
linux_source=$2
dest_source=$3

curr_dir=$build_source
complete_list=""

# validate input parameters
if [ ! -d "$1" ] ; then
	echo "Build Source parameter is not correct"
	echo "<usage>"
	echo "list_recur [-h] build_source linux_source dest_source"
fi
if [ ! -d "$2" ] ; then
	echo "Linux Source parameter is not correct"
	echo "<usage>"
	echo "list_recur [-h] build_source linux_source dest_source"
fi
if [ ! -d "$3" ] ; then
	echo "Destination Source directory is not present ... "
	echo "Creating $3 ..."
	mkdir $3
fi

# Source the utility functions
source list_recur.sh

# process the files one by one. The rules of processing is as
# follows.
#	1. For every .o or .cmd file there should be a corresponding .cmd or .o
#	   file and a corresponding source (.s, .S, .c) file.
#	2. Files that are present in the build tree but not in the source tree
#
# Parameters: 	file1 file2 file3 .... filen
#				The files are expected to be with obsolute path.
#
# Return	:	The built source files (*.c, *.s, *.S) are listed in
# 				standard output. 
#				All the other files present in the build directory are listed 
#				in standard	error.

analyse_list() {
	for file in "$@" ; do
		# Just the file name
		just_file=${file##*/}
		# Just the extension
		ext_name=${just_file##*\.}	
		is_cmd="N"	
		is_obj="N"	
		is_source="N"	
		
		if [ "$ext_name" == o ] ; then
			# It is an object file 
			o_file=$file
			cmd_file=${file%/*}/.${just_file}.cmd
			c_file=$linux_source/${file#$build_source}
		elif [ "$ext_name" == cmd ] ; then
			# It is a command file
			cmd_file=$file
			o_file=${file%/*}/${just_file#\.}
			o_file=${o_file%cmd}o
			c_file=$linux_source/${o_file#$build_source}
		else 
			echo "$file U" >&2
			continue
		fi
		c_file=${c_file%\.o}.c
		s_file=${c_file%\.c}.s
		S_file=${c_file%\.c}.S

		if [ -f "$o_file" ] ; then
			is_o="Y"
		fi
		if [ -f "$cmd_file" ] ; then
			is_cmd="Y"
		fi
		if [ -f "$c_file" ] ; then
			is_source="Y"
			s_file=$c_file
		fi
		if [ -f "$s_file" ] ; then
			is_source="Y"
		fi
		if [ -f "$S_file" ] ; then
			is_source="Y"
			s_file=$S_file
		fi

		if [ "$is_source" == "Y" ] ; then
			echo "$s_file"
		fi
		if [ "$is_o$is_source$is_cmd" != "YYY" ] ; then
			echo "$file $is_o $is_cmd $is_source" >&2	
		fi
	done
}

list_recur -h $curr_dir >> $3/stree.list
complete_list=$(cat $dest_source/stree.list)
analyse_list $complete_list  2>$3/issues.list >$3/s.list
