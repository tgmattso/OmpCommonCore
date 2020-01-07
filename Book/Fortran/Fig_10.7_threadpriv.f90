! sample compile command to generate *.o object file:
!      gfortran -fopenmp -c Fig_10.7_threadpriv.f90

module data_mod
   implicit none
   integer :: counter
   !$omp threadprivate(counter)
   type node
      integer :: data
      type(node), pointer :: next
   end type node
   contains
      subroutine init_list(p)
         type (node), pointer :: p
         ! init list here
      end subroutine
      subroutine processwork(p)
         type (node), pointer :: p
         ! proces work here
      end subroutine
      subroutine freeList(p)
         type (node), pointer :: p
         ! free list here
      end subroutine
      subroutine inc_count()
          integer :: counter 
          counter = counter + 1
      end subroutine
end module data_mod
  
program main
   use omp_lib
   use data_mod
   implicit none 

   type(node), pointer :: head
   type(node), pointer :: p
   counter = 0
   call init_list(p)
   head => p

   !$omp parallel private(p)
      !$omp single
         p => head
         do
            !$omp task firstprivate(p)
               counter = counter + 1
               call processwork(p)
            !$omp end task
            p => p%next
            if (.not. associated(p)) exit
         end do
      !$omp end single
   !$omp end parallel

   call freeList(p)
end program main
