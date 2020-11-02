//
//  Schrodingers racy program ... is the cat dead or alive?
//
//  You can use atomics and make the program race free, or comment out
//  the atomics and run with a race condition.  It works in both cases
//
//  History: Written by Tim Mattson, Feb 2019
//
#include <stdbool.h>
#include <stdio.h>
#include <sys/time.h>
#include <omp.h>

// random number generator parameters
// (from numerical recipies) 
#define MULT 4096
#define ADD  150889
#define MOD  714025

#define NTRIALS 100

// seed the pseudo random sequence with time of day
void seedIt(long *val)
{
   struct timeval tv;
   gettimeofday(&tv, NULL);
   *val = (long)tv.tv_usec;
}

// Linear congruential random number generator
long nextRan(long last)
{
   long next;
   next = (long) (MULT*last+ADD)%MOD;
   return next;
}

// flip a coin ... heads (true) or tails (false)
bool flip(long *coin)
{
   *coin = nextRan(*coin);
   if (*coin > MOD/2) 
      return true;
   else
      return false;
}

// wait a short random amount of time
double waitAbit()
{
   double val= 0.0;
   long i, count, rand;
   seedIt(&rand);
   count = nextRan(rand);
  
   // do some math to make us wait a while
   for (i = 0; i < count; i++){
      rand = nextRan(rand);
      val += (double)rand / ((double)MULT);
   }
   
   return val;
}

int main()
{
   double wait_val;
   long rand,i, dcount= 0, lcount=0; 
   int dead_or_alive;

   for(i = 0; i < NTRIALS; i++) {
   #pragma omp parallel num_threads(2) shared(dead_or_alive)
   {
      if (omp_get_thread_num() == 0)
      {
         printf(" with %d threads\n", omp_get_num_threads());
         printf("Schrodingers program says the cat is ");
      }
       
      #pragma omp single
      {
         // "flip a coin" to choose which task is for the dead
         // cat and which for the living cat.
         long coin;
         seedIt(&coin);
         bool HorT = flip(&coin);

         // without the atomics, these tasks are participating in a 
         // data race, but the program logic works fine if the actual 
         // value is messed up since in C any int other than 1 is false
         #pragma omp task
         {
            double val = waitAbit();
            // a store of a single machine word (bool)
//             #pragma omp atomic write
            dead_or_alive = HorT;
         }
         #pragma omp task
         {
            double val = waitAbit();
            // a store of a single machine word (bool)
//             #pragma omp atomic write
            dead_or_alive = !HorT;
         }
      }
   }
   if (dead_or_alive) {
      printf(" alive. %d\n", (int)dead_or_alive);
      lcount++;
   }
   else {
      printf(" dead. %d\n", (int)dead_or_alive);
      dcount++;
   }
   } // end loop over trials (for testing only)

   printf("dead %d times and alive %d times \n", dcount, lcount);
   return 0;
}
