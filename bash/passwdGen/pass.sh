#!/bin/sh

ALPHABET="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"

if [ $# -ne 1 ]; then
  echo "Usage: $0 <length of the passwd to generate>"
  exit 1
fi

L="$1"
PASS=""
for i in `seq $L`; do
  PASS=$PASS${ALPHABET:(($RANDOM%${#ALPHABET})):1}
done

echo $PASS

exit


