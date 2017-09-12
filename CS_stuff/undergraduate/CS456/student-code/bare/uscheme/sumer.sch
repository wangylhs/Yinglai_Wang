(val sumer (lambda (xs) (foldr + 0 
			       (lambda (xs) (map (lambda (y) (foldr + 0 y))(map (lambda (x) (filter number? x) xs)))))))
