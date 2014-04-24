#ifndef H_DEFESA_DEFINED
#define H_DEFESA_DEFINED

#define DEFAULT_ACCURACY 3.14
#define DEFAULT_HP 20
#define DEFAULT_POWER 2
#define DEFAULT_FREQUENCY 7
#define CRITICAL_DISTANCE 7.77
#include "general.h"

/*Outros tipos de tiro podem ser adicionados mais tarde*/
typedef enum {NORMAL} TIRO_TIPO;

typedef struct {
   Point *position;
   double accuracy;
   int hp;
   int damage;
   int shotPower;
   int shotFrequency;
   int shotType;
   double distance;
} Defense;

Defense *initDefense(Point *p, int hp, TIRO_TIPO  shotType);

int isDestroyed(Defense *d);

void hit(Defense *d, int shotPower);

void alterAtkPattern(Defense *d);

#endif
