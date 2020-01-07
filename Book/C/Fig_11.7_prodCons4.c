#include <omp.h>
#include <stdlib.h>
int main()
{

double *A;
int flag = 0;  // a flag to communicate when the consumer can start
omp_set_num_threads(2);
   
#pragma omp parallel shared(A, flag)
{
   int id = omp_get_thread_num();
   int nthrds = omp_get_num_threads();
   int flag_temp;
     
   // we need two or more threads for this program
   if ((id == 0) && (nthrds < 2)) exit(-1);
     
   if (id == 0) {
      produce(A);
      #pragma omp atomic write seq_cst
         flag = 1;
   }

   if (id == 1) {
      while(1) {
         #pragma omp atomic read seq_cst
            flag_temp = flag;
         if(flag_temp != 0) break;
      }
      consume(A);
   }
}

}
