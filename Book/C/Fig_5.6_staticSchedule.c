#include <stdio.h>
#include <math.h>
#include <omp.h>

#define ITER 100000000   // use a smaller value if available memory is small

void main()
{
   int i;
   double A[ITER];
   for (i = 0; i < ITER; ++i)
      A[i] = 2.0*i;

   #pragma omp parallel 
   {
      int i; 
      int id = omp_get_thread_num();
      double tdata = omp_get_wtime();
 
      #pragma omp for schedule(static)
      for (i = 1; i < ITER; i++) // notice i starts from 1 since
                                 // the denominator below cannot be 0
         A[i] = A[i] * sqrt(i) / pow(sin(i), tan(i));
      tdata = omp_get_wtime() - tdata;

      if (id == 0) printf("Time spent is %f sec \n", tdata);
   }
}
