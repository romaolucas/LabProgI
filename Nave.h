#ifndef NAVE_H_INCLUDED
#define NAVE_H_INCLUDED

#define INITIAL_HP 100
#define INITIAL_SPEED 10
#define INITIAL_HEIGHT 50
#define INITIAL_SPOS 300
#define INITIAL_HPOS 0

#include "general.h"
#include "Tiro.h"

typedef struct
{
  int hp;
  int speed;
  double height;
  double scenarioPos;
  double horizontalPos;
  Point *orientation;
  TIRO_TIPO attackType;
} Ship;

void initShip();

void shipShoot();

int isShipDestroyed();

void shipGotHit(int shotPower);

void freeShip();

extern Ship *ship;



#endif
