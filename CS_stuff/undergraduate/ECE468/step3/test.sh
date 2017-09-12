#!/bin/bash
c=1
while [ $c -le 21 ]
do
	java -cp lib/antlr.jar:classes/ Micro testcases/input/test$c.micro > myout/myout$c.out
	((c++))
done
