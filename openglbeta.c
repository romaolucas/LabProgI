#include <GL/glut.h>
#include<math.h> 
#include<stdio.h> 
#include "Cenario.h"
 
double user_theta  = 0.;
double user_height = 7.;
double zdist = 0.;

void drawSphere(double r, int lats, int longs) {
  int i, j;
  for(i = 0; i <= lats; i++) {
      double lat0 = M_PI * (-0.5 + (double) (i - 1) / lats);
      double z0  = sin(lat0);
      double zr0 =  cos(lat0);

      double lat1 = M_PI * (-0.5 + (double) i / lats);
      double z1 = sin(lat1);
      double zr1 = cos(lat1);

      glBegin(GL_QUAD_STRIP);
      for(j = 0; j <= longs; j++) {
          double lng = 2 * M_PI * (double) (j - 1) / longs;
          double x = cos(lng);
          double y = sin(lng);

          glNormal3f(x * zr0, y * zr0, z0);
          glVertex3f(x * zr0, y * zr0, z0);
          glNormal3f(x * zr1, y * zr1, z1);
          glVertex3f(x * zr1, y * zr1, z1);
      }
      glEnd();
  }
}

void computeLocation() {
  double x = 2 * cos(0);     // my x-, y-, and z-coordinates
  double y = 2 * sin(0);
  double z = 0;
  double d = sqrt(x * x + y * y + z * z); // distance to origin

  glMatrixMode(GL_PROJECTION);        // Set projection parameters.
  glLoadIdentity();
  //glFrustum(-d * 0.5, d * 0.5, -d * 0.5, d * 0.5, d - 1.1, d + 1.1);
  //gluLookAt(x, y, z,  0, 0, 0,  0, 0, 1);
//  gluLookAt(
 // 			0.0,  8.0, -20.0,	/* olho (0,8,60) */
 // 			0.0,  8.0,   0.0,	/* centro (0,8,0) */
 // 			0.0,  1.0,   0.0);	/* orientação (topo na direção Y) */
 // gluPerspective(   40.0,		/* ângulo de visão */
	//			     1.0,		/* aspecto */
	//			    20.0,		/* plano próximo */
//				  1000.0);		/* plano distante */
  /* Modo de projeção */
  gluPerspective(   40.0,		/* ângulo de visão */
				     1.0,		/* aspecto */
				    20.0,		/* plano próximo */
				  1000.0);		/* plano distante */

  /* coordenadas do modelo */
  glMatrixMode(GL_MODELVIEW);
  /* posição da câmera */
  gluLookAt(0.0, 8.0, 60.0,		/* olho (0,8,60) */
			0.0, 8.0, 0.0,      /* centro(0,8,0) */
			0.0, 1.0, 0.);      /* orientação (topo na direção Y) */


}

// Initializes information for drawing within OpenGL.
void init() {
  GLfloat sun_direction[] = { 0.0, 2.0, -1.0, 1.0 };
  GLfloat sun_intensity[] = { 0.7, 0.7, 0.7, 1.0 };
  GLfloat ambient_intensity[] = { 0.3, 0.3, 0.3, 1.0 };

  glClearColor(1.0, 1.0, 1.0, 0.0);   // Set window color to white.
  computeLocation();

  glEnable(GL_DEPTH_TEST);            // Draw only closest surfaces

  glEnable(GL_LIGHTING);              // Set up ambient light.
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient_intensity);

  glEnable(GL_LIGHT0);                // Set up sunlight.
  glLightfv(GL_LIGHT0, GL_POSITION, sun_direction);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, sun_intensity);

  glEnable(GL_COLOR_MATERIAL);        // Configure glColor().
  glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
  glDepthFunc(GL_LEQUAL); 
  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  
}

// Draws the current image.
void draw() {
  nodeDefense *d;
  nodeTiro *t;
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear window.
  glLoadIdentity();
  gluLookAt(
  			0.0,  8.0, -20.0,	/* olho (0,8,60) */
  			0.0,  8.0,   0.0,	/* centro (0,8,0) */
  			0.0,  1.0,   0.0);	/* orientação (topo na direção Y) */
  glColor4f(1.0, 1.0, 1.0,1.0);
  glEnable(GL_NORMALIZE);
  glShadeModel(GL_SMOOTH);
  for (d = defenseList->next; d != NULL; d = d->next)
  { 
    glTranslatef(d->defense->position->x, d->defense->position->y, d->defense->position->z); 
    glBegin(GL_QUADS);                // Begin drawing the color cube with 6 quads
    {
       glColor3f(0.0f, 0.8f, 0.0f);     // Green
       glVertex3f( 0.8f, 0.8f, -0.8f);
       glVertex3f(-0.8f, 0.8f, -0.8f);
       glVertex3f(-0.8f, 0.8f,  0.8f);
       glVertex3f( 0.8f, 0.8f,  0.8f);
 
       // Bottom face (y = -0.8f)
       glColor3f(0.0f, 0.8f, 0.0f);     // Green
       glVertex3f( 0.8f, -3.0f,  0.8f);
       glVertex3f(-0.8f, -3.0f,  0.8f);
       glVertex3f(-0.8f, -3.0f, -0.8f);
       glVertex3f( 0.8f, -3.0f, -0.8f);
 
       // Front face  (z = 0.8f)
       glColor3f(1.0f, 0.0f, 0.0f);     // Red
       glVertex3f( 0.8f,  0.8f, 0.8f);
       glVertex3f(-0.8f,  0.8f, 0.8f);
       glVertex3f(-0.8f, -3.0f, 0.8f);
       glVertex3f( 0.8f, -3.0f, 0.8f);
 
       // Back face (z = -0.8f)
       glColor3f(1.0f, 0.0f, 0.0f);     // Red
       glVertex3f( 0.8f, -3.0f, -0.8f);
       glVertex3f(-0.8f, -3.0f, -0.8f);
       glVertex3f(-0.8f,  0.8f, -0.8f);
       glVertex3f( 0.8f,  0.8f, -0.8f);
 
       // Left face (x = -0.8f)
       glColor3f(1.0f, 0.0f, 0.0f);     // Red
       glVertex3f(-0.8f,  0.8f,  0.8f);
       glVertex3f(-0.8f,  0.8f, -0.8f);
       glVertex3f(-0.8f, -3.0f, -0.8f);
       glVertex3f(-0.8f, -3.0f,  0.8f);
  
       // Right face (x = 0.8f)
       glColor3f(0.0f, 0.8f, 0.0f);     // Green
       glVertex3f(0.8f,  0.8f, -0.8f);
       glVertex3f(0.8f,  0.8f,  0.8f);
       glVertex3f(0.8f, -3.0f,  0.8f);
       glVertex3f(0.8f, -3.0f, -0.8f);
    } 
    glEnd();  // End of drawing color-cube
  }
  glColor3f(0.0f, 0.0f, 0.0f); 
  for (t = tiroList->next; t != NULL; t = t->next) 
  { 
    glPushMatrix(); 
    glTranslatef(t->tiro->position->x, t->tiro->position->y, t->tiro->position->z); 
    glColor4f(1.0, 0, 0, 1.0);
    glutSolidSphere(0.2, 40, 40);
    glPopMatrix();
   }
  glutSwapBuffers();
  //glutPostRedisplay();
  glFlush();
}

void timeStep(int n) {
   glutTimerFunc(100, timeStep, 1);
   glutPostRedisplay();
}

// Called when a "special" key is pressed
void special(int k, int x, int y) {
  switch(k) {
  case GLUT_KEY_UP:    user_height += 0.1; break;
  case GLUT_KEY_DOWN:  user_height -= 0.1; break;
  case GLUT_KEY_LEFT:  user_theta  += 0.1; break;
  case GLUT_KEY_RIGHT: user_theta  -= 0.1; break;
  }
  computeLocation();
  glutPostRedisplay();
}

void keyb(unsigned char k, int x, int y) {
   switch(k) {
      case 'w': case 'W':
         zdist += 0.1;
         break;
      case 's': case 'S':
         zdist -= 0.1;
         break;
      case 'q': case 'Q':
         exit(EXIT_SUCCESS);
   }
   computeLocation();
   glutPostRedisplay();
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
  //glutInitWindowPosition(50, 100);    // Set up display window.
  glutInitWindowSize(900, 900);
  glutCreateWindow("Sphere");

  init();
  glutDisplayFunc(draw);
  glutTimerFunc(100, timeStep, 1);
  glutSpecialFunc(special);
  glutKeyboardFunc(keyb);
  glutMainLoop();
  return 0;
}

