// sample compile command: "gcc -fopenmp -c Fig_10.7_threadpriv.c" to generate *.o object file
// will get warning messages about functions init_list, processwork, and freeList are implicitly declared

#include <stdio.h>
#include <sys/time.h>
#include <omp.h>

struct node {
   int data;
   struct node * next;
};

int counter = 0;
#pragma omp threadprivate(counter)

void inc_count()
{
   counter++;
}

int main() 
{
   struct node *p = NULL; 
   struct node *head = NULL; 
   init_list(p);
   head = p;

   #pragma omp parallel 
   {
      #pragma omp single
      {
         p = head;
         while (p) {
            #pragma omp task firstprivate(p) 
            {
               inc_count();
               processwork(p);
            }
         p = p->next;
         }
      }
   printf("thread \%d ran \%d tasks\n",omp_get_thread_num(),counter);
   } 
   freeList(p);

   return 0;
}
