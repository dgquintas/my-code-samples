package transcendental 

import "math"

var Pi float64
//there may be any number of init()'s in each 
//source file. They are always executed in a 
//single-thread env. 
func init() {
    Pi = 4*math.Atan(1)
}

