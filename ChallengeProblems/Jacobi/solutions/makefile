#
#  USAGE:
#     make          ... to build the program
#     make test     ... to run the default test case
#
include ../../../MakeDefs/make.def

EXES= jac_solv_parfor jac_solv_par_for$(EXE) \
     jac_solv_simd$(EXE) jac_solv_simd$(EXE)

JAC_PAR_FOR_OBJS  = jac_solv_par_for.$(OBJ) mm_utils.$(OBJ) 

JAC_PARFOR_OBJS  = jac_solv_parfor.$(OBJ) mm_utils.$(OBJ) 

JAC_SIMD_OBJS  = jac_solv_simd.$(OBJ) mm_utils.$(OBJ) 

all: $(EXES)

jac_solv_par_for$(EXE): $(JAC_PAR_FOR_OBJS) mm_utils.h
	$(CLINKER) $(CFLAGS) -o jac_solv_par_for$(EXE) $(JAC_PAR_FOR_OBJS) $(LIBS)

jac_solv_parfor$(EXE): $(JAC_PARFOR_OBJS) mm_utils.h
	$(CLINKER) $(CFLAGS) -o jac_solv_parfor$(EXE) $(JAC_PARFOR_OBJS) $(LIBS)

jac_solv_simd$(EXE): $(JAC_SIMD_OBJS) mm_utils.h
	$(CLINKER) $(CFLAGS) -o jac_solv_simd$(EXE) $(JAC_SIMD_OBJS) $(LIBS)

test: $(EXES)
	$(PRE)jac_solv_parfor 
	$(PRE)jac_solv_par_for$(EXE) 
	$(PRE)racey_tasks$(EXE) 

clean:
	$(RM) $(EXES) *.$(OBJ)

.SUFFIXES:
.SUFFIXES: .c .cpp  .$(OBJ)

.c.$(OBJ):
	$(CC) $(CFLAGS) -c $<

.cpp.$(OBJ):
	$(CC) $(CFLAGS) -c $<
