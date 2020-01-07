# 
include ../../../make.def

EXES= matmul_stras_par$(EXE)  matmul_par$(EXE) matmul_recur_par$(EXE) 

all: $(EXES)

matmul_stras_par$(EXE):  matmul_stras_par.$(OBJ) 
	$(CLINKER) $(OPTFLAGS) -o  matmul_stras_par  matmul_stras_par.$(OBJ) $(LIBS)


matmul_par$(EXE):  matmul_par.$(OBJ) 
	$(CLINKER) $(OPTFLAGS) -o  matmul_par  matmul_par.$(OBJ) $(LIBS)


matmul_recur_par$(EXE):  matmul_recur_par.$(OBJ) 
	$(CLINKER) $(OPTFLAGS) -o  matmul_recur_par  matmul_recur_par.$(OBJ) $(LIBS)

test: $(EXES)
	$(PRE)matmul_stras_par$(EXE) 
	$(PRE)matmul_par$(EXE) 
	$(PRE)matmul_recur_par$(EXE) 

clean:
	$(RM) $(EXES) *.$(OBJ)

.SUFFIXES:
.SUFFIXES: .c .cpp  .$(OBJ)

.c.$(OBJ):
	$(CC) $(CFLAGS) -c $<

.cpp.$(OBJ):
	$(CC) $(CFLAGS) -c $<
