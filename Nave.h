#ifndef NAVE_H_INCLUDED
#define NAVE_H_INCLUDED

#define INITIAL_HP 100
#define INITIAL_SPEED 1.0
#define INITIAL_HEIGHT 0.0
#define INITIAL_SPOS -20.0
#define INITIAL_HPOS 0.0

#include "general.h"
#include "Tiro.h"

typedef struct
{
  int hp;
  int vidas;
  int speed;
  Point *position;
  Point *orientation;
  TIRO_TIPO attackType;
} Ship;

void initShip();

void shipShoot();

int isShipDestroyed();

void shipGotHit(int shotPower);

void freeShip();

int updateShip();

extern Ship *ship;



#endif
