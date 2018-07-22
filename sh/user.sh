#! /usr/bin/bash

echo "Please Select your Option"
echo "1. Reboot Activity "
echo "2. Login Activity "
echo "3. Disk Activity "
echo "4. User Home directories "
echo "5. CPU Activity"

read SEL


uhome() {

typeset -i NEW
NEW=1
echo UID,  USER,  HOME,  SIZE
for UIDVAR in $(cut -d: -f3 /etc/passwd )
do
UVAR=$(sed -n "`echo $NEW`p" /etc/passwd | cut -d: -f1 - )
HVAR=$(sed -n "`echo $NEW`p" /etc/passwd | cut -d: -f6 - )

if [ $UIDVAR -ge 99 ]
then
        if [ $UIDVAR -le 60000 ]
        then
                SVAR=$(du -sh $HVAR | cut -f1 - )
                echo $UIDVAR, $UVAR, $HVAR, $SVAR
                fi
        fi
NEW=$NEW+1

done
} 

cpuact()
{
SAROP=$(sar 1 1)
USERACT=$(echo "$SAROP" | sed -n 5p | cut -c12-19 -   ) 
SYSACT=$(echo "$SAROP" | sed -n 5p | cut -c20-27 -   ) 
WAITBIO=$(echo "$SAROP" | sed -n 5p | cut -c28-35 -   )
IDLEACT=$(echo "$SAROP" | sed -n 5p | cut -c36-44 -   ) 

echo "		CPU Activity"
echo "          "

echo " Activity	          Percentage(%) "
echo "				"
	
echo "User Activity         = $USERACT"
echo "System Activity       = $SYSACT "
echo "Waiting for Block I/O = $WAITBIO" 
echo "Idle                  = $IDLEACT"
}	

case "$SEL" in

	1) last reboot ;;
	2) last | grep -v reboot ;; 
	3)  df -kh | grep /dev/dsk ;;
        4) uhome ;; 
        5) cpuact ;;  
esac

