#include "Defesa.h"
#include "general.h"
#include "Cenario.h"
#include "Nave.h"
#include <stdlib.h>
#include <math.h>

Defense *initDefense(Point *p, int hp, TIRO_TIPO shotType) {
   Defense *d;
   d = mallocSafe(sizeof(Defense));
   d->position = p;
   d->created = clock();
   if (hp == 0) d->hp = DEFAULT_HP;
   if (shotType == NORMAL) {
     d->accuracy = DEFAULT_ACCURACY;
     d->shotPower = DEFAULT_POWER;
     d->shotFrequency = DEFAULT_FREQUENCY;
   }
   return d;
}

int isDefenseDestroyed(Defense *d) {
   return d->hp <= 0;
}

void defenseGotHit(Defense *d, int shotPower) {
   d->hp -= shotPower;
}

void alterAttackPattern(Defense *d) {
   if (d->distance <= CRITICAL_DISTANCE) d->shotFrequency += 2;
}

void collisionsDefense(Defense *d)
{
   nodeTiro *t;
   t = tiroList->next;
   while (t != NULL) {
         if (collision(d->position, t->tiro->position)) {
            defenseGotHit(d, t->tiro->shotPower);
            nodeTiro *aux = t;
            t = t->next;
            freeTiro(aux->tiro);
            free(aux);
         }
         else t = t->next;
      }
   
}

boolean updateDefense(Defense *d)
{ 
   int elapsed;
   clock_t instant;
   collisionsDefense(d);
   d->position->z -= (double) DZ;
   if (d->position->z < 0) return TRUE;
   instant = clock();
   elapsed = (instant - d->created)/CLOCKS_PER_SEC *1000;
   if (elapsed % d->shotFrequency == 0) {
      Point *p = initPoint(d->position->x, d->position->y, d->position->z - 2*EPSILON); 
      Point *q = initPoint(ship->position->x - d->position->x, ship->position->y - d->position->y,
            ship->position->z - d->position->z);
      includeTiro(initTiro(p, q, NORMAL));
   }
   return FALSE;
}

/*Não basta dar free em d, precisa librera a struct position também*/
void freeDefense(Defense *d)
{
  if(d != NULL)
  {
    free(d->position);
    free(d);
  }
}
