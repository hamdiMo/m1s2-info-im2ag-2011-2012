/*
 * cube.c : projection image d'un cube
 * 
 * E.B. 
 */


#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

GLdouble Xrot = 0, Yrot = 0, Zrot = 0, Xtrans = 0, Ytrans = 0, Ztrans = 400;
int width = 400, height = 400;
double focal = 90;
int size = 200;

/* Fonction de Dessin */
void displayCube() 
{
  int size2 = size/2;

  glBegin(GL_LINE_LOOP);
  glVertex3f(-size2,-size2,-size2);
  glVertex3f(size2,-size2,-size2);
  glVertex3f(size2,size2,-size2);
  glVertex3f(-size2,size2,-size2);
  glEnd();

  glBegin(GL_LINE_LOOP);
  glVertex3f(-size2,-size2,size2);
  glVertex3f(size2,-size2,size2);
  glVertex3f(size2,size2,size2);
  glVertex3f(-size2,size2,size2);
  glEnd();

  glBegin(GL_LINE_STRIP);
  glVertex3f(-size2,-size2,size2);
  glVertex3f(-size2,-size2,-size2);
  glEnd();

  glBegin(GL_LINE_STRIP);
  glVertex3f(-size2,size2,size2);
  glVertex3f(-size2,size2,-size2);
  glEnd();

  glBegin(GL_LINE_STRIP);
  glVertex3f(size2,size2,size2);
  glVertex3f(size2,size2,-size2);
  glEnd();

  glBegin(GL_LINE_STRIP);
  glVertex3f(size2,-size2,size2);
  glVertex3f(size2,-size2,-size2);
  glEnd();
} 

void display()
{
  glClear( GL_COLOR_BUFFER_BIT);
  glPushMatrix();
  /* deplacement souris */
  double angle = Xrot + Yrot + Zrot;
  glTranslatef(Xtrans , -Ytrans, -Ztrans);
  glRotatef(Xrot, 1, 0, 0);
  glRotatef(Yrot, 0, 1, 0);
  glRotatef(Zrot, 0, 0, 1);
  
  displayCube();

  glPopMatrix();
  glFlush();
}


int beginx, beginy, moving = 0, translating = 0, translatingZ = 0, rotating = 0;

/* Fonction de gestion de l'evenement click d'un bouton de la souris */
void mouse(int button, int state, int x, int y)
{
  if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) {
    translating = 1;
    beginx = x;
    beginy = y;
  }
  if (button == GLUT_MIDDLE_BUTTON && state == GLUT_UP) {
    translating = 0;
  }
  if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
    translatingZ = 1;
    beginx = x;
    beginy = y;
  }
  if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP) {
    translatingZ = 0;
  }
  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
    rotating = 1;
    beginx = x;
    beginy = y;
  }
  if (button == GLUT_MIDDLE_BUTTON && state == GLUT_UP) {
    rotating = 0;
  }
}
 
/* Fonction de gestion de l'evenement deplacement de la souris */
void mouseMotion(int x, int y)
{
  if (translating) {
    Xtrans = Xtrans + (double)(x - beginx);
    Ytrans = Ytrans + (double)(y - beginy);
    beginx = x;
    beginy = y;
    display();
  }
  else if (translatingZ) {
    Ztrans = Ztrans + (double)(x - beginx) + (double)(y - beginy);
    beginx = x;
    beginy = y;
    display();
  }
  else if (rotating) {
    Yrot = Yrot + (double)(x - beginx);
    Xrot = Xrot + (double)(y - beginy);
    beginx = x;
    beginy = y;
    display();
  }
}


/* Fonction de reaffichage */
static void reshape(GLsizei w, GLsizei h)
{
  width = w;
  height = h;
  glViewport(0, 0, width, height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  /* glOrtho(-200.0, 200.0, -200.0 , 200, -200.0, 200.0); */
  /* glFrustum(-200.0, 200.0, -200.0 , 200, -200.0, 200.0); */
  gluPerspective(focal, (double)(width/height), 0, 100.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}


/* Fonction de test de touche du clavier */
static void key( unsigned char key, int x, int y )
{
  switch (key) {
  case 43: /* + */
    focal+=5;
    reshape(width, height);
    display();
    break;
  case 45: /* - */
    focal-=5;
    reshape(width, height);
    display();
    break;
  case 27:               /* sortie si ESC */
    exit(0);
  }
}


 
/*  Main Loop
 *  Ouverture de la fenetre d'affichage de tailles et titre donnes 
 *  et definition des fonctions de gestion d'evenement.
 */
int main(int argc, char** argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize (width, height);
  glutCreateWindow ("cube");
  
  glClearColor (0.4, 0.4, 0.4, 0.0);
  glutMouseFunc(mouse);
  glutMotionFunc(mouseMotion);
  glutKeyboardFunc(key);
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutMainLoop();
  return 0;
}
