!C combine Fig_6.11_mandelbrotSolutionPart2.f90 and Fig_6.10_mandelbrotSolutionPart1.f90 into one file, and name it as mandel_par.f90
!C (notice part2 of mandel_par_module has to come before part1 of main program)) 
!C sample compile command: gfortran -fopenmp -o mandel_wrong mandel_par.f90

       PROGRAM mandel_par

       USE OMP_LIB
       USE mandel_par_module
       IMPLICIT NONE

       INTEGER :: i, j
          REAL(KIND = DP) :: area, error
          REAL(KIND = DP) :: eps = 1.0e-5

       TYPE(d_complex) :: c

!C   Loop over grid of points in the complex plane which contains the Mandelbrot set,
!C   testing each point to see whether it is inside or outside the set.

!$OMP PARALLEL DO DEFAULT(shared) FIRSTPRIVATE(eps) PRIVATE(c,j) 
       DO i = 1, NPOINTS  
       DO j = 1, NPOINTS 
          c%r = -2.0 + 2.5 * DBLE(i-1) / DBLE(NPOINTS) + eps
          c%i = 1.125 * DBLE(j-1) / DBLE(NPOINTS) + eps
          CALL testpoint(c)
       ENDDO
       ENDDO
!$OMP END PARALLEL DO

!C Calculate area of set and error estimate and output the results
       write(*,*)"numoutside=", numoutside
   
       area = 2.0*2.5*1.125 * DBLE(NPOINTS*NPOINTS - numoutside)    &
     &        / DBLE(NPOINTS*NPOINTS)
       error = area / DBLE(NPOINTS)

       WRITE(*,100) area, error
100    FORMAT("Area of Mandlebrot set = ", f12.8, f12.8)
       WRITE(*,*)"Correct answer should be around 1.510659"

       END PROGRAM mandel_par
