/*Tiro.c
Descrição: aqui é tiro, porrada e bomba*/

#include <stdlib.h>
#include <math.h>
#include "general.h"
#include "Tiro.h"

Tiro *initTiro(Point *position, Point *orientation, TIRO_TIPO shotType, SRC origem)
{
  Tiro *t;
  t = mallocSafe(sizeof(Tiro));
  t->position = position;
  t->source = origem;
  t->orientation = orientation;
  if (shotType == NORMAL){
     t->velocity = DEFAULT_VELO;
     t->shotPower = DEFAULT_DMG;
   } /*soh um tipo de tiro por enquanto*/
  return t;  
  
}

boolean updateTiro(Tiro *t)
{
   double alpha = 0.04;
   t->position->x += t->orientation->x*alpha;
   t->position->y += t->orientation->y*alpha;
   t->position->z += (double) t->velocity * DZ * t->orientation->z > 0 ? 1 : -1;
   /*Nota: fabs == módulo da biblioteca math.h*/
   return (fabs(t->position->x) > MAX_X || fabs(t->position->y) > MAX_Y || t->position->z < Z_ORIGIN || t->position->z > MAX_Z);
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
