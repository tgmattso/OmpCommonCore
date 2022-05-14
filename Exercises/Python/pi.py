from numba import njit
from numba.openmp import openmp_context as openmp
from numba.openmp import omp_get_wtime

N = 100000000

@njit
def piFunc(NumSteps):
    step = 1.0/NumSteps
    sum = 0.0
    startTime = omp_get_wtime()
    for i in range(NumSteps):
        x = (i+0.5)*step
        sum = sum + 4.0/(1.0 + x*x)
    pi = step*sum
    runTime = omp_get_wtime() - startTime
    print(" pi = ",pi," with ",NumSteps," steps in ",runTime," seconds")
    return pi

pi = piFunc(N)
