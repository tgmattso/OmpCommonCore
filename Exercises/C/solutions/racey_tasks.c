//
// This is a very simple program to play with tasks.
//
// the idea is to print one of two strings
//
//     I think race cars are fun.
//     I think car races are fun
//
//  This is a race condition since depending on how the
//  threads are scheduled, you will get a different answer.
//  We aren't writing any variables.  Hence this is not
//  a data race and the program is legal.
//

#include <stdio.h>
#include <omp.h>

int main()
{

   printf("I think");

   #pragma omp parallel
   {
      #pragma omp single
      {
         #pragma omp task
            printf(" car");

         #pragma omp task
            printf(" race");
      }
   }
   printf("s");
   printf(" are fun!\n");
 
}
