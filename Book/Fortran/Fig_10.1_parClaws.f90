! sample compile command to generate *.o object file:
!      gfortran -fopenmp -c Fig_10.1_parClaw.f90

program main
   use omp_lib

   interface
     !  initialization function 
      subroutine initMats(N, A, T)
         integer :: N
         real, dimension(:,:), allocatable :: A, T
      end subroutine 
     !  transform function 
      subroutine transform(N, id, Nthrds, A, T)
         integer :: N, id, Nthrds
         real, dimension(:,:), allocatable :: A, T
      end subroutine 
   end interface

   real :: trace = 0
   integer :: i, id, N, Nthrds
   real, dimension(:,:), allocatable :: A, T

   integer :: narg     ! number of Arg
   character(len=10) :: name ! Arg name

   narg = command_argument_count()
   if (narg == 1) then
      call get_command_argument(1,name)
      read(name,*) N
   else
       N = 10
   endif
   print *, "N=", N

   ! allocate space for three N x N matrices and initialize them
   allocate (T(N,N))
   allocate (A(N,N))
   call initMats(N, A, T)
 
   !$omp parallel if(N>100) num_threads(4) default(none) &
   !$omp&          shared(A,T,N) private (i,id,Nthrds) reduction(+:trace)
      id = omp_get_thread_num()
      Nthrds = omp_get_num_threads()
      call transform(N, id, Nthrds, T, A)

      ! compute trace of A matrix
      ! i.e., the sum of diagonal elements
      !$omp do
         do i = 1, N
            trace = trace + A(i,i)
         enddo
      !$omp end do
   !$omp end parallel
   print *, " transform complete with trace = ",trace
end program main 
