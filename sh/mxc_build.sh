# Initialising the variables
target=$2 ; [ $target ] || { echo "Error : Enter the target "; exit 1; }
export PATH=/opt/montavista/mobilinux/devkit/arm/v6_vfp_le/bin/:$PATH
export CROSS_COMPILE=/opt/montavista/mobilinux/devkit/arm/v6_vfp_le/bin/arm_v6_vfp_le-
export TARGET_PLATFORM_CONFIG=${target}_defconfig
export PLATFORM=$(echo $target | sed 'y/abcdefghijklmnopqrstuvwxyz/ABCDEFGHIJKLMNOPQRSTUVWXYZ/')
export LINUXPATH=/home/pratap/LINUX2.6/linux			# On using different linux tree change here 
export KBUILD_OUTPUT=~/LINUX2.6/kbuild/${target}		# On using different linux tree change here 

if [ $target == imx27ads ] ; then
	export PATH=/opt/mtwk/usr/local/gcc-3.4.3-glibc-2.3.4/arm-linux/bin:$PATH
	export CROSS_COMPILE=/opt/mtwk/usr/local/gcc-3.4.3-glibc-2.3.4/arm-linux/bin/arm-linux-
fi

is_config=""

while getopts fckytnh options ; do
	if [ "$options" == f ] ; then
		make ARCH=arm CROSS_COMPILE=${CROSS_COMPILE} menuconfig
		is_config=y
	fi
	if [ "$options" == c ] ; then
		make mrproper 
		make -k clean 
		make ARCH=arm CROSS_COMPILE=${CROSS_COMPILE} $TARGET_PLATFORM_CONFIG
	fi
	if [ "$options" == k ] ; then
		if [ "$is_config" == "y" ] ; then
			: #export TARGET_PLATFORM_CONFIG=$KBUILD_OUTPUT/.config
		fi
		make ARCH=arm CROSS_COMPILE=${CROSS_COMPILE} zImage
	fi
	if [ "$options" == y ] ; then
		# On using different linux tree change here 
		su -c "cp /home/pratap/LINUX2.6/kbuild/${target}/arch/arm/boot/zImage /tftpboot/ptp_$target"
	fi
	if [ "$options" == t ] ; then
		cd $LINUXPATH/../misc/ 
		make ARCH=arm PLATFORM=${PLATFORM} CROSS_COMPILE=${CROSS_COMPILE} KBUILD_OUTPUT=${KBUILD_OUTPUT} LINUXPATH=${LINUXPATH}
	fi
	if [ "$options" == n ] ; then
		cd $LINUXPATH/../misc/ 
		make ARCH=arm PLATFORM=${PLATFORM} CROSS_COMPILE=${CROSS_COMPILE} KBUILD_OUTPUT=${KBUILD_OUTPUT} LINUXPATH=${LINUXPATH} clean
	fi
	if [ "$options" == h ] ; then
		echo "${0##*/} [-fckyth] i30030ads | i30030evb | imx31ads | imx27ads | mxc30030ads | mxc30030evb | mxc91131evb | mxc27530evb" 
		printf "\t %s \n\t %s \n\t %s \n\t %s \n\t %s \n\t %s \t\n %s \n" \
						"f configure the kernel" \
						"c clean" \
						"k build kernel" \
						"y copy the built image" \
						"t build the unit test" \
						"n clean the unit test" \
						"h this help "
		echo ""
		printf "The options should be given in the proper sequence \n"
	fi
done
