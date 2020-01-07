! sample compile command to generate *.o object file:
!     gfortran -fopenmp -c Fig_8.3_regPromote.f90

program main
   use omp_lib
   implicit none

   interface
      function doit(A, N, id) 
         integer :: N, id
         real*8 :: A(N)
         real*8 :: doit
      end function
   end interface

   integer, parameter :: MAX = 10000
   integer, parameter :: NMAX = 1000
   real, parameter :: TOL = 0.0001
   
   integer :: iter, N
   real*8 :: A(NMAX)
   real*8 :: conv
   integer :: id, nthrd

   iter = 0
   N = 1000
   A = 0.0
   conv = 0.0

   !$omp parallel shared(A,N,iter) firstprivate(conv) private(id,nthrd)
      id = omp_get_thread_num()
      nthrd = omp_get_num_threads()

      do while (iter < MAX) 
         conv = doit(A, N, id)
         if (conv < TOL) exit
         if (id == 0) iter = iter + 1
      end do 
   
   !$omp end parallel

end program main
