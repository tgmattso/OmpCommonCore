#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <omp.h>

#define ITER 50000000  // use a smaller value if available memory is small

bool check_prime(int num)
{
   int i;
   for (i = 2; i <= sqrt(num); i++) {
      if (num % i == 0)
         return false;
   }
   return true;
}

void main( )
{
   int sum = 0;

   #pragma omp parallel 
   {
      int i;
      int id = omp_get_thread_num();
      double tdata = omp_get_wtime();
 
      #pragma omp for reduction (+:sum) schedule(dynamic)
      for (i = 2; i <= ITER ; i++) {
         if (check_prime(i)) sum++;
      }
      tdata = omp_get_wtime() - tdata;

      if (id == 0) printf("Number of prime numbers is %d in %f sec \n", sum, tdata);
   }
}
