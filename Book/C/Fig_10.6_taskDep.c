// sample compile command: "gcc -fopenmp -c Fig_10.6_taskDep.c" to generate *.o object file

#include <omp.h>

// functions Awork through Ework not shown

int main()
{
   float A, B, C, D, E;
   #pragma omp parallel shared(A, B, C, D, E)
   {
      #pragma omp single
      {
         #pragma omp task depend(out:A)
            Awork(&A);
         #pragma omp task depend(out:E)
            Ework(&E);
         #pragma omp task depend(in:A) depend(out:B)
            Bwork(&B);
         #pragma omp task depend(in:A) depend(out:C)
            Cwork(&C);
         #pragma omp task depend(in:B,C,E)
            Dwork(&E);
      }
   }
}
