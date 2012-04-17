/*
 * sphere.c : affichage de sphere
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <GL/glut.h>

GLenum doubleBuffer=GL_TRUE;
GLint width,height;
int flat = 1==1, infinity = 1 == 0, ambient = 1==0, specular = 1==0, diffuse = 1==0;
double Xrot=0, Yrot=0, Xtrans=0, Ytrans=0;
double Xlight=0, Ylight=0, Zlight=3.0, XrotLight=0, YrotLight=0, ZrotLight=0;
double XrotScene=0, YrotScene=0;

void DrawSphere(double R, int numc, int numt)
{
 
  
  glPushMatrix();
  glTranslatef(Xtrans, -Ytrans, 0);
  glRotatef(Yrot*180.0/M_PI , 0.0, -1.0, 0.0);
  glRotatef(Xrot*180.0/M_PI , 1.0, 0.0, 0.0);
  glutSolidSphere(1.0,20,20);
  glPopMatrix();
  
  glPushMatrix();
  glTranslatef(Xlight, -Ylight, Zlight);
  /* glRotatef(ZrotLight*180.0/M_PI , 0.0, 0.0, 1.0); */
  /* glRotatef(YrotLight*180.0/M_PI , 0.0, -1.0, 0.0); */
  /* glRotatef(XrotLight*180.0/M_PI , 1.0, 0.0, 0.0); */
  glutWireCube(0.1);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(-Xlight, Ylight, -Zlight);
  glutWireCube(0.1);
  glPopMatrix();

  /*
   * A COMPLETER
   */

  glFlush();
  if (doubleBuffer) {
    glutSwapBuffers();
  }
  
}



int beginx, beginy, moving = 0, translating = 0, rotating = 0;
/* Fonction de gestion de l'evenement click d'un bouton de la souris */
void mouse(int button, int state, int x, int y)
{
 
  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
    moving = 1;
    beginx = x;
    beginy = y;
  }
  if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
    moving = 0;
  }
  if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) {
    translating = 1;
    beginx = x;
    beginy = y;
  }
  if (button == GLUT_MIDDLE_BUTTON && state == GLUT_UP) {
    translating = 0;
  }
  if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
    rotating = 1;
    beginx = x;
    beginy = y;
  }
  if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP) {
    rotating = 0;
  }
}
 
/* Fonction de gestion de l'evenement deplacement de la souris */
void mouseMotion(int x, int y)
{
  if (moving) {
    Xrot = Xrot + (double)(y - beginy) * 10 / height;
    Yrot = Yrot - (double)(x - beginx) * 10 / width;
    beginx = x;
    beginy = y;
    glutPostRedisplay();
   }
  if (translating) {
    Xtrans = Xtrans + ((double)(x - beginx))/10;
    Ytrans = Ytrans + ((double)(y - beginy))/10;
    beginx = x;
    beginy = y;
    glutPostRedisplay();
  }
  if (rotating) {
    XrotScene = XrotScene + ((double)(x - beginx))/10;
    YrotScene = YrotScene + ((double)(y - beginy))/10;
    beginx = x;
    beginy = y;
    glutPostRedisplay();
  }
}


/* Mise a jour des variables de tailles de fenetre*/
void set_screen_wh(GLsizei w, GLsizei h)
{
        width=w;
        height=h;
}


void Reshape(int w, int h)
{
  
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45, (float) w/ (float)h, 0.1, 100.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef(0,0,-5.0 );
  set_screen_wh(w,h);
  glutPostRedisplay();

}


void display()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  glPushMatrix();
  glRotatef(YrotScene*180.0/M_PI , 0.0, -1.0, 0.0);
  glRotatef(XrotScene*180.0/M_PI , 1.0, 0.0, 0.0);
  
  init_rendu();

  DrawSphere(1.0, 30,30);

  glPopMatrix();
}

void Key(unsigned char key, int x, int y)
{
  switch (key) {
  case 27: 
    exit(1);
    break;
    
    /** Deplacement de la source lumineuse */
  case 43:
    Zlight -= 0.1;
    break;
  case 45:
    Zlight += 0.1;
    break;
  case 122:
    Ylight -= 0.1;
    break;
  case 115: 
    Ylight += 0.1;
    break;
  case 113: 
    Xlight -= 0.1;
    break;
  case 100: 
    Xlight += 0.1;
    break;

    /** Proprieté de la lumiere */
  case 102:
    flat = 1 == 1;
    printf("Flat\n");
    break;
  case 103:
    flat = 1 == 0;
    printf("Gouraud\n");
    break;
  case 105:
    infinity = !infinity;
    if (infinity) printf("Position infinie\n");
    else printf("Position finie\n");
    break;
  case 119:
    ambient = !ambient;
    if (ambient) printf("Lumiere ambiante active\n");
    else printf("Lumiere ambiante inactive\n");
    break;
  case 120:
    specular = !specular;
    if (specular) printf("Lumiere speculaire active\n");
    else printf("Lumiere speculaire inactive\n");
    break;
  case 99:
    diffuse = !diffuse;
    if (diffuse) printf("Lumiere diffuse active\n");
    else printf("Lumiere diffuse inactive\n");
    break;

  default :
    printf("touche n° %i\n", key);
    break;
  }
  glutPostRedisplay();
}


/* rendu : definitions */
void init_rendu()
{
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);

  GLfloat lum_disable[]={0.0,0.0,0.0,0.0};
  GLfloat lum_ambient[]={0.1,0.1,0.1,1.0};
  GLfloat lum_diffuse[]={1.0,1.0,0.0,1.0};
  GLfloat lum_speculaire[]={1.0,1.0,1.0,1.0};

  GLfloat lum_position[]={Xlight, -Ylight, Zlight, 1.0};
  if (infinity) lum_position[3] = 0.0;

  if (ambient) glLightfv(GL_LIGHT0, GL_AMBIENT, lum_ambient);
  else glLightfv(GL_LIGHT0, GL_AMBIENT, lum_disable);
  
  if (diffuse) glLightfv(GL_LIGHT0, GL_DIFFUSE, lum_diffuse);
  else glLightfv(GL_LIGHT0, GL_DIFFUSE, lum_disable);

  if (specular) glLightfv(GL_LIGHT0, GL_SPECULAR, lum_speculaire);
  else glLightfv(GL_LIGHT0, GL_SPECULAR, lum_disable);

  glLightfv(GL_LIGHT0, GL_POSITION, lum_position);

  glEnable(GL_LIGHT2);

  GLfloat lum2_ambient[]={0.1,0.1,0.1,1.0};
  GLfloat lum2_diffuse[]={1.0,0.0,1.0,1.0};
  GLfloat lum2_speculaire[]={1.0,1.0,1.0,1.0};

  GLfloat lum2_position[]={-Xlight, Ylight, -Zlight, 1.0};
  if (infinity) lum2_position[3] = 0.0;

  if (ambient) glLightfv(GL_LIGHT2, GL_AMBIENT, lum2_ambient);
  else glLightfv(GL_LIGHT2, GL_AMBIENT, lum_disable);
  
  if (diffuse) glLightfv(GL_LIGHT2, GL_DIFFUSE, lum2_diffuse);
  else glLightfv(GL_LIGHT2, GL_DIFFUSE, lum_disable);

  if (specular) glLightfv(GL_LIGHT2, GL_SPECULAR, lum2_speculaire);
  else glLightfv(GL_LIGHT2, GL_SPECULAR, lum_disable);

  glLightfv(GL_LIGHT2, GL_POSITION, lum2_position);
  
  GLfloat mat_ambient[]={0.1,0.1,0.1,1.0};
  GLfloat mat_diffuse[]={1.0,1.0,0.0,1.0};
  GLfloat mat_speculaire[]={1.0,1.0,1.0,1.0};
  GLfloat mat_brillance[]={50.0};

  glMaterialfv(GL_FRONT,GL_SPECULAR,mat_ambient);
  glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse);
  glMaterialfv(GL_FRONT,GL_SPECULAR,mat_speculaire);
  glMaterialfv(GL_FRONT,GL_SHININESS,mat_brillance);
  
  if (flat) glShadeModel(GL_FLAT);
  else glShadeModel(GL_SMOOTH);
}

/*  Main Loop
 *  Ouverture de la fenetre d'affichage de tailles et titre donnes 
 *  et definition des fonctions de gestion d'evenement.
 */
int main(int argc, char **argv)
{
    GLenum type;

    glutInit(&argc, argv);
    glutInitWindowPosition(0, 0); 
    glutInitWindowSize( 500, 400);

    type = GLUT_RGB;
    type |= (doubleBuffer) ? GLUT_DOUBLE : GLUT_SINGLE;
    glutInitDisplayMode(type | GLUT_DEPTH);
 

 
   if (glutCreateWindow("Sphere") == GL_FALSE) {
        exit(1);
    }
  
  
   glEnable(GL_DEPTH_TEST);

   init_rendu();
  
   glClearColor (0.0, 0.4, 0.4, 0.0);
   glutMouseFunc(mouse);
   glutMotionFunc(mouseMotion);
   glutReshapeFunc(Reshape);
   glutKeyboardFunc(Key);
   glutDisplayFunc(display);
   glutMainLoop();
   return 0;
}

