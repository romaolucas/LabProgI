#include <GL/glut.h>
#include<math.h>
#include<stdio.h>
#define PI 3.1415

double user_angle = 0;
/*coordenadas da nave*/
double px = 0;
double py = 0;
double pz = 0;
/*constantes aleatórias para desenho*/
double cst_x = 1;
double cst_L = 3;
double cst_l = 1.5;

/*Parte original minha: desenhar a nave*/
void drawShip();

/*Inicializar e/ou configurar openGL*/
void init();

void draw();

void computeLocation();

void timeStep(int n);

/*Funções de teclado*/
//void special(int k, int x, int y); por enquanto só normal

void keyb(unsigned char k, int x, int y);

int main(int argc, char **argv){
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(900, 900); //Pensar melhor aqui o tamanho
  glutCreateWindow("Nave");
  init();
  glutDisplayFunc(draw);
  glutTimerFunc(100, timeStep, 1);
  //  glutSpecialFunc(special);
  glutKeyboardFunc(keyb);
  glutMainLoop();
  return 0;
}

void drawShip()
{
  glPushMatrix();
  glTranslatef(px, py, pz);
  glBegin(GL_TRIANGLES);
     glColor4f(0., 0., 1., 0.5);
     /*primeiro triângulo*/
     glVertex3f(0., cst_x, 0);
     glVertex3f(-cst_x * sin((2 * PI)/3), cst_x * cos(2 * PI/3), 0);
     glVertex3f(-cst_x * sin((4 * PI)/3), cst_x * cos((4 * PI)/3), 0);
     /*Segundo triangulo - base*/
     glColor4f(0., 1., 0., 0.5);
     glVertex3f(-cst_L, cst_x * cos(2 * PI/3), 0);
     glVertex3f(cst_L, cst_x * cos(2 * PI/3), 0);
     glVertex3f(0, cst_x * cos(2 * PI/3), cst_L);
     /*Terceiro e quarto triangulos - piramide*/
     glColor4f(0., 1., 1., 0.5);
     glVertex3f(0., cst_x, 0);
     glVertex3f(-cst_x * sin((2 * PI)/3), cst_x * cos(2 * PI/3), 0);
     glVertex3f(0, cst_x * cos(2 * PI/3), cst_L);
     glVertex3f(0., cst_x, 0);
     glVertex3f(-cst_x * sin((4 * PI)/3), cst_x * cos((4 * PI)/3), 0);
     glVertex3f(0, cst_x * cos(2 * PI/3), cst_L);
     /*Quinto e sexto quadrados - decoração*/
     glColor4f(1., 0., 0., 0.5);
     glVertex3f(-cst_l, cst_x * cos(2 * PI/3), 0);
     glVertex3f(-cst_L - 0.5, cst_x + 0.5, 0);
     glVertex3f(-cst_l, cst_x * cos(2 * PI/3), cst_L - 1.4);
     glVertex3f(cst_l, cst_x * cos(2 * PI/3), 0);
     glVertex3f(cst_L + 0.5, cst_x + 0.5, 0);
     glVertex3f(cst_l, cst_x * cos(2 * PI/3), cst_L - 1.4);
  
  glEnd();
  glPopMatrix();
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


void draw()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Limpa tudo
  glLoadIdentity();
  computeLocation();
  gluLookAt(
	    0.0, 0.0, -5.0, /*Olho*/
            0.0, 0.0, 0.0,    /*Centro*/
            0.0, 1.0, 0.0); /*Orientação (topo na direção Y)*/

  glColor4f(1.0, 1.0, 1.0, 1.0);
  glEnable(GL_NORMALIZE);
  glEnable(GL_TEXTURE_2D);
  glPushMatrix();
  glRotatef(user_angle, 0, 1, 0);
  drawShip();
  glPopMatrix();
  glutSwapBuffers();
  glFlush();
}

void computeLocation() {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(40.0,
		  1.0,
                  20.0,
                  1000.0);
  glMatrixMode(GL_MODELVIEW);
  gluLookAt(0.0, 10.0, 60.0,
            0.0, 8.0, 0.0,
            0.0, 1.0, 0.);

}
void timeStep(int n){
  glutTimerFunc(100, timeStep, 1);
  glutPostRedisplay();
}

void keyb(unsigned char k, int x, int y) {
  switch(k) {
    case 'w':
    case 'W':
      py += 0.5;
      break;
    case 's':
    case 'S':
      py -= 0.5;
      break;
    case 'a':
    case 'A':
      px += 0.5;
      break;
    case 'd':
    case 'D':
      px -= 0.5;
      break;
    case 'q':
    case 'Q':
      user_angle += 0.93;
      break;
    case 'e':
    case 'E':
      user_angle -= 0.93;
      break;
  }
  glutPostRedisplay();
}
