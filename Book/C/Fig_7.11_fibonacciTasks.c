int fib (int n)
{   
   int x,y;
   if (n < 2) return n;

#pragma omp task shared(x)
   x = fib(n-1);
#pragma omp task shared(y)
   y = fib(n-2);
#pragma omp taskwait
   return (x+y);
}

int main()
{  
   int NW = 30;
   #pragma omp parallel
   { 
      #pragma omp single
         fib(NW);
   }
}
