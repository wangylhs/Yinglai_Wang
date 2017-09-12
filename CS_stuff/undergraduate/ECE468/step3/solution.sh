#!/bin/bash
c=1
while [ $c -le 21 ]
do
java -jar step3_468.jar testcases/input/test$c.micro > solution/out$c.out
((c++))
done
