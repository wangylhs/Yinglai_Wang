osx_omp:
	g++-4.9 omp.cpp -o omp -fopenmp -std=c++11

ecegrid_omp:
	g++ omp.cpp -o omp -fopenmp -std=c++0x

test_omp:
	./run_test_omp.sh

osx_mpi:
	mpic++ -fopenmp mpi.cpp -o mpi -std=c++11

ecegrid_mpi:
	mpic++ -fopenmp mpi.cpp -o mpi -std=gnu++0x

test_mpi:
	./run_test_mpi.sh

osx_maketest:
	make osx_mpi
	make test_mpi

ece_maketest:
	make ecegrid_mpi
	make test_mpi
