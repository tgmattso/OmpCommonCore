#include <stdio.h>
#include <omp.h>

// a simple function called by each thread
void pooh(int ID, double* A) 
{
   A[ID] = ID;
}

int main()
{
  double A[10] = {0};    // an array visible to all threads
  omp_set_num_threads(4);
  #pragma omp parallel
  {
    int ID = omp_get_thread_num();  // a variable local to each thread
    pooh(ID, A);
    printf(" A of ID(\%d) = \%lf\n",ID,A[ID]);
  } // end of parallel region
}
