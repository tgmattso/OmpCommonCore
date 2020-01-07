! sample compile command to generate *.o object file:
!      gfortran -fopenmp -c Fig_11.6_hist.f90

program main
   use omp_lib
   implicit none 

   integer, parameter :: num_trials = 1000000	 ! number of x values
   integer, parameter :: num_bins = 100		   ! number of bins in histogram
   real*8, save :: xlow = 0.0;		   ! low end of x range
   real*8, save :: xhi = 10.0;		   ! high end of x range

   real*8 :: x                 
   integer*8 :: hist(num_bins)   ! the histogram
   integer*8 :: ival, i
   real*8 :: bin_width    ! the width of each bin in the hi, stogram
   real*8 :: sumh, sumhsq, ave, std_dev
   integer(kind=omp_lock_kind) :: hist_lcks(num_bins)   ! array of locks, one per bucket

   interface
      function drandom() result(val)
         real*8 :: val
      end function
      subroutine seed(low_in, hi_in)
         real*8, intent(in) :: low_in, hi_in
      end subroutine
   end interface

   call seed(xlow, xhi)     ! seed random generator over range of x
   bin_width = (xhi - xlow) / dble(num_bins)

   ! initialize the histogram and the array of locks
   !$omp parallel do schedule(static) 
      do i = 1, num_bins
         hist(i) = 0
         call omp_init_lock(hist_lcks(i))
      enddo 
   !$omp end parallel do 
   ! test uniform pseudorandom sequence by assigning values 
   ! to the right histogram bin
   !$omp parallel do schedule(static) private(x,ival)
      do i = 1, num_trials
         x = drandom()
         ival = int8((x - xlow)/bin_width)
         ! protect histogram bins. Low overhead due to uncontended locks
         call omp_set_lock(hist_lcks(ival))     
         hist(ival) = hist(ival) + 1                               
         call omp_unset_lock(hist_lcks(ival))  
      enddo
   !$omp end parallel do

   sumh = 0.0
   sumhsq = 0.0
   ! compute statistics (ave, std_dev) and destroy locks
   !$omp parallel do schedule(static) reduction(+:sumh,sumhsq)
      do i = 1, num_bins
         sumh  = sumh + hist(i)
         sumhsq = sumhsq + hist(i)*hist(i)
         call omp_destroy_lock(hist_lcks(i)) 
      enddo
   !$omp end parallel do

   ave = sumh / dble(num_bins)
   std_dev = sqrt(sumhsq /(dble(num_bins) - ave * ave)) 
end program main 
