#ifndef H_DEFESA_DEFINED
#define H_DEFESA_DEFINED

#define DEFAULT_ACCURACY 3.14
#define DEFAULT_HP 20
#define DEFAULT_POWER 2
#define DEFAULT_FREQUENCY 7
#define CRITICAL_DISTANCE 7.77
#include "general.h"
#include "Tiro.h"

typedef struct {
   Point *position;
   double accuracy;
   int hp;
   int shotPower;
   int shotFrequency;
   int shotType;
   double distance;
   clock_t created;
} Defense;

Defense *initDefense(Point *p, int hp, TIRO_TIPO  shotType);

int isDefenseDestroyed(Defense *d);

boolean updateDefense(Defense *d);

void defenseGotHit(Defense *d, int shotPower);

void alterAtkPattern(Defense *d);

void freeDefense(Defense *d);

#endif
