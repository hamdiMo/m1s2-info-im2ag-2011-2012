/*
 * grid.c : patchs de splines
 * 
 * E.B. 
 */


#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

GLenum doubleBuffer=GL_TRUE;   
GLint precision= 10;
GLdouble Xrot = 0, Yrot = 0, Xtrans = 0.5, Ytrans = -0.5, Ztrans = 0;
GLint beginx, beginy, rotating = 0, xytranslating = 0, ztranslating = 0;
GLint xi=0,yi=0;

/* matrice de Bezier */
GLfloat Bezier[4][4] = 
  {{-1,3,-3,1},
   {3,-6,3,0},
   {-3,3,0,0},
   {1,0,0,0}} ;

/* matrice des Bsplines */
GLfloat Bspline[4][4] = 
  {{-1/6.0,3/6.0,-3/6.0,1/6.0},
   {3/6.0,-6/6.0,3/6.0,0},
   {-3/6.0,0,3/6.0,0},
   {1/6.0,4/6.0,1/6.0,0}} ;
/* matrice des Catmull-Rom */
GLfloat CatmullRom[4][4] = 
  {{-1/2.0 , 3/2.0 , -3/2.0 , 1/2.0},
   {2/2.0 , -5/2.0 , 4/2.0 , -1/2.0},
   {-1/2.0 , 0 , 1/2.0 , 0},
   {  0 , 1 ,0,0}};
        
/* points de controles */
GLfloat grid4x4[4][4][3] =
  {
    {
      {-2.0, -2.0, 0.0},
      {-0.5, -2.0, 0.0},
      {0.5, -2.0, 0.0},
      {2.0, -2.0, 0.0}},
    {
      {-2.0, -0.5, 0.0},
      {-0.5, -0.5, 0.0},
      {0.5, -0.5, 0},
      {2.0, -0.5, 0.0}},
    {
      {-2.0, 0.5, 0.0},
      {-0.5, 0.5, 0.0},
      {0.5, 0.5, 0.0},
      {2.0, 0.5, 0.0}},
    {
      {-2.0, 2.0, 0.0},
      {-0.5, 2.0, 0.0},
      {0.5, 2.0, 0.0},
      {2.0, 2.0, 0.0}}
  };
GLfloat grid5x5[5][5][3] =
  {
    {
      {-2.0, -2.0, 0.0},
      {-0.5, -2.0, 0.0},
      {0.5, -2.0, 0.0},
      {2.0, -2.0, 0.0},
      {3.5, -2.0, 0.0}},
    {
      {-2.0, -0.5, 0.0},
      {-0.5, -0.5, 0.0},
      {0.5, -0.5, 0},
      {2.0, -0.5, 0.0}, 
      {3.5, -0.5, 0.0}},
    {
      {-2.0, 0.5, 0.0},
      {-0.5, 0.5, 0.0},
      {0.5, 0.5, 0.0},
      {2.0, 0.5, 0.0},
      {3.5, 0.5, 0.0}},
    {
      {-2.0, 2.0, 0.0},
      {-0.5, 2.0, 0.0},
      {0.5, 2.0, 0.0},
      {2.0, 2.0, 0.0},
      {3.5, 2.0, 0.0}},
    {
      {-2.0, 3.5, 0.0},
      {-0.5, 3.5, 0.0},
      {0.5, 3.5, 0.0},
      {2.0, 3.5, 0.0},
      {3.5, 3.5, 0.0}}
  };
GLfloat grid7x7[7][7][3] =
  {
    { {-3.5, -3.5, 0.0},
      {-2.0, -3.5, 0.0},
      {-0.5, -3.5, 0.0},
      {0.5, -3.5, 0.0},
      {2.0, -3.5, 0.0},
      {3.5, -3.5, 0.0},
      {5.0, -3.5, 0.0}},
    { 
      {-3.5, -2.0, 0.0}, 
      {-2.0, -2.0, 0.0},
      {-0.5, -2.0, 0.0},
      {0.5, -2.0, 0.0},
      {2.0, -2.0, 0.0},
      {3.5, -2.0, 0.0},
      {5.0, -2.0, 0.0}},
    { 
      {-3.5, -0.5, 0.0},
      {-2.0, -0.5, 0.0},
      {-0.5, -0.5, 0.0},
      {0.5, -0.5, 0.0},
      {2.0, -0.5, 0.0}, 
      {3.5, -0.5, 0.0},
      {5.0, -0.5, 0.0}},
    {
      {-3.5, 0.5, 0.0},
      {-2.0, 0.5, 0.0},
      {-0.5, 0.5, 0.0},
      {0.5, 0.5, 0.0},
      {2.0, 0.5, 0.0},
      {3.5, 0.5, 0.0},
      {5.0, 0.5, 0.0}},
    {
      {-3.5, 2.0, 0.0},
      {-2.0, 2.0, 0.0},
      {-0.5, 2.0, 0.0},
      {0.5, 2.0, 0.0},
      {2.0, 2.0, 0.0},
      {3.5, 2.0, 0.0},
      {5.0, 2.0, 0.0}},
    {
      {-3.5, 3.5, 0.0},
      {-2.0, 3.5, 0.0},
      {-0.5, 3.5, 0.0},
      {0.5, 3.5, 0.0},
      {2.0, 3.5, 0.0},
      {3.5, 3.5, 0.0},
      {5.0, 3.5, 0.0}},
    {
      {-3.5, 5.0, 0.0},
      {-2.0, 5.0, 0.0},
      {-0.5, 5.0, 0.0},
      {0.5, 5, 0.0},
      {2.0, 5, 0.0},
      {3.5, 5, 0.0},
      {5.0, 5, 0.0}}
  };
GLfloat *grid = &grid7x7[0][0][0];
int uSize = 7;
int vSize = 7;
GLfloat grid4x4X[4][4];
GLfloat grid4x4Y[4][4];
GLfloat grid4x4Z[4][4];


void init_tab(int k , int l)
{
  int i, j;

  for(i=0 ; i < 4 ; i++)
    for(j=0 ; j < 4 ; j++){
      grid4x4X[i][j] = grid[((i+k)*vSize+j+l)*3];
      grid4x4Y[i][j] = grid[((i+k)*vSize+j+l)*3+1];
      grid4x4Z[i][j] = grid[((i+k)*vSize+j+l)*3+2];
    }
}


/*Fonctions de calculs matriciels */
void matmult44x44(GLfloat res[4][4], GLfloat mat1[4][4], GLfloat mat2[4][4])
{
  int i,j, k ;
  GLfloat r[4][4], val ;
 
 
  for(i = 0; i < 4 ; i++)
    for(j = 0; j < 4 ; j++){
      val = 0;
      for(k = 0; k < 4 ; k++)
        val += mat1[i][k] * mat2[k][j] ;
      r[i][j] = val;
    }
  for(i = 0; i < 4 ; i++)
    for(j = 0; j < 4 ; j++)
      res[i][j] = r[i][j];
}           
void transpmat44(GLfloat tmat[4][4], GLfloat mat[4][4])
{
  int i, j ;
  for(i= 0; i < 4 ; i++)
    for(j = 0; j < 4 ; j++)
      tmat[i][j] = mat[j][i];
}
/* void matmult14x44(GLfloat res[4], GLfloat mat1[4], GLfloat mat2[4][4]) */
/* { */
/*   int i,j; */
/*   GLfloat r[4]; */
 
/*   for(i = 0; i < 4 ; i++) { */
/*     r[i] = 0; */
/*     for(j = 0; j < 4 ; j++) r[i] += mat1[j] * mat2[j][i]; */
/*   } */
/* } */
void matmult44x41(GLfloat res[4], GLfloat mat1[4][4], GLfloat mat2[4])
{
  int i,j;
  GLfloat r[4];
 
  for(i = 0; i < 4 ; i++) {
    r[i] = 0;
    for(j = 0; j < 4 ; j++) r[i] += mat1[i][j] * mat2[j];
  }
  for(i = 0; i < 4 ; i++) {
    res[i] = r[i];
  }
}
GLfloat matmult14x41(GLfloat mat1[4], GLfloat mat2[4])
{
  int i;
  GLfloat val ;
 
  val = 0;
  for(i = 0; i < 4 ; i++) val += mat1[i] * mat2[i];
  return val;
}




/* Fonctions de Dessin */
void drawControlPoints(void)
{
  int i;

  glColor3f(1.0, 1.0, 0.0);
  glPointSize(5.0);
  glBegin(GL_POINTS);
  for (i = 0; i < uSize * vSize; i++) {
    if(i != xi *vSize + yi)
      glVertex3fv(&grid[i * 3]);
    else{
      glColor3f(0.0, 1.0, 0.0); 
      glVertex3fv(&grid[i * 3]);
      glColor3f(1.0, 1.0, 0.0);
    }
  }
  glEnd();
}

GLfloat **matspline = (GLfloat **) Bezier;

void display()
{
  GLfloat s,t, s3, s2, t3, t2, x,y,z ;
  GLfloat X[4][4],Y[4][4],Z[4][4], temp[4][4], vectTmp[4] ;
  GLfloat transpmatspline[4][4];
  GLfloat patch[precision+1][precision+1][3];
  int i, j, k, l, Inck = 1, Incl = 1 ;

  glClear( GL_COLOR_BUFFER_BIT);
  glColor3f(1.0, 0.0, 0.0);
  glPointSize(1.0);
  glPushMatrix();
  glRotatef(Yrot*180.0/M_PI , 0.0, -1.0, 0.0); /* deplacement */
  glRotatef(Xrot*180.0/M_PI , 1.0, 0.0, 0.0);  /* souris      */

  transpmat44(transpmatspline, matspline);

  if (matspline == (GLfloat **) Bezier) { Inck = 3 ; Incl = 3 ; }
  else { Inck = 1 ; Incl = 1 ; }

  for(k=0 ; k < uSize - 3 ; k+= Inck)
    for(l=0 ; l < vSize - 3 ; l+= Incl) {
      init_tab(k,l);  

      /* calculs des matrices */
      matmult44x44(X, grid4x4X, transpmatspline);
      matmult44x44(X, matspline, X);

      matmult44x44(Y, grid4x4Y, transpmatspline);
      matmult44x44(Y, matspline, Y);

      matmult44x44(Z, grid4x4Z, transpmatspline);
      matmult44x44(Z, matspline, Z);

      /* courbes selon t */
      for (x = 0; x < precision+1; x++) {
	t = x / precision;
	t2 = t * t;
	t3 = t2 * t;
	GLfloat polyT[4] = { t3, t2, t, 1 };

	GLfloat vectX[4], vectY[4], vectZ[4];
	matmult44x41(vectX, X, polyT);
	matmult44x41(vectY, Y, polyT);
	matmult44x41(vectZ, Z, polyT);

	/* courbes selon s */
	for (y = 0; y < precision+1; y++) {
      	  s = y / precision;
      	  s2 = s * s;
      	  s3 = s2 * s;
      	  GLfloat polyS[4] = { s3, s2, s, 1 };
	
	  patch[(int)x][(int)y][0] = matmult14x41(polyS, vectX);
	  patch[(int)x][(int)y][1] = matmult14x41(polyS, vectY);
	  patch[(int)x][(int)y][2] = matmult14x41(polyS, vectZ);
	}
      }
      glColor3f(1.0, 0.0, 0.0);
      for (i = 0; i < precision; i++) {
	for (j = 0; j < precision; j++) {
	  glBegin(GL_LINE_LOOP);
	  glVertex3f(patch[i][j][0], patch[i][j][1], patch[i][j][2]);
	  glVertex3f(patch[i+1][j][0], patch[i+1][j][1], patch[i+1][j][2]);
	  glVertex3f(patch[i+1][j+1][0], patch[i+1][j+1][1], patch[i+1][j+1][2]);
	  glVertex3f(patch[i][j+1][0], patch[i][j+1][1], patch[i][j+1][2]);
	  glEnd();
	}
      }
    }
  
  drawControlPoints();
  glPopMatrix();
  glFlush();
  if (doubleBuffer) {
    glutSwapBuffers();
  }

}



/* Fonction de gestion de l'evenement click d'un bouton de la souris */
void mouse(int button, int state, int x, int y)
{
 
  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
    rotating = 1;
    beginx = x;
    beginy = y;
  }
  if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
    rotating = 0;
  }


  if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) {
    xytranslating = 1;
    beginx = x;
    beginy = y;
  }
  if (button == GLUT_MIDDLE_BUTTON && state == GLUT_UP) {
    xytranslating = 0;
  }
  if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
    ztranslating = 1;
    beginx = x;
    beginy = y;
  }   
  if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP) {
    ztranslating = 0;
  }          
}
 
/* Fonction de gestion de l'evenement deplacement de la souris */
void mouseMotion(int x, int y)
{
  if (rotating) {
    Xrot = Xrot + (y - beginy) / 100.0 ;
    Yrot = Yrot - (x - beginx) / 100.0 ;
    beginx = x;
    beginy = y;
    display();
  }
  
  if (xytranslating) {
    grid[(xi *vSize + yi)*3]= grid[(xi *vSize + yi)*3]+ (double)(x - beginx)/ 10.0;
    grid[(xi *vSize + yi)*3+1]= grid[(xi *vSize + yi)*3+1]- (double)(y - beginy)/ 10.0;
    beginx = x;
    beginy = y;
    display();
  }
  if (ztranslating) {
    grid[(xi *vSize + yi)*3+2]= grid[(xi *vSize + yi)*3+2]- (double)(y - beginy)/ 10.0;
    beginx = x;
    beginy = y;
    display();
  }           
}


/* Fonction de test de touche du clavier */
static void key( unsigned char key, int x, int y )
{
  switch (key) {
  case 27:               /* sortie si ESC */
    exit(0);
  case 'b':
    matspline = (GLfloat **) Bezier;display();
    break ;
  case 'B':
    matspline = (GLfloat **) Bspline;display();
    break ;
  case 'c':
    matspline = (GLfloat **) CatmullRom;display();
    break ;
  case '+':
    precision += 10;display();
    printf("Precision : %d \n",precision);
    break; 
  case '-':
    precision -= 10;display();
    printf("Precision : %d \n",precision);
    break; 
  
  }
}

static void SpecialKey( int key, int x, int y )
{
  switch (key) {      
  case GLUT_KEY_LEFT:
    yi =  yi > 0 ? yi - 1 : vSize -1 ;display();
    break ;
  case GLUT_KEY_RIGHT:
    yi = (yi + 1)%vSize;display();
    break;
  case GLUT_KEY_UP:
    xi = (xi +1)%uSize;display();
    break ;
  case GLUT_KEY_DOWN:
    xi =  xi > 0 ? xi - 1 : uSize -1;display();
    break;
  }
}

 
/* Fonction de reaffichage */
static void reshape(GLsizei w, GLsizei h)
{
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glFrustum(-5.0, 5, -5.0, 5, 15.0, 50.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef(0,0,-20);
}


/*  Main Loop
 *  Ouverture de la fenetre d'affichage de tailles et titre donnes 
 *  et definition des fonctions de gestion d'evenement.
 */
int main(int argc, char** argv)
{
  GLenum type;      
  
  glutInit(&argc, argv);
  glutInitWindowSize (400, 400);
  
  type = GLUT_RGB;
  type |= (doubleBuffer) ? GLUT_DOUBLE : GLUT_SINGLE;
  glutInitDisplayMode(type | GLUT_DEPTH);
  if (glutCreateWindow("Splines") == GL_FALSE) {
    exit(1);
  }      
  init_tab(0, 0);
  printf("\n\nResolution : '+'et '-' ;\nBezier : b, Bspline B, Catmull-Rom : c ;\nMouvement point de vue : bouton milieu souris ; \nMouvement point controle selectionne : bouton gauche (xy) et droit (z) souris ;\nSelection point de controle : fleches \n");        

  glClearColor (0.4, 0.4, 0.4, 0.0);
  glutMouseFunc(mouse);
  glutMotionFunc(mouseMotion);
  glutKeyboardFunc(key);
  glutSpecialFunc(SpecialKey);       
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutMainLoop();
  return 0;
}
