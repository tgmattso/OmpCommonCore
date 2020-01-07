          PROGRAM MAIN

          USE OMP_LIB
          IMPLICIT NONE

          INTEGER :: i
          INTEGER, PARAMETER :: num_steps = 100000000
          REAL*8 :: x, pi, sum, step
          REAL*8 :: start_time, run_time

          sum = 0.0

          step = 1.0/num_steps
          start_time = OMP_GET_WTIME()

          DO i = 1, num_steps
             x = (i - 0.5) * step
             sum = sum + 4.0 / (1.0 + x * x)
          ENDDO

          pi = step * sum
          run_time = OMP_GET_WTIME() - start_time

          WRITE(*,100) pi, num_steps,  run_time
100       FORMAT('pi = ', f15.8, ',', i14, ' steps,',f8.3,' secs')

          END PROGRAM MAIN 
