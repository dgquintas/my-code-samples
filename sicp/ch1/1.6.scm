; Alyssa P. Hacker doesn't see why if needs to be provided as a special form.
; ``Why can't I just define it as an ordinary procedure in terms of cond?'' she
; asks. Alyssa's friend Eva Lu Ator claims this can indeed be done, and she
; defines a new version of if:

(define (new-if predicate then-clause else-clause)
  (cond (predicate then-clause)
        (else else-clause)))

; Eva demonstrates the program for Alyssa:

(new-if (= 2 3) 0 5)
;5

(new-if (= 1 1) 0 5)
;0

; Delighted, Alyssa uses new-if to rewrite the square-root program:

(define (sqrt-iter guess x)
  (display guess)
  (display "\n")
  (display x)
  (display "\n\n")
  (new-if (good-enough? guess x)
          guess
          (sqrt-iter (improve guess x)
                     x)))
(define (improve guess x)
  (average guess (/ x guess)))

(define (average x y)
  (/ (+ x y) 2))

(define (good-enough? guess x)
  (< (abs (- (square guess) x)) 0.001))


; What happens when Alyssa attempts to use this to compute square roots? Explain.

;; It'll, for every invocation of "sqrt-iter", calculate the complete answer, which
;; is utterly inefficient, obviously. This is because "new-if" is not a special form,
;; even if it evaluates to one. Therefore, both its arguments will be evaluated 
;; before the operator ("new-if") is. 
