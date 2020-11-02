! NAME:   PI SPMD final version without false sharing
! This program will numerically compute the integral of
!                   4/(1+x*x) 
! from 0 to 1.  The value of this integral is pi -- which 
! is great since it gives us an easy way to check the answer.

! The program was parallelized using OpenMP and an SPMD 
! algorithm.  The following OpenMP specific lines were 
! added: 

! (1) A line to include omp.h -- the include file that 
! contains OpenMP's function prototypes and constants.

! (2) A pragma that tells OpenMP to create a team of threads
! with an integer variable i being created for each thread.

! (3) two function calls: one to get the thread ID (ranging
! from 0 to one less than the number of threads), and the other
! returning the total number of threads.

! (4) A "single" construct so only one thread prints the number
! of threads.

! (5) A cyclic distribution of the loop by changing loop control
! expressions to run from the thread ID incremented by the number 
! of threads.  Local sums accumlated into sum[id].

! (6) A barrier to make sure everyone's done.

! (7) A single construct so only one thread combines the local
! sums into a single global sum.

! Note that this program avoids the false sharing problem
! by storing partial sums into a private scalar.

! History: C Code written by Tim Mattson, 11/1999
!          Adapted to Fortran code by Helen He and Tim Mattson, 09/2017
!          Changed to Fortran90 code by Helen He, 11/2020 

        PROGRAM MAIN
        USE OMP_LIB
        IMPLICIT NONE

        INTEGER :: i, j, id, numthreads, nthreads
        INTEGER, PARAMETER :: num_steps=100000000
        INTEGER, PARAMETER :: MAX_THREADS=4
        REAL*8 :: pi, real_sum, step, full_sum, x
        REAL*8 :: start_time, run_time
        REAL*8 :: sum(0:MAX_THREADS-1)
        REAL*8 :: partial_sum

        full_sum = 0.0

        step = 1.0 / num_steps
        start_time = OMP_GET_WTIME()

        DO j = 1, MAX_THREADS
           CALL OMP_SET_NUM_THREADS(j)
           full_sum = 0.0
           start_time = OMP_GET_WTIME()

!$OMP PARALLEL PRIVATE(i, id, numthreads, partial_sum, x)
           id = OMP_GET_THREAD_NUM()
           numthreads = OMP_GET_NUM_THREADS()
           partial_sum = 0.0

!$OMP SINGLE 
           nthreads = numthreads
!$OMP END SINGLE NOWAIT

           DO i = id, num_steps - 1, numthreads
              x = (i + 0.5) * step
              partial_sum = partial_sum + 4.0 / (1.0 + x*x)
           ENDDO

!$OMP CRITICAL
           full_sum = full_sum + partial_sum
!$OMP END CRITICAL

!$OMP END PARALLEL
      
           pi = step * full_sum
           run_time = OMP_GET_WTIME() - start_time
           WRITE(*,100) pi, run_time, nthreads
100        FORMAT('pi is ',f15.8,' in ',f8.3,'secs and ',i3,' threads')
        ENDDO

        END PROGRAM MAIN
