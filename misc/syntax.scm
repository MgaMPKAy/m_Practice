(define-syntax m-and
  (syntax-rules ()
    ((_) #t)
    ((_ e) e)
    ((_ e1 e2 e3 ...)
     (if e1 (and e2 e3 ...) #f))))

(define-syntax m-or
  (syntax-rules ()
    ((_) #f)
    ((_ e) e)
    ((_ e1 e2 e3 ...)
     (let ((t e1))
       (if t t (or e2 e3 ...))))))

(define m-list?
  (lambda (x)
    (letrec ((race
	      (lambda (h t)
		(if (pair? h)
		    (let ((h (cdr h)))
		      (if (pair? h)
			  (and (not (eq? h t))
			       (race (cdr h) (cdr t)))
			  (null? h)))
		    (null? h)))))
      (race x x))))