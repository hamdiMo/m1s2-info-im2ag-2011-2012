#######################################
# Makefile OpenGL                     #  
#                                     #
# E.B.                                #
#######################################
 

PROG = sphere

all : $(PROG) 


# Librairie GL
INCDIR =
LIBDIR = -L/usr/lib -L/usr/X11R6/lib
XLIBS =  -lX11 -lXext -lXmu -lXi
GL_LIBS = $(LIBDIR) -lglut -lGLU -lGL -lm $(XLIBS)


# Variables pour la compilation des fichiers
CC        =  gcc
CFLAGS    =  -g -Wall
CPPFLAGS  =  -DDEBUG $(INCDIR)
LDFLAGS   =  -g 



%.o : %.c 
	$(CC) -c $(CPPFLAGS) $(CFLAGS) $< -o $@ 

$(PROG): % : %.o 
	$(CC) $(LDFLAGS) -o $@ $<  $(GL_LIBS)
 

clean:
	/bin/rm -f $(PROG)
	/bin/rm -f *.o