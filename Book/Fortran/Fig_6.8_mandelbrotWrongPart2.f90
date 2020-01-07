// combine Fig_6.8_mandelbrotWrongPart1_C and Fig_6.9_mandelbrotWrongPart2_c into one file, and name it as mandel_wrong.c
// sample compile command: gcc -fopenmp -o mandel_wrong mandel_wrong.c

void testpoint(void) {

// Does the iteration z=z*z+c, until |z| > 2 when point is known to 
// be outside set. If loop count reaches MAXITER, point is considered 
// to be inside the set.

   struct d_complex z;
   int iter;
   double temp;

   z = c;
   for (iter = 0; iter < MAXITER; iter++) {
      temp = (z.r * z.r) - (z.i * z.i) + c.r;
      z.i = z.r * z.i * 2 + c.i;
      z.r = temp;
      if ((z.r * z.r + z.i * z.i) > 4.0) {
         numoutside++;
         break;
      }
   }
}
