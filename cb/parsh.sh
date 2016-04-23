#!/bin/bash

#if [ "$1" = "" ]; then
#  echo 'Usage: cluster_ssh "ip1 ip2 ip3..." "command"'
#  exit 0
#fi
#
#for i in $1; do
#  echo "Running on $i: $2"
#  #sshpass -p couchbase ssh -q -o "StrictHostKeyChecking no" -o "UserKnownHostsFile /dev/null" root@$i "$2"
#  ssh -q -o "StrictHostKeyChecking no" -o "UserKnownHostsFile /dev/null" prataprc@$i "$2"
#done

if [ "$1" = "" ]; then
  echo 'Usage: cluster_ssh "ip1 ip2 ip3..." "command"'
  exit 0
fi

for i in $1; do
  echo "$i: Running $2"
  (sshpass -p couchbase ssh -q -o "StrictHostKeyChecking no" -o "UserKnownHostsFile /dev/null" root@$i "$2" 2>&1 | sed "s/^/$i: /") &
  #(ssh -q -o "StrictHostKeyChecking no" -o "UserKnownHostsFile /dev/null" couchbase@$i "$2" 2>&1 | sed "s/^/$i: /") &
done

wait
