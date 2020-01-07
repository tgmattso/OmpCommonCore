          PROGRAM MAIN
          IMPLICIT NONE

          INTEGER :: i
          INTEGER, PARAMETER :: num_steps = 1000000
          REAL :: x, pi, sum, step

          sum = 0.0

          step = 1.0/num_steps

          DO i = 1, num_steps
             x = (i - 0.5) * step
             sum = sum + 4.0 / (1.0 + x * x)
          ENDDO

          pi = step * sum
          print *, "pi=", pi

          END PROGRAM MAIN 
