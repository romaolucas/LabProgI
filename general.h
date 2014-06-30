/*general.h: algumas structs pra usarmos repetidas vezes*/
#ifndef H_GENERAL_DEFINED
#define H_GENERAL_DEFINED
#include <stdio.h>
#include <time.h>
#define EPSILON 0.042
#define DZ 0.2
#define MAX_X 6
#define MAX_Y 15
#define MAX_Z 25
#define Z_ORIGIN -25.0

typedef struct
{
  double x, y, z;
} Point;
typedef enum{
   FALSE,
   TRUE
} boolean;

/*Distância básica entre dois pontos*/
double calcDistance(Point *a, Point *b);

/*Inicializador de pontos*/
Point *initPoint(double x, double y, double z);

int collision(Point *a, float radA, Point *b, float radB);

void *mallocSafe (size_t nbytes);

double RandomNumber(double low, double high);
#endif
