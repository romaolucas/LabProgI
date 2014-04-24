/*general.h: algumas structs pra usarmos repetidas vezes*/
#ifndef H_GENERAL_DEFINED
#define H_GENERAL_DEFINED

typedef struct
{
  int x, y, z;
} Point;

/*Distância básica entre dois pontos*/
double calcDistance(Point *a, Point *b);

/*Inicializador de pontos*/
Point *initPoint(int x, int y, int z);

#endif
