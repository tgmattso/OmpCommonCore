#include <stdio.h>
#include <omp.h>

int main()
{
  omp_set_num_threads(4);
  int size_of_team;
  #pragma omp parallel
  {
    int ID = omp_get_thread_num();  
    int NThrds = omp_get_num_threads();
    if (ID == 0) size_of_team = NThrds;
  } // end of parallel region
  printf("We just did the join on a team of size \%d", size_of_team);
}
