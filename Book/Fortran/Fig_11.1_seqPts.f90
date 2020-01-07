! sample compile command to generate *.o object file:
!      gfortran -fopenmp -c Fig_11.1_seqPts.f90

program main 
   implicit none
   integer :: a , b, c, d, e   
   integer :: i, N = 100
   integer, external :: func1, func2, func3

  ! The two comma operators plus the full expression define sequence 
  ! points ... all ordered by sequenced-before relations.

   a = 1;  b = 2; c = 0   

  ! 3 sequence points: the full statement plus the 2 function calls.
  ! The + operator is not a sequence point so the function calls are
  ! unordered and therefore, indeterminately sequenced. 
				            
   d = func2(a) + func3(b)  

  ! each expression in the for statement is a sequence point.   
  ! they occur in a sequenced-before relation. 

    do i = 1, N
      ! function invocations are each a sequence point. Argument 
      ! evaluations are unordered or indeterminately sequenced. 
      e = func1(func2(a), func3(b))  
   enddo
            
   ! There is no Fortran increment syntax such as a++ in C.
   ! a = a + 1 evaluates a + 1 first, then store the new value in a.

   a = a + 1                               
end program main 
