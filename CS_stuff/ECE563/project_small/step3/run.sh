#!/bin/bash

./mat_omp_step3
mpirun -n 4 mat_mpi_step3
mpirun -n 16 mat_mpi_step3
