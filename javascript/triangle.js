var SEMIBASE = 10
var res 
var i = 0
for( var i = 0; i < SEMIBASE; i++ ){
  res = ''
  for(var j = 0; j < (SEMIBASE-i); j++ ){
    res += ' '
  }
  for(var k = 0; k <= 2*i; k++ ){
    res += '#'
  }
  print(res)
}
