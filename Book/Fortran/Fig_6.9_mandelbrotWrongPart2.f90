!C combine Fig_6.9_mandelbrotWrongPart2.f90 and Fig_6.8_mandelbrotWrongPart1.f90 into one file, and name it as mandel_wrong.f90
!C (notice part2 of mandel_wrong_module has to come before part1 of main program))   
!C sample compile command: gfortran -fopenmp -o mandel_wrong mandel_wrong.f90



       MODULE  mandel_module
       implicit none

       INTEGER, PARAMETER :: DP = SELECTED_REAL_KIND(14)

       REAL(KIND = DP) :: r

       INTEGER, PARAMETER :: NPOINTS=1000
       INTEGER, PARAMETER :: MAXITER=1000
       INTEGER :: numoutside=0

       TYPE d_complex
          REAL(KIND = DP) :: r
          REAL(KIND = DP) :: i
       END TYPE d_complex

       TYPE(d_complex) :: c

       contains 

          SUBROUTINE testpoint()

!C Does the iteration z=z*z+c, until |z| > 2 when point is known to be outside set
!C If loop count reaches MAXITER, point is considered to be inside the set

          implicit none
          TYPE(d_complex) :: z
          INTEGER :: iter
          REAL(KIND = DP) :: temp

          z = c

          DO iter = 1, MAXITER
             temp = (z%r*z%r) - (z%i*z%i) + c%r
             z%i = z%r*z%i*2 + c%i
             z%r = temp

             IF ((z%r*z%r + z%i*z%i) > 4.0) THEN 
                numoutside = numoutside + 1
                EXIT
             ENDIF
          ENDDO

          END SUBROUTINE

       END MODULE mandel_module
