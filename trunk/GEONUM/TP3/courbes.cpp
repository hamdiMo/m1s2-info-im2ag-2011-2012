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
double         points    [  nb_points_max  ][2];

unsigned       ordre         = 3;
double         pts_ctrl  [3*nb_points_max+2][2];
double         pts_ctrl_2[4*nb_points_max+3][2];
double**       pts_ctrl_k[1000];

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
	int o = 3;
    for (unsigned i=1; i<nb_points; i++) {
		// Controle de la dérivée
        // pts_ctrl[3*i-1][0] = 2.0f*pts_ctrl[3*i][0] - pts_ctrl[3*i+1][0];
        // pts_ctrl[3*i-1][1] = 2.0f*pts_ctrl[3*i][1] - pts_ctrl[3*i+1][1];
		pts_ctrl_k[o][o*i-1][0] = 2.0f*pts_ctrl_k[o][o*i][0] - pts_ctrl_k[o][o*i+1][0];
        pts_ctrl_k[o][o*i-1][1] = 2.0f*pts_ctrl_k[o][o*i][1] - pts_ctrl_k[o][o*i+1][1];
    }
}

void calcul_ctrl_2() {
	int o = 4;
	// int n = 3;
	for (unsigned i=0; i<nb_points; i++) {
		// A transformer: Elevation de degré

		/*//////////////////////////////////////////////
		// Points 0
		pts_ctrl_2[4*i][0] = pts_ctrl[3*i][0];
		pts_ctrl_2[4*i][1] = pts_ctrl[3*i][1];

		for (int k = 1; k < n+1; k++) {
			pts_ctrl_2[4*i + k][0] = (((double)k / (n+1)) * pts_ctrl[3*i + k-1][0]) + ((1. - ((double)k / (n+1))) * pts_ctrl[3*i + k][0]);
			pts_ctrl_2[4*i + k][1] = (((double)k / (n+1)) * pts_ctrl[3*i + k-1][1]) + ((1. - ((double)k / (n+1))) * pts_ctrl[3*i + k][1]);
		}
		
		// Points 4
		pts_ctrl_2[4*i+4][0] = pts_ctrl[3*i+3][0];
		pts_ctrl_2[4*i+4][1] = pts_ctrl[3*i+3][1];
		*///////////////////////////////////////////////

		///////////////////////////////////////////////
		// Points 0
		pts_ctrl_k[o][o*i][0] = pts_ctrl_k[o-1][(o-1)*i][0];
		pts_ctrl_k[o][o*i][1] = pts_ctrl_k[o-1][(o-1)*i][1];

		for (int k = 1; k < o; k++) {
			pts_ctrl_k[o][o*i + k][0] = (((double)k / o) * pts_ctrl_k[o-1][(o-1)*i + k-1][0]) + ((1. - ((double)k / o)) * pts_ctrl_k[o-1][(o-1)*i + k][0]);
			pts_ctrl_k[o][o*i + k][1] = (((double)k / o) * pts_ctrl_k[o-1][(o-1)*i + k-1][1]) + ((1. - ((double)k / o)) * pts_ctrl_k[o-1][(o-1)*i + k][1]);
		}
		
		// Points 4
		pts_ctrl_k[o][o*i+o][0] = pts_ctrl_k[o-1][(o-1)*i+(o-1)][0];
		pts_ctrl_k[o][o*i+o][1] = pts_ctrl_k[o-1][(o-1)*i+(o-1)][1];
		///////////////////////////////////////////////
	}
}

void calcul_ctrl_3() {
	int o = 4;
   
    for (unsigned i=1; i<nb_points; i++) {
		// Controle de la dérivée
        pts_ctrl_k[o][o*i-1][0] = 2.0f*pts_ctrl_k[o][o*i][0] - pts_ctrl_k[o][o*i+1][0];
        pts_ctrl_k[o][o*i-1][1] = 2.0f*pts_ctrl_k[o][o*i][1] - pts_ctrl_k[o][o*i+1][1];

		// A ajouter pour C^2
		///////////////////////////////////////////////
		pts_ctrl_k[o][o*i+2][0] = pts_ctrl_k[o][o*i-2][0] + 2.0f*pts_ctrl_k[o][o*i+1][0] - 2.0f*pts_ctrl_k[o][o*i-1][0];
		pts_ctrl_k[o][o*i+2][1] = pts_ctrl_k[o][o*i-2][1] + 2.0f*pts_ctrl_k[o][o*i+1][1] - 2.0f*pts_ctrl_k[o][o*i-1][1];
		///////////////////////////////////////////////
    }
}

void calcul_ctrl_k() {
	int k = ordre;
	
    for (unsigned i=1; i<nb_points; i++) {
    	for (int d = 1; d <= ordre - 2; d++) {
			
		}
		// Controle de la dérivée
        pts_ctrl_k[o][o*i-1][0] = 2.0f*pts_ctrl_k[o][o*i][0] - pts_ctrl_k[o][o*i+1][0];
        pts_ctrl_k[o][o*i-1][1] = 2.0f*pts_ctrl_k[o][o*i][1] - pts_ctrl_k[o][o*i+1][1];

		pts_ctrl_k[o][o*i+2][0] = pts_ctrl_k[o][o*i-2][0] + 2.0f*pts_ctrl_k[o][o*i+1][0] - 2.0f*pts_ctrl_k[o][o*i-1][0];
		pts_ctrl_k[o][o*i+2][1] = pts_ctrl_k[o][o*i-2][1] + 2.0f*pts_ctrl_k[o][o*i+1][1] - 2.0f*pts_ctrl_k[o][o*i-1][1];
    }
	
	if (k < 3) k = 3;

	if (pts_ctrl_k[k] == NULL) {
		pts_ctrl_k[k] = malloc((k*nb_points_max + k-1) * sizeof(double*));
	}

	for (int j = 0; j < k; j++) pts_ctrl_k[k][i + j] = malloc(2 * sizeof(double));

    for (unsigned i=1; i<nb_points; i++) {
    
		// Controle de la dérivée
        pts_ctrl_2[4*i-1][0] = 2.0f*pts_ctrl_2[4*i][0] - pts_ctrl_2[4*i+1][0];
        pts_ctrl_2[4*i-1][1] = 2.0f*pts_ctrl_2[4*i][1] - pts_ctrl_2[4*i+1][1];

		// A ajouter pour C^2
		///////////////////////////////////////////////
		pts_ctrl_2[4*i+2][0] = pts_ctrl_2[4*i-2][0] + 2.0f*pts_ctrl_2[4*i+1][0] - 2.0f*pts_ctrl_2[4*i-1][0];
		pts_ctrl_2[4*i+2][1] = pts_ctrl_2[4*i-2][1] + 2.0f*pts_ctrl_2[4*i+1][1] - 2.0f*pts_ctrl_2[4*i-1][1];
		///////////////////////////////////////////////
    }
}

float Bezier(float t, unsigned i, unsigned n) {
	float res = 1.0f;
	for (unsigned k=0; k<  i; k++) res *= t/float(k+1);
	for (unsigned k=0; k<n-i; k++) res *= (1.0f-t)/float(k+1);
	for (unsigned k=1; k<= n; k++) res *= float(k);
    return res;
}

void trace_Bezier() {
  if (nb_points<2) return;

  for (unsigned j=0; j<nb_points-1; j++) {
    glColor3d(color[j%3][0], color[j%3][1], color[j%3][2]);
    glBegin(GL_LINE_STRIP);
	for (unsigned k=0; k<=100; k++) {
		float t = float(k)/100.0f;
		float x = 0.0;
		float y = 0.0;
		for (unsigned i=0; i<ordre + 1; i++) {
			x += Bezier(t, i, ordre)*pts_ctrl_k[ordre][ordre*j+i][0];
			y += Bezier(t, i, ordre)*pts_ctrl_k[ordre][ordre*j+i][1];
		}
		glVertex2f(x, y);
	}
    glEnd();
  }
}

/////////////////////////////////////////////////////////////
// Commandes
/////////////////////////////////////////////////////////////
void motion(int x, int y) {
    if (depl_pt==nb_points_max) return;

    float x2 = 2.0f*(double(x)-double(width)/2.0)/double(width);
    float y2 =-2.0f*(double(y)-double(height)/2.0)/double(height);

	for (int o = 3; o <= ordre; o++) {
		pts_ctrl_k[o][depl_pt][0] = x2;
		pts_ctrl_k[o][depl_pt][1] = y2;	
	}

	calcul_ctrl_k();

	/* if (type) {
		pts_ctrl_2[depl_pt][0] = x2;
		pts_ctrl_2[depl_pt][1] = y2;

		calcul_ctrl_3();
	} else {
		pts_ctrl[depl_pt][0] = x2;
		pts_ctrl[depl_pt][1] = y2;

		calcul_ctrl  ();
		calcul_ctrl_2();
	} */
    
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

              pts_ctrl[3*nb_points+1][0] = x2 +0.01f;
              pts_ctrl[3*nb_points+1][1] = y2;

              nb_points++;
			  if (nb_points>1) {
				  calcul_ctrl();
				  calcul_ctrl_2();
			  }
           }

        } else {
            // Recherche du point de contrôle libre le plus proche
            
            // Tangente
			if (type) {
				double d1 = dist(x2, y2, pts_ctrl_2[1][0], pts_ctrl_2[1][1]);
				depl_pt = 1;
				for (unsigned i=0; i<=nb_points; i++) {
					double d2 = dist(x2, y2, pts_ctrl_2[4*i+1][0], pts_ctrl_2[4*i+1][1]);
					if (d1>d2) {
						d1 = d2;
						depl_pt = 4*i+1;
					}
					
					d2 = dist(x2, y2, pts_ctrl_2[4*i+2][0], pts_ctrl_2[4*i+2][1]);
					if (d1>d2) {
						d1 = d2;
						depl_pt = 4*i+2;
					}
				}
			} else {
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
	case 'c':
		type = !type;
		break;
    case 'd':   // d pour deplacement
        depl = !depl;
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
		if (type) {
			for (unsigned i=0; i<4*nb_points-3; i++) glVertex2f(pts_ctrl_2[i][0], pts_ctrl_2[i][1]);
		} else {
			for (unsigned i=0; i<3*nb_points-2; i++) glVertex2f(pts_ctrl  [i][0], pts_ctrl  [i][1]);
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
		if (type) {
			for (unsigned i=0; i<nb_points-1; i++) {
				// Points de contrôle libre
				glColor3d(0.0f, 1.0f, 0.0f);
				glVertex2f(pts_ctrl_2[4*i+1][0], pts_ctrl_2[4*i+1][1]);
				glVertex2f(pts_ctrl_2[4*i+2][0], pts_ctrl_2[4*i+2][1]);

				// Points de contrôles non libre
				glColor3d(0.0f, 0.0f, 1.0f);
				glVertex2f(pts_ctrl_2[4*i+3][0], pts_ctrl_2[4*i+3][1]);
			}
			// Points de contrôle libre
			glColor3d(0.0f, 1.0f, 0.0f);
			glVertex2f(pts_ctrl_2[4*nb_points-3][0], pts_ctrl_2[4*nb_points-3][1]);

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
