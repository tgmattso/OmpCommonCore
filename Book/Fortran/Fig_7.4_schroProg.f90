! sample compile command: "gfortran -fopenmp -c Fig_7.4_schroProg.f90" to generate *.o object file

program main
   use omp_lib
   implicit none
   external :: seedIt 
   logical, external :: flip
   real*8, external :: waitAbit

   real*8 :: wait_val, val
   integer*8 :: rand, i 
   logical :: dead_or_alive
   
   ! "flip a coin" to choose which task is for the dead
   ! cat and which for the living cat.
   integer*8 :: coin
   logical ::  HorT

   call omp_set_num_threads(2)
   call seedIt(coin)
   HorT = flip(coin)
   
   print *, "Schrodinger's program says the cat is"
    
   !$omp parallel shared(HorT, dead_or_alive) private(val)
      ! These tasks are participating in a data race        
      !$omp task
         val = waitAbit()
         dead_or_alive = HorT
      !$omp end task
      !$omp task
         val = waitAbit()
         dead_or_alive = .not. HorT
      !$omp end task
   !$omp end parallel
   if (dead_or_alive) then
      print *, " alive. "
   else 
      print *, " dead. "
   endif

end program main
