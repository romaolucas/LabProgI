#ifndef NAVE_H_INCLUDED
#define NAVE_H_INCLUDED

#define INITIAL_HP 100
#define INITIAL_SPEED 10
#define INITIAL_HEIGHT 50
#define INITIAL_SPOS 300
#define INITIAL_HPOS 0


typedef struct
{
  int hp;
  int speed;
  int height;
  int scenarioPos;
  int horizontalPos;
  Point *orientation;
  TIRO_TIPO attackType;
} Ship;

void initShip();

int isShipDestroyed();

void shipGotHit(int dmg);

extern Ship *ship;



#endif
