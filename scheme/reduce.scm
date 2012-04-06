(define reduce 
  (lambda (proc lst)
    (let loop ( (x (car lst))
                   (l (cdr lst)) )
      (if (null? l) x
            (loop (apply proc (list x (car l))) (cdr l))))))
    