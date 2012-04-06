; Observe that our model of evaluation allows for combinations whose operators
; are compound expressions. Use this observation to describe the behavior of
; the following procedure:

(define (a-plus-abs-b a b)
  ((if (> b 0) + -) a b))

; The result of the if will be an operator, which upon being evaluated will
; result in plus if b is positive and minus if b is negative, resulting
; overall in the a-plus-abs-b procedure returning the sum as expected.
; The lesson here is that returned values from expressions can be interpreted
; as operators

