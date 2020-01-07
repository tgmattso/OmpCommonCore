#
# This makefile was used to test that all the Fortran source files in the
# current director will compile.
#
# We can't build many of the executables since we left off a number
# of anciliary function.  So the only target I care about is obj, i.e.
# test these files with the command:
#
#    make obj
#
# Author: Tim Mattson based on GraphBLAS makefile from Scott McMillian
# 

include ../../MakeDefs/make.def

# define variable SOURCES to contain all the program files
include makeSourceFor.lst


OBJECTS		= $(SOURCES:.f90=.o)
TARGETS		= $(SOURCES:.f90=.exe)
DSYM   		= $(SOURCES:.f90=.exe.dSYM)
#HEADERS		= $(wildcard $(INCDIR)/*.h)
#PCHS		= $(HEADERS:=.gch)

.PHONY		: all clean

obj             : $(OBJECTS)
all		: $(TARGETS)

%.s 		: %.f90 $(HEADERS)
		$(FC) -S $(FFLAGS) $<

%.o  		: %.f90 $(HEADERS)
		$(FC) -c $(FFLAGS) $<

%.exe  		: %.o
		$(FC) $^ -o $@ $(LIB)

clean		:
		/bin/rm -rf a.out $(TARGETS) $(OBJECTS) $(PCHS) $(DSYM) *~


squeaky		: clean
		/bin/rm -f $(SOURCES:%.f90=%.d)


.SECONDARY	: $(OBJECTS)

-include $(SOURCES:%.f90=%.d)
