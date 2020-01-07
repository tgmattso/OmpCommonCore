	  PROGRAM MAIN
	  IMPLICIT NONE

	  INTEGER :: i
	  INTEGER, PARAMETER :: num_steps = 100000
	  REAL :: x0, x1, x2, x3, pi, sum
	  REAL :: step

	  sum = 0.0
	  step = 1.0/num_steps

	  DO i = 1, num_steps, 4
	     x0 = (i - 0.5) * step
	     x1 = (i + 0.5) * step
	     x2 = (i + 1.5) * step
	     x3 = (i + 2.5) * step
	     sum = sum + 4.0 * (1.0 / (1.0 + x0 * x0) + 1.0 /(1.0 + x1 * x1)  &
		       & + 1.0 / (1.0 + x2 * x2) + 1.0 /(1.0 + x3 * x3))  
	  ENDDO

	  pi = step * sum

          WRITE(*,100) pi, num_steps
100       FORMAT('pi = ', f15.8, ',', i14, ' steps')

          END PROGRAM MAIN 
