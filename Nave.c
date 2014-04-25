#include <stdlib.h>
#include "Nave.h"
#include "Tiro.h"
#include "general.h"

Ship *ship;

void initShip()
{
    ship = mallocSafe(sizeof(Ship));
    ship->hp = INITIAL_HP;
    ship->speed = INITIAL_SPEED;
    ship->height = INITIAL_HEIGHT;
    ship->scenarioPos = INITIAL_SPOS;
    ship->horizontalPos = INITIAL_HPOS;
    ship->orientation = initPoint(0, 0, 0);/*direcao do começo*/
    ship->attackType = NORMAL;
}

int isShipDestroyed()
{
   return ship->hp <= 0;
}

void shipGotHit(int dmg)
{
  ship->hp -= dmg;
}

void freeShip()
{
   free(ship->orientation);
   free(ship);
}
