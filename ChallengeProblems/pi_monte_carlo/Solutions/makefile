# 
include ../../../MakeDefs/make.def

EXES= pi_mc_par$(EXE)
RAN_OBJS = random_par.$(OBJ) 

all: $(EXES)

pi_mc_par$(EXE): pi_mc_par.$(OBJ) $(RAN_OBJS)
	$(CLINKER) $(OPTFLAGS) -o pi_mc_par pi_mc_par.$(OBJ) $(RAN_OBJS) $(LIBS)

test: $(EXES)
	$(PRE)pi_mc_par$(EXE) 


clean:
	$(RM) $(EXES) *.$(OBJ)

.SUFFIXES:
.SUFFIXES: .c .cpp  .$(OBJ)

.c.$(OBJ):
	$(CC) $(CFLAGS) -c $<

.cpp.$(OBJ):
	$(CC) $(CFLAGS) -c $<
