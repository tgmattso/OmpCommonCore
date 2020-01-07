C This program will numerically compute the integral of
C                   4/(1+x*x) 
C from 0 to 1.  The value of this integral is pi -- which 
C is great since it gives us an easy way to check the answer.

C This version of the program uses a divide and concquer algorithm
C and recurrsion.

C History: C code written by Tim Mattson, 10/2013.
C adapted to Fortran code by Helen He, 09/2017. 

       PROGRAM MAIN
       USE OMP_LIB
       IMPLICIT NONE

       INTEGER i
       INTEGER, PARAMETER :: num_steps = 1024*1024*1024
       REAL*8  step, pi, sum
       REAL*8  init_time, final_time, pi_comp
 
       step = 1.0 / num_steps

       init_time = OMP_GET_WTIME()
       sum = pi_comp(0,num_steps,step)
       pi = step * sum
       final_time = OMP_GET_WTIME() - init_time
       WRITE(*,100) num_steps, pi, final_time 
100    FORMAT(' for ', i14,' steps, pi = ', f15.8,' in ', f8.3,' secs') 

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
          sum1 = pi_comp(Nstart,         Nfinish-iblk/2,step)
          sum2 = pi_comp(Nfinish-iblk/2, Nfinish,       step)
          sum = sum1 + sum2
       ENDIF

       END FUNCTION pi_comp


