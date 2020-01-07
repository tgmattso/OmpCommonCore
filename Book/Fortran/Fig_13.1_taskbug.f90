! sample compile command to generate *.o object file:
!      gfortranc -fopenmp -c Fig_13.1_taskBug.f90

subroutine  work()
   use omp_lib
   implicit none

   !$omp task   ! task 1
      !$omp task   ! task 2
          !$omp critical    ! Critical region 1
             ! do work here
          !$omp end critical  ! end Critical Region 1
      !$omp end task  ! end task2
      !$omp critical  ! Critical Region 2
         !$omp task  ! task 3
             ! do work here } 
         !$omp end task  ! end task3
      !$omp end critical ! end Critical Region 2
   !$omp end task    ! end task 1
end subroutine 
