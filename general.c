/*Aqui para algumas structs e funções que podem ser usadas varias vezes*/
#include "general.h"
#include <math.h>
#include <stdlib.h>

double calcDistance(Point *a, Point *b)
{
  return sqrt(pow(a->x - b->x, 2) + pow(a->y - b->y, 2) + pow(a->z - b->z, 2));
}

Point *initPoint(int x, int y, int z)
{
  Point *ponto = malloc(sizeof(Point));
  ponto->x = x;
  ponto->y = y;
  ponto->z = z;
  return ponto;  
}
