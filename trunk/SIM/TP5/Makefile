#######################################
# Makefile OpenGL                     #  
#                                     #
# E.B.                                #
#######################################
 

PROG = splines

all : $(PROG) 


# Librairie GL
GL_LIBS = -lglut -lGLU -lm 


# Variables pour la compilation des fichiers
CC        =  gcc
CFLAGS    =  -g -Wall
CPPFLAGS  =  -DDEBUG
LDFLAGS   =  -g 



%.o : %.c 
	$(CC) -c $(CPPFLAGS) $(CFLAGS) $< -o $@ 

$(PROG): % : %.o 
	$(CC) $(LDFLAGS) -o $@ $<  $(GL_LIBS)
 

clean:
	/bin/rm -f $(PROG)
	/bin/rm -f *.o
