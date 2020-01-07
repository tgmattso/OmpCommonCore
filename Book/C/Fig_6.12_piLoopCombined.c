#include <stdio.h>
#include <omp.h>

#define NTHREADS 4

static long num_steps = 100000000;
double step;

int main ()
{
   int i;
   double x, pi, sum = 0.0;
   double start_time, run_time;

   step = 1.0/(double) num_steps;
   omp_set_num_threads(NTHREADS);
   start_time = omp_get_wtime();

   #pragma omp parallel for private(x) reduction(+:sum) 
      for (i = 0; i < num_steps; i++) {
         x = (i + 0.5) * step;
         sum += 4.0 / (1.0 + x * x);
      }

   pi = step * sum;
   run_time = omp_get_wtime() - start_time;
   printf("pi is %f in %f seconds %d threads\n", pi, run_time);
}
