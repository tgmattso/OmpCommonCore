#include <stdio.h>
#include <omp.h>     // The OpenMP include file

int main()
{
   #pragma omp parallel
   {   
      printf(" Hello ");
      printf(" World \n");
   }
}
