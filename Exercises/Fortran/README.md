This directory contains exercises and solutions for working with
the running examples as you read the book:

    The OpenMP Common Core: Making OpenMP Simple Again

Information about these programs can be found in the comments and 
the book

To use these programs, go to ../../MakeDefs and copy the 
appropriate "def" file into "make.def".  For example on a linux 
system running the gnu compilers, I'd type

  cp ../../MakeDefs/linux_gnu.def ../../MakeDefs/make.def

Then build the programs and test them

   make test

The solutions directory uses the same make.def file so to build
the solutions, just type "make test".  

We have tested these programs under Linux with the gnu and Intel compilers,
and on OS-X with the gnu environment loaded with Apple's xcode and homebrew. 
Apple's OpenMP environment at this time does not have cpu_set_t
so xthi_omp.c and xthi_nested_omp.c will not build, and are
commented out from the makefile.

We have used these programs with the PGI compiler (pgi.def) and the
Intel compilers under Windows, but we have not tested these cases recently 
and they may need some work.

For windows users, to run these on Windows 7 we used the follwing
procedure.  First go to the start menu, and select 
   
    INtel parallel studio 2011/command prompt/ ia64 visual studio 2010 mode

cd to the appropriate folder.  Copy the approprate make.def and then
use nmake to build

Note: We cannot run the stream program on Apple OSX systems due to a 
problem linking in the right timing modules. We'll fix this in a later
release.

