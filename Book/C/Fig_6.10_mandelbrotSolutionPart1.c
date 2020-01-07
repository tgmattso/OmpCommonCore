// combine Fig_6.10_mandelbrotSolutionPart1.c and Fig_6.11_mandelbrotSolutionPart2.c into one file, and name it as mandel_par.c
// sample compile command: gcc -fopenmp -o mandel_par mandel_par.c

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

# define NPOINTS 1000 
# define MXITR 1000 

struct d_complex {
   double r; double i; 
};

void testpoint(struct d_complex);
struct d_complex c; 
int numoutside = 0;

int main ()
{ 
   int i, j;
   double area, error, eps = 1.0e-5;
   #pragma omp parallel for private(c,j) firstprivate(eps)
      for (i = 0; i < NPOINTS; i++) { 
         for (j = 0; j < NPOINTS; j++) {
            c.r = -2.0 + 2.5 * (double)(i)/(double)(NPOINTS) + eps; 
            c.i = 1.125 * (double)(j)/(double)(NPOINTS) + eps; 
            testpoint(c);
         } 
      }
   area = 2.0 * 2.5 * 1.125 * (double)(NPOINTS * NPOINTS      \
          - numoutside)/(double)(NPOINTS * NPOINTS);
   error = area / (double)NPOINTS; 
}
