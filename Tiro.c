/*Tiro.c
Descrição: aqui é tiro, porrada e bomba*/

#include <stdlib.h>
#include <math.h>
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

boolean updateTiro(Tiro *t)
{
  /*Tem que ter cuidado quando for definir t->orientation.
  Ele tem que ter norma 1*/
   double norm = sqrt(t->orientation->x*t->orientation->x + t->orientation->y*t->orientation->y + t->orientation->z
         *t->orientation->z);
   t->position->x = t->orientation->x * t->velocity/norm;
   t->position->y = t->orientation->y * t->velocity/norm;
   t->position->z = ((t->orientation->z * t->velocity) - (double) DZ)/norm;
   printf("P(%4.2f, %4.2f, %4.2f)\n", t->position->x, t->position->y, t->position->z);
   /*Nota: fabs == módulo da biblioteca math.h*/
   return (fabs(t->position->x) > MAX_X || fabs(t->position->y) > MAX_Y || t->position->z < 0);
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
