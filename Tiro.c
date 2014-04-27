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

void freeTiro(Tiro *t)
{
  if (t != NULL)
  {
    free(t->position);
    free(t->orientation);
    free(t);
  }
}
