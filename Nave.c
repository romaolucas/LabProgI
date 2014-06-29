#include <stdlib.h>
#include <math.h>
#include "Nave.h"
#include "Tiro.h"
#include "Cenario.h"
#include "general.h"

Ship *ship;

void initShip()
{
    ship = mallocSafe(sizeof(Ship));
    ship->hp = INITIAL_HP;
    ship->vidas = 3;
    ship->speed = INITIAL_SPEED;
    ship->position = initPoint(INITIAL_HPOS, INITIAL_HEIGHT, INITIAL_SPOS);
    ship->orientation = initPoint(0.0, 0.0, 20.0);/*direcao do comeco*/
    ship->attackType = NORMAL;
}

int isShipDestroyed()
{
   return ship->hp <= 0;
}

void shipShoot()
{  
   Point *position = initPoint(ship->position->x, ship->position->y, ship->position->z + 2*EPSILON);
   Point *orientation = initPoint(ship->orientation->x, ship->orientation->y, ship->orientation->z);
   includeTiro(initTiro(position, orientation, NORMAL, NAVE));
}

void shipGotHit(int dmg)
{
  ship->hp -= dmg;
}

void reviveShip()
{
    ship->hp = INITIAL_HP;
    ship->vidas -= 1;
    ship->speed = INITIAL_SPEED;
    ship->position = initPoint(INITIAL_HPOS, INITIAL_HEIGHT, INITIAL_SPOS);
    ship->orientation = initPoint(0.0, 0.0,20.0);/*direcao do comeco*/
    ship->attackType = NORMAL;
}

void collisionsShip(){
   nodeTiro *at = tiroList;
   nodeTiro *t = at->next;
   while (t != NULL) {
      /*criar um campo position para a nave*/
      if (t->tiro->source == DEFESA && collision(t->tiro->position, 0.15, ship->position, 3.5)) {
         printf("colisao\n");
         shipGotHit(t->tiro->shotPower);
         at->next = t->next; 
         freeTiro(t->tiro);
         free(t);
         t = at->next;
         at = t;
         if (t != NULL) t = t->next;
      }
      else { 
         at = t;
         if (t != NULL) t = t->next;
      }

      if (isShipDestroyed()) reviveShip();

   }
}

int updateShip()
{ 
   Point *p, *q;
   collisionsShip();/*Checa colisão nave<=>tiro*/

   return TRUE;
}

void freeShip()
{
   free(ship->orientation);
   free(ship->position);
   free(ship);
}
