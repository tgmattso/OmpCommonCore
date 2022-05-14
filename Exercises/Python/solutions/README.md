These are parallel OpenMP programs in Python for the PyOMP tutorial
we are developing.   Some of them select the number of threads
in the source code (using omp_set_num_threads) while others take the
number of threads from the command line.  In that case, put the
number of threads on the command line as shown for 8 threads an the
pi_loop program:

     OMP_NUM_THREADS=8 python pi_loop.py

