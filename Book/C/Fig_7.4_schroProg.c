// sample compile command: "gcc -fopenmp -c Fig_7.4_schroProg.c" to generate *.o object file

#include <stdbool.h>
#include <omp.h>
#include <stdio.h>
// Three functions we use but do not show here:
// 1. Set seed for a pseudo-random sequence
void seedIt(long *val);
// 2. function to flip a coin (randomly return true or false)
bool flip(long *coin);
// 3. wait a short random amount of time
double waitAbit();

int main()
{
   double wait_val;
   long rand, i; 
   int dead_or_alive;
   omp_set_num_threads(2);
   
   // "flip a coin" to choose which task is for the dead
   // cat and which for the living cat.
   long coin;
   seedIt(&coin);
   bool HorT = flip(&coin);
   
   printf("Schrodinger's program says the cat is");
    
   #pragma omp parallel shared(HorT, dead_or_alive)
   {
      // These tasks are participating in a data race        
      #pragma omp task
      {
         double val = waitAbit();
         dead_or_alive = HorT;
      }
      #pragma omp task
      {
         double val = waitAbit();
         dead_or_alive = !HorT;
      }
   } 
   if (dead_or_alive)
      printf(" alive. \n");
   else 
      printf(" dead. \n");

   return 0;
}
