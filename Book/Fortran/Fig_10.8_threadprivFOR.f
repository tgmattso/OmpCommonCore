// sample compile command: gfortran -fopenmp -c Fig_10.8_threadprivFOR.f" to generate *.o object file

      INTEGER FUNCTION INCREMENT_COUNTER()
      COMMON/INC_COMMON/COUNTER
!$OMP THREADPRIVATE(/INC_COMMON/)
      COUNTER = COUNTER +1
      INCREMENT_COUNTER = COUNTER
      RETURN
      END FUNCTION INCREMENT_COUNTER    
