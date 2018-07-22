#################### GENERIC FUNCTIONS ########################################
##### The functions are designed such a way that they are modular and #########
##### can be re-used.												  #########	
###############################################################################

# list_recur function lists all the files inside the directory recursively in
# depth first fashion. The list is sent to the std. output
#
# Parameter1:	Options -h (h - hidden)
# Parameter2:	Base Directory
#
# Return	:	Lists all the files (based on the -h option) recursively
# 				starting from the base directory

list_recur() {
	# Initialise the local variables (similar to static)
	local this_list=""
	local this_dir_list=""
	while getopts hs option ; do
		if [ "$option" == "h" ] ; then
			is_hidden="-h"
		elif [ "$option" == "s" ] ; then
			is_sym="-s"
		fi
	done
	shift $(( OPTIND - 1 ))
	if [ "$is_hidden" = "-h" ] ; then
		this_list=$(ls -a $1)
	fi
	# Listing Loop, all the files in the directory are outputed in the
	# standard output and the directory list is collected
	for file in $this_list ; do
		if [ "$file" == "." -o "$file" == ".." ] ; then
			continue;
		fi
		if [ \( -e "$1/$file" \) -a \( -f "$1/$file" \) ] ; then
			echo "${1%/}/$file"
		fi
		if [ \( -e "$1/$file" \) -a \( -d "$1/$file" \) ] ; then
			this_dir_list="$this_dir_list ${1%/}/$file "
		fi
	done
	# Recursive Engine
	for dir in $this_dir_list ; do
		if [ \( -L "$dir" \) -a \( "$is_sym" != "s" \) ] ; then
			continue;
		fi
		list_recur $is_hidden $is_sym $dir	
	done
}
