#include <stdlib.h>
#include <stdio.h>
#include "Util.h"



int main(int argc, char* argv[])
    {
    FILE* ifp;
    gray* graymap;
    int ich1, ich2, rows, cols, maxval, pgmraw ;
    int i, j;


    /* Test des arguments */
    if ( argc != 2 ){
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
    if(ich2 != '2' && ich2 != '5')
      pm_erreur(" mauvais type de fichier ");
    else
      if(ich2 == '2')
	pgmraw = 0;
      else pgmraw = 1;

    /* Lecture des dimensions [DONE] */
    cols = pm_getint( ifp );
    rows = pm_getint( ifp );
    
    /* Allocation memoire  */
    graymap = (gray *) malloc(cols * rows * sizeof(gray));

    /* Lecture [DONE] */
    maxval = pm_getint( ifp );
    for(i=0; i < rows; i++)
      for(j=0; j < cols ; j++)
	if (pgmraw) 
	  graymap[i * cols + j] = pm_getrawbyte(ifp);
	else 
	  graymap[i * cols + j] = pm_getint(ifp);
    
    /* Ecriture */
    if(pgmraw)
      printf("P2\n");
    else
      printf("P5\n");

    printf("%d %d \n", cols, rows);
    printf("%d\n",maxval);
    for(i=0; i < rows; i++)
      for(j=0; j < cols ; j++)
	if (pgmraw) /* on stocke l'information sous forme ASCII */
	  printf( "%u ", graymap[i * cols + j] );
	else /* on stocke l'information sous forme binaire */
	  printf( "%c", graymap[i * cols + j] );

      /* fermeture */
      fclose(ifp);
      return 0;
}
