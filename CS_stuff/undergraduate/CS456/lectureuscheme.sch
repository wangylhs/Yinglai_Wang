;; Litteral
;; --------
5 

;; Symbol
;; ------
'a

;; Boolean
;; -------

#t

(if 1 1 0)

(if #t 1 0)

;; (+ (= 0 0) 1) <- 2 in impcore

;; (+ (= 0 0) 1) <- error in uscheme

;; list of S-exp
;; ('a 'b 'c)

;; list of S-exp (call)
(+ 4 5)


;; Lists
;; -----

'()

'(3 1)

'(3 a)

'(3 'a)

cons

(cons 3 '())

(cons 3 '(4 5))

(cons 3 '(4 (5)))

(car '(4 (5)))

(cdr '(4 (5)))

(car (cons 'a '(c b d)))

(car (cdr (cons 'a '(c b d))))

(cadr (cons 'a '(c b d)))

(null? '(a b))

(null? '())

;; (null? 0) <- It is well defined!

;; Recursion 
;; ---------

(define length (xs)
  (if (null? xs)
      0
      (+ 1 (length (cdr xs)))))

(define rdc (xs)
  (if (null? xs) 
      xs
      (cons (car xs) (rdc (cdr xs)))))


(define rac (xs)
  (if (null? xs) 
    'error
    (if (= (length xs) 1)
	(car xs)
	(rac (cdr xs)))))

(define append (xs ys)
  (if (null? xs) 
      ys
      (cons (car xs) (append (cdr xs) ys))))

;; Accumulators
;; ------------

(define fact (n)
  (if (= n 0)
      1
      (* n (fact (- n 1)))))

(define factaux (n m) 
  (if (= n 0) 
      m
      (factaux (- n 1) (* n m))))

;; ^^^^ Tail recursion! (as efficient as a while loop)

(define fact1 (n) (factaux n 1))

;; ################# 09/12/2014 #################

(define revaux (xs ys) 
  (if (null? xs) 
      ys
      (revaux (cdr xs) (cons (car xs) ys))))

(define rev (xs) (revaux xs '()))

;; Sorting 
;; -------

(define insert (x xs)
  (if (null? xs)
      (list1 x)
      (if (< x (car xs))
	     (cons x xs)
	     (cons (car xs) (insert x (cdr xs))))))

(define insertion_sort (xs)
  (if (null? xs)
      xs
      (insert (car xs) (insertion_sort (cdr xs)))))

;; (define eq_list? (xs ys)
;;   (if (null? xs) 
;;       (null? ys)
;;       (if (null? ys) 
;; 	  #f
;; 	  (and (= (car xs) (car ys)) (eq_list? (cdr xs) (cdr ys))))))

;; pairs
;; -----

(cons 'a 'b)

(pair? (cons 'a 'b))

(pair? (cons 'a '(b)))

(pair? '())

(pair? '(a b c))

(pair? '(a))

;; Is it true that either (null? xs) or (pair? xs)
;; (= #t (or (null? xs) (pair? xs)))

;; When is it true?

;; Association Lists
;; -----------------

(define mk-alist-pair (k a) (list2 k a)) 

(define alist-pair-key (pair) (car pair)) 

(define alist-pair-attribute (pair) (cadr pair))

(define alist-first-key (alist) (alist-pair-key (car alist)))

(define alist-first-attribute (alist) 
  (alist-pair-attribute (car alist))) 

(define bind (k a alist) 
  (if (null? alist) 
      (list1 (mk-alist-pair k a)) 
      (if (equal? k (alist-first-key alist)) 
	  (cons (mk-alist-pair k a) (cdr alist)) 
	  (cons (car alist) (bind k a (cdr alist))))))

(define find (k alist) 
  (if (null? alist) 
      '() 
      (if (equal? k (alist-first-key alist)) 
	  (alist-first-attribute alist) 
	  (find k (cdr alist)))))


(val al (bind 'I 'Ching '()))

(val al (bind 'E 'Coli '()))

(val al (bind 'I 'Magnin '()))

(val fruits 
     '((apple  ((texture crunchy) (color green) ))
       (banana ((texture mushy)   (color yellow)))))

(define property (k p plist)
     (find p (find k plist)))

(define set-property (k p a plist)
     (bind k (bind p a (find k plist)) plist))

(property 'apple 'texture fruits)

(set fruits (set-property 'apple 'color 'red fruits))

(property 'apple 'color fruits)

(define has-property (p a alist) (= (find p alist) a))

(define gather-property (p a plist)
  (if (null? plist)
      '()
      (if (has-property p a (alist-first-attribute plist))
	  (cons (alist-first-key plist) (gather-property p a (cdr plist)))
	  (gather-property p a (cdr plist)))))

(set fruits (set-property 'lemon 'color 'yellow fruits))

(gather-property 'color 'yellow fruits)

;; Local Variables: let
;; --------------------

;; (let x = e in e')

(let ((x (+ 3 1)) 
      (y 2)) 
  (+ x y))

(val x 0)

(let ((x (+ 3 1)) 
      (y 2)) 
  (+ x y))

;; For writing complex expressions!

(let ((x (+ 3 1)) 
      (y 2)) 
  (begin (set x 5) (+ x y)))

(let ((x (+ 3 1)) 
      (y x)) 
  (+ x y))

(let* ((x (+ 3 1)) 
       (y x)) 
  (+ x y))

(val x 'global-x)
(val y 'global-y)

(let ((x 'local-x)
      (y x))
  (list2 x y))

(let*
     ((x 'local-x)
      (y x))
     (list2 x y))

;; letrec
;; ------

(val even?
     (letrec
	 ((odd-test (lambda (n) (not (even-test n))))
	  (even-test
	   (lambda (n)
	     (if (= n 0)
		 #t
		 (odd-test (- n 1))))))
       even-test))


;; First-class functions: lambda
;; -----------------------------

(lambda (x) x)

((lambda (x) x) 5)

((lambda (x) x) (lambda (x) x))

(((lambda (x) x) (lambda (x) x)) 5)

(val id (lambda (x) x))

(id 5)

(id id)

((id id) 5)

((lambda (x y z) (+ x (+ y z))) 1 2 3)

(define apply-n-times (n f x)
  (if (= 0 n)
      x
      (apply-n-times (- n 1) f (f x))))

(define times2 (x) (* 2 x))

(val add (lambda (x) (lambda (y) (+ x y))))

(val add1 (add 1))

(add1 4)

;; ################# 09/15/2014 #################

;; closures
;; --------

(val counter-from
     (lambda (x)
       (lambda () (set x (+ x 1)))))

(val five (counter-from 5))

(val resettable-counter-from
     (lambda (x)
       (list2
	(lambda () (set x (+ x 1)))
	(lambda () (set x 0)))))

(val step  
     (lambda (counter) ((car counter))))

(val reset 
     (lambda (counter) ((cadr counter))))

;; Persistent State
;; ----------------

(val arand 
     (lambda (seed) (mod (+ (* seed 9) 5) 1024)))

(val mk-irand (lambda (arng seed)
                     (lambda () (set seed (arng seed)))))

(val irand (mk-irand arand 1))

(irand)

;; Higher-Order Programming
;; ------------------------

(define o (f g) (lambda (x) (f (g x))))

(define even? (n) (= 0 (mod n 2)))

(val odd? (o not even?))

(val cur_plus (lambda (x) (lambda (y) (+ x y))))

(val add3 (cur_plus 3))

(add3 1)

(val <-curried (lambda (n) (lambda (m) (< n m))))

(val positive? (<-curried 0))

(define curry (f) 
  (lambda (x) (lambda (y) (f x y))))

(define uncurry (f) 
  (lambda (x y) ((f x) y)))

(val zero? ((curry =) 0))
(zero? 0)

(val new+ (uncurry (curry +)))
(new+ 1 4)

;; Higher-order List Programming
;; -----------------------------

(define filter (p? xs)
  (if (null? xs)
      '()
      (if (p? (car xs))
	  (cons (car xs) (filter p? (cdr xs)))
	  (filter p? (cdr xs)))))

(define map (f xs)
  (if (null? xs)
      '()
      (cons (f (car xs)) (map f (cdr xs)))))

(define exists? (p? xs)
  (if (null? xs)
      #f
      (if (p? (car xs))
	  #t
	  (exists? p? (cdr xs)))))

(define all? (p? xs)
  (if (null? xs)
      #t
      (if (p? (car xs))
	  (all? p? (cdr xs))
	  #f)))

(define foldr (op zero xs)
  (if (null? xs)
      zero
      (op (car xs) (foldr op zero (cdr xs)))))

(define foldl (op zero xs)
  (if (null? xs)
      zero
      (foldl op (op (car xs) zero) (cdr xs))))

;; Continuation Passing Style
;; --------------------------

(define find-c (key alist success-cont failure-cont)
  (letrec
      ((search (lambda (alist)
		 (if (null? alist)
		     (failure-cont)
		     (if (equal? key (alist-first-key alist))
			 (success-cont (alist-first-attribute alist))
			 (search (cdr alist)))))))
    (search alist)))

(find-c 'Hello '((Hello Dolly) (Goodnight Irene))
	(lambda (v) (list2 'the-answer-is v))
	(lambda ()  'the-key-was-not-found))

(find-c 'Goodbye '((Hello Dolly) (Goodnight Irene))
	(lambda (v) (list2 'the-answer-is v))
	(lambda ()  'the-key-was-not-found))

(define find-default (key table default)
  (find-c key table (lambda (x) x) (lambda () default)))

(define mk-insertion-sort (lt)
  (letrec (
    (insert (lambda (x xs)
       (if (null? xs)
	   (list1 x)
	   (if (lt x (car xs))
	       (cons x xs)
	       (cons (car xs) (insert x (cdr xs)))))))
    (sort (lambda (xs)
       (if (null? xs)
	   '()
	   (insert (car xs) (sort (cdr xs)))))))
    sort))

(define freq (words)
  (let
      ((add (lambda (word table)
	      (bind word (+ 1 (find-default word table 0)) table)))
       (sort (mk-insertion-sort (lambda (p1 p2) (> (cadr p1) (cadr p2))))))
    (sort (foldr add '() words))))

(freq '(it was the best of times , it was the worst of times ! ))

(define followers (words)
  (letrec
    ((add (lambda (word follower table)
       (bind word
         (add-element follower (find-default word table '()))
	 table)))
     (walk (lambda (first rest table)
	     (if (null? rest)
		 table
		 (walk (car rest) (cdr rest) (add first (car rest) table))))))
    (walk (car words) (cdr words) '())))

(val multi-followers
     (o
      ((curry filter) (lambda (p) (> (length (cadr p)) 1)))
      followers))

(define variable-of (literal)
     (if (symbol? literal)
        literal
        (cadr literal)))

(define binds? (literal alist)
     (find-c (variable-of literal) alist (lambda (_) #t) (lambda () #f)))

(define satisfying-value (literal)
      (symbol? literal))  ; #t satisfies 'x; #f satisfies '(not x)

(define satisfies? (literal alist)
      (find-c (variable-of literal) alist
              (lambda (b) (= b (satisfying-value literal)))
              (lambda () #f)))

(define make-literal-true (lit cur fail succeed)
     (if (satisfies? lit cur)
        (succeed cur fail)
        (if (binds? lit cur)
           (fail)
           (succeed (bind (variable-of lit) (satisfying-value lit)
			  cur) fail))))

(define make-disjunction-true (literals cur fail succeed)
     (if (null? literals)
       (fail)
       (make-literal-true (car literals) cur 
          (lambda () (make-disjunction-true (cdr literals) cur fail succeed))
          succeed)))

(define make-cnf-true (disjunctions cur fail succeed)
     (if (null? disjunctions)
       (succeed cur fail)
       (make-disjunction-true (car disjunctions) cur fail
          (lambda (cur resume)
             (make-cnf-true (cdr disjunctions) cur resume succeed)))))

(define one-solution (formula)
      (make-cnf-true formula '() (lambda () 'no-solution)
                                 (lambda (cur resume) cur)))

(val f '((x y z) ((not x) (not y) (not z)) (x y (not z))))

(one-solution f)


