program main
   use omp_lib
   implicit none

   integer :: x, y, r
   integer :: id, nthrds
   x = 0
   y = 0
   r = 0
   call omp_set_num_threads(2)  ! request two threads
   !$omp parallel private(id,nthrds)
      id = omp_get_thread_num()    
      !$omp single
         nthrds = omp_get_num_threads()
         ! verify that we have at least two threads
         if (nthrds < 2) stop 1 
      !$omp end single

      if (id == 0) then
         x = 1
         r = x
      else if (id == 1) then
         if (r == 1) then
            y = x;
            if (y /= 1) then
                stop "fails y==1"   ! Assertion will occasionally fail; 
                                    ! i.e., r == 1 while x == 0
            endif
         endif
      endif
   !$omp end parallel
end program main
