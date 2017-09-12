echo $(ls -xS docs/*.txt) | xargs mpiexec -n 1 ./mpi_test
echo $(ls -xS docs/*.txt) | xargs mpiexec -n 2 ./mpi_test
echo $(ls -xS docs/*.txt) | xargs mpiexec -n 4 ./mpi_test
echo $(ls -xS docs/*.txt) | xargs mpiexec -n 8 ./mpi_test
echo $(ls -xS docs/*.txt) | xargs mpiexec -n 16 ./mpi_test
