! sample compile command: 
!      gfortran -fopenmp -c Fig_4.10_crit.f90
! to generate *.o object file

program crit
   use omp_lib
   implicit none

   real :: res = 0.0
   integer :: niters = 1000
   real :: B
   integer :: i, id, nthrds

   interface
      function big_job(i)
         real :: big_job
         integer, intent(in) :: i
      end function big_job

      function consume(a)
         real :: consume
         real, intent(in) :: a
      end function consume
   end interface

   !$omp parallel private (id, nthrds)
      id = omp_get_thread_num()
      nthrds = omp_get_num_threads()
      do i = id, niters - 1, nthrds
         B = big_job(i)
         !$omp critical
            res = res + consume(B)
         !$omp end critical
      end do

   !$omp end parallel

end program crit
