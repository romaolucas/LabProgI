/*Tiro.c
Descrição: aqui é tiro, porrada e bomba*/

#include <stdlib.h>
#include "general.h"
#include "Tiro.h"
#define DEFAULT_DAMAGE 2

Tiro *initTiro(Point *position, Point *orientation, int velocity, int shotPower, TIRO_TIPO tipo)
{
  Tiro *t;
  t = mallocSafe(sizeof(Tiro));
  t->position = initPoint(position->x, position->y, position->z);
  t->orientation = initPoint(orientation->x, orientation->y, orientation->z);
  t->velocity = velocity;
  t->shotPower = shotPower;
  return t;  
}

void freeTiro(Tiro *t)
{
  if (t != null)
  {
    free(t->position);
    free(t->orientation);
    free(t);
  }
}
