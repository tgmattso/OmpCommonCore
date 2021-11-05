/*
**  PROGRAM: Mandelbrot area (solution)
**
**  PURPOSE: Program to compute the area of a  Mandelbrot set.
**           The correct answer should be around 1.510659.
**
**  USAGE:   Program runs without input ... just run the executable
**
**  ADDITIONAL EXERCISES:  Experiment with the schedule clause to fix 
**               the load imbalance.   Experiment with atomic vs. critical vs.
**               reduction for numoutside.
**            
**  HISTORY: Written:  (Mark Bull, August 2011).
**
**           Changed "complex" to "d_complex" to avoid collsion with 
**           math.h complex type.   Fixed data environment errors
**           (Tim Mattson, September 2011)
**
**           Changed "atomic" to "critical" to match Common Core
**           (Helen He, November 2020)
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

# define NPOINTS 1000 
# define MXITR 1000 

struct d_complex {
   double r; 
   double i; 
};

void testpoint(struct d_complex);
struct d_complex c; 
int numoutside = 0;

int main ()
{ 
   int i, j;
   double area, error, eps = 1.0e-5;

// Loop over grid of points in the complex plane which contains the Mandelbrot set,
// testing each point to see whether it is inside or outside the set.
   double initTime = omp_get_wtime();
   #pragma omp parallel for private(c) firstprivate(eps) collapse(2) schedule(dynamic,100)
      for (i = 0; i < NPOINTS; i++) { 
         for (j = 0; j < NPOINTS; j++) {
            c.r = -2.0 + 2.5 * (double)(i)/(double)(NPOINTS) + eps; 
            c.i = 1.125 * (double)(j)/(double)(NPOINTS) + eps; 
            testpoint(c);
         } 
      }

// Calculate area of set and error estimate and output the results
   area = 2.0 * 2.5 * 1.125 * (double)(NPOINTS * NPOINTS      \
          - numoutside)/(double)(NPOINTS * NPOINTS);
   error = area / (double)NPOINTS; 
   double runtime = omp_get_wtime() - initTime;
   printf("runtime = %lf seconds with %d threads\n",runtime, omp_get_num_threads());

   printf("Area of Mandlebrot set = %12.8f +/- %12.8f\n",area,error);
   printf("Correct answer should be around 1.510659\n");
}

void testpoint(struct d_complex c)
{
// Does the iteration z=z*z+c, until |z| > 2 when point is known to be outside set
// If loop count reaches MAXITER, point is considered to be inside the set
   struct d_complex z;
   int iter;
   double temp;

   z = c;
   for (iter = 0; iter < MXITR; iter++) {
      temp = (z.r * z.r) - (z.i * z.i) + c.r; 
      z.i = z.r * z.i * 2 + c.i;
      z.r = temp;
      if ((z.r * z.r + z.i * z.i) > 4.0) { 
         #pragma omp critical
            numoutside++;
         break; 
      }
   } 
}
