#ifndef H_TIRO_DEFINED
#define H_TIRO_DEFINED
#include "general.h" /*Pegar struct point*/

#define DEFAULT_DMG 20
#define DEFAULT_VELO 2
/*Outros tipos de tiro podem ser adicionados mais tarde*/
typedef enum {NORMAL} TIRO_TIPO;

typedef enum {NAVE, DEFESA} SRC;

typedef struct
{
  Point *position;
  Point *orientation;
  int velocity;
  int shotPower;
  SRC source;
} Tiro;

Tiro *initTiro(Point *position, Point *orientation, TIRO_TIPO shotType, SRC origem);

void freeTiro(Tiro *t);

boolean updateTiro(Tiro *t);

#endif
