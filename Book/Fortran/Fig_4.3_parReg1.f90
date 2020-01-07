Program parReg1 
   use omp_lib
  implicit none

   integer :: ID, size_of_team, NThrds
   call omp_set_num_threads(4)                                              
   !$omp parallel private(ID,NThrds)
      ID = omp_get_thread_num()
      NThrds = omp_get_num_threads()
      if (ID == 0) size_of_team = NThrds
   !$omp end parallel
  print *, "We just did the join on a team of size ", size_of_team
end Program parReg1
