#include "Defesa.h"
#include <stdlib.h>
#include <math.h>

Defense *initDefense(int x, int y, int z, int hp, TIRO_TIPO shotType) {
   Defense *d;
   d = malloc(sizeof(Defense));
   d->position = initPoint(x, y, z);
   d->damage = 0;
   if (hp == 0) d->hp = DEFAULT_HP;
   if (shotType == NORMAL) {
     d->accuracy = DEFAULT_ACCURACY;
     d->shotPower = DEFAULT_POWER;
     d->shotFrequency = DEFAULT_FREQUENCY;
   }
   return d;
}

int isDestroyed(Defense *d) {
   return d->hp == d->damage;
}

void calcDistance(Defense *d, Point *p) {
  d->distance = calcDistance(d->position, p);
}

void hit(Defense *d, int shotPower) {
   d->damage += shotPower;
}

void alterAttackPattern(Defense *d) {
   if (d->distance <= CRITICAL_DISTANCE) d.shotFrequency += 2;
}

/*Não basta dar free em d, precisa librera a struct position também*/
void freeDefense(Defense *d)
{
  free(d->position);
  free(d);
}
