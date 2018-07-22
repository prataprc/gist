# Builing the Linux Navigation Tree
#	1. The current version works only for Linux 2.6 Kernel where every
#	   buildable source file is dependant on 
#		.c and .h files
#		CONFIG_*
#		command line build options
#	   These details are available in .*.o.cmd files present for every .c 
#	   that are compiled.
#
# USAGE:
#	nlx	<linux_build_dir> <navigation_dir>

ARCH=i386

nlx_runtime=$HOME/.sky/nlx
nlx_build_list=$HOME/.sky/nlx/build_list
nlx_source_list=$HOME/.sky/nlx/source_list
nlx_stat=$HOME/.sky/nlx/statistics
nlx_tree=$HOME/store/"navigate-"`date +%F-%T`

# Subrouting to copy the source files one by one 
function copy_source 
{
	local per_file=$1
	local list=`echo $per_file | awk -F / '{print $2}'`
	local list=$list" "`echo $per_file | awk -F / '{print $3}'`
	local list=$list" "`echo $per_file | awk -F / '{print $4}'`
	local list=$list" "`echo $per_file | awk -F / '{print $5}'`
	local list=$list" "`echo $per_file | awk -F / '{print $6}'`
	local list=$list" "`echo $per_file | awk -F / '{print $7}'`
	local list=$list" "`echo $per_file | awk -F / '{print $8}'`
	local list=$list" "`echo $per_file | awk -F / '{print $9}'`
	local path="/"

	for dd in $list ; do
		if [ -d "."$path$dd ]; then
			if [ ! -d $nlx_tree$path$dd ]; then
				echo "Creating Directory $dd ..."
				mkdir $nlx_tree$path$dd
			fi
			path=$path$dd"/"
			continue
		fi
		if [ -f "."$path$dd ]; then
			echo "Copying the source file $per_file ..."
			cp $per_file $nlx_tree$path$dd
			return
		fi
		echo "Error $per_file path : $path dd : $dd ..."
	done
}

# Check Whether the required host programs/scripts are available
echo "Checking for Dependencies ..."
if [ `which sr` ]; then
 	echo -e "\tsr command Okay ..."
else
	echo -e "\tsr command Missing ..."
	echo "Exiting ... "; exit 1	# Exit Point
fi

if [ -d $nlx_runtime ]; then
	echo "Using the existing $nlx_runtime Directory ... "
	echo "Removing the old build_list file ..." ; rm $nlx_build_list
	echo "Removing the old source_list file ..." ; rm $nlx_source_list
	echo "Removing the old statistics file ..." ; rm $nlx_stat

else
	mkdir $nlx_runtime
fi

# Create build list containing all the .o files
sr *.o > $nlx_build_list
wc $nlx_build_list
# Create source list containing all the .c & .s files
touch $nlx_source_list
# Create the Navigation Directory
mkdir $nlx_tree
# Create the Statistics file
echo 		"DATE					: "`date` > $nlx_stat
echo		"Source Tree				: "$PWD	  >> $nlx_stat
echo		"Navigation Tree			: "$nlx_tree>>$nlx_stat
echo		"HOME					: "$HOME >> $nlx_stat

build_list=`cat $nlx_build_list`

echo 		"" >> $nlx_stat
echo	"\t------------------------------------------------------" >> $nlx_stat
echo 	"" >> $nlx_stat
echo	"Following files doesnt have a corresponding source file :">> $nlx_stat

cnt_orphans=0;
cnt_asm=0;
cnt_c=0;
for per_file in $build_list ; do
	src_file=`echo $per_file | sed {s/.o$/.c/}`
	if [ -f $src_file ]; then
		echo $src_file >> $nlx_source_list	
		((cnt_c++))
		copy_source $src_file
		continue
	fi
	src_file=`echo $per_file | sed {s/.o$/.C/}`
	if [ -f $src_file ]; then
		echo $src_file >> $nlx_source_list	
		((cnt_c++))
		copy_source $src_file
		continue
	fi
	src_file=`echo $per_file | sed {s/.o$/.s/}`
	if [ -f $src_file ]; then
		echo $src_file >> $nlx_source_list	
		((cnt_asm++))
		copy_source $src_file
		continue
	fi
	src_file=`echo $per_file | sed {s/.o$/.S/}`
	if [ -f $src_file ]; then
		echo $src_file >> $nlx_source_list	
		((cnt_asm++))
		copy_source $src_file
		continue
	fi
	echo -e	"	"$per_file >> $nlx_stat
	((cnt++));
done

# Copy the Include directories
echo "Copying the include files ... "
cp -R include $nlx_tree/
rm -rf $nlx_tree/include/asm-*
cp -R include/asm-i386 $nlx_tree/include/

echo 	"" >> $nlx_stat
echo	"\t------------------------------------------------------" >> $nlx_stat
echo 	"" >> $nlx_stat
echo	"File Statistics : " >> $nlx_stat
echo -e	"	No of .h files		: "`sr *.h | wc -l`>> $nlx_stat
echo -e	"	No of .H files		: "`sr *.H | wc -l`>> $nlx_stat
echo -e	"	No of .c files		: "`sr *.c | wc -l`>> $nlx_stat
echo -e	"	No of .C files		: "`sr *.C | wc -l`>> $nlx_stat
echo -e	"	No of .s files		: "`sr *.s | wc -l`>> $nlx_stat
echo -e	"	No of .S files		: "`sr *.S | wc -l`>> $nlx_stat
echo -e	"	No of .o files		: "`cat $nlx_build_list | wc -l`>> $nlx_stat
echo -e	"	No of .ko files		: "`sr *.ko | wc -l`>> $nlx_stat
echo -e	"	No of compiled C files	: "$cnt_c >> $nlx_stat
echo -e	"	No of compiled ASM files: "$cnt_asm >> $nlx_stat
echo -e "	Header files used	: "`find $nlx_tree -name *.[hH] | wc -l` >> $nlx_stat

echo	"\tTotal no of objects without direct source code : "$cnt >> $nlx_stat


#Generating ctags
echo "Generating the Ctags ... "
cd $nlx_tree
ctags -R .

#Creating a link in the 'dev' directory
rm -rf $HOME/dev/source
ln -s $nlx_tree $HOME/dev/source
