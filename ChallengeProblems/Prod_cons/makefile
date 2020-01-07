# 
include ../../MakeDefs/make.def

EXES= prod_cons$(EXE)

all: $(EXES)


prod_cons$(EXE): prod_cons.$(OBJ)
	$(CLINKER) $(OPTFLAGS) -o prod_cons prod_cons.$(OBJ) $(LIBS)

test: $(EXES)
	$(PRE)prod_cons$(EXE)  

clean:
	$(RM) $(EXES) *.$(OBJ)

.SUFFIXES:
.SUFFIXES: .c .cpp  .$(OBJ)

.c.$(OBJ):
	$(CC) $(CFLAGS) -c $<

.cpp.$(OBJ):
	$(CC) $(CFLAGS) -c $<
