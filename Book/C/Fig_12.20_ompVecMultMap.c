#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#define N 1024
int main()
{
   float *a, *b, *c;
   int i;
   
   a = (float*) malloc(N * sizeof(float));
   b = (float*) malloc(N * sizeof(float));   
   c = (float*) malloc(N * sizeof(float));
   
// initialize a, b, and c (code not shown)

#pragma omp target map(to:a[0:N],b[0:N]) map(tofrom:c[0:N])
#pragma omp teams distribute parallel for simd
   for (i = 0; i < N; i++)
      c[i] += a[i] * b[i];
}
