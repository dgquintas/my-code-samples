#!/bin/bash

func() {
  for param in $*; do
    printf "Passed param '%s' to function '%s'\n" $1 ${FUNCNAME[0]}
  done
  printf "There's a total of %d params passed to this func\n" $#
}




func "foo" "bar" "lol"

func 
