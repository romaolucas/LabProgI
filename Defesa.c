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
   d->hp = DEFAULT_HP;
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
   nodeTiro *at;
   at = tiroList;
   t = at->next;
   while (t != NULL) {
      if (collision(d->position, t->tiro->position)) {
            defenseGotHit(d, t->tiro->shotPower);
            at->next = t->next;
            freeTiro(t->tiro);
            free(t);
            t = at->next;
         }
         at = t;
         if (t != NULL)
            t = t->next;
      }
   
}

boolean updateDefense(Defense *d)
{ 
   collisionsDefense(d);
   d->position->z -= (double) DZ; 
   if (d->position->z < Z_ORIGIN) return TRUE;
   double shootChance = RandomNumber(0.0, 100.0);
   if (shootChance > 97.0) {
      Point *p = initPoint(d->position->x, d->position->y - 1.1f, d->position->z - 1.0); 
      Point *q = initPoint(ship->position->x - d->position->x , ship->position->y - d->position->y,
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
