/*Tiro.c
Descrição: aqui é tiro, porrada e bomba*/

#include <stdlib.h>
#include "general.h"
#define DEFAULT_DAMAGE 2

Tiro *initTiro(int px, int py, int pz, int ox, int oy, int oz, int velocity, int shotPower TIRO_TIPO tipo)
{
  Tiro *t;
  t = mallocSafe(sizeof(Tiro));
  t->position = initPoint(px, py, pz);
  t->orientation = initPoint(ox, oy, oz);
  t->velocity = velocity;
  t->shotPower = shotPower;
  return t;  
}

void freeTiro(Tiro *t)
{
  free(t->position);
  free(t->orientation);
  free(t);
}
