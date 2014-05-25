/*general.h: algumas structs pra usarmos repetidas vezes*/
#ifndef H_GENERAL_DEFINED
#define H_GENERAL_DEFINED
#include <stdio.h>
#include <time.h>
#define EPSILON 0.042
#define DZ 5
#define MAX_X 600
#define MAX_Y 500

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

int collision(Point *a, Point *b);

void *mallocSafe (size_t nbytes);

double RandomNumber(double low, double high);
#endif
