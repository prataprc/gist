# !/bin/bash

all_size=`m68k-unknown-linux-gnu-objdump -h *.o | grep "\.data" | cut -d" " -f 13`
total=0;
for each_size in $all_size ; do
    s=`echo 0x$each_size`
    total=$(( total + s ))
done
echo $total
