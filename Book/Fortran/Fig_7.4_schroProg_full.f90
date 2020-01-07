!  Schrodingers racy program ... is the cat dead or alive?
!
!  You can use atomics and make the program race free, or comment out
!  the atomics and run with a race condition.  It works in both cases
!
!  History: Written by Tim Mattson, Feb 2019
!           Converted to Fortran by Helen He, Nov 2019


program main
   use omp_lib
   implicit none

   ! random number generator parameters
   ! (from numerical recipies)
   integer, parameter :: MULT = 4096
   integer, parameter :: ADD = 150889
   integer, parameter :: MOD_val = 714025

   real*8 :: wait_val, val
   integer*8 :: rand, i, dcount, lcount, coin
   logical :: dead_or_alive, HorT
   integer, parameter :: NTRIALS = 10

   dcount = 0
   lcount = 0

   do i = 1, NTRIALS
   !$omp parallel num_threads(2) shared(dead_or_alive) private(val)
       if(omp_get_thread_num() == 0) then
         print *, " with ", omp_get_num_threads(), " threads."
         write(*, '(a)', advance='no')"Schrodingers program says the cat is "
       endif
       
       !$omp single
          ! "flip a coin" to choose which task is for the dead
          ! cat and which for the living cat.
          call seedIt(coin)
          HorT = flip(coin)

          ! without the atomics, these tasks are participating in a 
          ! data race, but the program logic works fine if the actual 
          ! value is messed up since in C any int other than 1 is false
          !$omp task
              val = waitAbit()
              ! a store of a single machine word (bool)
              !$omp atomic write
                 dead_or_alive = HorT
              !$omp end atomic
          !$omp end task
          !$omp task
              val = waitAbit()
              ! a store of a single machine word (bool)
              !$omp atomic write
                 dead_or_alive = .not. HorT
              !$omp end atomic
          !$omp end task
       !$omp end single
   !$omp end parallel

   if (dead_or_alive) then
       print *, " alive."
       lcount = lcount + 1
   else 
       print *, " dead."
       dcount = dcount + 1
   endif
   end do   ! end loop over trials (for testing only)

   print *, " dead ", dcount, " times", " and alive ", lcount, " times."

   contains

! seed the pseudo random sequence with time of day
    subroutine seedIt(val)
       implicit none
       integer*8 :: val
       val = int (omp_get_wtime())
    end subroutine seedIt

! Linear congruential random number generator
   integer*8 function nextRan(last) result(next)
      implicit none
      integer*8, intent(in) :: last
      next = mod(MULT*last+ADD, MOD_val)
   end function nextRan


! flip a coin ... heads (true) or tails (false)
   logical function flip(coin)
      implicit none
      integer*8 :: coin
      coin = nextRan(coin)
      if (coin > MOD_val/2) then
         flip = .true.
      else
         flip = .false.
      endif
   end function flip

! wait a short random amount of time
   real*8 function waitAbit() result(val)
      implicit none
      integer*8 :: i, count, rand
      val = 0.0
      call seedIt(rand)
      count = nextRan(rand)
  
      ! do some math to make us wait a while
      do i = 1, count
         rand = nextRan(rand)
         val = val + dble(rand)/dble(MULT)
      end do  
   end function waitAbit
   
end program main
