#!/bin/bash

java -cp lib/antlr.jar:classes/ Micro testcases/input/step4_testcase.micro > my1.out
java -cp lib/antlr.jar:classes/ Micro testcases/input/step4_testcase2.micro > my2.out
java -cp lib/antlr.jar:classes/ Micro testcases/input/test_adv.micro > myadv.out
java -cp lib/antlr.jar:classes/ Micro testcases/input/test_if.micro > myif.out
java -cp lib/antlr.jar:classes/ Micro testcases/input/test_while.micro > mywhile.out
