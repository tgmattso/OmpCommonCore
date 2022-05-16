          PROGRAM MAIN
          USE OMP_LIB
          IMPLICIT NONE

          INTEGER :: i, id
          INTEGER, PARAMETER :: num_steps=100000000
          INTEGER :: NTHREADS = 4
          REAL*8 :: x, pi, sum, step
          REAL*8 :: start_time, run_time

          sum = 0.0

          step = 1.0 / num_steps

          CALL OMP_SET_NUM_THREADS(NTHREADS)
          start_time = OMP_GET_WTIME()

!$OMP PARALLEL PRIVATE(i,x) 
!$OMP DO REDUCTION(+:sum)
          DO i = 1, num_steps
             x = (i - 0.5) * step
             sum = sum + 4.0 / (1.0 + x * x)
          ENDDO
!$OMP END DO
!$OMP END PARALLEL  

          pi = step * sum
          run_time = OMP_GET_WTIME() - start_time
          WRITE(*,100) pi, run_time
100       FORMAT('pi is ',f15.8,' in ',f8.3,' secs')

          END PROGRAM MAIN
