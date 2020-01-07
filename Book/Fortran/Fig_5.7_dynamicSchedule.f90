program main
 
   use omp_lib
   implicit none

   integer, parameter :: ITER = 50000000   ! use a smaller value if available memory is small
   integer :: i, id
   real*8 :: tdata
   integer :: sum = 0

   !$omp parallel private (i, id, tdata)
      id = omp_get_thread_num()
      tdata = omp_get_wtime()
 
   !$omp do reduction (+:sum) schedule(dynamic)
      do i = 2, ITER
         if (check_prime(i) == 1) sum = sum + 1 
      enddo
   !$omp end do

      tdata = omp_get_wtime() - tdata

      if (id == 0) print *, "Number of prime numbers is ", &
                   & sum, "in ", tdata, " sec"
   !$omp end parallel

   contains
      integer function check_prime (num) 
         implicit none
         integer, intent (in) :: num
         integer :: i, iend

         iend = int (sqrt(num*1.0))
         do i = 2, iend
            if (mod(num,i) == 0) then
                check_prime = 0
                return
            endif
         enddo

         check_prime = 1

      end function check_prime

end program main



