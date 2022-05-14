from numba import njit
from numba.openmp import openmp_context as openmp
from numba.openmp import omp_get_wtime, omp_get_num_threads, omp_set_num_threads

@njit
def piFunc(NumSteps):
    step = 1.0/NumSteps
    sum = 0.0
    startTime = omp_get_wtime()
    with openmp ("parallel for private(x) reduction(+:sum)"):
        for i in range(NumSteps):
           x = (i+0.5)*step
           sum += 4.0/(1.0 + x*x)

    pi = step*sum
    runTime = omp_get_wtime() - startTime
    print(" pi = ",pi," with ",NumSteps," steps in ",runTime," seconds")
    return pi

startTimeWithJit = omp_get_wtime()
pi = piFunc(100000000)
print(" runtime with JIT = ",omp_get_wtime() - startTimeWithJit)
