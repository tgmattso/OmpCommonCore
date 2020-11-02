! This program will numerically compute the integral of
!                   4/(1+x*x) 
! from 0 to 1.  The value of this integral is pi -- which 
! is great since it gives us an easy way to check the answer.

! This version of the program uses a divide and concquer algorithm
! and recurrsion.

! History: C code written by Tim Mattson, 10/2013.
!          Adapted to Fortran code by Helen He, 09/2017. 
!          Updated to Fortran90 code by Helen He, 11/2019. 


module data_mod
   integer, parameter :: num_steps = 1024*1024*1024
   integer, parameter :: MIN_BLK = 1024*256              

   contains
      real*8 recursive function pi_comp(Nstart, Nfinish, step) result(sum)
         implicit none
 
         integer, intent(in) :: Nstart, Nfinish
         real*8 :: x, sum1, sum2, step
         integer :: i, iblk
      
         sum = 0.0
 
         if (Nfinish - Nstart < MIN_BLK) then
            do i = Nstart,  Nfinish - 1 
               x = (i + 0.5) * step
              sum = sum + 4.0 / (1.0 + x * x)
            enddo
         else
            iblk = Nfinish - Nstart
            sum1 = pi_comp(Nstart, Nfinish - iblk/2, step)
            sum2 = pi_comp(Nfinish - iblk/2, Nfinish, step)
            sum = sum1 + sum2
         endif

      end function 

end module data_mod

program main
   use omp_lib
   use data_mod
   implicit none

   integer :: i
   real*8 :: pi, sum, step
   real*8 :: init_time, final_time

   init_time = OMP_GET_WTIME()

   step = 1.0 / num_steps
   sum = pi_comp(0, num_steps, step)
   pi = step * sum

   final_time = OMP_GET_WTIME() - init_time
   write(*,100) num_steps, pi, final_time 
100    FORMAT(' With ', i14,' steps, pi = ', f15.8,' in ', f8.3,' secs') 

end program main 
