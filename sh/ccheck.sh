#/bin/bash

# my_files=`find ./bin/ -type f -print | grep -v CVS` ; for name in $my_files ; do cvs diff $name ; done
# my_files=`find ./notes/ -type f -print | grep -v CVS` ; for name in $my_files ; do cvs diff $name ; done
# my_files=`find ./company/ -type f -print | grep -v CVS` ; for name in $my_files ; do cvs diff $name ; done
# my_files=`find ./misc/ -type f -print | grep -v CVS` ; for name in $my_files ; do cvs diff $name ; done
# my_files=`find ./sandbox/ -type f -print | grep -v CVS` ; for name in $my_files ; do cvs diff $name ; done
# my_files=`find ./sh-env/ -type f -print | grep -v CVS` ; for name in $my_files ; do cvs diff $name ; done

cd $HOME/bin/ && cvs diff
cd $HOME/notes/ && cvs diff
cd $HOME/company/ && cvs diff
cd $HOME/misc/ && cvs diff
cd $HOME/sandbox/ && cvs diff
cd $HOME/env/ && cvs diff
