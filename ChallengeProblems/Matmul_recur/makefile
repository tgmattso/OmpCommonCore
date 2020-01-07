# 
include ../../MakeDefs/make.def

EXES= matmul_stras$(EXE)  matmul$(EXE) matmul_recur$(EXE) 

all: $(EXES)

matmul_stras$(EXE):  matmul_stras.$(OBJ) 
	$(CLINKER) $(OPTFLAGS) -o  matmul_stras  matmul_stras.$(OBJ) $(LIBS)


matmul$(EXE):  matmul.$(OBJ) 
	$(CLINKER) $(OPTFLAGS) -o  matmul  matmul.$(OBJ) $(LIBS)


matmul_recur$(EXE):  matmul_recur.$(OBJ) 
	$(CLINKER) $(OPTFLAGS) -o  matmul_recur  matmul_recur.$(OBJ) $(LIBS)

test: $(EXES)
	$(PRE)matmul_stras$(EXE) 
	$(PRE)matmul$(EXE) 
	$(PRE)matmul_recur$(EXE) 

clean:
	$(RM) $(EXES) *.$(OBJ)

.SUFFIXES:
.SUFFIXES: .c .cpp  .$(OBJ)

.c.$(OBJ):
	$(CC) $(CFLAGS) -c $<

.cpp.$(OBJ):
	$(CC) $(CFLAGS) -c $<
