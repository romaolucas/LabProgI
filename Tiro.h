#ifndef H_TIRO_DEFINED
#define H_TIRO_DEFINED
#include "general.h" /*Pegar struct point*/
#include "Defesa.h" /*Pegar TIRO_TIPO*/

typedef struct
{
  Point *position;
  Point *orientation;
  int velocity;
  int shotPower;
  TIRO_TIPO tipo;
  
} Tiro;

Tiro *initTiro(int px, int py, int pz, int ox, int oy, int oz, int velocity, TIRO_TIPO tipo);

void freeTiro(Tiro *t);

#endif
