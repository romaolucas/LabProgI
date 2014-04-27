#ifndef H_TIRO_DEFINED
#define H_TIRO_DEFINED
#include "general.h" /*Pegar struct point*/

#define DEFAULT_DAMAGE 2
/*Outros tipos de tiro podem ser adicionados mais tarde*/
typedef enum {NORMAL} TIRO_TIPO;


typedef struct
{
  Point *position;
  Point *orientation;
  int velocity;
  int shotPower;
  
} Tiro;

Tiro *initTiro(Point *position, Point *orientation, int velocity, int shotPower);

void freeTiro(Tiro *t);

#endif
