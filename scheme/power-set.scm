#lang racket
(define (power-set L)
  (if (null? L)
      '(())
      (let ((rest (power-set (cdr L))))
        (append (map (lambda (element) (cons (car L) element))
                     rest)
                rest))))

(power-set '(a b c d))