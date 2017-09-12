(class Array SequenceableCollection
    () ; representation is primitive
    (class-method new: primitive arrayNew:)
    (class-method new () (error: self #size-of-Array-must-be-specified))

;;implement method from
	    (class-method from: (aCollection) (locals arr index)
	    	(class-method from: (aCollection) (locals arr index) 
        	(set arr (new: Array (size aCollection)))
        	(set index 1)
        	(do: aCollection (block (x) 
            	     (at:put: arr index x)
            	     (set index (+ index 1))))
        	arr ; finally, return the new array)



    (method size      primitive arraySize)
    (method at:       primitive arrayAt:)
    (method at:put:   primitive arrayAt:Put:)
    (method species   () Array)
    (method printName () nil) ; names of arrays aren't printed
    
;;;usm.nw:5130
(method add:             (x)   (fixedSizeError self))
(method remove:ifAbsent: (x b) (fixedSizeError self))
(method fixedSizeError   ()    (error: self #arrays-have-fixed-size))
;;;usm.nw:5137
(method select:  (_) (error: self #select-on-arrays-not-implemented))
(method collect: (_) (error: self #collect-on-arrays-not-implemented))
;;;usm.nw:5143
(method firstKey () 1)
(method lastKey  () (size self))
(method do: (aBlock) (locals index)
    (set index (firstKey self))
    (timesRepeat: (size self)
       [(value aBlock (at: self index))
        (set index (+ index 1))]))
;;;usm.nw:5120
)