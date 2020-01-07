/* This nested OpenMP version is adapted by Helen He
from the hybrid MPI/OpenMP Cray Source code "xthi.c" available at:
http://docs.cray.com/books/S-2496-4101/html-S-2496-4101/cnlexamples.html
*/

#define _GNU_SOURCE

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sched.h>
#include <omp.h>

/* Borrowed from util-linux-2.13-pre7/schedutils/taskset.c */
static char *cpuset_to_cstr(cpu_set_t *mask, char *str)
{
  char *ptr = str;
  int i, j, entry_made = 0;
  for (i = 0; i < CPU_SETSIZE; i++) {
    if (CPU_ISSET(i, mask)) {
      int run = 0;
      entry_made = 1;
      for (j = i + 1; j < CPU_SETSIZE; j++) {
        if (CPU_ISSET(j, mask)) run++;
        else break;
      }
      if (!run)
        sprintf(ptr, "%d,", i);
      else if (run == 1) {
        sprintf(ptr, "%d,%d,", i, i + 1);
        i++;
      } else {
        sprintf(ptr, "%d-%d,", i, i + run);
        i += run;
      }
      while (*ptr != 0) ptr++;
    }
  }
  ptr -= entry_made;
  *ptr = 0;
  return(str);
}

int main(int argc, char *argv[])
{
  int thread1, thread2;
  cpu_set_t coremask1, coremask2;
  char clbuf1[7 * CPU_SETSIZE], hnbuf1[64];
  char clbuf2[7 * CPU_SETSIZE], hnbuf2[64];

  memset(clbuf1, 0, sizeof(clbuf1));
  memset(clbuf2, 0, sizeof(clbuf2));
  memset(hnbuf1, 0, sizeof(hnbuf1));
  memset(hnbuf2, 0, sizeof(hnbuf2));
  (void)gethostname(hnbuf1, sizeof(hnbuf1));
  (void)gethostname(hnbuf2, sizeof(hnbuf2));

  #pragma omp parallel private(thread1, coremask1, clbuf1) 
  {
    thread1 = omp_get_thread_num();
    (void)sched_getaffinity(0, sizeof(coremask1), &coremask1);
    cpuset_to_cstr(&coremask1, clbuf1);
    #pragma omp barrier
    printf("Hello from level 1: thread level 1= %d, on %s. (core affinity = %s)\n",
            thread1, hnbuf1, clbuf1);

        #pragma omp parallel private(thread2, coremask2, clbuf2)
        {
        thread2 = omp_get_thread_num();
        (void)sched_getaffinity(0, sizeof(coremask2), &coremask2);
         cpuset_to_cstr(&coremask2, clbuf2);
         #pragma omp barrier
         printf("Hello from level 2: thread level 1=  %d, thread level 2= %d, on %s. (core affinity = %s)\n",
                 thread1, thread2, hnbuf2, clbuf2);
        }        
  }
  return(0);
}
