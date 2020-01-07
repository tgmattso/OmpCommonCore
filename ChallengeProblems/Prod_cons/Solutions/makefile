# 
include ../../../MakeDefs/make.def

EXES= prod_cons_par$(EXE) 

all: $(EXES)


prod_cons_par$(EXE): prod_cons_par.$(OBJ)
	$(CLINKER) $(OPTFLAGS) -o prod_cons_par prod_cons_par.$(OBJ) $(LIBS)

test: $(EXES)
	$(PRE)prod_cons_par$(EXE)  

clean:
	$(RM) $(EXES) *.$(OBJ)

.SUFFIXES:
.SUFFIXES: .c .cpp  .$(OBJ)

.c.$(OBJ):
	$(CC) $(CFLAGS) -c $<

.cpp.$(OBJ):
	$(CC) $(CFLAGS) -c $<
