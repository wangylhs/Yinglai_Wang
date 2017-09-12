#!/bin/bash

java -jar final.jar testcases/fma.micro.txt > sol/myfma.out
java -jar final.jar testcases/factorial2.micro.txt > sol/myfac.out
java -jar final.jar testcases/fibonacci2.micro.txt > sol/myfib.out
java -jar final.jar testcases/step4_testcase.micro > sol/mystep41.out
java -jar final.jar testcases/step4_testcase2.micro > sol/mystep42.out
java -jar final.jar testcases/test_adv.micro > sol/myadv.out
java -jar final.jar testcases/test_combination.micro > sol/mycomb.out
java -jar final.jar testcases/test_expr.micro > sol/myexpr.out
java -jar final.jar testcases/test_if.micro > sol/myif.out
java -jar final.jar testcases/test_mult.micro > sol/mymult.out
java -jar final.jar testcases/test_while.micro > sol/mywhile.out
