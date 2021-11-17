#
#  USAGE:
#     make          ... to build the program
#     make test     ... to run the default test case
#

include ../../MakeDefs/make.def

# Note Stream doesn't work on Apple systems due to a 
# problem with the timing infrastructure.  
EXES=hello$(EXE) pi$(EXE) pi_recur$(EXE) mandel$(EXE) racey$(EXE)  \
#	 stream$(EXE) stream_nft$(EXE) 

all: $(EXES)

hello$(EXE): hello.$(OBJ) 
	$(FLINKER) $(OPTFLAGS) -o hello hello.$(OBJ) $(LIBS)

pi$(EXE): pi.$(OBJ) 
	$(FLINKER) $(OPTFLAGS) -o pi pi.$(OBJ) $(LIBS)

pi_recur$(EXE): pi_recur.$(OBJ) 
	$(FLINKER) $(OPTFLAGS) -o pi_recur pi_recur.$(OBJ) $(LIBS)

mandel$(EXE):  mandel.$(OBJ) 
	$(FLINKER) $(OPTFLAGS) -o mandel mandel.$(OBJ) $(LIBS)

racey$(EXE):  racey.$(OBJ) 
	$(FLINKER) $(OPTFLAGS) -o racey racey.$(OBJ) $(LIBS)

stream$(EXE):  mysecond.$(OBJ) stream.$(OBJ)
	$(FLINKER) $(OPTFLAGS) -o stream mysecond.$(OBJ) stream.$(OBJ) $(LIBS)

stream_nft$(EXE): mysecond.$(OBJ) stream_nft.$(OBJ) 
	$(FLINKER) $(OPTFLAGS) -o stream_nft mysecond.$(OBJ) stream_nft.$(OBJ) $(LIBS) 

test: $(EXES)
	$(PRE)hello$(EXE) 
	$(PRE)pi$(EXE) 
	$(PRE)pi_recur$(EXE) 
#	$(PRE)stream$(EXE) 
#	$(PRE)stream_nft$(EXE) 
	$(PRE)mandel$(EXE) 

clean:
	$(RM) $(EXES) *.$(OBJ) *.mod

.SUFFIXES:
.SUFFIXES: .f .f90 .c .$(OBJ)

.f.$(OBJ):
	$(FC) $(FFLAGS) -c $<

.f90.$(OBJ):
	$(FC) $(FFLAGS) -c $<

.c.$(OBJ):
	$(CC) $(CFLAGS) -c $<
