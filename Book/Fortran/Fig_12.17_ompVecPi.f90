          PROGRAM MAIN
          IMPLICIT NONE

          INTEGER :: i
          INTEGER, PARAMETER :: num_steps = 100000
          REAL :: x, pi, sum, step

          sum = 0.0

          step = 1.0/num_steps

!$OMP parallel SIMD private(x) reduction(+:sum)
          DO i = 1, num_steps
             x = (i - 0.5) * step
             sum = sum + 4.0 / (1.0 + x * x)
          ENDDO
!$OMP end parallel SIMD

          pi = step * sum
          print *, "pi=", pi

          END PROGRAM MAIN 
