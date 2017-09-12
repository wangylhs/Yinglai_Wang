#!/bin/bash

./run.sh $* > test1

x=0
y=0
while [ $x -eq 0 ]
do
./run.sh $* > test2

cmp test1 test2
x=$?
y=$((y+1))
echo $y
done
