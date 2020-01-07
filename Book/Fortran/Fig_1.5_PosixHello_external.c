#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define NUM_THREADS 4

void *PrintHelloWorld(void *InputArg)
{
   printf(" Hello ");
   printf(" World \n");
}

void pthreads_c_()
{
   pthread_t threads[NUM_THREADS];
   int id;
   pthread_attr_t attr;
   pthread_attr_init(&attr);
   pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

   for (id = 0; id < NUM_THREADS; id++) {
      pthread_create(&threads[id], &attr, PrintHelloWorld, NULL);
   }

   for (id = 0; id < NUM_THREADS; id++){
      pthread_join(threads[id], NULL);
   }

   pthread_attr_destroy(&attr);
   pthread_exit(NULL);
}
