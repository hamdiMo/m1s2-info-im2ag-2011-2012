#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "Util.h"



int main(int argc, char* argv[]) {
  FILE* ifp;
  gray *redmap, *greenmap, *bluemap;
  int ich1, ich2, rows, cols, maxval, ppmraw ;
  int i, j;


  /* Test des arguments */
  if ( argc != 2 ) {
    printf("\nUsage : %s fichier \n\n", argv[0]);
    exit(0);
  }

  /* Ouverture */
  ifp = fopen(argv[1],"r");
  if (ifp == NULL) {
    printf("erreur d'ouverture du fichier %s\n", argv[1]);
    exit(1);
  }

  /* Lecture du Magic number */
  ich1 = getc( ifp );
  if ( ich1 == EOF )
    pm_erreur( "EOF / erreur de lecture / nombre magique" );
  ich2 = getc( ifp );
  if ( ich2 == EOF )
    pm_erreur( "EOF / erreur de lecture / nombre magique" );
  if(ich2 != '3' && ich2 != '6')
    pm_erreur(" mauvais type de fichier ");
  if(ich2 == '3')
    ppmraw = 0;
  else ppmraw = 1;
 
  /* Lecture des dimensions [DONE] */
  cols = pm_getint( ifp );
  rows = pm_getint( ifp );
    
  /* Allocation memoire  */
  redmap = (gray *) malloc(cols * rows * sizeof(gray));
  greenmap = (gray *) malloc(cols * rows * sizeof(gray));
  bluemap = (gray *) malloc(cols * rows * sizeof(gray));

  /* Lecture [DONE] */
  maxval = pm_getint( ifp );
  for(i=0; i < rows; i++)
    for(j=0; j < cols ; j++) 
      if (ppmraw) {
	redmap[i * cols + j] = pm_getrawbyte(ifp);
	greenmap[i * cols + j] = pm_getrawbyte(ifp);
	bluemap[i * cols + j] = pm_getrawbyte(ifp);
      } 
      else { 
	redmap[i * cols + j] = pm_getint(ifp);
	greenmap[i * cols + j] = pm_getint(ifp);
	bluemap[i * cols + j] = pm_getint(ifp);
      }
    
  /* Ecriture */
  if(ppmraw)
    printf("P5\n");
  else
    printf("P2\n");

  printf("%d %d \n", cols, rows);
  printf("%d\n",maxval);
  for(i=0; i < rows; i++)
    for(j=0; j < cols ; j++) {
      gray value = floor((redmap[i * cols + j] * 0.1 + greenmap[i * cols + j] * 0.6 + bluemap[i * cols + j] * 0.3) + 0.5);
      if (ppmraw) printf( "%c", value );
      else printf( "%u ", value );
    }

  /* fermeture */
  fclose(ifp);
  return 0;
}
