#
#  USAGE:
#     make          ... to build the program
#     make test     ... to run the default test case
#
include ../../../MakeDefs/make.def

EXES=hello_par$(EXE) pi_spmd_simple$(EXE) pi_spmd_simple_padded$(EXE) \
     pi_spmd_final$(EXE) pi_loop$(EXE) mandel_par$(EXE) mandel_reduction$(EXE) \
     pi_task$(EXE) racey_tasks$(EXE) pi_vec$(EXE) schro_prog$(EXE) 

all: $(EXES)

hello_par$(EXE): hello_par.$(OBJ) 
	$(CLINKER) $(OPTFLAGS) -o hello_par$(EXE) hello_par.$(OBJ) $(LIBS)

pi_spmd_simple$(EXE): pi_spmd_simple.$(OBJ) 
	$(CLINKER) $(OPTFLAGS) -o pi_spmd_simple$(EXE) pi_spmd_simple.$(OBJ) $(LIBS)

pi_spmd_simple_padded$(EXE): pi_spmd_simple_padded.$(OBJ) 
	$(CLINKER) $(OPTFLAGS) -o pi_spmd_simple_padded$(EXE) pi_spmd_simple_padded.$(OBJ) $(LIBS)

pi_spmd_final$(EXE): pi_spmd_final.$(OBJ) 
	$(CLINKER) $(OPTFLAGS) -o pi_spmd_final$(EXE) pi_spmd_final.$(OBJ) $(LIBS)

pi_loop$(EXE): pi_loop.$(OBJ) 
	$(CLINKER) $(OPTFLAGS) -o pi_loop$(EXE) pi_loop.$(OBJ) $(LIBS)

pi_vec$(EXE): pi_vec.$(OBJ) 
	$(CLINKER) $(OPTFLAGS) -o pi_vec$(EXE) pi_vec.$(OBJ) $(LIBS)

mandel_par$(EXE): mandel_par.$(OBJ) 
	$(CLINKER) $(OPTFLAGS) -o mandel_par$(EXE) mandel_par.$(OBJ) $(LIBS)

mandel_reduction$(EXE): mandel_reduction.$(OBJ) 
	$(CLINKER) $(OPTFLAGS) -o mandel_reduction$(EXE) mandel_reduction.$(OBJ) $(LIBS)

schro_prog$(EXE): schro_prog.$(OBJ) 
	$(CLINKER) $(OPTFLAGS) -o schro_prog$(EXE) schro_prog.$(OBJ) $(LIBS)

racey_tasks$(EXE): racey_tasks.$(OBJ) 
	$(CLINKER) $(OPTFLAGS) -o racey_tasks$(EXE)  racey_tasks.$(OBJ) $(LIBS)

pi_task$(EXE): pi_task.$(OBJ) 
	$(CLINKER) $(OPTFLAGS) -o pi_task$(EXE) pi_task.$(OBJ) $(LIBS)

test: $(EXES)
	$(PRE)hello_par$(EXE) 
	$(PRE)pi_spmd_simple$(EXE) 
	$(PRE)pi_spmd_simple_padded$(EXE) 
	$(PRE)pi_spmd_final$(EXE) 
	$(PRE)pi_loop$(EXE) 
	$(PRE)mandel_par$(EXE) 
	$(PRE)pi_task$(EXE)  
	$(PRE)racey_tasks$(EXE) 
	$(PRE)schro_prog$(EXE) 
	$(PRE)pi_vec$(EXE)  

clean:
	$(RM) $(EXES) *.$(OBJ)

.SUFFIXES:
.SUFFIXES: .c .cpp  .$(OBJ)

.c.$(OBJ):
	$(CC) $(CFLAGS) -c $<

.cpp.$(OBJ):
	$(CC) $(CFLAGS) -c $<
