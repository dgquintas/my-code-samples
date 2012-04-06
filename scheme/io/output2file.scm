(begin
  (define o (open-output-file "fout.txt"))
  (display "hello" o)
  (write-char #\space o)
  (display 'world o)
  (newline o)

  (close-output-port o))

