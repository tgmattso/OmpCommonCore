        PROGRAM MAIN
        USE OMP_LIB
        IMPLICIT NONE

        INTEGER :: i, j, id, numthreads, nthreads
        INTEGER, PARAMETER :: num_steps=100000000
        INTEGER, PARAMETER :: MAX_THREADS=4
        REAL*8 :: pi, real_sum, step, full_sum, x
        REAL*8 :: start_time, run_time
        REAL*8 :: sum(0:MAX_THREADS-1)
        REAL*8 :: partial_sum

        full_sum = 0.0
        step = 1.0 / num_steps

        CALL OMP_SET_NUM_THREADS(MAX_THREADS)
        full_sum = 0.0
        start_time = OMP_GET_WTIME()

!$OMP PARALLEL PRIVATE(i,id,numthreads,partial_sum,x)
        id = OMP_GET_THREAD_NUM()
        numthreads = OMP_GET_NUM_THREADS()
        partial_sum = 0.0

       if (id == 0)  nthreads = numthreads

        DO i = id, num_steps-1, numthreads
           x = (i+0.5)*step
           partial_sum = partial_sum + 4.0/(1.0+x*x)
        ENDDO

!$OMP CRITICAL
        full_sum = full_sum + partial_sum
!$OMP END CRITICAL

!$OMP END PARALLEL

        pi = step * full_sum
        run_time = OMP_GET_WTIME() - start_time
        WRITE(*,100) pi, run_time, nthreads
100     FORMAT('pi is ',f15.8,' in ',f8.3,'secs and ',i3,' threads')

        END PROGRAM MAIN

