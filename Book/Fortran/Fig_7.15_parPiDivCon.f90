module data_mod
   integer, parameter :: num_steps = 1024*1024*1024
   integer, parameter :: MIN_BLK = 1024*256              

   contains
      real*8 recursive function pi_comp(Nstart, Nfinish, step) result(sum)
         use omp_lib
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
            !$omp task shared(sum1)
               sum1 = pi_comp(Nstart, Nfinish - iblk/2, step)
            !$omp end task 
            !$omp task shared(sum2)
               sum2 = pi_comp(Nfinish - iblk/2, Nfinish, step)
            !$omp end task 
            !$omp taskwait
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

   step = 1.0 / num_steps

   !$omp parallel
      !$omp single
         sum = pi_comp(0, num_steps, step);
      !$omp end single
   !$omp end parallel

   pi = step * sum

   WRITE(*,100) pi, num_steps
100       FORMAT('pi = ', f15.8, ',', i14, ' steps')

end program main 
