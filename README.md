
This repository supports readers of our book:

     The OpenMP Common Core: making OpenMP Simple Again

We encourage readers to explore the material actively; mixing
time spent reading with time spent coding.   To that end, we
provide lots of code for our readers to explore organized into
the following directories.

      Book: Code used in the book.  This includes any
      code that appears in the figures as well as code
      fragments embedded in the the text of the book.
      We provide these in both C and Fortran.

      ChallengeProblems: A set of more complex problems to
      support advanced studies in OpenMP.  In each case
      we include serial code you can start with and a
      directory of solutions.  Currently, these are
      only provided in C.

      Exercises: code and solutions for the running 
      examples used in the book.  We recommend pausing 
      as you read the book and experimenting with these
      exercises ... afterall, we all learn most "by doing"
      We provide these in both C and Fortran.
      
      MakeDefs: Files included by our makefiles to support
      C and Fortran on various platforms.  You should copy
      one that is close to what you need, and modify it
      to reference the compilers you wish to use.  Put
      this copy in the MakeDefs director and call it make.def
      
   
Join the Slack workspace "OmpCommonCore-SC20" for the SC20 OpenMP Common Core Tutorial:

	https://tinyurl.com/yyn3dxrl   
	
You can use any system with a working OpenMP compiler for the hands-on exercises
in the "Exercises" directory.  The templates for "make.def" to be used for different 
architectuers are available in the "MakeDefs" directrory.
	
Training accounts on the NERSC Cori system are provided from Nov 8 to Nov 16:

-- Get an account on Cori

	Apply for a training account (expires Nov 16, 2020) 
	https://iris.nersc.gov/train use 4-letter code “bq2d”

-- Obtain the exercises on Cori

	% ssh trainxxx@cori.nersc.gov
	% cd $SCRATCH
	% cp -r /global/cfs/cdirs/training/2020/OpenMP_SC20 . (notice the “dot” at the end) 
	% cd OpenMP_SC20/Exercises/C (or % cd OpenMP_SC20/Exercises/Fortran)
	% make (for all codes)

-- Compile on Cori

	The default compiler is Intel. Use compiler wrappers (ftn, cc, and CC) 
	and the OpenMP compiler flag to build an individual code, such as:
	% cc -qopenmp -O0 mycode.c 
	% ftn -qopenmp -O0 mycode.f90

	To use another compiler, such as gcc: 
	% module swap PrgEnv-intel PrgEnv-gnu 
	% cc -fopenmp -O0 mycode.c
	
	Here -O0 is used on purpose to prevent compiler optimizations from 
	"fixing" certain OpenMP issues (such as false sharing) that we would 
	like to expose.  You can set to a higher optimization level such as 
	-O3 to improve performance.

-- Run on Cori

	Get on a compute node with an interactive batch session first
	With a node reservation during the SC20 tutorial:
	– Haswell node: % salloc -N 1 -C haswell -q regular -t 1:00:00 --reservation=omp_hsw -A ntrain
	– KNL node: % salloc -N 1 -C knl -q regular -t 1:00:00 --reservation=omp_knl -A ntrain
	(use --reservation=omp2_hsw and omp2_knl on Nov 10)

	Without a node reservation outside the SC20 tutorial:
	- Haswell node: % salloc -N 1 -C haswell -q interactive -t 30:00 
	- KNL node: % salloc -N 1 -C knl -q interactive -t 30:00

	To run on the allocated compute node:
	-- Set number of threads, such as: 
	% export OMP_NUM_THREADS=4 
	-- Then run: % ./a.out

