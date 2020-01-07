        PROGRAM MAIN
        USE OMP_LIB
        IMPLICIT NONE

        INTEGER, PARAMETER :: MAX_THREADS = 4
        INTEGER ::  i, j, id, numthreads, nthreads
        INTEGER, PARAMETER :: num_steps = 100000000
        REAL*8 ::  pi, real_sum, step, x
        REAL*8 :: start_time, run_time
        REAL*8 :: sum(0:MAX_THREADS-1)

        step = 1.0 / num_steps

        CALL OMP_SET_NUM_THREADS(MAX_THREADS)
        start_time = omp_get_wtime()

!$OMP PARALLEL PRIVATE(id,x,numthreads)
        id = omp_get_thread_num()
        numthreads = OMP_GET_NUM_THREADS()
        sum(id) = 0.0

        IF (id == 0)  THEN
           nthreads = numthreads
        ENDIF

        DO i = id, num_steps - 1, numthreads
           x = (i + 0.5) * step
           sum(id) = sum(id) + 4.0 / (1.0 + x * x)
        ENDDO
!$OMP END PARALLEL

        pi = 0.0
        DO i = 0, nthreads-1
           pi = pi + sum(i)
        ENDDO

        pi = step * pi
        run_time = OMP_GET_WTIME() - start_time
        WRITE(*,100) pi, num_steps,  run_time
100     FORMAT('pi = ', f15.8, ',', i14, ' steps,',f8.3,' secs')

        END PROGRAM MAIN


