! This program will numerically compute the integral of
!                  4/(1+x*x) 
! from 0 to 1.  The value of this integral is pi -- which 
! is great since it gives us an easy way to check the answer.

! The program was parallelized using OpenMP by adding just
! four lines 

! (1) A line to include omp.h -- the include file that 
! contains OpenMP's function prototypes and constants.

! (2) A pragma that tells OpenMP to create a team of threads

! (3) A pragma to cause one of the threads to print the
! number of threads being used by the program.

! (4) A pragma to split up loop iterations among the team
! of threads.  This pragma includes 2 clauses to (1) create a 
! private variable and (2) to cause the threads to compute their
! sums locally and then combine their local sums into a 
! single global value.

! History: C Code written by Tim Mattson, 11/1999
!          Adapted to Fortran code by Helen He, 09/2017 
!          Changed to Fortran90 code by Helen He, 11/2020 

  PROGRAM MAIN
  USE OMP_LIB
  IMPLICIT NONE

  INTEGER :: i, id, nthreads
  INTEGER, PARAMETER :: num_steps = 100000000
  REAL*8 :: x, pi, sum, step
  REAL*8 :: start_time, run_time

  DO id = 1, 4
     sum = 0.0

     step = 1.0 / num_steps

     CALL OMP_SET_NUM_THREADS(id)
     start_time = OMP_GET_WTIME()

!$OMP PARALLEL PRIVATE(i,x) 
!$OMP SINGLE
     nthreads = OMP_GET_NUM_THREADS()
!$OMP END SINGLE NOWAIT
!$OMP DO REDUCTION(+:sum)
     DO i = 1, num_steps
        x = (i - 0.5) * step
        sum = sum + 4.0 / (1.0 + x * x)
     ENDDO
!$OMP END DO
!$OMP END PARALLEL  

     pi = step * sum
     run_time = OMP_GET_WTIME() - start_time
     WRITE(*,100) pi, run_time, nthreads
100  FORMAT('pi is ',f15.8,' in ',f8.3,'secs and ',i3,' threads')

  ENDDO

  END PROGRAM MAIN
