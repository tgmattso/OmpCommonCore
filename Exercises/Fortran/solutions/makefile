#
#  USAGE:
#     make          ... to build the program
#     make test     ... to run the default test case
#
include ../../../MakeDefs/make.def

EXES=hello_par$(EXE) pi_spmd_simple$(EXE) pi_spmd_final$(EXE)\
     pi_loop$(EXE)  pi_temp$(EXE) pi_task$(EXE) mandel_par$(EXE)\
     mandel_reduction$(EXE) pi_spmd_simple_padded$(EXE) racek_tasks$(EXE)  

all: $(EXES)

hello_par$(EXE): hello_par.$(OBJ) 
	$(FLINKER) $(OPTFLAGS) -o hello_par$(EXE) hello_par.$(OBJ) $(LIBS)

pi_spmd_simple$(EXE): pi_spmd_simple.$(OBJ) 
	$(FLINKER) $(OPTFLAGS) -o pi_spmd_simple$(EXE) pi_spmd_simple.$(OBJ) $(LIBS)

pi_spmd_simple_padded$(EXE): pi_spmd_simple_padded.$(OBJ) 
	$(FLINKER) $(OPTFLAGS) -o pi_spmd_simple_padded$(EXE) pi_spmd_simple_padded.$(OBJ) $(LIBS)

pi_spmd_final$(EXE): pi_spmd_final.$(OBJ) 
	$(FLINKER) $(OPTFLAGS) -o pi_spmd_final$(EXE) pi_spmd_final.$(OBJ) $(LIBS)

pi_loop$(EXE): pi_loop.$(OBJ) 
	$(FLINKER) $(OPTFLAGS) -o pi_loop$(EXE) pi_loop.$(OBJ) $(LIBS)

pi_temp$(EXE): pi_temp.$(OBJ) 
	$(FLINKER) $(OPTFLAGS) -o pi_temp$(EXE) pi_temp.$(OBJ) $(LIBS)

mandel_par$(EXE): mandel_par.$(OBJ) 
	$(FLINKER) $(OPTFLAGS) -o mandel_par$(EXE) mandel_par.$(OBJ) $(LIBS)

mandel_reduction$(EXE): mandel_reduction.$(OBJ) 
	$(FLINKER) $(OPTFLAGS) -o mandel_reduction$(EXE) mandel_reduction.$(OBJ) $(LIBS)

pi_task$(EXE): pi_task.$(OBJ) 
	$(FLINKER) $(OPTFLAGS) -o pi_task$(EXE) pi_task.$(OBJ) $(LIBS)

racey_tasks$(EXE): racey_tasks.$(OBJ) 
	$(FLINKER) $(OPTFLAGS) -o racey_tasks$(EXE) racey_tasks.$(OBJ) $(LIBS)

test: $(EXES)
	$(PRE)hello_par$(EXE) 
	$(PRE)pi_spmd_simple$(EXE) 
	$(PRE)pi_spmd_simple_padded$(EXE) 
	$(PRE)pi_spmd_final$(EXE) 
	$(PRE)pi_loop$(EXE) 
	$(PRE)mandel_par$(EXE) 
	$(PRE)pi_task$(EXE)  
	$(PRE)racey_tasks$(EXE)  


clean:
	$(RM) $(EXES) *.$(OBJ) *.mod

.SUFFIXES:
.SUFFIXES: .f .f90  .$(OBJ)

.f.$(OBJ):
	$(FC) $(FFLAGS) -c $<

.f90.$(OBJ):
	$(FC) $(FFLAGS) -c $<
