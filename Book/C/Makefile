#
# This makefile was used to test that all the C source files in the
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
include makeSource.lst


OBJECTS		= $(SOURCES:.c=.o)
TARGETS		= $(SOURCES:.c=.exe)
DSYM   		= $(SOURCES:.c=.exe.dSYM)
#HEADERS		= $(wildcard $(INCDIR)/*.h)
#PCHS		= $(HEADERS:=.gch)

.PHONY		: all clean

obj             : $(OBJECTS)
all		: $(TARGETS)

%.s 		: %.c $(HEADERS)
		$(CC) -S $(CCFLAGS) $<

%.o  		: %.c $(HEADERS)
		$(CC) -c $(CCFLAGS) $<

%.exe  		: %.o
		$(CC) $^ -o $@ $(LIB)

clean		:
		/bin/rm -rf a.out $(TARGETS) $(OBJECTS) $(PCHS) $(DSYM) *~


squeaky		: clean
		/bin/rm -f $(SOURCES:%.c=%.d)


.SECONDARY	: $(OBJECTS)

-include $(SOURCES:%.c=%.d)
