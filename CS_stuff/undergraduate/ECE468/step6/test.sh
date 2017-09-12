#!/bin/bash

java -cp lib/antlr.jar:classes/ Micro fma.micro.txt > myfma.out
java -cp lib/antlr.jar:classes/ Micro factorial2.micro.txt > myfac.out
java -cp lib/antlr.jar:classes/ Micro fibonacci2.micro.txt > myfib.out

