!  PROGRAM: Mandelbrot area
!
!  PURPOSE: Program to compute the area of a  Mandelbrot set.
!           Correct answer should be around 1.510659.
!
!  USAGE:   Program runs without input ... just run the executable
!           
!  HISTORY: Written:  (Mark Bull, August 2011).
!           Changed "comples" to "d_comples" to avoid collsion with 
!           math.h complex type (Tim Mattson, September 2011)
!           Converted to Fortran90 code (Helen He, September 2017)
!           Implemented a "reduction" version (Helen He, November 2020)

  MODULE  mandel_reduction_module
  implicit none

  INTEGER, PARAMETER :: DP = SELECTED_REAL_KIND(14)

  INTEGER, PARAMETER :: NPOINTS = 1000
  INTEGER, PARAMETER :: MAXITER = 1000
  INTEGER :: numoutside = 0

  TYPE d_complex
     REAL(KIND = DP) :: r
     REAL(KIND = DP) :: i
  END TYPE d_complex

  contains 

     INTEGER FUNCTION testpoint(c) result(outside)

! Does the iteration z=z*z+c, until |z| > 2 when point is known to be outside set
! If loop count reaches MAXITER, point is considered to be inside the set

     implicit none
     TYPE(d_complex) :: z,c
     INTEGER :: iter
     REAL(KIND = DP) :: temp

     z = c
     outside = 0

     DO iter = 1, MAXITER
        temp = (z%r*z%r) - (z%i*z%i) + c%r
        z%i = z%r*z%i*2 + c%i
        z%r = temp

        IF ((z%r*z%r + z%i*z%i) > 4.0) THEN 
           outside = outside + 1
           EXIT
        ENDIF
     ENDDO

     END FUNCTION testpoint

  END MODULE mandel_reduction_module


  PROGRAM mandel_reduction

  USE OMP_LIB
  USE mandel_reduction_module
  IMPLICIT NONE

  INTEGER :: i, j
  REAL(KIND = DP) :: area, error
  REAL(KIND = DP) :: eps = 1.0e-5
  INTEGER :: outside

  TYPE(d_complex) :: c

  CALL OMP_SET_NUM_THREADS(4)

! Loop over grid of points in the complex plane which contains the Mandelbrot set,
! testing each point to see whether it is inside or outside the set.

!$OMP PARALLEL DO DEFAULT(shared) FIRSTPRIVATE(eps) PRIVATE(c,j) REDUCTION(+:numoutside) 

  DO i = 1, NPOINTS  
  DO j = 1, NPOINTS 
     c%r = -2.0 + 2.5 * DBLE(i-1) / DBLE(NPOINTS) + eps
     c%i = 1.125 * DBLE(j-1) / DBLE(NPOINTS) + eps
     numoutside = numoutside + testpoint(c)
  ENDDO
  ENDDO
!$OMP END PARALLEL DO

! Calculate area of set and error estimate and output the results
  write(*,*)"numoutside=", numoutside
   
  area = 2.0*2.5*1.125 * DBLE(NPOINTS*NPOINTS - numoutside)    &
     &        / DBLE(NPOINTS*NPOINTS)
  error = area / DBLE(NPOINTS)

  WRITE(*,100) area, error
100    FORMAT("Area of Mandlebrot set = ", f12.8, f12.8)
  WRITE(*,*)"Correct answer should be around 1.510659"

  END PROGRAM mandel_reduction
