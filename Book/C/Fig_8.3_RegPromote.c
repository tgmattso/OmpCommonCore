// sample compile command: "gcc -fopenmp -c Fig_8.3_RegPromote.c" to generate *.o object file

#include <omp.h>
#define TOL  0.0001
#define MAX  100000
#define NMAX 1000

//embarrassingly parallel computation, returns a convergence parameter
double doit(double *A, int N, int id); 

int main()
{
   int iter = 0;
   int N = 1000;
   double A[NMAX] = {0.0};
   double conv=0.0;
   #pragma omp parallel shared(A,N,iter) firstprivate(conv)
   {
      int id = omp_get_thread_num();
      int nthrd = omp_get_num_threads();

      while (iter < MAX) {
         conv = doit(A, N, id);
         if (conv < TOL) break;
         if (id == 0) iter++;
      }
   } //end parallel region
}
