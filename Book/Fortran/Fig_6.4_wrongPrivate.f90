! sample compile command to generate *.o object file:
!     gfortran -fopenmp -c Fig_6.4_wrongPrivate.f90

program wrong
   integer :: tmp
   tmp = 0

!$omp parallel do private(tmp)
   do j = 1, 1000
      tmp = tmp +j
   enddo
!$omp end parallel do

   print *, tmp   ! tmp is 0 here
end program wrong
