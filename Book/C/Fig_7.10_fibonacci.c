int fib (int n)
{
   int x,y;
   if (n < 2) return n;

   x = fib(n-1);
   y = fib(n-2);
   return (x+y);
}

int main()
{
   int NW = 30;
   fib(NW);
}
