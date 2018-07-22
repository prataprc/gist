#!/bin/bash
scriptpath=$(dirname $(dirname $0))
echo $scriptpath
case $scriptpath in 
  ./*)  echo `pwd` ;;
   * )  dirname $scriptpath
esac
