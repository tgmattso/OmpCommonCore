from numba import njit
import numpy as np
from numba.openmp import openmp_context as openmp
from numba.openmp import omp_get_wtime, omp_get_thread_num 
from numba.openmp import omp_set_num_threads, omp_get_num_threads

NSTEPS = 100000000

@njit
def piFunc(NumSteps):
    step = 1.0/NumSteps
    NTHREADS = 4
    partialSums = np.zeros(NTHREADS)
    omp_set_num_threads(NTHREADS)
    startTime = omp_get_wtime()
    #with openmp("parallel default(none) shared(numThreads,partialSums,step,NumSteps) private(x,i,localSum,  threadID)"):
    with openmp("parallel"):
       threadID = omp_get_thread_num()
       numThreads = omp_get_num_threads()
       if(threadID == 0): 
          print("number of threads =",numThreads)

       localSum = 0.0
       for i in range(threadID,NumSteps,numThreads):
           x = (i+0.5)*step
           localSum = localSum + 4.0/(1.0 + x*x)
       partialSums[threadID] = localSum

    sum = 0.0
    for i in range(numThreads):
        sum = sum + partialSums[i]

    pi = step*sum
    runTime = omp_get_wtime() - startTime
    print(" pi = ",pi," with ",NumSteps," steps in ",runTime," seconds")
    return pi

start = omp_get_wtime()
pi = piFunc(NSTEPS)
print("time including JIT time",omp_get_wtime()-start)
