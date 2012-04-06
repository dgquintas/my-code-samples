/* Write a package to implement it. There
should be a function to get the next value.
(You don't have structs yet; can you find a
way to save state without globals?) But
instead of addition, make the operation
settable by a function provided by the user.
Integers? Floats? Strings? Up to you. */

package fibo

type Operator func(a,b int64) int64

func Next() func(Operator) (int,int64)  {
    var n int = 1
    var fn_1, fn int64 = 0, 1

    return func(op Operator) (int,int64) {
        n++
        fn_1, fn = fn, op(fn_1, fn)
        return n,fn
    }
}




