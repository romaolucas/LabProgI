/*general.h: algumas structs pra usarmos repetidas vezes*/
#ifndef H_GENERAL_DEFINED
#define H_GENERAL_DEFINED
#include <stdio.h>
#include <time.h>
#define EPSILON 0.042
#define DZ 0.2
#define MAX_X 10
#define MAX_Y 20
#define Z_ORIGIN -35.0

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
