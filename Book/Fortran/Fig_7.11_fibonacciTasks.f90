recursive integer function fib (n) result(res)
   use omp_lib
   implicit none 

   integer, intent(in) :: n
   integer ::  x, y
   if (n < 2) then
      res = n
   else
      !$omp task shared (x)
         x = fib(n-1)
      !$omp end task
      !$omp task shared (y)
          y = fib(n-2)
      !$omp end task
      !$omp taskwait
      res = x + y
   endif
end function fib

program main
   use omp_lib
   implicit none

   interface
      function fib (n)
         integer :: fib
         integer, intent(in) :: n
      end function fib
   end interface

   integer :: NW, result
   NW = 30
   !$omp parallel
      !$omp single
          result = fib(NW)
      !$omp end single
   !$omp end parallel
   print *, "fib(",NW,")=", result
end program main
