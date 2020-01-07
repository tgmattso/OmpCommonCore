#include <stdio.h>
#include <omp.h>

#define NTHREADS 4
#define CBLK     8

static long num_steps = 100000000;
double step;
int main ()
{
   int i, j, actual_nthreads;
   double pi, start_time, run_time;
   double sum[NTHREADS][CBLK]={0.0};

   step = 1.0 / (double) num_steps;

   omp_set_num_threads(NTHREADS);

   start_time = omp_get_wtime();
   #pragma omp parallel
   {
      int i;
      int id = omp_get_thread_num();
      int numthreads = omp_get_num_threads();
      double x;

      if (id == 0) actual_nthreads = numthreads;
	  
      for (i = id; i < num_steps; i += numthreads) {
         x = (i + 0.5) * step;
         sum[id][0] += 4.0 / (1.0 + x * x);
      }
   } // end of parallel region
   pi = 0.0;
   for (i = 0; i < actual_nthreads; i++)
      pi += sum[i][0];

   pi = step * pi;
   run_time = omp_get_wtime() - start_time;
   printf("\n pi is \%f in \%f seconds \%d thrds \n",
                    pi,run_time,actual_nthreads);
}	  
