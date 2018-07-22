list1=a; list2=b

if [ \( diff cbase.sh cs.sh \) -a \( $list1 == $list2 \) ] ; then
    echo "no diff"
else
    echo "diff"
fi
