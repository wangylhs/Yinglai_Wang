(class Integer Number
    () ; abstract class
    (method div: (n) (subclassResponsibility self))
    (method mod: (n) (- self (* n (div: self n))))
    (method gcd: (n) (if (= n (coerce: self 0)) [self] [(gcd: n (mod: self n))]))
    (method lcm: (n) (* self (div: n (gcd: self n))))
    
(method asFraction () (num:den:  Fraction self 1))
(method asFloat    () (mant:exp: Float    self 0))
(method asInteger  () self)
(method coerce: (aNumber) (asInteger aNumber))
(method reciprocal () (num:den: Fraction 1 self)) 
(method / (aNumber) (/ (asFraction self) aNumber))
(method timesRepeat: (aBlock) (locals count)
    (ifTrue: (negative self) [(error: self #negative-repeat-count)])
    (set count self)
    (while [(!= count 0)]
         [(value aBlock)
          (set count (- count 1))]))
)

(class Fraction Number
    (num den)
    (class-method num:den: (a b) (initNum:den: (new self) a b))
    (method initNum:den: (a b) ; private
        (setNum:den: self a b)
        (signReduce self)
        (divReduce self))
    (method setNum:den: (a b) (set num a) (set den b) self) ; private
    
(method signReduce () ; private
    (ifTrue: (negative den)
        [(set num (negated num)) (set den (negated den))])
    self)

(method divReduce () (locals temp) ; private
    (if (= num 0)
        [(set den 1)]
        [(set temp (gcd: (abs num) den))
         (set num  (div: num temp))
         (set den  (div: den temp))])
    self)
(method num () num)
(method den () den)
(method = (f)
    (and: (= num (num f)) [(= den (den f))]))
(method < (f)
    (< (* num (den f)) (* (num f) den)))
(method negated () (setNum:den: (new Fraction) (negated num) den))
(method * (f)
    (divReduce
        (setNum:den: (new Fraction)
                        (* num (num f))
                        (* den (den f)))))
(method + (f) (locals temp)
    (set temp (lcm: den (den f)))
    (divReduce
        (setNum:den: (new Fraction)
                     (+ (* num (div: temp den)) (* (num f) (div: temp (den f))))
                     temp)))
(method reciprocal ()
   (signReduce (setNum:den: (new Fraction) den num)))
(method print () (print num) (print #/) (print den) self)
(method asInteger  () (div: num den))
(method asFloat    () (/ (asFloat num) (asFloat den)))
(method asFraction () self)
(method coerce: (aNumber) (asFraction aNumber))
(method negative         () (negative num))
(method positive         () (positive num))
(method strictlyPositive () (strictlyPositive num))
)