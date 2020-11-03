  PROGRAM MAIN
  USE OMP_LIB
  IMPLICIT NONE

  INTEGER :: nthreads=4
  INTEGER :: id

  CALL OMP_SET_NUM_THREADS(nthreads)

!$OMP PARALLEL private(id)
  id = OMP_GET_THREAD_NUM()
  PRINT *, "Hello World from thread = ", id, &
     &         " with ", OMP_GET_NUM_THREADS(), " threads"
!$OMP END PARALLEL
  PRINT *, "all done, with hopefully ",nthreads," threads"

  END PROGRAM MAIN
