C This program will numerically compute the integral of
C                  4/(1+x*x) 
C from 0 to 1.  The value of this integral is pi -- which 
C is great since it gives us an easy way to check the answer.

C The program was parallelized using OpenMP by adding just
C four lines 

C (1) A line to include omp.h -- the include file that 
C contains OpenMP's function prototypes and constants.
 
C (2) A pragma that tells OpenMP to create a team of threads

C (3) A pragma to cause one of the threads to print the
C number of threads being used by the program.

C (4) A pragma to split up loop iterations among the team
C of threads.  This pragma includes 2 clauses to (1) create a 
C private variable and (2) to cause the threads to compute their
C sums locally and then combine their local sums into a 
C single global value.

C History: C Code written by Tim Mattson, 11/1999.
C          Adapted to Fortran code by Helen He, 09/2017. 

        PROGRAM MAIN
        USE OMP_LIB
        IMPLICIT NONE

        INTEGER i
        INTEGER*8 num_steps
        REAL*8 error  
        INTEGER, PARAMETER :: NSTEPS=100000000
        REAL*8, PARAMETER :: REAL_PI = 3.1415926535897932
        REAL*8 x, pi, sum, step
        REAL*8 start_time, run_time

        sum = 0.0

        CALL OMP_SET_NUM_THREADS(4)

        num_steps = 1
        DO WHILE  (num_steps < NSTEPS) 
           step = 1.0/ num_steps

           sum = 0.0
!$OMP PARALLEL DO REDUCTION(+:sum) PRIVATE(x)
           DO i=1, num_steps
              x = (i-0.5)*step
              sum = sum + 4.0/(1.0+x*x)
           ENDDO
!$OMP END PARALLEL DO

           pi = step * sum
           error = ABS(pi-REAL_PI)
             
           WRITE(*,100) 1.0*num_steps, pi, error
100        FORMAT(f20.6, f15.8, e15.7)

          num_steps = 10 * num_steps
          ENDDO

          STOP
          END
