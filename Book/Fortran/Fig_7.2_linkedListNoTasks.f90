! sample compile command to generate *.o object file:
!      gfortran -fopenmp -c Fig_7.2_linkedListNoTasks.f90

module list_mod
   integer, parameter :: NMAX = 10
   type :: node
      integer :: data
      integer :: procResult
      type(node), pointer :: next
   end type node
end module list_mod

program main 
   use list_mod
   implicit none

   type(node), pointer :: p => null()
   type(node), pointer :: temp => null()
   type(node), pointer :: head => null()
   type(node), dimension(:), allocatable, target :: parr
   
   interface
   ! initialize the list (not shown)
      subroutine initList(p)
         use list_mod
         implicit none
         type(node), pointer :: p
      end subroutine initList

   ! a long computation (not shown)
      integer function work(data)
         implicit none
         integer :: data 
      end function work
   end interface

   integer :: i, count
    
   call initList(p)
    
   ! save head of the list
   head => p  

   count = 0
   do
      p = p%next
      count = count + 1 
      if (.not. associated(p)) exit
   end do

   allocate(parr(NMAX))

   do i = 1, count
      head => p
      head => parr(i)
      p => p%next 
   end do

   !$omp parallel do schedule(static,1) 
   do i = 1, count
      call procWork(parr(i)) 
   end do
   !$omp end parallel do 

  contains

  subroutine procWork (a_node)
     use list_mod
     implicit none
     type(node) :: a_node
     integer :: n
     n = a_node%data
     p%procResult = work(n)
  end subroutine procWork 

end program main 
