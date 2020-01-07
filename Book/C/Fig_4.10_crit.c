// sample compile command: "gcc -fopenmp -c Fig_4.10_crit.c" to generate *.o object file

#include <stdio.h>
#include <omp.h>

int main()
{
   float  res = 0.0;
   int niters = 1000;;
   #pragma omp parallel
   {     
      float B; int i, id, nthrds;
      id = omp_get_thread_num();
      nthrds = omp_get_num_threads();
      for (i = id; i < niters; i += nthrds) {
         B = big_job(i);
         #pragma omp critical
            res += consume(B);
      }
   } // end of parallel region
}
