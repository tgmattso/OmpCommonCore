#
#  USAGE:
#     make          ... to build the program
#     make test     ... to run the default test case
#
include ../../../MakeDefs/make.def

EXES= mm_testbed$(EXE) 
MM_OBJS  = mm_testbed.$(OBJ) mm_utils.$(OBJ) mm_tst_cases.$(OBJ) \
           mm_ijk.$(OBJ) mm_ikj.$(OBJ) mm_ikj_par.$(OBJ) mm_trans.$(OBJ)

all: $(EXES)

mm_testbed$(EXE): $(MM_OBJS) mm_utils.h
	$(CLINKER) $(CFLAGS) -o mm_testbed$(EXE) $(MM_OBJS) $(LIBS)

test: $(EXES)
	$(PRE)mm_testbed$(EXE) 

clean:
	$(RM) $(EXES) *.$(OBJ)

.SUFFIXES:
.SUFFIXES: .c .cpp  .$(OBJ)

.c.$(OBJ):
	$(CC) $(CFLAGS) -c $<

.cpp.$(OBJ):
	$(CC) $(CFLAGS) -c $<
