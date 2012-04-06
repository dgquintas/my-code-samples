LS='ls /'
CMD='wc -l '

#echo $LS "|" $CMD
$LS | $CMD 


fifo=`mktemp`
mkfifo $fifo

