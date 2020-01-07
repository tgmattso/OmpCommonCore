C This program will numerically compute the integral of
C                   4/(1+x*x) 
C from 0 to 1.  The value of this integral is pi -- which 
C is great since it gives us an easy way to check the answer.

C This version of the program uses a divide and concquer algorithm
C with tasks and taskwait.

C History: C Code written by Tim Mattson, 10/2013
C          Adapted to Fortran code by Helen He, 09/2017. 

       PROGRAM MAIN
       USE OMP_LIB
       IMPLICIT NONE

       INTEGER i, j
       INTEGER, PARAMETER :: num_steps = 1024*1024*1024
       INTEGER, PARAMETER :: MAX = 4
       REAL*8  step, pi, sum
       REAL*8  init_time, final_time, pi_comp
 
       step = 1.0 / num_steps

       DO j = 1, MAX
          CALL omp_set_num_threads(j)
          init_time = OMP_GET_WTIME()

!$OMP PARALLEL 
!$OMP SINGLE 
         PRINT *, "num threads=",omp_get_num_threads()
               sum = pi_comp(0,num_steps,step)
!$OMP END SINGLE 
!$OMP END PARALLEL 
          pi = step * sum;
          final_time = OMP_GET_WTIME() - init_time;
          WRITE(*,100) num_steps, pi, final_time 
100       FORMAT(' for ',i14,' steps, pi = ',f15.8,' in ',f8.3,' secs') 

       ENDDO

       STOP
       END

       RECURSIVE FUNCTION pi_comp(Nstart,Nfinish,step) RESULT(sum)
       IMPLICIT NONE

       INTEGER i, iblk
       INTEGER, PARAMETER :: MIN_BLK = 1024*1024*256
       INTEGER Nstart, Nfinish
       REAL*8 x, sum, sum1, sum2, step

       sum = 0.0

       IF (Nfinish-Nstart < MIN_BLK) THEN
          DO i = Nstart, Nfinish
             x = (i+0.5)*step
             sum = sum + 4.0/(1.0+x*x)
          ENDDO
       ELSE
          iblk = Nfinish-Nstart

!$OMP TASK SHARED(sum1)
          sum1 = pi_comp(Nstart,         Nfinish-iblk/2,step)
!$OMP END TASK 
!$OMP TASK SHARED(sum2)
          sum2 = pi_comp(Nfinish-iblk/2, Nfinish,       step)
!$OMP END TASK 
!$OMP TASKWAIT
          sum = sum1 + sum2
       ENDIF

       END FUNCTION pi_comp
