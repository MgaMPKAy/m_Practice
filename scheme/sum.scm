(define m-sum
  (lambda (from to func)
    (if (> from to)
	0
	(+ (func from) (m-sum (+ from 1) to  func)))))

(define m-square
  (lambda (x)
    (* x x)))

(define m-cube
  (lambda (x)
    (* x x x)))

(define (sum L)
  (cond ((eq? L '()) 0)
        ((eq? (cdr L) '()) (car L))
        (#t (+ (car L)(sum (cdr L))))))
(sum '(1 2 3))