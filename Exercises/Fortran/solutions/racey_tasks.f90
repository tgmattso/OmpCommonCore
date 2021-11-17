! This is a very simple program to play with tasks.
! the idea is to print one of two strings
!     I think race cars are fun.
!     I think car races are fun
!  This is a race condition since depending on how the
!  threads are scheduled, you will get a different answer.
!  We aren't writing any variables.  Hence this is not
!  a data race and the program is legal.

program main
   use omp_lib
   implicit none

   write(*,"(A)",advance="no")"I think"

!$OMP PARALLEL
   !$OMP SINGLE
      !$OMP TASK
         write(*,"(A)",advance="no")" car"
         call sleep(1)
      !$OMP END TASK

      !$OMP TASK
         write(*,"(A)",advance="no")" race"
         call sleep(1)
      !$OMP END TASK
   !$OMP END SINGLE
!$OMP END PARALLEL
   write(*,"(A)",advance="no")"s"
   write(*,"(A)")" are fun!"

end program main
