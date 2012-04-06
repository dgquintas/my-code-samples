for k in `seq 672 -16 16`; do 
  maxMN=$(expr \( 512 \* 1024 \) \/ \(  $k \* 4  \))
  maxMN=$(expr $maxMN - \( $maxMN \% 5 \))
  let kEnd=$maxMN/4
  for mn in `seq $maxMN -5 $kEnd`; do 
    echo -n "$k $mn "; 
    let k2=$k*2; 
    ./a.out $k2 $k2 $k2 $k $mn 2; 
  done; 
  echo ""; 
done
