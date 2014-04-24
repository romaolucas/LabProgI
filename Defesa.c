#include "Defesa.h"
#include <math.h>

Defense initDefense(int x, int y, int z, int hp, int shotType) {
   Defense d;
   d.x = x;
   d.y = y;
   d.z = z;
   d.damage = 0;
   if (hp == 0) d.hp = DEFAULT_HP;
   if (shotType) {
     d.accuracy = DEFAULT_ACCURACY;
     d.shotPower = DEFAULT_POWER;
     d.shotFrequency = DEFAULT_FREQUENCY;
   }
   return d;
}

int isDestroyed(Defense d) {
   return d.hp == d.damage;
}

void calcDistance(Defense d, int xn, int yn, int zn) {
   d.distance = sqrt((d.x - xn)*(d.x - xn) + (d.y - yn)*(d.y - yn) + (d.z - zn)*(d.z - zn));
}

void hit(Defense d, int shotPower) {
   d.damage += shotPower;
}

void alterAttackPattern(Defense d) {
   if (d.distance <= CRITICAL_DISTANCE) d.shotFrequency += 2;
}
