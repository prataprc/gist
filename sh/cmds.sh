# This script finds all the executables that are available for the current
# user and creates data base out of it.
#

database=$HOME/.sky/dbs/cmds
cmd_list=$HOME/.sky/dbs/cmds/cmd_list

no_of_dirs=`echo $PATH | awk -F : '{print NF}'`
((no_of_dirs++))
count=1
while [ $count != $no_of_dirs ] ; do
	dir=`echo $PATH | awk -F : '{print $NF}'`
	cd $dir 
	list=`ls -1`
	echo "Commands in " $dir > $cmd_list
	echo $dir
	echo "" >> $cmd_list
	for cmd in $list ; do
		echo $cmd
		mode=`stat -c %a $cmd`
		echo $mode
		if [ ! -f $cmd ] ; then
			continue
		fi
		mode=`echo $mode | cut -c 1`
		echo $mode
		if [ mode == 7 ] ; then
			echo "\t"$cmd >> $cmd_list
			continue
		fi
		if [ mode == 5 ] ; then
			echo "\t"$cmd >> $cmd_list
			continue
		fi
	done
	echo "" >> $cmd_list
	((count++))
done
