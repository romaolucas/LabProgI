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
    ship->orientation = initPoint(0.0, 0.0, 1.0);/*direcao do comeco*/
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
   includeTiro(initTiro(position, orientation, NORMAL));
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
    ship->orientation = initPoint(0.0, 0.0,1.0);/*direcao do comeco*/
    ship->attackType = NORMAL;
}

void collisionsShip(){

   nodeTiro *t = tiroList->next;
   t = tiroList->next;
   while (t != NULL) {
      /*criar um campo position para a nave*/
      if (collision(ship->position, t->tiro->position)) {
         shipGotHit(t->tiro->shotPower);
         nodeTiro *aux = t;
         t = t->next;
         freeTiro(aux->tiro);
         free(aux);
      }
      else t = t->next;
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
