
This repository supports readers of our book:

     The OpenMP Common Core: making OpenMP Simple Again

We encourage readers to explore the material actively; mixing
time spent reading with time spent coding.   To that end, we
provide lots of code for our readers to explore examples organized into
the following directories.

      Book: Code used in the book.  This includes any
      code that appears in the figures as well as code
      fragments embedded in the text of the book.
      We provide these in both C and Fortran.

      ChallengeProblems: A set of more complex problems to
      support advanced studies in OpenMP.  In each case,
      we include a serial code you can start with and a
      directory of solutions.  Currently, these are
      only provided in C.

      Exercises: code and solutions for the running 
      examples used in the book.  We recommend pausing 
      as you read the book and experiment with these
      exercises ... after all, we all learn most "by doing"
      We provide these in both C and Fortran.
      
      MakeDefs: Files included by our makefiles to support
      C and Fortran on various platforms.  You should copy
      one that is close to what you need, and modify it
      to reference the compilers you wish to use.  Put
      this copy in the MakeDefs directory and call it make.def
	
You can use any system with a working OpenMP compiler for the hands-on exercises
in the "Exercises" directory.  The templates for "make.def" to be used for different 
architectures are available in the "MakeDefs" directory.
	
Training accounts on the NERSC Perlmutter system for SC23 are provided from Nov 11 to Nov 17, 2023:

-- Get an account on Perlmutter

      -- Apply for a NERSC Cori training account: https://iris.nersc.gov/train use 4-letter code: epg6
    
-- Obtain the exercises on Perlmutter

	% ssh trainxxx@perlmutter.nersc.gov
	% cd $SCRATCH
	% cp -r /global/cfs/cdirs/training/2022/OpenMP_SC23 . (notice the “dot” at the end) 
	% cd OpenMP_SC23/Exercises/C (or % cd OpenMP_SC23/Exercises/Fortran)
	% make (for all codes)

-- Compile on Perlmutter

	The default compiler is GNU. Use compiler wrappers (ftn, cc, and CC) 
	and the OpenMP compiler flag to build an individual code, such as:
	% cc -fopenmp -O0 mycode.c 
	% ftn -fopenmp -O0 mycode.f90

	To use another compiler, such as Nvidia: 
	% module swap PrgEnv-gnu PrgEnv-nvidia
	% cc -mp -O0 mycode.c
	
	Here -O0 is used on purpose to prevent compiler optimizations from 
	"fixing" certain OpenMP issues (such as false sharing) that we would 
	like to expose.  You can set to a higher optimization level such as 
	-O3 to improve performance.

-- Run on Perlmutter

	Get on a compute node with an interactive batch session first
	With a node reservation during the SC23 tutorial:
	– to get a dedicated node:
         % salloc -N 1 -C cpu -q regular -t 1:00:00 --reservation=omp_sc23 -A ntrain2
	- to run on a shared node:
        % salloc -N 1 -C cpu -q shared -c 16 -t 1:00:00 --reservation=omp_sc23 -A ntrain2
	 
	Without a node reservation outside the SC23 tutorial:
	– to get a dedicated node:
        % salloc -N 1 -C cpu -q regular -t 1:00:00 -A ntrain2
	- to run on a shared node:
        % salloc -N 1 -C cpu -q shared -c 16 -t 1:00:00 -A ntrain2
	
	To run on the allocated compute node:
	-- Set number of threads, such as: 
	% export OMP_NUM_THREADS=4 
	-- Then run: % ./a.out

