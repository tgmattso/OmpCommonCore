#include <x86intrin.h>
#include <stdio.h>
static long num_steps = 1000000;
float scalar_four = 4.0f, scalar_zero = 0.0f, scalar_one = 1.0f;
float step;
int main ()
{
   int i;
   float pi;
   float vsum[4], ival;
   step = 1.0f/(double) num_steps;
  
   __m128 ramp  = _mm_setr_ps(0.5, 1.5, 2.5, 3.5);
   __m128 one   = _mm_load1_ps(&scalar_one);
   __m128 four  = _mm_load1_ps(&scalar_four);
   __m128 vstep = _mm_load1_ps(&step);
   __m128 sum   = _mm_load1_ps(&scalar_zero);
   __m128 xvec;
   __m128 denom;
   __m128 eye;
   
   for (i = 0; i < num_steps; i = i + 4){
      ival  = (float) i;
      eye   = _mm_load1_ps(&ival);
      xvec  = _mm_mul_ps(_mm_add_ps(eye,ramp), vstep);
      denom = _mm_add_ps(_mm_mul_ps(xvec,xvec), one);
      sum   = _mm_add_ps(_mm_div_ps(four,denom), sum);
   }
   _mm_store_ps(&vsum[0], sum);

   pi = step * (vsum[0] + vsum[1] + vsum[2] + vsum[3]);
   printf ("pi=%f\n", pi);
}	  
