!C combine Fig_6.9_mandelbrotWrongPart2.f90 and Fig_6.8_mandelbrotWrongPart1.f90 into one file, and name it as mandel_wrong.f90
!C (notice part2 of mandel_wrong_module has to come before part1 of main program)) 
!C sample compile command: gfortran -fopenmp -o mandel_wrong mandel_wrong.f90

       PROGRAM mandel_wrong
       USE OMP_LIB
       USE mandel_module
       IMPLICIT NONE

       INTEGER :: i, j
       REAL(KIND = DP) :: area, error
       REAL(KIND = DP) :: eps = 1.0e-5

!C   Loop over grid of points in the complex plane which contains the Mandelbrot set,
!C   testing each point to see whether it is inside or outside the set.

!$OMP PARALLEL DO DEFAULT(shared) PRIVATE(c,eps)

       DO i = 1, NPOINTS
       DO j = 1, NPOINTS
          c%r = -2.0 + 2.5 * DBLE(i-1) / DBLE(NPOINTS) + eps
          c%i = 1.125 * DBLE(j-1) / DBLE(NPOINTS) + eps
          CALL testpoint()
       ENDDO
       ENDDO
!$OMP END PARALLEL DO

!C Calculate area of set and error estimate and output the results
   
       area = 2.0 * 2.5 *1.125 * DBLE(NPOINTS*NPOINTS - numoutside)   &
     &        /DBLE(NPOINTS*NPOINTS)
       error = area / DBLE(NPOINTS)

       PRINT *, "numoutside=", numoutside
       WRITE(*,100) area, error
100    FORMAT("Area of Mandlebrot set = ", f12.8, "  +/-", f12.8)
       PRINT *,"Correct answer should be around 1.510659"

       END PROGRAM mandel_wrong 
