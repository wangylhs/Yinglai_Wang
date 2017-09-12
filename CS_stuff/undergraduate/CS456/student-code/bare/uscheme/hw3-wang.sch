;;Q1
;;1
;;LIST(SEXP)⊆SEXP
;;(S-expr) ::= ((S-espr)*)
;;


;;2(a)
(define counthelp (x xs counter)
    (if (null? xs) counter
        (if (= x (car xs)) (counthelp x (cdr xs) (+ 1 counter)) (counthelp x (cdr xs) counter))
    )
)
(define count (x xs) (counthelp x xs 0))

;;2(b)
(define countall (x xs)
    (if (null? xs)
        0
        (if (not(pair? (car xs)))
            (if (= (car xs) x)
                (+ 1 (countall x (cdr xs)))
                (+ 0 (countall x (cdr xs))))
    (+ (countall x (cdr xs)) (countall x (car xs))))))

;;2(c)
(define mirror (xs)
    (if (null? xs) xs
        (if (pair? (car xs))
        (append (mirror (cdr xs)) (list1(mirror (car xs))))
        (append (mirror (cdr xs)) (list1 (car xs))))))

;;2(d)
(define flatten (xs)
    (if (null? xs) xs
        (if (equal? (car xs) '())
            (append '() (flatten (cdr xs)))
            (if (pair? (car xs))
            (append (flatten (car xs)) (flatten (cdr xs)))
            (append (list1 (car xs)) (flatten (cdr xs)))))))
;;2(e)
(define contig-help (xs ys)
    (if(null? xs) #t
                  (if (= (car xs) (car ys)) (contig-help (cdr xs) (cdr ys))
                  #f)))
(define contig-sublist? (xs ys)
    (if(= (car xs) (car ys)) (contig-help xs ys) (contig-sublist? xs (cdr ys))))
;;2(f)
(define sublist? (xs ys)
    (if(null? xs) #t
                  (if(null? ys) #f
                                (if(= (car xs) (car ys)) (sublist? (cdr xs) (cdr ys))
                                                         (sublist? xs (cdr ys))))))


;;5
(define takewhile (predict? xs)
    (if (predict? (car xs)) (cons (car xs) (takewhile predict? (cdr xs))) '()))
(define dropwhile (predict? xs)
    (if (predict? (car xs)) (dropwhile predict? (cdr xs)) (append xs '())))


;;14
;;(define vector-length (x y)
;;   (let ((+ *)
;;         (* +))
;;     (sqrt (* (+ x x) (+ y y)))))
;;
;;This procedure use "let" changes "+" to "*" operation and changes "*" to "+" operation.
;;"let" creates local variables that do not affect each other.
;;So the last line actually does is (sqrt(+ (* x x) (* y y)))


;;Q2
(define take (n xs)
  (if (null? xs) xs
      (if (= n 0) '()
	  (cons (car xs) (take (- n 1) (cdr xs))))))
(define drop (n xs)
  (if (null? xs) xs
      (if (= n 0) xs
	  (drop (- n 1) (cdr xs)))))

;;Q3
(define zip (xs ys)
  (if (null? xs) xs
      (cons (list2 (car xs) (car ys)) (zip (cdr xs)(cdr ys)))))
(define unzip (xs)
  (if (null? xs) xs
      (list2 (map car xs) (map cadr xs))))

;;Q4
(define merge (xs ys)
  (if (null? xs) ys
      (if (null? ys) xs
	  (if (< (car xs) (car ys)) (cons (car xs) (merge (cdr xs) ys))
	      (cons (car ys) (merge xs (cdr ys)))))))
;;Q5
(define interleave (xs ys)
  (if (null? xs) (if (null? ys) ys (interleave ys xs)) (cons (car xs) (interleave ys (cdr xs)))))








