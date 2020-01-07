#include <stdio.h>
static long num_steps = 100000;
float step;
int main ()
{
   int i;
   float x0, x1, x2, x3, pi, sum = 0.0;

   step = 1.0f / (double) num_steps;

   for (i = 1; i <= num_steps; i = i+4) {
      x0 = (i - 0.5f) * step;
      x1 = (i + 0.5f) * step;
      x2 = (i + 1.5f) * step;
      x3 = (i + 2.5f) * step;
      sum = sum + 4.0f * (1.0f/(1.0f+x0*x0) + 1.0f/(1.0f+x1*x1) \
                   + 1.0f/(1.0f+x2*x2) + 1.0f/(1.0f+x3*x3));
   }
   pi = step * sum;
   printf("pi = \%lf, \%ld steps\n ",pi, num_steps);
}	  
