// sample compile command: "gcc -fopenmp -c Fig_13.1_taskBug.c" to generate *.o object file

void work()
{
   #pragma omp task  //task 1
   {         
   
      #pragma omp task   //task 2
      {   
      
              #pragma omp critical // Critical region 1
               {/* do work here */}
      }
      #pragma omp critical // Critical Region 2
      {
         
         #pragma omp task // task 3
            {/* do work here */}  
      }
   }
}
