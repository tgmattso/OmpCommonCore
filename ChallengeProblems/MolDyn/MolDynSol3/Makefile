# Makefile for the molecular dynamics code

include ../../../MakeDefs/make.def


#
# Object files
#
MDOBJS=    main.$(OBJ) \
	dfill.$(OBJ) \
	domove.$(OBJ) \
      dscal.$(OBJ) \
	fcc.$(OBJ) \
	forces.$(OBJ) \
	mkekin.$(OBJ) \
	mxwell.$(OBJ) \
	prnout.$(OBJ) \
      random.$(OBJ) \
	velavg.$(OBJ) 

#
# Compile
#
md$(EXE):	$(MDOBJS)
	$(CLINKER) $(OPTFLAGS) -o $@ $(MDOBJS) $(LIBS)

test: md$(EXE)
	$(PRE)md$(EXE)

.c.o:
	$(CC) $(CFLAGS) -c $<

#
# Clean out object files and the executable.
#
clean:
	$(RM) *.$(OBJ) md$(EXE)
