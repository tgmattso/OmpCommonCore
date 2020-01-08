This directory contains exercises and solutions for working 
with the running examples we use in our book:

    The OpenMP Common Core: Making OpenMP Simple Again

We have versions of these exercises in C and Fortran.  Solutions
to the exercise can be found in the pair of directories:

     C/solutions
     Fortran/solutions

It is important that you DO NOT look at the solutions before trying
the exercises on your own.

To use these programs, go to directory ../MakeDefs and 
copy the appropriate "def" file into "make.def".  For example 
on a linux system running the gnu compilers, I'd type

  cp ../MakeDefs/linux_gnu.def ../MakeDefs/make.def

Then build the programs and test them

   make test

The solutions directory uses the same make.def file so to build
the solutions, just type "make test".  

We have tested these programs under Linux with the gnu and Intel 
compilers, and on OS-X with the gnu environment we loaded with 
Apple's xcode and homebrew.  Apple's OpenMP environment at this 
time does not have cpu_set_t so xthi_omp.c and xthi_nested_omp.c 
will not build, and are commented out in the makefile.

We have used these programs with the PGI compiler (pgi.def) and the
Intel compilers under Windows, but we have not tested these 
cases recently and they may need some work.

For windows users, to run these on Windows 7 we used the follwing
procedure.  First go to the start menu, and select 
   
    INtel parallel studio 2011/command prompt/ ia64 visual studio 2010 mode

cd to the appropriate folder.  Copy the approprate make.def and 
then use nmake to build.

Finally, we have a second option for Fortran programmers.  In our 
opinion, a Fortran programmer should be comfortable with the basics
of C.  Hence, we provide a file called "learningC.c".  This file 
contains a C program the comments of which explain the 
features of C used in the book.  Basically, Fortran programmers 
can spend time with this file and learn enough C to read the book 
and do the exercises in C.   

You can compile a c program using the command:

      gcc learningC.c

and run the resulting program:

      ./a.out

Then make changes to the code to explore C and become comfortable 
writing your own code in C. 
