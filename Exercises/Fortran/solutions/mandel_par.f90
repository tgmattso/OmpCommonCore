!  PROGRAM: Mandelbrot area
!
!  PURPOSE: Program to compute the area of a  Mandelbrot set.
!           Correct answer should be around 1.510659.
!           WARNING: this program may contain errors
!
!  USAGE:   Program runs without input ... just run the executable
!            
!  HISTORY: Written:  (Mark Bull, August 2011).
!           Changed "comples" to "d_comples" to avoid collsion with 
!           math.h complex type (Tim Mattson, September 2011)
!           Adapted to Fortran90 code (Helen He, September 2017)
!	    Simplified Fortran90 code based on Tim's corresponding
!           simplification in C (Helen He, November 2023)


  MODULE  mandel_module
  implicit none

  INTEGER, PARAMETER :: DP = SELECTED_REAL_KIND(14)

  INTEGER, PARAMETER :: NPOINTS=1000
  INTEGER, PARAMETER :: MAXITER=1000
  INTEGER :: numoutside=0

  contains 

     SUBROUTINE testpoint(creal, cimag)

! Does the iteration z=z*z+c, until |z| > 2 when point is known to be outside set
! If loop count reaches MAXITER, point is considered to be inside the set

     INTEGER :: iter
     REAL(KIND = DP) :: temp
     REAL(KIND = DP) :: zreal, zimag
     REAL(KIND = DP) :: creal, cimag

     zreal = creal
     zimag = cimag

     DO iter = 1, MAXITER
        temp = (zreal*zreal)-(zimag*zimag)+creal
        zimag = zreal*zimag*2+cimag
        zreal = temp

        IF ((zreal*zreal+zimag*zimag)>4.0) THEN 
           !$OMP CRITICAL
           numoutside = numoutside + 1
           !$OMP END CRITICAL
           EXIT
        ENDIF
     ENDDO

     END SUBROUTINE

  END MODULE mandel_module

  PROGRAM MAIN
  USE OMP_LIB
  USE mandel_module
  IMPLICIT NONE

  INTEGER :: i, j
  REAL(KIND = DP) :: area, error
  REAL(KIND = DP) :: eps = 1.0e-5
  REAL(KIND = DP) :: creal, cimag

! Loop over grid of points in the complex plane which contains the Mandelbrot set,
! testing each point to see whether it is inside or outside the set.

!$OMP PARALLEL DO DEFAULT(shared) PRIVATE(creal,cimag,j) FIRSTPRIVATE(eps)

  DO i = 1, NPOINTS
  DO j = 1, NPOINTS
     creal = -2.0+2.5*DBLE(i-1)/DBLE(NPOINTS)+eps
     cimag = 1.125*DBLE(j-1)/DBLE(NPOINTS)+eps
     CALL testpoint(creal, cimag)
  ENDDO
  ENDDO
!$OMP END PARALLEL DO

! Calculate area of set and error estimate and output the results
   
  area = 2.0*2.5*1.125*DBLE(NPOINTS*NPOINTS-numoutside)   &
     &        /DBLE(NPOINTS*NPOINTS)
  error = area/DBLE(NPOINTS)

  write(*,*)"numoutside=", numoutside
  WRITE(*,100) area, error
100    FORMAT("Area of Mandlebrot set = ", f12.8, "  +/-", f12.8)
  WRITE(*,*)"Correct answer should be around 1.510659"

  END PROGRAM MAIN
