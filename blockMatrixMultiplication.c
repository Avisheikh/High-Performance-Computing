#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define min(a,b) (((a)<(b))?(a):(b))
#define N 2000
#define M 2000
#define P 2000
#define BLK_SIZE 128

void naiveMatrixMultiplication(double *C, const double *A, const double *B, int m, int n, int p)
{
    int i, j, k;

     for(i=0; i<m; i++) {
         for(j=0; j<n; j++) {
          C[p*i+j]=0;
          for(k=0; k<p; k++) {
            C[p*i+j] += A[n*i+k] * B[p*k+j];
           }
          }
        }
}

void blockMatrixMultiplication(double *C, const double *A, const double *B, int m, int n, int p)
{
      int i, j, k, ii, jj, kk, bs = BLK_SIZE;

      for(ii = 0; ii < m; ii += bs)
		for(jj = 0; jj < p; jj += bs)
			for(kk = 0; kk < n; kk += bs)
				for(i = ii; i < min(m, ii+bs); i++)
					for(j = jj; j < min(p, jj+bs); j++)
						for(k = kk; k < min(n, kk+bs); k++)
							C[p*i+j] += A[n*i+k] * B[p*k+j];
}


void mxm_product(double *dest, const double *a, const double *b, int m, int n, int p)
{

	printf("Matrix dimensions %dx%d\n", m, n);
	printf("Block size: %d\n", BLK_SIZE);


}

int time_difference(struct timespec *start,
                    struct timespec *finish,
                    long long int *difference) {
  long long int ds =  finish->tv_sec - start->tv_sec;
  long long int dn =  finish->tv_nsec - start->tv_nsec;

  if(dn < 0 ) {
    ds--;
    dn += 1000000000;
  }
  *difference = ds * 1000000000 + dn;
  return !(*difference > 0);
}



int main()
{
    int m, n, p;
    struct timespec start, finish;
    long long int time_elapsed;
	double *a, *b, *c;

    m = M;
	n = N;
	p = P;
	a = (double*)malloc((m * n) * sizeof(double));
	b = (double*)malloc((n * p) * sizeof(double));
	c = (double*)calloc(m * p, sizeof(double));

    //optimized algorithm
    clock_gettime(CLOCK_MONOTONIC, &start);

    blockMatrixMultiplication(c, a, b, m, n, p);

    clock_gettime(CLOCK_MONOTONIC, &finish);
      time_difference(&start, &finish, &time_elapsed);
      printf("Time elapsed for blocked matrix multiplication was %lldns or %0.9lfs\n", time_elapsed,
                                             (time_elapsed/1.0e9));

    //naive algorithm
    clock_gettime(CLOCK_MONOTONIC, &start);

    naiveMatrixMultiplication(c, a, b, m, n, p);

    clock_gettime(CLOCK_MONOTONIC, &finish);
      time_difference(&start, &finish, &time_elapsed);
      printf("Time elapsed for navie matrix multiplication was %lldns or %0.9lfs\n", time_elapsed,(time_elapsed/1.0e9));

    mxm_product(c, a, b, m, n, p);

	return 0;
}
