from numba import njit
from numba.openmp import openmp_context as openmp

@njit
def hello():
    with openmp ("parallel"):
        print("hello")
        print("world")

hello()
