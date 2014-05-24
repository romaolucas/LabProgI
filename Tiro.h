#ifndef H_TIRO_DEFINED
#define H_TIRO_DEFINED
#include "general.h" /*Pegar struct point*/

#define DEFAULT_DMG 2
#define DEFAULT_VELO 5
/*Outros tipos de tiro podem ser adicionados mais tarde*/
typedef enum {NORMAL} TIRO_TIPO;


typedef struct
{
  Point *position;
  Point *orientation;
  int velocity;
  int shotPower;
  
} Tiro;

Tiro *initTiro(Point *position, Point *orientation, TIRO_TIPO shotType);

void freeTiro(Tiro *t);

void updateTiro(Tiro *t);

#endif
