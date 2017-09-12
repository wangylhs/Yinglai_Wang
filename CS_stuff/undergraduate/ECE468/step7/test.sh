#!/bin/bash

java -cp lib/antlr.jar:classes/ Micro testcases/fma.micro.txt > myout/myfma.out
java -cp lib/antlr.jar:classes/ Micro testcases/factorial2.micro.txt > myout/myfac.out
java -cp lib/antlr.jar:classes/ Micro testcases/fibonacci2.micro.txt > myout/myfib.out
java -cp lib/antlr.jar:classes/ Micro testcases/step4_testcase.micro > myout/mystep41.out
java -cp lib/antlr.jar:classes/ Micro testcases/step4_testcase2.micro > myout/mystep42.out
java -cp lib/antlr.jar:classes/ Micro testcases/test_adv.micro > myout/myadv.out
java -cp lib/antlr.jar:classes/ Micro testcases/test_combination.micro > myout/mycomb.out
java -cp lib/antlr.jar:classes/ Micro testcases/test_expr.micro > myout/myexpr.out
java -cp lib/antlr.jar:classes/ Micro testcases/test_if.micro > myout/myif.out
java -cp lib/antlr.jar:classes/ Micro testcases/test_mult.micro > myout/mymult.out
java -cp lib/antlr.jar:classes/ Micro testcases/test_while.micro > myout/mywhile.out





