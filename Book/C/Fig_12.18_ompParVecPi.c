#include<stdio.h>
#include <omp.h>
static long num_steps = 100000000;
double step;
int main ()
{
   int i;
   double x, pi, sum = 0.0;

   step = 1.0f / (double) num_steps;

   #pragma omp parallel for simd private(x) reduction(+:sum)
   for (i = 0; i < num_steps; i++) {
      x = (i + 0.5f) * step;
      sum += 4.0f / (1.0f + x * x);
   }

   pi = step * sum;
   printf("pi=%f\n",pi);
}	  
