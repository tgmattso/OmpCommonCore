program main
   use omp_lib
   implicit none

   integer, parameter :: ITER = 100000000   ! use a smaller value if available memory is small
   integer :: i, id
   real*8 :: A(iter)
   real*8 :: tdata 
   real :: x

   do i = 1, ITER
      A(i) = 2.0 * i
   enddo

   !$omp parallel private (id, tdata, x) 

      id = omp_get_thread_num()
      tdata = omp_get_wtime()
 
      !$omp do schedule(static)
      do i = 1, ITER
         x =  i * 1.0
         A(i) = A(i) * sqrt(x) / (sin(x) ** tan(x))
      enddo

      tdata = omp_get_wtime() - tdata

      if (id == 0) print *, "Time spent is ", tdata, " sec"

   !$omp end parallel
end program main
