recursive integer function fib (n) result(res)
   implicit none
   integer, intent(in) :: n
   integer ::  x, y
   if (n < 2) then
      res = n
   else
      x = fib(n-1)
      y = fib(n-2)
      res = x + y
   endif
end function fib

program main
   implicit none

   interface
      function fib (n)
         integer :: fib
         integer, intent(in) :: n
      end function fib
   end interface

   integer :: NW, result
   NW = 30
   result = fib(NW)
   print *, "fib(",NW,")=", result
end program main
