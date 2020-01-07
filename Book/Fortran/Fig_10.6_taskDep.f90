! sample compile command to generate *.o object file:
!      gfortran -fopenmp -c Fig_10.6_taskDep.f90

program main
   use omp_lib
   implicit none
   external :: AWork, BWork, Cwork, Dwork, Ework
   real :: A, B, C, D, E

   !$omp parallel shared(A, B, C, D, E)
      !$omp single
         !$omp task depend(out:A)
            call Awork(A)
         !$omp end task 
         !$omp task depend(out:E)
            call Ework(E)
         !$omp end task 
         !$omp task depend(in:A) depend(out:B)
            call Bwork(B)
         !$omp end task 
         !$omp task depend(in:A) depend(out:C)
            call Cwork(C)
         !$omp end task 
         !$omp task depend(in:B,C,E)
            call Dwork(E)
         !$omp end task 
      !$omp end single
   !$omp end parallel 
end program main
