; Ben Bitdiddle has invented a test to determine whether the interpreter he is
; faced with is using applicative-order evaluation or normal-order evaluation.
; He defines the following two procedures:

(define (p) (p))
;; introduces "p" as a compound procedure. Note that invoking it will 
;; result in a infinite (recursive) loop.

(define (test x y)
  (if (= x 0)
      0
      y))


; Then he evaluates the expression

(test 0 (p))

; What behavior will Ben observe with an interpreter that uses
; applicative-order evaluation? What behavior will he observe with an
; interpreter that uses normal-order evaluation? Explain your answer. (Assume
; that the evaluation rule for the special form if is the same whether the
; interpreter is using normal or applicative order: The predicate expression is
; evaluated first, and the result determines whether to evaluate the consequent
; or the alternative expression.)

;; applicative-order evaluation: evaluate arguments and then apply
;; normal-order evaluation: fully expand (until primitive operators is all
;; there is) and then reduce. Does not evaluate operands until their values
;; are needed
;;
;; Thus:
;; * applicative-order: (test 0 (p))
;;                            0 (p)
;;                            0 (p)
;;                              ... infinite loop while evaluating the (p) arg
;;
;; * normal-order: (test 0 (p)) 
;;                 (if (= 0 0) <- x evaluated to 0 cos needed for test
;;                   0
;;                   (p)) <- (p) never evaluated
;;                 Result: 0
;;
;;
;;
