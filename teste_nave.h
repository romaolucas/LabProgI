#ifndef H_TESTE_NAVE_DEFINED
#define H_TESTE_NAVE_DEFINED

#include <GL/glut.h>
#include<math.h>
#include<stdio.h>
#include "Cenario.h"
#include "general.h"
#include "Nave.h"
#include "Defesa.h"
#include "Tiro.h"
#define PI 3.1415

extern int forceField;

/*Parte original minha: desenhar a nave*/
void drawShip();

/*Inicializar e/ou configurar openGL*/
void init();

void draw();

void computeLocation();

void timeStep(int n);

/*Funções de teclado*/

void keydown(unsigned char k, int x, int y);

void keyup(unsigned char k, int x, int y);

void skeyb(int k, int x, int y);

/*Recebe informação da tabela de keys*/
void updateKeyboard();

/*funções auxiliares/matemáticas*/
double fmin(double one, double two);

double fmax(double one, double two);

double closeToZero(double now, double rate);

#endif
