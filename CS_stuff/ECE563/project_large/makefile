all:
	gcc -fopenmp -o map_omp map_omp.c
	mpicc -fopenmp -o map_mpi map_mpi.c
clean:
	rm map_omp map_mpi
