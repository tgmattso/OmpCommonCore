! sample compile command to generate *.o object file:
!       gfortran -fopenmp -c Fig_6.3_sharedEx.f90

program sharedEx 
   use omp_lib
   implicit none
   integer :: A, B, C
  
   interface 
      subroutine initialize(A, B, C)
      integer, intent(out) :: A, B, C
      end subroutine
   end interface

   call initialize(A, B, C)

   ! remember the value of A before the parallel region
   print *, 'A before =', A

!$omp parallel shared (B,C) private(A)
   A = omp_get_thread_num()
   !$omp critical
      C = B + A
   !$omp end critical
!$omp end parallel

   ! A in the parallel region goes out of scope, we revert
   ! to the original variable for A
   print *, 'A after = ', A, ' and C = ', C

end program sharedEx
