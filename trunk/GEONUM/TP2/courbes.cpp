#include <iostream>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <math.h>
#include <float.h>

using namespace std;

/////////////////////////////////////////////////////////////
// Variables Globales
/////////////////////////////////////////////////////////////
// Taille de la fenêtre
unsigned width  = 1200;
unsigned height = 1200;

// Points Data
unsigned       nb_points     = 0;
const unsigned nb_points_max = 100;
double         points  [  nb_points_max  ][2];
double         pts_ctrl[3*nb_points_max+2][2];

// Couleurs
double color[3][3] = {{1, 0, 0},	// Rouge
                      {0, 1, 0},	// Vert
                      {0, 0, 1}};	// Bleu

// Other
bool     depl    = false;
bool     type    = false;
unsigned depl_pt = nb_points_max;

/////////////////////////////////////////////////////////////
// Other
/////////////////////////////////////////////////////////////
double dist(float x0, float y0, float x1, float y1) {return sqrt((x0-x1)*(x0-x1) + (y0-y1)*(y0-y1));}

/////////////////////////////////////////////////////////////
// Calcul Béziers
/////////////////////////////////////////////////////////////
void calcul_ctrl() {   
    if (type==0) {
        for (unsigned i=1; i<nb_points-1; i++) {
	    	// Programmez Ici
            pts_ctrl[3*i+1][0] = (2.0f)*pts_ctrl[3*i][0] - pts_ctrl[3*i-1][0];
           	pts_ctrl[3*i+1][1] = (2.0f)*pts_ctrl[3*i][1] - pts_ctrl[3*i-1][2];

            // Deuxieme point
          	pts_ctrl[3*i+2][0] = pts_ctrl[3*i-2][0] + 2.0f * pts_ctrl[3*i+1][0] - pts_ctrl[3*i-1][0];
            pts_ctrl[3*i+2][1] = pts_ctrl[3*i-2][1] + 2.0f * pts_ctrl[3*i+1][1]- pts_ctrl[3*i+1][1];


	    	// Premier point
            //pts_ctrl[3*i+1][0] = (2.0f/3.0f)*pts_ctrl[3*i][0] + (1.0f/3.0f)*pts_ctrl[3*i+3][0];
            //pts_ctrl[3*i+1][1] = (2.0f/3.0f)*pts_ctrl[3*i][1] + (1.0f/3.0f)*pts_ctrl[3*i+3][1];

            // Deuxieme point
            //pts_ctrl[3*i+2][0] = (1.0f/3.0f)*pts_ctrl[3*i][0] + (2.0f/3.0f)*pts_ctrl[3*i+3][0];
            //pts_ctrl[3*i+2][1] = (1.0f/3.0f)*pts_ctrl[3*i][1] + (2.0f/3.0f)*pts_ctrl[3*i+3][1];
        }
    } else {
        for (unsigned i=1; i<nb_points; i++) {
            // Premier point
            pts_ctrl[3*i+1][0] = (2.0f/3.0f)*pts_ctrl[3*i][0] + (1.0f/3.0f)*pts_ctrl[3*i+3][0];
            pts_ctrl[3*i+1][1] = (2.0f/3.0f)*pts_ctrl[3*i][1] + (1.0f/3.0f)*pts_ctrl[3*i+3][1];

            // Deuxieme point (A supprimer)
            pts_ctrl[3*i+2][0] = (1.0f/3.0f)*pts_ctrl[3*i][0] + (2.0f/3.0f)*pts_ctrl[3*i+3][0];
            pts_ctrl[3*i+2][1] = (1.0f/3.0f)*pts_ctrl[3*i][1] + (2.0f/3.0f)*pts_ctrl[3*i+3][1];
            if (i==nb_points-1) {
				pts_ctrl[3*nb_points-2][0] = pts_ctrl[3*nb_points-3][0] + 0.01f;
				pts_ctrl[3*nb_points-2][1] = pts_ctrl[3*nb_points-3][1];
	    	}
	    	// Fin de (A supprimer)
        }
    }
}

unsigned fact(unsigned i){
	//if(i==0) return 1;
	//return i*fact(i-1);
	unsigned n=1;
	for(unsigned j=1;j<i+1;j++){
		n=n*j;
	}
	return n;
}

float Power(float i, unsigned e){
	//if(e==0) return 1.0;
	//return i*Power(i,e-1);
	float n = 1.0;
	for(unsigned j=1; j < e+1; j++){
		n = n*i;
	}
	return n;
}

float Bezier(float t, unsigned i) {
    // Programmez Ici   
    return ((float)(Power(t,i) * Power(1.0-t,3-i) * fact(3)))/float(fact(i)*fact(3-i));
}

void trace_Bezier() {
  if (nb_points<2) return;

  for (unsigned j=0; j<nb_points-1; j++) {
    glColor3d(color[j%3][0], color[j%3][1], color[j%3][2]);
    glBegin(GL_LINE_STRIP);
    for(unsigned i=0;i<51;i++){
    	float pts[2]={0,0};
    	float t = float (i)/50.0;
    	pts[0]=Bezier(t,0)*pts_ctrl[0][0] + Bezier(t,1)*pts_ctrl[1][0] + Bezier(t,2)*pts_ctrl[2][0] + Bezier(t,3)*pts_ctrl[3][0];
    	pts[1]=Bezier(t,0)*pts_ctrl[0][1] + Bezier(t,1)*pts_ctrl[1][1] + Bezier(t,2)*pts_ctrl[2][1] + Bezier(t,3)*pts_ctrl[3][1];
    	glVertex2f(pts[0],pts[1]);    	
    }
    // Programmez Ici
    
    glEnd();
  }
}

/////////////////////////////////////////////////////////////
// Commandes
/////////////////////////////////////////////////////////////
void motion(int x, int y) {
    if (depl_pt==nb_points_max) return;

    float x2 = 2.0f*(double(x)-double( width)/2.0)/double( width);
    float y2 =-2.0f*(double(y)-double(height)/2.0)/double(height);

    pts_ctrl[depl_pt][0] = x2;
    pts_ctrl[depl_pt][1] = y2;

    calcul_ctrl();
    
    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y) {
    float x2 = 2.0f*(double(x)-double( width)/2.0)/double( width);
    float y2 =-2.0f*(double(y)-double(height)/2.0)/double(height); 

    if (state == GLUT_DOWN) {
        // Déplacement d'un points: Programmez Ici:
        if (!depl) {
           // Création d'un points
           if (nb_points!=nb_points_max) {
              points[nb_points][0] = x2;
              points[nb_points][1] = y2;

              pts_ctrl[3*nb_points][0] = x2;
              pts_ctrl[3*nb_points][1] = y2;

              if (type==0) {
                  if (nb_points==1) {
                      // 1er point de ctrl: libre
                      pts_ctrl[1][0] = (2.0/3.0)*points[0][0] + (1.0f/3.0f)*x2;
                      pts_ctrl[1][1] = (2.0/3.0)*points[0][1] + (1.0f/3.0f)*y2;

                      // 2eme point de ctrl: libre
                      pts_ctrl[2][0] = (1.0/3.0)*points[0][0] + (2.0f/3.0f)*x2;;
                      pts_ctrl[2][1] = (1.0/3.0)*points[0][1] + (2.0f/3.0f)*y2;;
                  }
              }

              pts_ctrl[3*nb_points+1][0] = x2 +0.01f;
              pts_ctrl[3*nb_points+1][1] = y2;

              nb_points++;
              if (nb_points>1) calcul_ctrl();
           }

        } else {
            // Recherche du point de contrôle libre le plus proche
            if (type==0) {
                // 2 premiers points
                double d1 = dist(x2, y2, pts_ctrl[1][0], pts_ctrl[1][1]);
                double d2 = dist(x2, y2, pts_ctrl[2][0], pts_ctrl[2][1]);
                if (d1<d2) depl_pt = 1;
                else       depl_pt = 2;
            } else {
                // Tangente
                double d1 = dist(x2, y2, pts_ctrl[1][0], pts_ctrl[1][1]);
                depl_pt = 1;
                for (unsigned i=1; i<=nb_points; i++) {
                    double d2 = dist(x2, y2, pts_ctrl[3*i+1][0], pts_ctrl[3*i+1][1]);
                    if (d1>d2) {
                        d1 = d2;
                        depl_pt = 3*i+1;
                    }
                }
            }
        }
    }

    if (state == GLUT_UP) depl_pt = nb_points_max;
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 27:    // Echap
        exit(0);
    case 'd':   // d pour deplacement
        depl = !depl;
        break;
    case 'c':   // c pour changer de primitive
        type = !type;
        calcul_ctrl();
        break;
    case 'r':   // r pour reset
        nb_points = 0;
        break;
    case '-':   // - pour enlever un point
        if (nb_points > 0) nb_points--;
        break;
    default:
        return;
    }
    glutPostRedisplay();
}

/////////////////////////////////////////////////////////////
// Fonctions Ecran
/////////////////////////////////////////////////////////////
void window_reshape(int w, int h) {
    width  = w;
    height = h;
    glViewport(0, 0, w, h);
    glutPostRedisplay();
}

void draw_objects() {
    // Trace les Segments (Type 1)
    glLineWidth(0.5f);
    glColor3d(1.0f, 1.0f, 1.0f);
    glBegin(GL_LINE_STRIP);
    for (unsigned i=0; i<nb_points; i++) {
        glVertex2f(points[i][0], points[i][1]);
    }
    glEnd();

    // Trace les Segments (Contrôle)
    if (nb_points>1) {
        glLineWidth(0.5f);
        glColor3d(1.0f, 1.0f, 0.0f);
        glBegin(GL_LINE_STRIP);
        for (unsigned i=0; i<3*nb_points-2; i++) {
            glVertex2f(pts_ctrl[i][0], pts_ctrl[i][1]);
        }
        glEnd();
    }

    // Trace Bezier
    trace_Bezier();

    // Trace les Sommets
    glPointSize(5.0f);
    glBegin(GL_POINTS);
    glColor3d(1.0f, 0.0f, 0.0f);
    for (unsigned i=0; i<nb_points; i++) glVertex2f(points[i][0], points[i][1]);

    if (nb_points>1) {
        if (type==0) {
            // Points de contrôle libre
            glColor3d(0.0f, 1.0f, 0.0f);
            glVertex2f(pts_ctrl[1][0], pts_ctrl[1][1]);
            glVertex2f(pts_ctrl[2][0], pts_ctrl[2][1]);

            // Points de contrôle non libre
            glColor3d(0.0f, 0.0f, 1.0f);
            for (unsigned i=1; i<nb_points-1; i++) {
                glVertex2f(pts_ctrl[3*i+1][0], pts_ctrl[3*i+1][1]);
                glVertex2f(pts_ctrl[3*i+2][0], pts_ctrl[3*i+2][1]);
            }
        } else {
            for (unsigned i=0; i<nb_points-1; i++) {
                // Points de contrôle libre
                glColor3d(0.0f, 1.0f, 0.0f);
                glVertex2f(pts_ctrl[3*i+1][0], pts_ctrl[3*i+1][1]);
                // Points de contrôle non libre
                glColor3d(0.0f, 0.0f, 1.0f);
                glVertex2f(pts_ctrl[3*i+2][0], pts_ctrl[3*i+2][1]);
            }
            // Points de contrôle libre
            glColor3d(0.0f, 1.0f, 0.0f);
            glVertex2f(pts_ctrl[3*nb_points-2][0], pts_ctrl[3*nb_points-2][1]);
        }
    }
    glEnd();
}

void draw_scene(void) {
    // Initialisation de la fenêtre
    glPushMatrix();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    // Enable
    glEnable(GL_POINT_SIZE);
    glEnable(GL_POINT_SMOOTH);

    // Création des objets
    draw_objects();

    // Swap pour afficher la prochaine fenêtre
    glutSwapBuffers();
    glPopMatrix();
}

/////////////////////////////////////////////////////////////
// Main
/////////////////////////////////////////////////////////////
int main(int argc, char *argv[]) {
    // Initialisation de Glut
    glutInit           (&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_RGB | GLUT_DOUBLE | GLUT_MULTISAMPLE | GLUT_STENCIL);
    glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
    glEnable(GL_POINT_SMOOTH);
    glEnable(GL_POINT_SIZE);

    // Taille et position de la fenêtre
    glutInitWindowSize    (1200, 1200);    // Window Size     1200x1200
    glutInitWindowPosition(200,   0);

    // Création et Titre de la fenêtre
    glutCreateWindow("Geometrie Numerique");

    // Fonction d'affichage (Renvoi à la fonction draw_scene)
    glutDisplayFunc(draw_scene);

    // Fonctions liers aux différentes commandes
    glutMouseFunc   (   mouse);
    glutMotionFunc  (  motion);
    glutKeyboardFunc(keyboard);

    // Fonction lier à la mise à l'échelle de la fenêtre
    glutReshapeFunc (window_reshape);

    glutSwapBuffers();
    glutMainLoop();
    return 0;
}
