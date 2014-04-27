#include <stdlib.h>
#include "Nave.h"
#include "Tiro.h"
#include "Cenario.h"
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
    ship->orientation = initPoint(0, 0, 0);/*direcao do come�o*/
    ship->attackType = NORMAL;
}

int isShipDestroyed()
{
   return ship->hp <= 0;
}

void naveShoot()
{  
   Point *position = initPoint(1,1,1);/* valor tem que ser mudado para a posicao onde o tiro vai nascer */
   Point *orientation = initPoint(ship->orientation->x, ship->orientation->y, ship->orientation->z);
   Tiro *tiro = initTiro(position, orientation, INITIAL_SPEED, DEFAULT_DMG);
   includeTiro(tiro);
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
