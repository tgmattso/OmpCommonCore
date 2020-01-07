Program parReg 
   use omp_lib
   implicit none

   real :: A(10)
   integer :: ID

   A = 0
   call omp_set_num_threads(4)                                               

   !$omp parallel private(ID)
      ID = omp_get_thread_num()
      call pooh (ID, A)
      write(*,100)ID, A(ID)
100 format("A of ID(", I3, ")=",f10.4) 
   !$omp end parallel

   contains

   subroutine pooh (ID, A)
      integer :: ID
      real, dimension(:) :: A
      A(ID) = ID
   end subroutine pooh 

end Program parReg
