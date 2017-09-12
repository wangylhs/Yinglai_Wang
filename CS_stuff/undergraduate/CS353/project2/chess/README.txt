The attached file contains test cases I have used before and a script to test by running the scheduler multiple times.
test.sh will execute scheduler multiple times and compare the results. test.sh will keep running infinitely until it finds a different output.
For each iteration, test.sh will print out iteration number. So you can let test.sh run till the number reaches 100, 200 or some large number.
If test.sh stops before that, the scheduler is incorrect.

Next, you can check whether they implement lock and unlock semantics correctly by checking the output.

test.sh use run.sh script that I gave to them with the code template. Put test.sh and test cases into the same directory as run.sh and their code, and run './test.sh [executable]'.
For example, after you compile sample1-1.c and generate sample1-1 executable, you can run ./test.sh ./sample1-1
Make sure both run.sh and test.sh files have execute permission. If run.sh is missing, you can use one from chess.tar.gz in project web page.

