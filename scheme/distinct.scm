(define x-not-in-list 
  (lambda (x cdrl)
        (let loop ((l cdrl))
          (if (null? l) #t
              (if (eqv? x (car l)) #f
                  (loop (cdr l)))))))
              
(define distinct? 
  (lambda (l)
    (let loop ((l l))
      (if (null? l) #t
          (if (x-not-in-list (car l) (cdr l)) (loop (cdr l))
              #f)))))
            
  