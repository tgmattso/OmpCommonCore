! This program will numerically compute the integral of
!                   4/(1+x*x) 
! from 0 to 1.  The value of this integral is pi -- which 
! is great since it gives us an easy way to check the answer.

! The is the original sequential program.  It uses the timer
! from the OpenMP runtime library

! History: C code written by Tim Mattson, 11/1999.
! adapted to Fortran code by Helen He, 09/2017. 

 
  PROGRAM MAIN
  USE OMP_LIB
  IMPLICIT NONE

  INTEGER :: i
  INTEGER, PARAMETER :: num_steps = 100000000
  REAL*8 :: x, pi, sum, step
  REAL*8 :: start_time, run_time

  sum = 0.0

  step = 1.0 / num_steps
  start_time = OMP_GET_WTIME()

  DO i = 1, num_steps
     x = (i - 0.5) * step
     sum = sum + 4.0 / (1.0 + x * x)
  ENDDO

  pi = step * sum
  run_time = OMP_GET_WTIME() - start_time

  WRITE(*,100) num_steps, pi,  run_time
100  FORMAT('pi with ',i14,' steps is ',f15.8,' in ',f8.3,' secs')

  END PROGRAM MAIN
