#include "teste_nave.h"

/*inclinação da nave*/
double z_angle = 0;
double x_angle = 0;

/*variaveis de controle do campo de forca*/

int forceField;
int beginFF;

/*variaveis para indicar o status do jogo*/
char jogador[200];


/*array de keyboard*/
int keyboard[256];
/*coordenadas da nave - desativado*/
double px = 0;
double py = 0;
double pz = 0;
/*constantes aleatórias para desenho*/
double cst_x = 1;
double cst_L = 3;
double cst_l = 1.5;
/*acc pro tiro*/
double shootAcc = 0.0;
/*controla o fim do jogo*/
int gameRunning = TRUE;



int main(int argc, char **argv){
  forceField = FALSE;
  initShip();
  initCenario();
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(900, 900); 
  glutCreateWindow("Nave");
  init();
  
  glutDisplayFunc(draw);
  glutTimerFunc(100, timeStep, 1);
  glutIgnoreKeyRepeat(TRUE);
  glutKeyboardFunc(keydown);
  glutKeyboardUpFunc(keyup);
  glutMainLoop();
  return 0;   
}

void drawShip()
{
  glPushMatrix();
  glTranslatef(ship->position->x, ship->position->y, ship->position->z); 
  glRotatef(z_angle, 0, 0, 1);
  glRotatef(x_angle, 1, 0, 0);
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
  if (forceField) {
   glPushMatrix();
   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
   glEnable( GL_BLEND );
   glColor4f(0, 0, 1.0, 0.1);
   glTranslatef(ship->position->x, ship->position->y, ship->position->z);
   glutSolidSphere(3.5, 100, 100); 
   glPopMatrix();
   glDisable(GL_BLEND);
  }
}

void init() {
  GLfloat sun_direction[] = { 0.0, 0.0, 0.0, 0.0 };
  GLfloat sun_intensity[] = { 1.0, 1.0, 1.0, 1.0 };
  GLfloat ambient_intensity[] = { 0.5, 0.5, 0.5, 1.0 };

  glClearColor(1.0, 1.0, 1.0, 0.0);   
  computeLocation();

  glEnable(GL_DEPTH_TEST);            

  glEnable(GL_LIGHTING);             
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient_intensity);

  glEnable(GL_LIGHT0);                
  glLightfv(GL_LIGHT0, GL_POSITION, sun_direction);
  glLightfv(GL_LIGHT0, GL_AMBIENT, sun_intensity);

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
  glColor4f(1.0, .85, 0.0,1.0);
  glDisable(GL_LIGHTING);
  glDisable(GL_LIGHT0);
  glPushMatrix();
  glTranslatef(0., -10., -30.);
  /*~Rio~*/
  glColor4f(0.0, 0.0, 0.5, 1.0);
  glBegin(GL_TRIANGLES);
  {
    glVertex3f(-60., 0., 0.);
    glVertex3f(-60., 0., 500.);
    glVertex3f(60., 0., 0.);
    glVertex3f(60., 0., 0.);
    glVertex3f(-60., 0., 500.);
    glVertex3f(60., 0., 500.);
  }
  glEnd();
  /*Terra*/
  glColor4f(0.48, 0.25, 0.01, 1.0);
  glBegin(GL_TRIANGLES);
  {
    glVertex3f(60., 0., 0.);
    glVertex3f(60., 0., 500.);
    glVertex3f(220., 0., 0.);
    glVertex3f(220., 0., 0.);
    glVertex3f(60., 0., 500.);
    glVertex3f(220., 0., 500.);
  }
  glEnd();
  glBegin(GL_TRIANGLES);
  {
    glVertex3f(-60., 0., 0.);
    glVertex3f(-60., 0., 500.);
    glVertex3f(-220., 0., 0.);
    glVertex3f(-220., 0., 0.);
    glVertex3f(-60., 0., 500.);
    glVertex3f(-220., 0., 500.);
  }
  glEnd();
  /*Céu*/
  glColor4f(0.6,0.75, 1. ,1.);
  glBegin(GL_TRIANGLES);
  {
    glVertex3f(-220., 0., 500.);
    glVertex3f(220., 0., 500.);
    glVertex3f(-220., 200., 500.);
    glVertex3f(220., 200., 500.);
    glVertex3f(220., 0., 500.);
    glVertex3f(-220., 200., 500.);
  }
  glEnd();
  glPopMatrix();
  glBegin(GL_QUADS);
  {
    glVertex3f( 21., 26.,  -19);
    glVertex3f( 5.5, 26.,  -19);
    glVertex3f( 5.5, 23.,  -19);
    glVertex3f( 21., 23.,  -19);
  }
  glEnd();
  glColor3f(0.0, 0.0, 0.0);
  sprintf(jogador, "HP: %d    Vidas: %d Pontos: %d", ship->hp, ship->vidas, ship->score);
  glRasterPos3f(16., 23.,-20);
  glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, jogador);
 
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  for (d = defenseList->next; d != NULL; d = d->next)
  { 
    glPushMatrix();
    glTranslatef(d->defense->position->x, d->defense->position->y, d->defense->position->z); 
    glBegin(GL_QUADS);              
    {  
       glColor3f(0.5f, 0.5f, 0.5f);         
       glVertex3f( 0.8f, 0.8f, -0.8f);
       glVertex3f(-0.8f, 0.8f, -0.8f);
       glColor3f(0.3f, 0.3f, 0.3f);
       glVertex3f(-0.8f, 0.8f,  0.8f);
       glVertex3f( 0.8f, 0.8f,  0.8f);
 
       /*Bottom face (y = -0.8f)*/
       glColor3f(0.5f, 0.5f, 0.5f);       
       glVertex3f( 0.8f, -3.0f,  0.8f);
       glVertex3f(-0.8f, -3.0f,  0.8f);
       glColor3f(0.3f, 0.3f, 0.3f);
       glVertex3f(-0.8f, -3.0f, -0.8f);
       glVertex3f( 0.8f, -3.0f, -0.8f);
 
       /* Front face  (z = 0.8f)*/
       glColor3f(0.5f, 0.5f, 0.5f);      
       glVertex3f( 0.8f,  0.8f, 0.8f);
       glVertex3f(-0.8f,  0.8f, 0.8f);
       glColor3f(0.3f, 0.3f, 0.3f);
       glVertex3f(-0.8f, -3.0f, 0.8f);
       glVertex3f( 0.8f, -3.0f, 0.8f);
 
       /* Back face (z = -0.8f)*/
       glColor3f(0.5f, 0.5f, 0.5f);      
       glVertex3f( 0.8f, -3.0f, -0.8f);
       glVertex3f(-0.8f, -3.0f, -0.8f);
       glColor3f(0.3f, 0.3f, 0.3f);
       glVertex3f(-0.8f,  0.8f, -0.8f);
       glVertex3f( 0.8f,  0.8f, -0.8f);
 
       /* Left face (x = -0.8f)*/
       glColor3f(0.5f, 0.5f, 0.5f);           
       glVertex3f(-0.8f,  0.8f,  0.8f);
       glVertex3f(-0.8f,  0.8f, -0.8f);
       glColor3f(0.3f, 0.3f, 0.3f);
       glVertex3f(-0.8f, -3.0f, -0.8f);
       glVertex3f(-0.8f, -3.0f,  0.8f);
  
       /* Right face (x = 0.8f)*/
       glColor3f(0.5f, 0.5f, 0.5f);      
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
    if (t->tiro->source == NAVE)
    glColor3f(0.0f, 0.0f, 0.0f); 
    else glColor3f(0.5f, 0.27f, 0.0f);
    glutSolidSphere(0.15, 60, 60);
    glPopMatrix();
   }
  drawShip();
  glPushMatrix();
  glTranslatef(ship->orientation->x, ship->orientation->y, -.5);
  glColor3f(0.0, 1.0, 0.0);
  glBegin(GL_LINE_LOOP);
  glVertex3f(-0.5, 1.0, 0.0);
  glVertex3f(-0.5, 3.0, 0.0);
  glVertex3f(1.5, 3.0, 0.0);
  glVertex3f(1.5, 1.0, 0.0);
  glEnd();
  glPopMatrix();
  glPushMatrix();
  glTranslatef(ship->orientation->x, ship->orientation->y, 0.0);
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
  if (ship->vidas < 0) 
  { 
    printf("GAME OVER - Score: %d\n", ship->score);
    freeShip();
    freeCenario();
    exit(EXIT_SUCCESS);
  }
  gameRunning = update();
  updateKeyboard();
  if ((glutGet(GLUT_ELAPSED_TIME) - beginFF) >= 1000)
     forceField = FALSE;
  glutPostRedisplay();
}

void keydown(unsigned char k, int x, int y) {
  keyboard[k] = TRUE;
}

void keyup(unsigned char k, int x, int y)
{
  keyboard[k] = FALSE;
}

void updateKeyboard()
{
  if (keyboard['w'] || keyboard['W'])
  { 
    if (ship->position->y < 20)
    {
     ship->position->y += 1;
     x_angle = fmax(-24, x_angle - 4);
    }   
  }
  if (keyboard['s'] || keyboard['S'])
  { 
    if (ship->position->y > -5)
    {
     ship->position->y -= 1;
     x_angle = fmin(24, x_angle + 4);
    }
  }
  if (keyboard['a'] || keyboard['A'])
  { 
    if (ship->position->x < 12)
    {
     ship->position->x +=1;
     z_angle = fmax(-35, z_angle - 5);
    }
  }
  if (keyboard['d'] || keyboard['D'])
  {
    if (ship->position->x > -12)
    {
     ship->position->x -= 1;
     z_angle = fmin(35, z_angle + 5);
    }
  }
  if (keyboard['e'] || keyboard['E']) {
     forceField = TRUE;
     beginFF = glutGet(GLUT_ELAPSED_TIME);
  }
  if (keyboard['u'] || keyboard['U'])
  {   if (shootAcc > 20)
      {
       shipShoot();
       shootAcc = 0.0;
      } else shootAcc += 10;
  }
  if (keyboard['q'] || keyboard['Q']) {
     freeCenario();
     exit(EXIT_SUCCESS);
  }
  if (!keyboard['w'] && !keyboard['W'] && !keyboard['s'] && !keyboard['S'])
    x_angle = closeToZero(x_angle, 4);
  if (!keyboard['a'] && !keyboard['A'] && !keyboard['d'] && !keyboard['D'])
    z_angle = closeToZero(z_angle, 5);

  ship->orientation->y = ship->position->y - tan(x_angle * PI/180) * 15;
  ship->orientation->x = ship->position->x;
}

double fmin(double one, double two){
  return one > two ? two : one;
}

double fmax(double one, double two){
  return one > two ? one : two;
}

double closeToZero(double now, double rate)
{
  if (now > 0)
    return now - rate;
  if (now < 0)
    return now + rate;
  return 0;
}
