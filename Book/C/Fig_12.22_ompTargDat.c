#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#define N  1024
int main()
{
   float *a, *b, *c, *d;
   int i;
   
   a = (float*)malloc(N*sizeof(float));
   b = (float*)malloc(N*sizeof(float));   
   c = (float*)malloc(N*sizeof(float));
   d = (float*)malloc(N*sizeof(float));
   
// initialize a, b, c, and d (code not shown)

#pragma omp target data map(to:a[0:N],b[0:N],c[0:N]) map(tofrom:d[0:N])
{
   #pragma omp target 
   #pragma omp teams distribute parallel for simd
   for (i = 0; i < N; i++)
      c[i] += a[i] * b[i];

   #pragma omp target 
   #pragma omp teams distribute parallel for simd
   for (i = 0; i < N; i++)
      d[i] += a[i] + c[i];
}

// continue in the program but only using d (not c)

}
