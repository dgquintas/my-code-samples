(define amb-fail '*)

(define initialize-amb-fail
  (lambda ()
    (set! amb-fail
      (lambda ()
        (error "amb tree exhausted")))))

(initialize-amb-fail)

(define-macro amb
  (lambda alts...
    `(let ((+prev-amb-fail amb-fail))
       (call/cc
        (lambda (+sk)

          ,@(map (lambda (alt)
                   `(call/cc
                     (lambda (+fk)
                       (set! amb-fail
                         (lambda ()
                           (set! amb-fail +prev-amb-fail)
                           (+fk 'fail)))
                       (+sk ,alt))))
                 alts...)

          (+prev-amb-fail))))))

(define assert
  (lambda (pred)
    (if (not pred) (amb))))


(define choose-color
  (lambda ()
    (amb 'red 'yellow 'blue 'white)))

(define color-europe
  (lambda ()

    ;choose colors for each country
    (let ((p (choose-color)) ;Portugal
          (e (choose-color)) ;Spain
          (f (choose-color)) ;France
          (b (choose-color)) ;Belgium
          (h (choose-color)) ;Holland
          (g (choose-color)) ;Germany
          (l (choose-color)) ;Luxemb
          (i (choose-color)) ;Italy
          (s (choose-color)) ;Switz
          (a (choose-color)) ;Austria
          )

      ;construct the adjacency list for
      ;each country: the 1st element is
      ;the name of the country; the 2nd
      ;element is its color; the 3rd
      ;element is the list of its
      ;neighbors' colors
      (let ((portugal
             (list 'portugal p
                   (list e)))
            (spain
             (list 'spain e
                   (list f p)))
            (france
             (list 'france f
                   (list e i s b g l)))
            (belgium
             (list 'belgium b
                   (list f h l g)))
            (holland
             (list 'holland h
                   (list b g)))
            (germany
             (list 'germany g
                   (list f a s h b l)))
            (luxembourg
             (list 'luxembourg l
                   (list f b g)))
            (italy
             (list 'italy i
                   (list f a s)))
            (switzerland
             (list 'switzerland s
                   (list f i a g)))
            (austria
             (list 'austria a
                   (list i s g))))
        (let ((countries
               (list portugal spain
                     france belgium
                     holland germany
                     luxembourg
                     italy switzerland
                     austria)))

          ;the color of a country
          ;should not be the color of
          ;any of its neighbors
          (for-each
           (lambda (c)
             (assert
              (not (memq (cadr c)
                         (caddr c)))))
           countries)

          ;output the color
          ;assignment
          (for-each
           (lambda (c)
             (display (car c))
             (display " ")
             (display (cadr c))
             (newline))
           countries))))))

(color-europe)
