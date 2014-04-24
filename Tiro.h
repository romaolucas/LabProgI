#ifndef H_TIRO_DEFINED
#define H_TIRO_DEFINED
#include "general.h" /*Pegar struct point*/

/*Outros tipos de tiro podem ser adicionados mais tarde*/
typedef enum {NORMAL} TIRO_TIPO;

typedef struct
{
  Point *position;
  Point *orientation;
  int velocity;
  int shotPower;
  TIRO_TIPO tipo;
  
} Tiro;

Tiro *initTiro(Point *position, Point *orientation, int velocity, int shotPower, TIRO_TIPO tipo);

void freeTiro(Tiro *t);

#endif
