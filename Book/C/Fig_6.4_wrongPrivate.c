// sample compile command: "gcc -fopenmp -c Fig_6.4_wrongPrivate.c" to generate *.o object file

#include <stdio.h>
void wrong() 
{ 
   int tmp = 0;
   #pragma omp parallel for private(tmp) 
      for (int j = 0; j < 1000; j++)
         tmp += j;   
      printf("%d\n", tmp);  //tmp is 0 here
}
