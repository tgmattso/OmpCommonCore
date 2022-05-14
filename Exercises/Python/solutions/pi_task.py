from numba import njit
from numba.openmp import openmp_context as openmp
from numba.openmp import omp_get_wtime, omp_get_num_threads, omp_set_num_threads

#set number of steps and block size to a power of two.   I do
#this because I'm lazy and want my recurrsive splitting of
#loop ranges to match the total number of iterations
#NSTEPS = 1024*1024*1024*1024
NSTEPS  = 100000000
MIN_BLK = 1024*256

@njit
def piComp(Nstart, Nfinish, step):
    iblk = Nfinish-Nstart
    if(iblk<MIN_BLK):
        sum = 0.0
        for i in range(Nstart,Nfinish):
            x= (i+0.5)*step
            sum += 4.0/(1.0 + x*x)
    else:
        sum1 = 0.0
        sum2 = 0.0
        with openmp ("task shared(sum1)"):
            sum1 = piComp(Nstart, Nfinish-iblk/2,step)

        with openmp ("task shared(sum2)"):
            sum2 = piComp(Nfinish-iblk/2,Nfinish,step)

        with openmp ("taskwait"):
            sum = sum1 + sum2

    return sum
    
@njit
def piFunc(NumSteps):
    step = 1.0/NumSteps
    sum = 0.0
    startTime = omp_get_wtime()
    with openmp ("parallel"):
        with openmp ("single"):
             print(" pi with tasks using ", omp_get_num_threads()," threads")
             sum = piComp(0,NumSteps,step)

    pi = step*sum
    runTime = omp_get_wtime() - startTime
    print(" pi = ",pi," with ",NumSteps," steps in ",runTime," seconds")
    return pi

startTimeWithJit = omp_get_wtime()
pi = piFunc(NSTEPS)
#pi = piFunc(MIN_BLK)
print(" runtime with JIT = ",omp_get_wtime() - startTimeWithJit)

