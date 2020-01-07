# 
#  Note ... there are two working versions of the code here.  One with 
#  tasks (linked_omp3_tasks) and one without.  there is a C++ version
#  of the code, but we need to do a bit more work to get it to 
#  build with this makefile.
#
include ../../../MakeDefs/make.def

EXES= linked_omp3_tasks$(EXE)  linked_omp25$(EXE) 

all: $(EXES)

linked_omp3_tasks$(EXE): linked_omp3_tasks.$(OBJ) 
	$(CLINKER) $(OPTFLAGS) -o linked_omp3_tasks linked_omp3_tasks.$(OBJ) $(LIBS)

linked_cpp$(EXE): linked_cpp.$(OBJ) 
	$(CLINKER) $(OPTFLAGS) -o linked_cpp linked_cpp.$(OBJ) $(LIBS)

linked_omp25$(EXE): linked_omp25.$(OBJ) 
	$(CLINKER) $(OPTFLAGS) -o linked_omp25 linked_omp25.$(OBJ) $(LIBS)

test: $(EXES)
	$(PRE)linked_omp3_tasks$(EXE) 
	$(PRE)linked_omp25$(EXE) 

clean:
	$(RM) $(EXES) *.$(OBJ)

.SUFFIXES:
.SUFFIXES: .c .cpp  .$(OBJ)

.c.$(OBJ):
	$(CC) $(CFLAGS) -c $<

.cpp.$(OBJ):
	$(CC) $(CFLAGS) -c $<
