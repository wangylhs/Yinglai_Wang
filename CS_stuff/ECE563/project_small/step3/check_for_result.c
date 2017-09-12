#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

#define SIZE 8

void mat_mul(int m, int n, int p, double** mat_1, double** mat_2, double** mat_3){
	int i,j,k;
	for (i=0; i<m; i++){
      for (j=0; j<n; j++){
        mat_3[i][j]=0;
        for (k=0; k<p; k++){
        	mat_3[i][j] += mat_1[i][k]*mat_2[k][j];
        }
      }
   }
}

void mat_mul_par(int m, int n, int p, double** mat_1, double** mat_2, double** mat_3){
	int i,j,k;
#pragma omp parallel shared(mat_1,mat_2,mat_3) private(i,j,k)
{
#pragma omp for schedule(static)
	for (i=0; i<m; i++){
      for (j=0; j<n; j++){
        mat_3[i][j]=0;
        for (k=0; k<p; k++){
        	mat_3[i][j] += mat_1[i][k]*mat_2[k][j];
        }
      }
   }
}
}


int main(int argc, char * argv[]){
	double t1, t2;
	double seq_time, par_time;
	double **mat_1, **mat_2, **mat_3;
	int i,j,k;
	/* initialize matrices */
	mat_1 = (double **)malloc(sizeof(double *)*SIZE);
	mat_2 = (double **)malloc(sizeof(double *)*SIZE);
	mat_3 = (double **)malloc(sizeof(double *)*SIZE);
	for(i=0;i<SIZE;i++){
		*(mat_1+i) = (double *)malloc(sizeof(double)*SIZE);
		*(mat_2+i) = (double *)malloc(sizeof(double)*SIZE);
		*(mat_3+i) = (double *)malloc(sizeof(double)*SIZE);
	}
	int ct=0;
	for(i=0;i<SIZE;i++){
		for(j=0;j<SIZE;j++){
			mat_1[i][j] = ct;
			mat_2[i][j] = ct;
			ct++;
		}
	}

	t1 = omp_get_wtime();
	mat_mul(SIZE, SIZE, SIZE, mat_1, mat_2, mat_3);
	t2 = omp_get_wtime();
	seq_time = t2-t1;
	/*
	omp_set_num_threads(2);
	t1 = omp_get_wtime();
	mat_mul_par(SIZE, SIZE, SIZE, mat_1, mat_2, mat_3);
	t2 = omp_get_wtime();
	par_time = t2-t1;

	printf("Martix Size\tSequential \t Parallel \t Speed Up\n");
	printf("%d(2 threads)\t%.6f\t%.6f\t%.6f\n", SIZE, seq_time, par_time, seq_time/par_time);

	omp_set_num_threads(4);
	t1 = omp_get_wtime();
	mat_mul_par(SIZE, SIZE, SIZE, mat_1, mat_2, mat_3);
	t2 = omp_get_wtime();
	par_time = t2-t1;
	printf("%d(4 threads)\t%.6f\t%.6f\t%.6f\n", SIZE, seq_time, par_time, seq_time/par_time);

	omp_set_num_threads(8);
	t1 = omp_get_wtime();
	mat_mul_par(SIZE, SIZE, SIZE, mat_1, mat_2, mat_3);
	t2 = omp_get_wtime();
	par_time = t2-t1;
	printf("%d(8 threads)\t%.6f\t%.6f\t%.6f\n", SIZE, seq_time, par_time, seq_time/par_time);

	omp_set_num_threads(16);
	t1 = omp_get_wtime();
	mat_mul_par(SIZE, SIZE, SIZE, mat_1, mat_2, mat_3);
	t2 = omp_get_wtime();
	par_time = t2-t1;
	printf("%d(16 threads)\t%.6f\t%.6f\t%.6f\n", SIZE, seq_time, par_time, seq_time/par_time);
     */
	for(i=0;i<SIZE;i++){
		for(j=0;j<SIZE;j++){
			printf("%.0f ", mat_3[i][j]);
		}
		printf("\n");
	}



	return 0;
}