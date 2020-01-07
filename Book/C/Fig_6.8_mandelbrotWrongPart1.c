// combine Fig_6.8_mandelbrotWrongPart1.c and Fig_6.9_mandelbrotWrongPart2.c into one file, and name it as mandel_wrong.c
// sample compile command: gcc -fopenmp -o mandel_wrong mandel_wrong.c

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

# define NPOINTS 1000
# define MAXITER 1000

void testpoint(void);

struct d_complex {
   double r;
   double i;
};

struct d_complex c;
int numoutside = 0;

int main() {
   int i, j;
   double area, error, eps = 1.0e-5;

// Loop over grid of points in the complex plane which contains 
// the Mandelbrot set, test each point to see whether it is 
// inside or outside the set

#pragma omp parallel for private(c,eps)
   for (i = 0; i < NPOINTS; i++) {
      for (j = 0; j < NPOINTS; j++) {
         c.r = -2.0 + 2.5 * (double)(i) / (double)(NPOINTS) + eps;
         c.i = 1.125 * (double)(j) / (double)(NPOINTS) + eps;
         testpoint();
      }
   }

// Calculate area of set and error estimate and output the results
   
   area = 2.0 * 2.5 * 1.125 * (double)(NPOINTS * NPOINTS - numoutside) 
         / (double)(NPOINTS * NPOINTS);
   error = area / (double)NPOINTS;

   printf("Area of Mandlebrot set = %12.8f +/- %12.8f\n",area,error);
   printf("Correct answer should be around 1.506\n");
}
