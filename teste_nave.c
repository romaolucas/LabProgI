#include <GL/glut.h>
#include<math.h>
#include<stdio.h>
#include "Cenario.h"
#include "general.h"
#include "Nave.h"
#include "Defesa.h"
#include "Tiro.h"
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
/*controla o fim do jogo*/
int gameRunning = TRUE;

/*Parte original minha: desenhar a nave*/
void drawShip();

/*Inicializar e/ou configurar openGL*/
void init();

void draw();

void computeLocation();

void timeStep(int n);

/*Funções de teclado*/

void keyb(unsigned char k, int x, int y);

void skeyb(int k, int x, int y);

int main(int argc, char **argv){

  initShip();
  initCenario();
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(900, 900); 
  glutCreateWindow("Nave");
  init();
  
  glutDisplayFunc(draw);
  glutTimerFunc(100, timeStep, 1);
  glutKeyboardFunc(keyb);
  glutSpecialFunc(skeyb);
  glutMainLoop();
  return 0;
   
}

void drawShip()
{
  glPushMatrix();
  glTranslatef(ship->position->x, ship->position->y, ship->position->z); 
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

void init() {
  GLfloat sun_direction[] = { 0.0, 2.0, 10.0, 1.0 };
  GLfloat sun_intensity[] = { 1.0, 1.0, 1.0, 1.0 };
  GLfloat ambient_intensity[] = { 0.5, 0.5, 0.5, 1.0 };

  glClearColor(1.0, 1.0, 1.0, 0.0);   
  computeLocation();

  glEnable(GL_DEPTH_TEST);            

  glEnable(GL_LIGHTING);             
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient_intensity);

  glEnable(GL_LIGHT0);                
  glLightfv(GL_LIGHT0, GL_POSITION, sun_direction);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, sun_intensity);

  glEnable(GL_COLOR_MATERIAL);     
  glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
  glDepthFunc(GL_LEQUAL); 
  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  
}


void draw()
{  
  nodeDefense *d;
  nodeTiro *t;
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); /*Limpa tudo*/
  glLoadIdentity();
  computeLocation();
  gluLookAt(
	    0.0, 0.0, -5.0, /*Olho*/
            0.0, 0.0, 0.0,    /*Centro*/
            0.0, 1.0, 0.0); /*Orientação (topo na direção Y)*/

  glColor4f(1.0, 1.0, 1.0, 1.0);
  glEnable(GL_NORMALIZE);
  glEnable(GL_TEXTURE_2D);
  glShadeModel(GL_SMOOTH);
  for (d = defenseList->next; d != NULL; d = d->next)
  { 
    glPushMatrix();
    glTranslatef(d->defense->position->x, d->defense->position->y, d->defense->position->z); 
    glBegin(GL_QUADS);              
    {  
       glColor3f(0.0f, 0.4f, 0.0f);     
       glVertex3f( 0.8f, 0.8f, -0.8f);
       glVertex3f(-0.8f, 0.8f, -0.8f);
       glColor3f(0.3f, 0.3f, 0.3f);
       glVertex3f(-0.8f, 0.8f,  0.8f);
       glVertex3f( 0.8f, 0.8f,  0.8f);
 
       /*Bottom face (y = -0.8f)*/
       glColor3f(0.0f, 0.4f, 0.0f);     
       glVertex3f( 0.8f, -3.0f,  0.8f);
       glVertex3f(-0.8f, -3.0f,  0.8f);
       glColor3f(0.3f, 0.3f, 0.3f);
       glVertex3f(-0.8f, -3.0f, -0.8f);
       glVertex3f( 0.8f, -3.0f, -0.8f);
 
       /* Front face  (z = 0.8f)*/
       glColor3f(0.4f, 0.0f, 0.0f);     
       glVertex3f( 0.8f,  0.8f, 0.8f);
       glVertex3f(-0.8f,  0.8f, 0.8f);
       glColor3f(0.3f, 0.3f, 0.3f);
       glVertex3f(-0.8f, -3.0f, 0.8f);
       glVertex3f( 0.8f, -3.0f, 0.8f);
 
       /* Back face (z = -0.8f)*/
       glColor3f(0.4f, 0.0f, 0.0f);     
       glVertex3f( 0.8f, -3.0f, -0.8f);
       glVertex3f(-0.8f, -3.0f, -0.8f);
       glColor3f(0.3f, 0.3f, 0.3f);
       glVertex3f(-0.8f,  0.8f, -0.8f);
       glVertex3f( 0.8f,  0.8f, -0.8f);
 
       /* Left face (x = -0.8f)*/
       glColor3f(0.4f, 0.0f, 0.0f);     
       glVertex3f(-0.8f,  0.8f,  0.8f);
       glVertex3f(-0.8f,  0.8f, -0.8f);
       glColor3f(0.3f, 0.3f, 0.3f);
       glVertex3f(-0.8f, -3.0f, -0.8f);
       glVertex3f(-0.8f, -3.0f,  0.8f);
  
       /* Right face (x = 0.8f)*/
       glColor3f(0.0f, 0.4f, 0.0f);     
       glVertex3f(0.8f,  0.8f, -0.8f);
       glVertex3f(0.8f,  0.8f,  0.8f);
       glColor3f(0.3f, 0.3f, 0.3f);
       glVertex3f(0.8f, -3.0f,  0.8f);
       glVertex3f(0.8f, -3.0f, -0.8f);
    } 
    glEnd();
    glPopMatrix();
  }


  for (t = tiroList->next; t != NULL; t = t->next) 
   { 
    glPushMatrix(); 
    glTranslatef(t->tiro->position->x, t->tiro->position->y, t->tiro->position->z); 
    glColor3f(0.0f, 0.0f, 0.0f); 
    glutSolidSphere(0.15, 60, 60);
    glPopMatrix();
   }

  glPushMatrix();
  glRotatef(user_angle, 0, 0, 1);
  drawShip();
  glPopMatrix();
  glPushMatrix();
  glTranslatef(ship->orientation->x, ship->orientation->y, 0.0);
  glColor3f(0.0, 1.0, 0.0);
  glBegin(GL_LINE_LOOP);
  glVertex3f(-0.5, 1.0, 0.0);
  glVertex3f(-0.5, 3.0, 0.0);
  glVertex3f(1.5, 3.0, 0.0);
  glVertex3f(1.5, 1.0, 0.0);
  glEnd();
  glBegin(GL_LINE_LOOP);
  glVertex3f(0.0, 1.3, 0.0);
  glVertex3f(0.0, 2.6, 0.0);
  glVertex3f(1.0, 2.6, 0.0);
  glVertex3f(1.0, 1.3, 0.0);
  glEnd();
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
  gameRunning = update();
  glutPostRedisplay();
}

void keyb(unsigned char k, int x, int y) {
  switch(k) {
    case 'w':
    case 'W':
      ship->position->y += 1.0;
      break;
    case 's':
    case 'S':
      ship->position->y -= 1.0;
      break;
    case 'a':
    case 'A':
      ship->position->x += 1.0;
      break;
    case 'd':
    case 'D':
      ship->position->x -= 1.0;
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

void skeyb(int k, int x, int y) {
   switch(k) {
      case GLUT_KEY_UP:
         ship->orientation->y += 1.0;
         break;
      case GLUT_KEY_DOWN:
         ship->orientation->y -= 1.0;
         break;
      case GLUT_KEY_LEFT:
         ship->orientation->x += 1.0;
         break;
      case GLUT_KEY_RIGHT:
         ship->orientation->x -= 1.0;
         break;
   }
}

