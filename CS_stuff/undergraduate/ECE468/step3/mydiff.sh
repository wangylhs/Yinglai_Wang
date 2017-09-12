#!/bin/bash

c=1

while [ $c -le 21 ]
do
diff -b -B myout/myout$c.out testcases/output/468/test$c.out
diff -b -B myout/myout$c.out solution/out$c.out
((c++))
done
