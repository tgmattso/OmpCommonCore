// sample compile command: "gcc -fopenmp -c Fig_10.1_parClaw.c" to generate *.o object file

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

// initialization and transform functions 
// (we will not show the function bodies)
extern void initMats(int N, float *A, float *T);
extern void transform(int N, int id, int Nthrds, float *A, float *T);

int main(int argc, char**argv)
{
   float trace=0;
   int i, id, N, Nthrds;
   float  *A, *T;

   // set matrix order N
   if (argc == 2)
      N = atoi(argv[1]);
   else
      N = 10;

   // allocate space for three N x N matrices and initialize them
   T = (float *) malloc(N*N*sizeof(float));
   A = (float *) malloc(N*N*sizeof(float));
   initMats(N, A, T);
 
   #pragma omp parallel if(N>100) num_threads(4) default(none) \
               shared(A,T,N) private (i,id,Nthrds) reduction(+:trace)
   {
      id = omp_get_thread_num();
      Nthrds = omp_get_num_threads();
      transform(N, id, Nthrds, T, A);

      // compute trace of A matrix
      // i.e., the sum of diagonal elements
      #pragma omp for
      for (i = 0; i < N; i++)
         trace += *(A+i*N+i);
    }
    printf(" transform complete with trace = \%f\n",trace);
}
