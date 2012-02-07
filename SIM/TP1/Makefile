#######################################
# Makefile PBM                        #
#                                     #
# E.B.                                #
#######################################


PROG = pxmtopxm pgmtopgm ppmtopgm

all : $(PROG)

# Variables pour la compilation des fichiers
CC        =  gcc
CFLAGS    =  -g -Wall -ln
CPPFLAGS  =  -DDEBUG
LDFLAGS   =  -g -lm

pxmtopxm : pxmtopxm.o Util.o

pgmtopgm : pgmtopgm.o Util.o

ppmtopgm : ppmtopgm.o Util.o

clean :
	@rm -f *.o

cleanall : clean
	@rm -f $(PROG)

