! This is a Fortran wrapper to call C Pthreads function
! To compile:
! % gfortran -c Fig_1.5_PosixHello.f90 
! % gcc -c Fig_1.5_PosixHello_external.c 
! % gfortran Fig_1.5_PosixHello.o Fig_1.5_PosixHello_external.o 

program main
   implicit none
   external :: pthreads_c
   call pthreads_c()
end program main 
