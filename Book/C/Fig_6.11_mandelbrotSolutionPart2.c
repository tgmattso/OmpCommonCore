// combine Fig_6.10_mandelbrotSolutionPart1.c and Fig_6.11_mandelbrotSolutionPart2.c into one file, and name it as mandel_par.c
// sample compile command: gcc -fopenmp -o mandel_par mandel_par.c

void testpoint(struct d_complex c)
{
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
