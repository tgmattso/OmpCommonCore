# 
include ../../MakeDefs/make.def

EXES= pi_mc$(EXE)

all: $(EXES)


pi_mc$(EXE): pi_mc.$(OBJ) random.$(OBJ)
	$(CLINKER) $(OPTFLAGS) -o pi_mc pi_mc.$(OBJ) random.$(OBJ) $(LIBS)

test: $(EXES)
	$(PRE)pi_mc$(EXE) 


clean:
	$(RM) $(EXES) *.$(OBJ)

.SUFFIXES:
.SUFFIXES: .c .cpp  .$(OBJ)

.c.$(OBJ):
	$(CC) $(CFLAGS) -c $<

.cpp.$(OBJ):
	$(CC) $(CFLAGS) -c $<
