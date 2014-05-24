/*Tiro.c
Descrição: aqui é tiro, porrada e bomba*/

#include <stdlib.h>
#include "general.h"
#include "Tiro.h"

Tiro *initTiro(Point *position, Point *orientation, TIRO_TIPO shotType)
{
  Tiro *t;
  t = mallocSafe(sizeof(Tiro));
  t->position = position;
  t->orientation = orientation;
  if (shotType == NORMAL){
     t->velocity = DEFAULT_VELO;
     t->shotPower = DEFAULT_DMG;
   } /*soh um tipo de tiro por enquanto*/
  return t;  
  
}

void updateTiro(Tiro *t)
{
  /*Tem que ter cuidado quando for definir t->orientation.
  Ele tem que ter norma 1*/
  t->position->x = t->orientation->x * t->velocity;
  t->position->y = t->orientation->y * t->velocity;
  t->position->z = (t->orientation->z * t->velocity) + (double) DZ;
}


void freeTiro(Tiro *t)
{
  if (t != NULL)
  {
    free(t->position);
    free(t->orientation);
    free(t);
  }
}
