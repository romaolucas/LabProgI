#include <stdio.h>
#include "general.h"
#include "Nave.h"
#include "Defesa.h"
#include "Tiro.h"
#include "Cenario.h"

int main() {
   int i, k = 1;
   Point *p, *q, *r;
   Defense *d;
   Tiro *t;
   initShip();
   initCenario();
   for (i = 0; i < 10; i++, k *= 7) {
      p = initPoint(k*1.0, k*1.0, k*1.0);
      r = initPoint(k*1.0, k*1.0, k*1.0);
      q = initPoint(k*2.0, k*2.0, k*2.0);
      d = initDefense(p, 0, NORMAL);
      t = initTiro(q, r, NORMAL);
      includeDefense(d);
      includeTiro(t);
   }
   imprimeCenario();
   freeShip();
   freeCenario();
   printf("Testaremos tudo aqui!\n");
   return 0;
}
