#
#  USAGE:
#     make          ... to build the program
#     make test     ... to run the default test case
#

include ../../MakeDefs/make.def

EXES= stencil$(EXE)  

STN_OBJS  = stencil.$(OBJ)  

all: $(EXES)

stencil$(EXE): $(STN_OBJS) 
	$(CLINKER) $(CFLAGS) -o stencil$(EXE) $(STN_OBJS) $(LIBS)

test: $(EXES)
	$(PRE)stencil$(EXE)  

clean:
	$(RM) $(EXES) *.$(OBJ)

.SUFFIXES:
.SUFFIXES: .c .cpp .$(OBJ)

.c.$(OBJ):
	$(CC) $(CFLAGS) -c $<

.cpp.$(OBJ):
	$(CC) $(CFLAGS) -c $<
