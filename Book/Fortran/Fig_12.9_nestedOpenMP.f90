subroutine report_num_threads(level) 
   use omp_lib
   implicit none

   integer :: level
   !$omp single
      write(*,100) level, omp_get_num_threads()
100   format("Level ", I3, ": number of threads in the team is ", I6)
   !$omp end single
end subroutine report_num_threads

program main
   use omp_lib
   implicit none
   external :: report_num_threads

   call omp_set_dynamic(.false.)
   !$omp parallel num_threads(2) 
      call report_num_threads(1)
      !$omp parallel num_threads(2) 
         call report_num_threads(2)
         !$omp parallel num_threads(2) 
            call report_num_threads(3)
         !$omp end parallel 
      !$omp end parallel 
   !$omp end parallel 
end program main 
