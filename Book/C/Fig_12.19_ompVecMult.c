#include<omp.h>
#include<stdio.h>
#define N 1024
int main()
{
   float a[N], b[N], c[N];
   int i;

// initialize a, b, and c (code not shown)

#pragma omp target
#pragma omp teams distribute parallel for simd
   for (i = 0;i < N; i++)
      c[i] += a[i] * b[i];
}
