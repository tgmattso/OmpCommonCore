program main
   use omp_lib
   implicit none

   integer, parameter :: N = 1024
   real*8 :: a(N), b(N), c(N)
   integer :: i

! initialize a, b, and c (code not shown)

!$omp target
!$omp teams distribute parallel do simd
   do i = 1, N
      c(i) = c(i) + a(i) * b(i)
   enddo
!$omp end teams distribute parallel do simd
!$omp end target 

end program main
