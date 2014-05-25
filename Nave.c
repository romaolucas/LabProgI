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

void naveShoot()
{  
   Point *position = initPoint(1.0,1.0,1.0);/* valor tem que ser mudado para a posicao onde o tiro vai nascer */
   Point *orientation = initPoint(ship->orientation->x, ship->orientation->y, ship->orientation->z);
   Tiro *tiro = initTiro(position, orientation, NORMAL);
   includeTiro(tiro);
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
    ship->orientation = initPoint(0.0, 0.0, 20.0);/*direcao do comeco*/
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
   int c;
   Point *p, *q;
   collisionsShip();/*Checa colisão nave<=>tiro*/

  /*movimenta nave de acordo com o que o usuario digitar
    * W, A, S, D controlam a direcao
    * U atirar
    * comandos para mudar a orientacao, talvez? por hora,
    * */
   c = getchar();
   switch (c) {
      case 'w': case 'W':
         ship->position->y += sqrt(3)*ship->speed;
         ship->orientation->y = ship->position->y;
         break;
      case 's': case 'S':
         ship->position->y -= sqrt(3)*ship->speed;
         ship->orientation->y = ship->position->y;
         break;
      case 'a': case 'A':
         ship->position->x -= sqrt(3)*ship->speed;
         ship->orientation->x = ship->position->x;
         break;
      case 'd': case 'D':
         ship->position->x += sqrt(3)*ship->speed;
         ship->orientation->x = ship->position->x;
         break;
      case 'u': case 'U':
         p = initPoint(ship->position->x, ship->position->y, ship->position->z + 2*EPSILON);
         q = initPoint(ship->orientation->x, ship->orientation->y, ship->orientation->z);
         includeTiro(initTiro(p, q, NORMAL));
         break;
       case 'q': case 'Q': case EOF:
         return FALSE;         
   }
   return TRUE;
}

void freeShip()
{
   free(ship->orientation);
   free(ship->position);
   free(ship);
}
