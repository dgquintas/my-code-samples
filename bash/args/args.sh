#!/bin/bash

if [ $# -lt 2 ] 
then
 echo lol
 exit 1
fi

echo $0
echo "Number of params: " $#
echo "Number of params: " $BASH_ARGC
echo "1st parameter: " $1
echo "All parameters (@): " $@
echo "All parameters (*): " $*
echo "All parameters (BASH_ARGV): " ${BASH_ARGV[@]}

for i in `seq ${BASH_ARGC}`; do 
  echo $i " -> " ${BASH_ARGV[i-1]};
done

echo "for with \$@"
for i in $@; do
  echo $i;
done

echo "for with \$*"
for i in $*; do
  echo $i;
done

