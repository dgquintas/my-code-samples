; Define a procedure that takes three numbers as arguments and returns the sum
; of the squares of the two larger numbers.

(define (sum-of-square-of-two-largest x y z)
 (define (square x) (* x x))
 (define (min-2 x y) (if (< x y) x y ))
 (define (min-3 x y z) (min-2 (min-2 x y) z))
 (- 
  (+ (square x) (square y) (square z))
  (square (min-3 x y z))
 ))

(sum-of-square-of-two-largest 1 2 3) ; 13
(sum-of-square-of-two-largest 3 5 1) ; 34
(sum-of-square-of-two-largest 1 1 1) ; 2
(sum-of-square-of-two-largest -1 -2 3) ; 10






